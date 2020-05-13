/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/

typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

class SpitAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener, public Slider::Listener, public ComboBox::Listener
{
public:
    SpitAudioProcessorEditor (SpitAudioProcessor&);
    ~SpitAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    
    void buttonStateHandler(TextButton* button, String noteName);
    
    void buttonConfig(TextButton* button, String noteName);
    void rangeSliderConfig(Slider* slider, bool isLow);
private:
//    AudioProcessorValueTreeState& valueTreeState;
    SpitAudioProcessor& processor;
    
    TextButton enable;
    ButtonAttachment enableAttachment { processor.parameters, "start", enable};
    
    TextButton C;
    TextButton CSharp;
    TextButton D;
    TextButton DSharp;
    TextButton E;
    TextButton F;
    TextButton FSharp;
    TextButton G;
    TextButton GSharp;
    TextButton A;
    TextButton ASharp;
    TextButton B;
    
    ButtonAttachment cAttachment        { processor.parameters, "c", C };
    ButtonAttachment cSharpAttachment   { processor.parameters, "cSharp", CSharp };
    ButtonAttachment dAttachment        { processor.parameters, "d", D };
    ButtonAttachment dSharpAttachment   { processor.parameters, "dSharp", DSharp };
    ButtonAttachment eAttachment        { processor.parameters, "e", E };
    ButtonAttachment fAttachment        { processor.parameters, "f", F };
    ButtonAttachment fSharpAttachment   { processor.parameters, "fSharp", FSharp };
    ButtonAttachment gAttachment        { processor.parameters, "g", G };
    ButtonAttachment gSharpAttachment   { processor.parameters, "gSharp", GSharp };
    ButtonAttachment aAttachment        { processor.parameters, "a", A };
    ButtonAttachment aSharpAttachment   { processor.parameters, "aSharp", ASharp };
    ButtonAttachment bAttachment        { processor.parameters, "b", B };
//
    Label rangeLabel;
    Slider rangeHigh;
    Slider rangeLow;
//
    SliderAttachment rangeHighAttachment { processor.parameters, "rangeHigh", rangeHigh };
    SliderAttachment rangeLowAttachment { processor.parameters, "rangeLow", rangeLow };
    
    Label tempoLabel;
    ComboBox tempoList;
    ComboBoxAttachment tempoAttachment { processor.parameters, "tempo", tempoList };
    
    Label logo;
    
    Colour onColor;
    Colour offColor;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpitAudioProcessorEditor)
};
