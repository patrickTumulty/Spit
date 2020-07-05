/*
  ==============================================================================

    MidiProcessor.cpp
    Created: 22 Apr 2020 5:23:49pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#include "MidiProcessor.h"


MidiProcessor::MidiProcessor()
{
    this->mAvailableMidiNotes = std::make_unique<SortedSet<int>>();
    this->mSelectedNotesFullRange = std::make_unique<SortedSet<int>>();
    this->mNoteLibrary = std::make_unique<std::map<String, int>>();
    this->mRandomNumHighValue = 0;
    this->mUpNext = 0;
    this->mCurrentPlaying = 0;
    this->makeNoteLibrary();
    this->mIsPlaying = false;
    this->mKillNotes = false;
    this->mRangeLow = 20;
    this->mRangeHigh = 109;
}

MidiProcessor::~MidiProcessor()
{
   
    
}

void MidiProcessor::printNotePool() // for debugging
{
    DBG(" >");
    for (int i = 0; i < this->mAvailableMidiNotes->size(); i++)
    {
        DBG(this->mAvailableMidiNotes->getReference(i));
    }
    DBG("\n");
}

void MidiProcessor::process(MidiBuffer &midiMessages, AudioPlayHead::CurrentPositionInfo &sessionInfo)
{
    mSamplesPerBeat = (60.0 / (sessionInfo.bpm * this->getTempoScaler())) * mSampleRate;
    mSampleCounter = sessionInfo.timeInSamples % (mSamplesPerBeat);
    
    eventTime = mSampleCounter % mBufferSize;
    if (mIsPlaying)
    {
        this->mKillNotes = true;
        if ((mSampleCounter + mBufferSize) >= mSamplesPerBeat)
        {
            this->mRandomNumHighValue = this->mAvailableMidiNotes->size();
            if (this->mRandomNumHighValue != 0)
            {
                this->note = this->mAvailableMidiNotes->getReference(this->getNextRandomNumber(this->mRandomNumHighValue-1));
                this->mCurrentPlaying = this->mUpNext;
                this->mUpNext = note;
                if (mCurrentPlaying != 0) { msgOff = MidiMessage::noteOff(1, mCurrentPlaying); }
                msgOn = MidiMessage::noteOn(1, mUpNext, (uint8)100);
                midiMessages.addEvent(msgOff, eventTime);
                midiMessages.addEvent(msgOn, eventTime);
            }
        }
    }
    else
    {
        if (this->mKillNotes)
        {
            msgOff = MidiMessage::noteOff(1, mUpNext);
            midiMessages.addEvent(msgOff, eventTime);
            this->mKillNotes = false;
        }
    }
}

int MidiProcessor::getNextRandomNumber(int highValue)
{
    return Random::getSystemRandom().nextInt(highValue);
}

void MidiProcessor::makeNoteLibrary()
{
    
    this->mNoteLibrary->insert(std::pair<String, int>("A",  21));
    this->mNoteLibrary->insert(std::pair<String, int>("A#", 22));
    this->mNoteLibrary->insert(std::pair<String, int>("B",  23));
    this->mNoteLibrary->insert(std::pair<String, int>("C",  24));
    this->mNoteLibrary->insert(std::pair<String, int>("C#", 25));
    this->mNoteLibrary->insert(std::pair<String, int>("D",  26));
    this->mNoteLibrary->insert(std::pair<String, int>("D#", 27));
    this->mNoteLibrary->insert(std::pair<String, int>("E",  28));
    this->mNoteLibrary->insert(std::pair<String, int>("F",  29));
    this->mNoteLibrary->insert(std::pair<String, int>("F#", 30));
    this->mNoteLibrary->insert(std::pair<String, int>("G",  31));
    this->mNoteLibrary->insert(std::pair<String, int>("G#", 32));

}

void MidiProcessor::updateMidiNotePool()
{
    
}

void MidiProcessor::addNotesToPool(String noteName)
{
    int current_note_value = this->mNoteLibrary->at(noteName);
    while(current_note_value < 109)
    {
        this->mAvailableMidiNotes->add(current_note_value);
        this->mSelectedNotesFullRange->add(current_note_value);
        current_note_value += 12;
    }
}

void MidiProcessor::removeNotesFromPool(String noteName)
{
    int current_note_value = this->mNoteLibrary->at(noteName);
    while(current_note_value < 109)
    {
        this->mAvailableMidiNotes->removeValue(current_note_value);
        this->mSelectedNotesFullRange->add(current_note_value);
        current_note_value += 12;
    }
}

void MidiProcessor::prepareToPlay()
{
    this->mNextNote = 50;
    this->mCurrentNote = 50;
}

void MidiProcessor::setSampleRate(int sampleRate)
{
    this->mSampleRate = sampleRate;
}

void MidiProcessor::setBufferSize(int bufferSize)
{
    this->mBufferSize = bufferSize;
}

void MidiProcessor::setIsPlaying(bool value)
{
    this->mIsPlaying = value;
}

void MidiProcessor::updateRange()
{
    int currentNote;
    
    for (int i = 0; i < this->mSelectedNotesFullRange->size(); i++)
    {
        currentNote = this->mSelectedNotesFullRange->getReference(i);
        
        if (this->mRangeLow <= this->mRangeHigh)
        {
            if (currentNote <= this->mRangeLow || currentNote > this->mRangeHigh)
            {
                if (this->mAvailableMidiNotes->contains(currentNote))
                {
                    this->mAvailableMidiNotes->removeValue(currentNote);
                }
            }
            else
            {
                if (this->mAvailableMidiNotes->contains(currentNote) == false)
                {
                    this->mAvailableMidiNotes->add(currentNote);
                }
            }
        }
        else if (this->mRangeLow > this->mRangeHigh)
        {
            if (currentNote <= this->mRangeHigh || currentNote > this->mRangeLow)
            {
                if (this->mAvailableMidiNotes->contains(currentNote) == false)
                {
                    this->mAvailableMidiNotes->add(currentNote);
                }
            }
            else
            {
                if (this->mAvailableMidiNotes->contains(currentNote))
                {
                    this->mAvailableMidiNotes->removeValue(currentNote);
                }
            }
        }
    }
}

void MidiProcessor::setRange(int low, int high)
{
    this->mRangeLow = low;
    this->mRangeHigh = high;
}

void MidiProcessor::setTempoScaler(float tempoScaler)
{
    this->mTempoScaler = tempoScaler;
}

float MidiProcessor::getTempoScaler()
{
    return this->mTempoScaler;
}




