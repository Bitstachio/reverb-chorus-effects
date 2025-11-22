/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "ReverbParams.h"
#include "ChorusParams.h"

//===== Component Initializers =====

void A3AudioProcessorEditor::initSlider(
    juce::Component &parent, juce::Label &mainLabel, juce::Label &unitLabel, juce::Slider &slider,
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
    juce::AudioProcessorValueTreeState &apvts, const juce::String &paramId, const juce::String &labelText,
    const juce::String &unitText, double minValue, double maxValue, double step,
    const A3AudioProcessorEditor::ColourPalette &palette) {
    mainLabel.setText(labelText, juce::dontSendNotification);
    mainLabel.setJustificationType(juce::Justification::centredLeft);
    mainLabel.setColour(juce::Label::textColourId, palette.text);

    unitLabel.setText(unitText, juce::dontSendNotification);
    unitLabel.setJustificationType(juce::Justification::centredRight);
    unitLabel.setColour(juce::Label::textColourId, palette.text);

    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(minValue, maxValue, step);
    slider.setPopupDisplayEnabled(false, false, nullptr);
    slider.setValue(minValue);

    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    slider.setColour(juce::Slider::backgroundColourId, palette.sliderBackground);
    slider.setColour(juce::Slider::trackColourId, palette.sliderTrack);
    slider.setColour(juce::Slider::thumbColourId, palette.sliderThumb);
    slider.setColour(juce::Slider::textBoxTextColourId, palette.text);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, palette.background);
    slider.setColour(juce::Slider::textBoxOutlineColourId, palette.accent);

    parent.addAndMakeVisible(mainLabel);
    parent.addAndMakeVisible(unitLabel);
    parent.addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
}

void A3AudioProcessorEditor::initToggleButton(
    juce::TextButton &button, std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> &attachment,
    const juce::String &paramId, const juce::String &labelText, const juce::Colour &offColour,
    const juce::Colour &onColour, const juce::Colour &textColour) {
    button.setButtonText(labelText + "\n[ OFF ]");
    button.setClickingTogglesState(true);
    button.setColour(juce::TextButton::buttonColourId, offColour);
    button.setColour(juce::TextButton::buttonOnColourId, onColour);
    button.setColour(juce::TextButton::textColourOffId, textColour);

    button.onClick = [this, &button, labelText]() {
        button.setButtonText(button.getToggleState() ? labelText + "\n[ ON ]" : labelText + "\n[ OFF ]");
    };

    addAndMakeVisible(&button);

    attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, paramId, button);
}

