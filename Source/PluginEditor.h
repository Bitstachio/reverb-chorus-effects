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
class A3AudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    A3AudioProcessorEditor(A3AudioProcessor &);
    ~A3AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A3AudioProcessor &audioProcessor;

    struct ColourPalette {
        juce::Colour background       = juce::Colour(0xff1e1e1e);
        juce::Colour text             = juce::Colour(0xfff0f0f0);
        juce::Colour accent           = juce::Colour(0xff4aa3df);
        juce::Colour buttonOff        = juce::Colour(0xff3a3a3a);
        juce::Colour buttonOn         = juce::Colour(0xff4aa3df);
        juce::Colour sliderBackground = juce::Colour(0xFF4A4A4A);
        juce::Colour sliderTrack      = juce::Colour(0xFF3B5770);
        juce::Colour sliderThumb      = juce::Colour(0xFF6AC1FF);
    } palette;

    juce::Slider   cutOffSlider;
    juce::Slider   rateSlider;
    juce::Slider   depthSlider;
    juce::Slider   gainSlider;
    juce::ComboBox filterMenu;
    juce::ComboBox phaserMenu;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>   cutOffValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>   rateValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>   depthValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>   gainValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> phaserMenuValue;

    //===== Component Initializers =====

    void initSlider(juce::Component &parent, juce::Label &mainLabel, juce::Label &unitLabel, juce::Slider &slider,
                    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
                    juce::AudioProcessorValueTreeState &apvts, const juce::String &paramId,
                    const juce::String &labelText, const juce::String &unitText, double minValue, double maxValue,
                    double step, const ColourPalette &palette);

    void initToggleButton(juce::TextButton                                                      &button,
                          std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> &attachment,
                          const juce::String &paramId, const juce::String &labelText, const juce::Colour &offColour,
                          const juce::Colour &onColour, const juce::Colour &textColour);

    //===== Reverb Parameters =====

    // Room Size
    juce::Label                                                           reverbRoomSizeLabel;
    juce::Label                                                           reverbRoomSizeUnitLabel;
    juce::Slider                                                          reverbRoomSizeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbRoomSizeAttachment;

    // Damping
    juce::Label                                                           reverbDampingLabel;
    juce::Label                                                           reverbDampingUnitLabel;
    juce::Slider                                                          reverbDampingSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbDampingAttachment;

    // Width
    juce::Label                                                           reverbWidthLabel;
    juce::Label                                                           reverbWidthUnitLabel;
    juce::Slider                                                          reverbWidthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbWidthAttachment;

    // Wet Level
    juce::Label                                                           reverbWetLevelLabel;
    juce::Label                                                           reverbWetLevelUnitLabel;
    juce::Slider                                                          reverbWetLevelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbWetLevelAttachment;

    // Dry Level
    juce::Label                                                           reverbDryLevelLabel;
    juce::Label                                                           reverbDryLevelUnitLabel;
    juce::Slider                                                          reverbDryLevelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbDryLevelAttachment;

    // Freeze Mode
    juce::TextButton                                                      reverbFreezeModeToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbFreezeModeAttachment;

    //===== Chorus Parameters =====

    // Rate
    juce::Label                                                           chorusRateLabel;
    juce::Label                                                           chorusRateUnitLabel;
    juce::Slider                                                          chorusRateSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusRateAttachment;

    // Depth
    juce::Label                                                           chorusDepthLabel;
    juce::Label                                                           chorusDepthUnitLabel;
    juce::Slider                                                          chorusDepthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusDepthAttachment;

    // Centre Delay
    juce::Label                                                           chorusCentreDelayLabel;
    juce::Label                                                           chorusCentreDelayUnitLabel;
    juce::Slider                                                          chorusCentreDelaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusCentreDelayAttachment;

    // Feedback
    juce::Label                                                           chorusFeedbackLabel;
    juce::Label                                                           chorusFeedbackUnitLabel;
    juce::Slider                                                          chorusFeedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusFeedbackAttachment;

    // Mix
    juce::Label                                                           chorusMixLabel;
    juce::Label                                                           chorusMixUnitLabel;
    juce::Slider                                                          chorusMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusMixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(A3AudioProcessorEditor)
};
