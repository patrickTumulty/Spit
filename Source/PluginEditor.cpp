/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SpitAudioProcessorEditor::SpitAudioProcessorEditor (SpitAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
    
    offColor = Colours::grey;
    onColor = Colours::orangered;
    
    
    this->buttonConfig(&C,     "C");
    this->buttonConfig(&CSharp,"C#");
    this->buttonConfig(&D,     "D");
    this->buttonConfig(&DSharp,"D#");
    this->buttonConfig(&E,     "E");
    this->buttonConfig(&F,     "F");
    this->buttonConfig(&FSharp,"F#");
    this->buttonConfig(&G,     "G");
    this->buttonConfig(&GSharp,"G#");
    this->buttonConfig(&A,     "A");
    this->buttonConfig(&ASharp,"A#");
    this->buttonConfig(&B,     "B");

    addAndMakeVisible(tempoList);
    addAndMakeVisible(tempoLabel);
    
    tempoLabel.attachToComponent(&tempoList, false);
    tempoLabel.setJustificationType(Justification::top);
    tempoLabel.setText("Tempo", NotificationType::dontSendNotification);
    
    tempoList.setColour(ComboBox::ColourIds::backgroundColourId, Colours::grey);
    tempoList.addItem("1/1", 1);
    tempoList.addItem("1/2", 2);
    tempoList.addItem("1/4", 3);
    tempoList.addItem("1/8", 4);
    tempoList.addItem("1/16", 5);
    tempoList.addItem("1/32", 6);
    tempoList.setSelectedId(3);
    tempoList.addListener(this);
    
    addAndMakeVisible(logo);
    logo.setText("SPIT", dontSendNotification);
    logo.setFont(Font ("Futura", 80.0, Font::bold)); // Futura
    logo.setJustificationType(Justification::centred);
    logo.setBorderSize(BorderSize<int>(20));
    logo.setColour(Label::ColourIds::outlineColourId, Colours::white);
    logo.setColour(Label::ColourIds::textColourId, Colours::white);
    logo.setColour(Label::ColourIds::backgroundColourId, Colours::orangered);
    
    addAndMakeVisible(enable);
    enable.setButtonText("START");
    enable.addListener(this);
    enable.setColour(TextButton::textColourOnId, Colours::white);
    enable.setColour(TextButton::textColourOffId, Colours::white);
    enable.setColour(TextButton::buttonColourId, Colours::grey);
    
    addAndMakeVisible(rangeHigh);
    this->rangeSliderConfig(&rangeHigh, false);
    this->rangeSliderConfig(&rangeLow, true);
}

SpitAudioProcessorEditor::~SpitAudioProcessorEditor()
{
}

void SpitAudioProcessorEditor::buttonConfig(TextButton* button, String noteName)
{
    addAndMakeVisible(button);
    button->setButtonText(noteName);
    button->setClickingTogglesState(true);
    button->setColour(TextButton::buttonColourId, offColor);
    button->setColour(TextButton::textColourOnId, Colours::white);
    button->setColour(TextButton::textColourOffId, Colours::white);
    button->addListener(this);
}

void SpitAudioProcessorEditor::rangeSliderConfig(Slider *slider, bool isLow)
{
    addAndMakeVisible(slider);
    slider->addListener(this);
    slider->setColour(Slider::thumbColourId, Colours::orangered);
    slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
    slider->setColour(Slider::textBoxOutlineColourId, Colours::grey);
    if (isLow)
    {
        Range<double> lowRange = Range<double>();
        lowRange.setStart(20);
        lowRange.setEnd(109);
        
        slider->setRange(lowRange, 1.0);
        slider->setValue(20);
        
        slider->setColour(Slider::trackColourId, Colours::grey);
        slider->setColour(Slider::backgroundColourId, Colours::orangered);
    }
    else
    {
        Range<double> highRange = Range<double>();
        highRange.setStart(20);
        highRange.setEnd(109);
        
        rangeLabel.attachToComponent(&rangeHigh, false);
        rangeLabel.setText("Range", NotificationType::dontSendNotification);
        rangeLabel.setJustificationType(Justification::top);
        
        slider->setRange(highRange, 1.0);
        slider->setValue(109);
        
        slider->setColour(Slider::backgroundColourId, Colours::grey);
        slider->setColour(Slider::trackColourId, Colours::orangered);
    }
}

//==============================================================================
void SpitAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::grey);
    
}

