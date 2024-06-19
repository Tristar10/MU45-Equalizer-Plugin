/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    juce::Slider mLFilterFcSlider;
    juce::Slider mLFilterGainSlider;
    juce::Slider mMFilterFcSlider;
    juce::Slider mMFilterQSlider;
    juce::Slider mMFilterGainSlider;
    juce::Slider mHFilterFcSlider;
    juce::Slider mHFilterGainSlider;
    juce::Slider mLPFilterFcSlider;
    juce::Slider mLPFilterQSlider;
    juce::Slider mHPFilterFcSlider;
    juce::Slider mHPFilterQSlider;
    juce::Label LfcLabel;
    juce::Label LgainLabel;
    juce::Label MQLabel;
    juce::Label MgainLabel;
    juce::Label MfcLabel;
    juce::Label HfcLabel;
    juce::Label Hgainlabel;
    juce::Label LPQLabel;
    juce::Label LPfcLabel;
    juce::Label HPQLabel;
    juce::Label HPfcLabel;
    juce::TextButton BBoost, VocalEnhance, EDM, PureMusic;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
