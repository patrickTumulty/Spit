/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MidiProcessor.h"

//==============================================================================
SpitAudioProcessor::SpitAudioProcessor() : AudioProcessor (BusesProperties()), parameters(*this, nullptr, Identifier("SpitParams"),
{
    std::make_unique<AudioParameterBool>(
                                         "c",   // ID
                                         "C",   // Name
                                         false  // Default
                                         ),
    std::make_unique<AudioParameterBool>(
                                        "cSharp",
                                        "CSharp",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "d",
                                        "D",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "dSharp",
                                        "DSharp",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "e",
                                        "E",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "f",
                                        "F",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "fSharp",
                                        "FSharp",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "g",
                                        "G",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "gSharp",
                                        "GSharp",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "a",
                                        "A",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "aSharp",
                                        "ASharp",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "b",
                                        "B",
                                        false
                                        ),
    std::make_unique<AudioParameterBool>(
                                        "start",
                                        "Start",
                                        false
                                        ),
    std::make_unique<AudioParameterInt>(
                                      "rangeLow",
                                      "RangeLow",
                                      20,
                                      109,
                                      20
                                      ),
    std::make_unique<AudioParameterInt>(
                                    "rangeHigh",
                                    "RangeHigh",
                                    20,
                                    109,
                                    109
                                    ),
    std::make_unique<AudioParameterChoice>("tempo",
                                           "Tempo",
                                           StringArray {
                                            "1/1",
                                            "1/2",
                                            "1/4",
                                            "1/8",
                                            "1/16",
                                            "1/32"},
                                            2)
})
{
    midiProcessor = new MidiProcessor();
    
    
    parameters.addParameterListener("c",        this);
    parameters.addParameterListener("cSharp",   this);
    parameters.addParameterListener("d",        this);
    parameters.addParameterListener("dSharp",   this);
    parameters.addParameterListener("e",        this);
    parameters.addParameterListener("f",        this);
    parameters.addParameterListener("fSharp",   this);
    parameters.addParameterListener("g",        this);
    parameters.addParameterListener("gSharp",   this);
    parameters.addParameterListener("a",        this);
    parameters.addParameterListener("aSharp",   this);
    parameters.addParameterListener("b",        this);
    
    parameters.addParameterListener("start",    this);
    parameters.addParameterListener("rangeHigh",this);
    parameters.addParameterListener("rangeLow", this);
    
    parameters.addParameterListener("tempo",    this);
}

SpitAudioProcessor::~SpitAudioProcessor()
{
}

//==============================================================================
const String SpitAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpitAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SpitAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SpitAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SpitAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpitAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SpitAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpitAudioProcessor::setCurrentProgram (int index)
{
}

const String SpitAudioProcessor::getProgramName (int index)
{
    return {};
}

void SpitAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SpitAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    midiProcessor->prepareToPlay();
    midiProcessor->setBufferSize(samplesPerBlock);
    midiProcessor->setSampleRate(sampleRate);

    
}

void SpitAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void SpitAudioProcessor::parameterChanged(const String &parameterID, float newValue)
{
    
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpitAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SpitAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

    
    buffer.clear();
    midiMessages.clear();
    
    getPlayHead()->getCurrentPosition(mInfo);
    
    midiProcessor->process(midiMessages, mInfo);
    
   
}

//==============================================================================
bool SpitAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SpitAudioProcessor::createEditor()
{
    return new SpitAudioProcessorEditor (*this);
}

//==============================================================================
void SpitAudioProcessor::getStateInformation (MemoryBlock& destData)
{
//    MemoryOutputStream stream(destData, false);
//    parameters.state.writeToStream (stream);
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void SpitAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
//    ValueTree tree = ValueTree::readFromData (data, sizeInBytes);
//    if (tree.isValid())
//    {
//        parameters.state = tree;
//    }
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
 
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

MidiProcessor * SpitAudioProcessor::getMidiProcessor()
{
    return this->midiProcessor;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpitAudioProcessor();
}