void SpitAudioProcessorEditor::resized()
{
    Rectangle<int> rightBounds = getLocalBounds().removeFromRight(200);
    
    GSharp.setBounds(  0,   0, 50, 100); // 1
    A.setBounds     ( 50,   0, 50, 100); // 2
    ASharp.setBounds(100,   0, 50, 100); // 3
    B.setBounds     (150,   0, 50, 100); // 4

    E.setBounds     (  0, 100, 50, 100); // 5
    F.setBounds     ( 50, 100, 50, 100); // 6
    FSharp.setBounds(100, 100, 50, 100); // 7
    G.setBounds     (150, 100, 50, 100); // 8

    C.setBounds     (  0, 200, 50, 100); // 9
    CSharp.setBounds( 50, 200, 50, 100); // 10
    D.setBounds     (100, 200, 50, 100); // 11
    DSharp.setBounds(150, 200, 50, 100); // 12
    
    enable.setBounds(rightBounds.removeFromTop(40));
    enable.setClickingTogglesState(true);

    rangeHigh.setBounds(201, 70, 200, 30);
    rangeLow.setBounds(201, 100, 200, 30);
    tempoList.setBounds(201, 160, 200, 30);
    logo.setBounds(220, 210, 160, 80);
    
}

void SpitAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    this->processor.getMidiProcessor()->setRange(rangeLow.getValue(), rangeHigh.getValue());
    this->processor.getMidiProcessor()->updateRange();
}

void SpitAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &C)
    {
        this->buttonStateHandler(&C, "C");
    }
    else if (button == &CSharp)
    {
        this->buttonStateHandler(&CSharp, "C#");
    }
    else if (button == &D)
    {
        this->buttonStateHandler(&D, "D");
    }
    else if (button == &DSharp)
    {
        this->buttonStateHandler(&DSharp, "D#");
    }
    else if (button == &E)
    {
        this->buttonStateHandler(&E, "E");
    }
    else if (button == &F)
    {
        this->buttonStateHandler(&F, "F");
    }
    else if (button == &FSharp)
    {
        this->buttonStateHandler(&FSharp, "F#");
    }
    else if (button == &G)
    {
        this->buttonStateHandler(&G, "G");
    }
    else if (button == &GSharp)
    {
        this->buttonStateHandler(&GSharp, "G#");
    }
    else if (button == &A)
    {
        this->buttonStateHandler(&A, "A");
    }
    else if (button == &ASharp)
    {
        this->buttonStateHandler(&ASharp, "A#");
    }
    else if (button == &B)
    {
        this->buttonStateHandler(&B, "B");
    }
    else if (button == &enable)
    {
        if (button->getToggleState())
        {
            button->setColour(TextButton::buttonOnColourId, Colours::orangered);
            this->processor.getMidiProcessor()->setIsPlaying(true);
        }
        else
        {
            button->setColour(TextButton::buttonColourId, Colours::grey);
            this->processor.getMidiProcessor()->setIsPlaying(false);
        }
    }
    button->colourChanged();
    
}

void SpitAudioProcessorEditor::buttonStateHandler(TextButton* button, String noteName)
{
    if(button->getToggleState())
    {
        button->setColour(TextButton::buttonOnColourId, onColor);
        this->processor.getMidiProcessor()->addNotesToPool(noteName);
    }
    else
    {
        button->setColour(TextButton::buttonColourId, offColor);
        this->processor.getMidiProcessor()->removeNotesFromPool(noteName);
    }
}

void SpitAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged->getText() == "1/1")
    {
        this->processor.getMidiProcessor()->setTempoScaler(0.25f);
    }
    else if (comboBoxThatHasChanged->getText() == "1/2")
    {
        this->processor.getMidiProcessor()->setTempoScaler(0.5f);
    }
    else if (comboBoxThatHasChanged->getText() == "1/4")
    {
        this->processor.getMidiProcessor()->setTempoScaler(1.0f);
    }
    else if (comboBoxThatHasChanged->getText() == "1/8")
    {
        this->processor.getMidiProcessor()->setTempoScaler(2.0f);
    }
    else if (comboBoxThatHasChanged->getText() == "1/16")
    {
        this->processor.getMidiProcessor()->setTempoScaler(4.0f);
    }
    else if (comboBoxThatHasChanged->getText() == "1/32")
    {
        this->processor.getMidiProcessor()->setTempoScaler(8.0f);
    }
}
