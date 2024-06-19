/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mLFilterFcParam = new juce::AudioParameterFloat("Low Shelf fc", // parameterID,
        "LFiltFc", // parameterName,
        20.0f, // minValue,
        500.0f, // maxValue,
        75.0f)); // defaultValue
    addParameter(mLFilterGainParam = new juce::AudioParameterFloat("Low Shelf Gain", // parameterID,
        "LFiltGain", // parameterName,
        -10.0f, // minValue,
        7.0f, // maxValue,
        0.0f)); // defaultValue
    addParameter(mMFilterFcParam = new juce::AudioParameterFloat("Midband fc", // parameterID,
        "MFiltFc", // parameterName,
        200.0f, // minValue,
        4000.0f, // maxValue,
        1000.0f)); // defaultValue
    // Filter Q parameter
    addParameter(mMFilterQParam = new juce::AudioParameterFloat("Midband Q", // parameterID,
        "MFiltQ", // parameterName,
        0.2f, // minValue,
        10.0f, // maxValue,
        0.7f)); // defaultValue
    addParameter(mMFilterGainParam = new juce::AudioParameterFloat("Midband Gain", // parameterID,
        "MFiltGain", // parameterName,
        -10.0f, // minValue,
        7.0f, // maxValue,
        0.0f)); // defaultValue
    addParameter(mHFilterFcParam = new juce::AudioParameterFloat("High Shelf fc", // parameterID,
        "HFiltFc", // parameterName,
        4000.0f, // minValue,
        20000.0f, // maxValue,
        8000.0f)); // defaultValue
    addParameter(mHFilterGainParam = new juce::AudioParameterFloat("High Shelf Gain", // parameterID,
        "HFiltGain", // parameterName,
        -10.0f, // minValue,
        7.0f, // maxValue,
        0.0f)); // defaultValue
    addParameter(mLPFilterFcParam = new juce::AudioParameterFloat("Low Pass fc", // parameterID,
        "LPFiltFc", // parameterName,
        4000.0f, // minValue,
        20000.0f, // maxValue,
        20000.0f)); // defaultValue
    addParameter(mLPFilterQParam = new juce::AudioParameterFloat("Low Pass Q", // parameterID,
        "LPFiltQ", // parameterName,
        0.2f, // minValue,
        1.4f, // maxValue,
        0.7f)); // defaultValue
    addParameter(mHPFilterFcParam = new juce::AudioParameterFloat("High Pass fc", // parameterID,
        "HPFiltFc", // parameterName,
        0.0f, // minValue,
        500.0f, // maxValue,
        0.0f)); // defaultValue
    addParameter(mHPFilterQParam = new juce::AudioParameterFloat("High Pass Q", // parameterID,
        "HPFiltQ", // parameterName,
        0.2f, // minValue,
        1.4f, // maxValue,
        0.7f)); // defaultValue
}

void NewProjectAudioProcessor::calcAlgorithmParams() {
    // Get the user parameter values
    float fc = mLFilterFcParam->get();
    float gaindB = mLFilterGainParam->get()*3;
    //To create a similar hearing effect to the default EQ, I multiplied by a coefficient of 3
    // Calculate filter coefficients
    float coeffs[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsLowShelf(coeffs, fc, gaindB, mFs);
    // Set the coefficients for each filter
    mLFilterL.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    mLFilterR.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
// DBG("Fc = "<<fc); // For debugging
    float fcM = mMFilterFcParam->get();
    float gaindBM = mMFilterGainParam->get()*3;
    float QM = mMFilterQParam->get();
    // Calculate filter coefficients
    float coeffsM[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsPeak(coeffsM, fcM, gaindBM, QM, mFs);
    // Set the coefficients for each filter
    mMFilterL.setCoefficients(coeffsM[0], coeffsM[1], coeffsM[2], coeffsM[3], coeffsM[4]);
    mMFilterR.setCoefficients(coeffsM[0], coeffsM[1], coeffsM[2], coeffsM[3], coeffsM[4]);
    float fcH = mHFilterFcParam->get();
    float gaindBH = mHFilterGainParam->get()*3;
    // Calculate filter coefficients
    float coeffsH[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsHighShelf(coeffsH, fcH, gaindBH, mFs);
    // Set the coefficients for each filter
    mHFilterL.setCoefficients(coeffsH[0], coeffsH[1], coeffsH[2], coeffsH[3], coeffsH[4]);
    mHFilterR.setCoefficients(coeffsH[0], coeffsH[1], coeffsH[2], coeffsH[3], coeffsH[4]);
    float fcLP = mLPFilterFcParam->get();
    float QLP = mLPFilterQParam->get();
    // Calculate filter coefficients
    float coeffsLP[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsLPF(coeffsLP, fcLP, QLP, mFs);
    // Set the coefficients for each filter
    mLPFilterL.setCoefficients(coeffsLP[0], coeffsLP[1], coeffsLP[2], coeffsLP[3], coeffsLP[4]);
    mLPFilterR.setCoefficients(coeffsLP[0], coeffsLP[1], coeffsLP[2], coeffsLP[3], coeffsLP[4]);
    float fcHP = mHPFilterFcParam->get();
    float QHP = mHPFilterQParam->get();
    // Calculate filter coefficients
    float coeffsHP[5]; // an array of 5 floats for filter coeffs: [b0, b1, b2, a1, a2]
    Mu45FilterCalc::calcCoeffsHPF(coeffsHP, fcHP, QHP, mFs);
    // Set the coefficients for each filter
    mHPFilterL.setCoefficients(coeffsHP[0], coeffsHP[1], coeffsHP[2], coeffsHP[3], coeffsHP[4]);
    mHPFilterR.setCoefficients(coeffsHP[0], coeffsHP[1], coeffsHP[2], coeffsHP[3], coeffsHP[4]);

}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mFs = sampleRate;
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    calcAlgorithmParams();
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);
    for (int samp = 0; samp < buffer.getNumSamples(); samp++)
    {
        channelDataLeft[samp] = (mLFilterL.tick(mMFilterL.tick(mHFilterL.tick(mLPFilterL.tick(mHPFilterL.tick(channelDataLeft[samp]))))));
        channelDataRight[samp] = (mLFilterR.tick(mMFilterR.tick(mHFilterR.tick(mLPFilterR.tick(mHPFilterR.tick(channelDataRight[samp]))))));
    }
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
