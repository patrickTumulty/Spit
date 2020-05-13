/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"

//==============================================================================

class SpitAudioProcessor  : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    SpitAudioProcessor();
    ~SpitAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;


    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void parameterChanged(const String &parameterID, float newValue) override;
    
    MidiProcessor * getMidiProcessor();
    
//    AudioProcessorValueTreeState& getValueTreeState();
    
    AudioProcessorValueTreeState parameters;
   
    
private:
    MidiProcessor * midiProcessor;
    AudioPlayHead::CurrentPositionInfo mInfo;
    
//    std::atomic<float>* cState = nullptr;
    float cState = 0.0f;
    Atomic<float>* cSharpState = nullptr;
    Atomic<float>* dState = nullptr;
    Atomic<float>* dSharpState = nullptr;
    Atomic<float>* eState = nullptr;
    Atomic<float>* fState = nullptr;
    Atomic<float>* fSharpState = nullptr;
    Atomic<float>* gState = nullptr;
    Atomic<float>* gSharpState = nullptr;
    Atomic<float>* aState = nullptr;
    Atomic<float>* aSharpState = nullptr;
    Atomic<float>* bState = nullptr;
    
    Atomic<float>* startState = nullptr;
    
    Atomic<float>* rangeLowState = nullptr;
    Atomic<float>* rangeHighState = nullptr;
    
    Atomic<float>* tempoState = nullptr;
    
    
    //==============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpitAudioProcessor)
};