//==============================================================================
A3AudioProcessorEditor::A3AudioProcessorEditor(A3AudioProcessor &p) : AudioProcessorEditor(&p), audioProcessor(p) {
    setSize(400, 200);

    filterMenu.setJustificationType(juce::Justification::centred);
    filterMenu.addItem("Filter: Low Pass", 1);
    filterMenu.addItem("Filter: Band Pass", 2);
    filterMenu.addItem("Filter: High Pass", 3);
    filterMenu.addItem("Filter: Off", 4);
    addAndMakeVisible(&filterMenu);

    phaserMenu.setJustificationType(juce::Justification::centred);
    phaserMenu.addItem("Phaser: On", 1);
    phaserMenu.addItem("Phaser: Off", 2);
    addAndMakeVisible(&phaserMenu);

    cutOffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutOffSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    cutOffSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&cutOffSlider);

    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rateSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&rateSlider);

    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    depthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&depthSlider);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&gainSlider);

    cutOffValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "CUTOFF",
                                                                                         cutOffSlider);
    rateValue   = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
                                                                                         "PHASERRATE", rateSlider);
    depthValue  = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
                                                                                         "PHASERDEPTH", depthSlider);
    gainValue   = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN",
                                                                                         gainSlider);
    filterMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        audioProcessor.apvts, "FILTERMENU", filterMenu);
    phaserMenuValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        audioProcessor.apvts, "PHASERMENU", phaserMenu);

    // Reverb parameters
    initSlider(*this, reverbRoomSizeLabel, reverbRoomSizeUnitLabel, reverbRoomSizeSlider, reverbRoomSizeAttachment,
               audioProcessor.apvts, "ROOM_SIZE", "Room Size", "[ % ]", ReverbParams::ROOM_SIZE_MIN,
               ReverbParams::ROOM_SIZE_MAX, ReverbParams::ROOM_SIZE_STEP, palette);
    initSlider(*this, reverbDampingLabel, reverbDampingUnitLabel, reverbDampingSlider, reverbDampingAttachment,
               audioProcessor.apvts, "DAMPING", "Damping", "[ % ]", ReverbParams::DAMPING_MIN,
               ReverbParams::DAMPING_MAX, ReverbParams::DAMPING_STEP, palette);
    initSlider(*this, reverbWidthLabel, reverbWidthUnitLabel, reverbWidthSlider, reverbWidthAttachment,
               audioProcessor.apvts, "WIDTH", "Width", "[ % ]", ReverbParams::WIDTH_MIN, ReverbParams::WIDTH_MAX,
               ReverbParams::WIDTH_STEP, palette);
    initSlider(*this, reverbWetLevelLabel, reverbWetLevelUnitLabel, reverbWetLevelSlider, reverbWetLevelAttachment,
               audioProcessor.apvts, "WET_LEVEL", "Wet Level", "[ % ]", ReverbParams::WET_MIN, ReverbParams::WET_MAX,
               ReverbParams::WET_STEP, palette);
    initSlider(*this, reverbDryLevelLabel, reverbDryLevelUnitLabel, reverbDryLevelSlider, reverbDryLevelAttachment,
               audioProcessor.apvts, "DRY_LEVEL", "Dry Level", "[ % ]", ReverbParams::DRY_MIN, ReverbParams::DRY_MAX,
               ReverbParams::DRY_STEP, palette);
    initToggleButton(reverbFreezeModeToggle, reverbFreezeModeAttachment, "FREEZE_MODE", "Freeze Mode",
                     palette.buttonOff, palette.buttonOn, palette.text);

    // Chorus parameters
    initSlider(*this, chorusRateLabel, chorusRateUnitLabel, chorusRateSlider, chorusRateAttachment,
               audioProcessor.apvts, "RATE", "Rate", "[ Hz ]", ChorusParams::RATE_MIN, ChorusParams::RATE_MAX,
               ChorusParams::RATE_STEP, palette);
    initSlider(*this, chorusDepthLabel, chorusDepthUnitLabel, chorusDepthSlider, chorusDepthAttachment,
               audioProcessor.apvts, "DEPTH", "Depth", "[ % ]", ChorusParams::DEPTH_MIN, ChorusParams::DEPTH_MAX,
               ChorusParams::DEPTH_STEP, palette);
    initSlider(*this, chorusCentreDelayLabel, chorusCentreDelayUnitLabel, chorusCentreDelaySlider,
               chorusCentreDelayAttachment, audioProcessor.apvts, "CENTRE_DELAY", "Centre Delay", "[ ms ]",
               ChorusParams::CENTRE_DELAY_MIN, ChorusParams::CENTRE_DELAY_MAX, ChorusParams::CENTRE_DELAY_STEP,
               palette);
    initSlider(*this, chorusFeedbackLabel, chorusFeedbackUnitLabel, chorusFeedbackSlider, chorusFeedbackAttachment,
               audioProcessor.apvts, "FEEDBACK", "Feedback", "[ % ]", ChorusParams::FEEDBACK_MIN,
               ChorusParams::FEEDBACK_MAX, ChorusParams::FEEDBACK_STEP, palette);
    initSlider(*this, chorusMixLabel, chorusMixUnitLabel, chorusMixSlider, chorusMixAttachment, audioProcessor.apvts,
               "MIX", "Mix", "[ % ]", ChorusParams::MIX_MIN, ChorusParams::MIX_MAX, ChorusParams::MIX_STEP, palette);
}

A3AudioProcessorEditor::~A3AudioProcessorEditor() {}

//==============================================================================
void A3AudioProcessorEditor::paint(juce::Graphics &g) {
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::greenyellow);
    juce::Rectangle<int> area      = getLocalBounds().reduced(5);
    juce::Rectangle<int> titleArea = area.removeFromTop(20);
    // int width = area.getWidth();
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::white);
    g.drawText("A3 Starter", titleArea, juce::Justification::centredTop);

    juce::Rectangle<int> innerArea = getLocalBounds().reduced(25); //(25, 25, 350, 150);
    g.setColour(juce::Colours::yellowgreen);
    g.drawRect(innerArea, 1.0f);

    int innerWidth = innerArea.getWidth();
    g.drawText("Cutoff", innerArea.getX(), 80, innerWidth / 4, 25, juce::Justification::centred);
    g.drawText("Rate", innerArea.getX() + innerWidth / 4, 80, innerWidth / 4, 25, juce::Justification::centred);
    g.drawText("Depth", innerArea.getX() + innerWidth / 2, 80, innerWidth / 4, 25, juce::Justification::centred);
    g.drawText("Gain", innerArea.getX() + 3 * innerWidth / 4, 80, innerWidth / 4, 25, juce::Justification::centred);
}

void A3AudioProcessorEditor::resized() {
    juce::Rectangle<int> area  = getLocalBounds().reduced(40);
    juce::Rectangle<int> menus = area.removeFromTop(20);
    int                  width = menus.getWidth();
    filterMenu.setBounds(menus.removeFromLeft(width / 2 - 5));
    phaserMenu.setBounds(menus.removeFromRight(width / 2 - 5));
    cutOffSlider.setBounds(35, 90, width / 4 - 10, area.getHeight() - 10);
    rateSlider.setBounds(120, 90, width / 4 - 10, area.getHeight() - 10);
    depthSlider.setBounds(209, 90, width / 4 - 10, area.getHeight() - 10);
    gainSlider.setBounds(295, 90, width / 4 - 10, area.getHeight() - 10);
}
