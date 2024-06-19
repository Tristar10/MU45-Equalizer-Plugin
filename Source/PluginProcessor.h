/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Mu45FilterCalc/Mu45FilterCalc.h"
#include "StkLite-4.6.2/BiQuad.h"


//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
    void calcAlgorithmParams();
    // User Parameters
    juce::AudioParameterFloat* mLFilterFcParam;
    juce::AudioParameterFloat* mLFilterGainParam;
    juce::AudioParameterFloat* mMFilterFcParam;
    juce::AudioParameterFloat* mMFilterQParam;
    juce::AudioParameterFloat* mMFilterGainParam;
    juce::AudioParameterFloat* mHFilterFcParam;
    juce::AudioParameterFloat* mHFilterGainParam;
    juce::AudioParameterFloat* mLPFilterFcParam;
    juce::AudioParameterFloat* mLPFilterQParam;
    juce::AudioParameterFloat* mHPFilterFcParam;
    juce::AudioParameterFloat* mHPFilterQParam;
    
    stk::BiQuad mLFilterL, mLFilterR, mMFilterL, mMFilterR, mHFilterL, mHFilterR, mLPFilterL, mLPFilterR, mHPFilterL, mHPFilterR; // The filters
    float mFs; // Sampling rate
};
