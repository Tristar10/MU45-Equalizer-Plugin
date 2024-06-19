/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    // Setup your sliders and other gui components - - - -
    auto& params = processor.getParameters();
    // Cuttoff Freq Slider
    juce::AudioParameterFloat* audioLFCParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
    mLFilterFcSlider.setBounds(50, 50, 100, 100);
    mLFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mLFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mLFilterFcSlider.setRange(audioLFCParam->range.start, audioLFCParam->range.end);
    mLFilterFcSlider.setValue(*audioLFCParam);
    mLFilterFcSlider.addListener(this);
    addAndMakeVisible(mLFilterFcSlider);
    //Gain slider
    juce::AudioParameterFloat* audioLGParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
    mLFilterGainSlider.setBounds(50, 500, 100, 100);
    mLFilterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mLFilterGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mLFilterGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mLFilterGainSlider.setRange(audioLGParam->range.start, audioLGParam->range.end);
    mLFilterGainSlider.setValue(*audioLGParam);
    mLFilterGainSlider.addListener(this);
    addAndMakeVisible(mLFilterGainSlider);
    // Cuttoff Freq Slider
    juce::AudioParameterFloat* audioMFCParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
    mMFilterFcSlider.setBounds(350, 50, 100, 100);
    mMFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mMFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mMFilterFcSlider.setRange(audioMFCParam->range.start, audioMFCParam->range.end);
    mMFilterFcSlider.setValue(*audioMFCParam);
    mMFilterFcSlider.addListener(this);
    addAndMakeVisible(mMFilterFcSlider);
    // Q slider
    juce::AudioParameterFloat* audioMQParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
    mMFilterQSlider.setBounds(350, 250, 100, 100);
    mMFilterQSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mMFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mMFilterQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mMFilterQSlider.setRange(audioMQParam->range.start, audioMQParam->range.end);
    mMFilterQSlider.setValue(*audioMQParam);
    mMFilterQSlider.addListener(this);
    addAndMakeVisible(mMFilterQSlider);
    //Gain slider
    juce::AudioParameterFloat* audioMGParam = (juce::AudioParameterFloat*)params.getUnchecked(4);
    mMFilterGainSlider.setBounds(350, 500, 100, 100);
    mMFilterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mMFilterGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mMFilterGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mMFilterGainSlider.setRange(audioMGParam->range.start, audioMGParam->range.end);
    mMFilterGainSlider.setValue(*audioMGParam);
    mMFilterGainSlider.addListener(this);
    addAndMakeVisible(mMFilterGainSlider);
    // Cuttoff Freq Slider
    juce::AudioParameterFloat* audioHFCParam = (juce::AudioParameterFloat*)params.getUnchecked(5);
    mHFilterFcSlider.setBounds(650, 50, 100, 100);
    mHFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mHFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mHFilterFcSlider.setRange(audioHFCParam->range.start, audioHFCParam->range.end);
    mHFilterFcSlider.setValue(*audioHFCParam);
    mHFilterFcSlider.addListener(this);
    addAndMakeVisible(mHFilterFcSlider);
    //Gain slider
    juce::AudioParameterFloat* audioHGParam = (juce::AudioParameterFloat*)params.getUnchecked(6);
    mHFilterGainSlider.setBounds(650, 500, 100, 100);
    mHFilterGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mHFilterGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mHFilterGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mHFilterGainSlider.setRange(audioHGParam->range.start, audioHGParam->range.end);
    mHFilterGainSlider.setValue(*audioHGParam);
    mHFilterGainSlider.addListener(this);
    addAndMakeVisible(mHFilterGainSlider);

    juce::AudioParameterFloat* audioLPFCParam = (juce::AudioParameterFloat*)params.getUnchecked(7);
    mLPFilterFcSlider.setBounds(500, 50, 100, 100);
    mLPFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mLPFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mLPFilterFcSlider.setRange(audioLPFCParam->range.start, audioLPFCParam->range.end);
    mLPFilterFcSlider.setValue(*audioLPFCParam);
    mLPFilterFcSlider.addListener(this);
    addAndMakeVisible(mLPFilterFcSlider);
    // Q slider
    juce::AudioParameterFloat* audioLPQParam = (juce::AudioParameterFloat*)params.getUnchecked(8);
    mLPFilterQSlider.setBounds(500, 500, 100, 100);
    mLPFilterQSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mLPFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mLPFilterQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mLPFilterQSlider.setRange(audioLPQParam->range.start, audioLPQParam->range.end);
    mLPFilterQSlider.setValue(*audioLPQParam);
    mLPFilterQSlider.addListener(this);
    addAndMakeVisible(mLPFilterQSlider);

    juce::AudioParameterFloat* audioHPFCParam = (juce::AudioParameterFloat*)params.getUnchecked(9);
    mHPFilterFcSlider.setBounds(200, 50, 100, 100);
    mHPFilterFcSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mHPFilterFcSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mHPFilterFcSlider.setRange(audioHPFCParam->range.start, audioHPFCParam->range.end);
    mHPFilterFcSlider.setValue(*audioHPFCParam);
    mHPFilterFcSlider.addListener(this);
    addAndMakeVisible(mHPFilterFcSlider);
    // Q slider
    juce::AudioParameterFloat* audioHPQParam = (juce::AudioParameterFloat*)params.getUnchecked(10);
    mHPFilterQSlider.setBounds(200, 500, 100, 100);
    mHPFilterQSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mHPFilterQSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mHPFilterQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mHPFilterQSlider.setRange(audioHPQParam->range.start, audioHPQParam->range.end);
    mHPFilterQSlider.setValue(*audioHPQParam);
    mHPFilterQSlider.addListener(this);
    addAndMakeVisible(mHPFilterQSlider);

    addAndMakeVisible (LfcLabel);
    LfcLabel.setText ("Low Shelf fc", juce::dontSendNotification);
    LfcLabel.setJustificationType(juce::Justification::centred);
    LfcLabel.attachToComponent(&mLFilterFcSlider, false);
    addAndMakeVisible (LgainLabel);
    LgainLabel.setText ("Low Shelf gain", juce::dontSendNotification);
    LgainLabel.setJustificationType(juce::Justification::centred);
    LgainLabel.attachToComponent(&mLFilterGainSlider, false);
    addAndMakeVisible (Hgainlabel);
    MfcLabel.setText ("Midband fc", juce::dontSendNotification);
    MfcLabel.setJustificationType(juce::Justification::centred);
    MfcLabel.attachToComponent(&mMFilterFcSlider, false);
    addAndMakeVisible (MfcLabel);
    MgainLabel.setText ("Midband gain", juce::dontSendNotification);
    MgainLabel.setJustificationType(juce::Justification::centred);
    MgainLabel.attachToComponent(&mMFilterGainSlider, false);
    addAndMakeVisible (MgainLabel);
    MQLabel.setText ("Midband Q", juce::dontSendNotification);
    MQLabel.setJustificationType(juce::Justification::centred);
    MQLabel.attachToComponent(&mMFilterQSlider, false);
    addAndMakeVisible (MQLabel);
    HfcLabel.setText ("High Shelf fc", juce::dontSendNotification);
    HfcLabel.setJustificationType(juce::Justification::centred);
    HfcLabel.attachToComponent(&mHFilterFcSlider, false);
    addAndMakeVisible (HfcLabel);
    Hgainlabel.setText ("High Shelf gain", juce::dontSendNotification);
    Hgainlabel.setJustificationType(juce::Justification::centred);
    Hgainlabel.attachToComponent(&mHFilterGainSlider, false);
    addAndMakeVisible (Hgainlabel);
    HPQLabel.setText ("Low Cut Q", juce::dontSendNotification);
    HPQLabel.setJustificationType(juce::Justification::centred);
    HPQLabel.attachToComponent(&mHPFilterQSlider, false);
    addAndMakeVisible (HPQLabel);
    HPfcLabel.setText ("Low Cut fc", juce::dontSendNotification);
    HPfcLabel.setJustificationType(juce::Justification::centred);
    HPfcLabel.attachToComponent(&mHPFilterFcSlider, false);
    addAndMakeVisible (HPfcLabel);
    LPQLabel.setText ("High Cut Q", juce::dontSendNotification);
    LPQLabel.setJustificationType(juce::Justification::centred);
    LPQLabel.attachToComponent(&mLPFilterQSlider, false);
    addAndMakeVisible (LPQLabel);
    LPfcLabel.setText ("High Cut fc", juce::dontSendNotification);
    LPfcLabel.setJustificationType(juce::Justification::centred);
    LPfcLabel.attachToComponent(&mLPFilterFcSlider, false);
    addAndMakeVisible (LPfcLabel);
    BBoost.setButtonText("Bass Boost");
    BBoost.setBounds(575, 250, 90, 30);
    BBoost.onClick = [&]()
    {
        mLFilterFcSlider.setValue(100);
        mLFilterGainSlider.setValue(2.2);
        
        mLPFilterFcSlider.setValue(20000);
        mHPFilterFcSlider.setValue(0);
        mHFilterGainSlider.setValue(0);
        mMFilterGainSlider.setValue(0);
    };
    BBoost.setColour(BBoost.textColourOffId, juce::Colours::black);
    BBoost.setColour(BBoost.buttonColourId, juce::Colours::grey);
    addAndMakeVisible(BBoost);
    EDM.setButtonText("EDM EQ");
    EDM.setBounds(575, 350, 90, 30);
    EDM.onClick = [&]()
    {
        mLFilterFcSlider.setValue(70);
        mLFilterGainSlider.setValue(1.5);
        mMFilterFcSlider.setValue(1700);
        mMFilterGainSlider.setValue(1.5);
        
        mLPFilterFcSlider.setValue(20000);
        mHPFilterFcSlider.setValue(0);
        mHFilterGainSlider.setValue(0);
    };
    EDM.setColour(EDM.textColourOffId, juce::Colours::black);
    EDM.setColour(EDM.buttonColourId, juce::Colours::grey);
    addAndMakeVisible(EDM);
    PureMusic.setButtonText("Clear EQ");
    PureMusic.setBounds(150, 250, 75, 30);
    PureMusic.onClick = [&]()
    {
        mMFilterFcSlider.setValue(1100);
        mMFilterGainSlider.setValue(1.3);
        mHFilterFcSlider.setValue(6000);
        mHFilterGainSlider.setValue(0.8);
        
        mLPFilterFcSlider.setValue(20000);
        mHPFilterFcSlider.setValue(0);
        mLFilterGainSlider.setValue(0);
    };
    PureMusic.setColour(PureMusic.textColourOffId, juce::Colours::black);
    PureMusic.setColour(PureMusic.buttonColourId, juce::Colours::grey);
    addAndMakeVisible(PureMusic);
    VocalEnhance.setButtonText("Vocal Enhancer");
    VocalEnhance.setBounds(150, 350, 75, 30);
    VocalEnhance.onClick = [&]()
    {
        mMFilterFcSlider.setValue(4000);
        mMFilterGainSlider.setValue(0.6);
        mHFilterFcSlider.setValue(8000);
        mHFilterGainSlider.setValue(2.5);
        
        mLPFilterFcSlider.setValue(20000);
        mHPFilterFcSlider.setValue(0);
        mLFilterGainSlider.setValue(0);
    };
    VocalEnhance.setColour(VocalEnhance.textColourOffId, juce::Colours::black);
    VocalEnhance.setColour(VocalEnhance.buttonColourId, juce::Colours::grey);
    addAndMakeVisible(VocalEnhance);
    
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Image background = juce::ImageCache::getFromMemory (BinaryData::Untitled_png, BinaryData::Untitled_pngSize);
    g.drawImageAt (background, 0, 0);
    g.setFont (25.0f);
    g.drawFittedText ("MU45 Project2", getLocalBounds(), juce::Justification::centredTop, 1);
    g.setColour (juce::Colours::white);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider * slider){
    auto& params = processor.getParameters();
    if (slider == &mLFilterFcSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
        *audioParam = mLFilterFcSlider.getValue(); // set the AudioParameter
        DBG("Low Shelf Fc Slider Changed");
    }
    else if (slider == &mLFilterGainSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
        *audioParam = mLFilterGainSlider.getValue(); // set the param
        DBG("Low Shelf Gain Slider Changed");
    }
    else if (slider == &mMFilterFcSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
        *audioParam = mMFilterFcSlider.getValue(); // set the AudioParameter
        DBG("Midband Fc Slider Changed");
    }
    else if (slider == &mMFilterQSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
        *audioParam = mMFilterQSlider.getValue(); // set the param
        DBG("Midband Q Slider Changed");
    }
    else if (slider == &mMFilterGainSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(4);
        *audioParam = mMFilterGainSlider.getValue(); // set the param
        DBG("Midband Gain Slider Changed");
    }
    else if (slider == &mHFilterFcSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(5);
        *audioParam = mHFilterFcSlider.getValue(); // set the AudioParameter
        DBG("High Shelf Fc Slider Changed");
    }
    else if (slider == &mHFilterGainSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(6);
        *audioParam = mHFilterGainSlider.getValue(); // set the param
        DBG("High Shelf Gain Slider Changed");
    }else if (slider == &mLPFilterFcSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(7);
        *audioParam = mLPFilterFcSlider.getValue(); // set the AudioParameter
        DBG("Low Pass Fc Slider Changed");
    }
    else if (slider == &mLPFilterQSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(8);
        *audioParam = mLPFilterQSlider.getValue(); // set the param
        DBG("Low Pass Q Slider Changed");
    }else if (slider == &mHPFilterFcSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(9);
        *audioParam = mHPFilterFcSlider.getValue(); // set the AudioParameter
        DBG("High Pass Fc Slider Changed");
    }
    else if (slider == &mHPFilterQSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(10);
        *audioParam = mHPFilterQSlider.getValue(); // set the param
        DBG("High Pass Q Slider Changed");
    }
};
