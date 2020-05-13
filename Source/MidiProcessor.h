/*
  ==============================================================================

    MidiProcessor.h
    Created: 22 Apr 2020 5:23:49pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <iostream>



class MidiProcessor
{
public:
    MidiProcessor();
    ~MidiProcessor();
    
    void process(MidiBuffer& midiMessages, AudioPlayHead::CurrentPositionInfo& sessionInfo);
    void setSampleRate(int sampleRate);
    void setBufferSize(int bufferSize);
    void prepareToPlay();
    void makeNoteLibrary();
    void updateMidiNotePool();
    void removeNotesFromPool(String noteName);
    void addNotesToPool(String noteName);
    void printNotePool();
    int getNextRandomNumber(int highValue);
    void setIsPlaying(bool value);
    
    void setTempoScaler(float tempoScaler);
    float getTempoScaler();
    
    void updateRange();
    
    void setRange(int low, int high);
    
private:
    int mRandomNumHighValue;
    
    int mSampleRate; // set in prepare to play
    int mBufferSize;
    
    int mCurrentNote;
    int mNextNote;
    
    int mCurrentPlaying;
    int mUpNext;
    int note;
    
    std::unique_ptr<SortedSet<int>> mAvailableMidiNotes;
    std::unique_ptr<SortedSet<int>> mSelectedNotesFullRange;
    std::unique_ptr<std::map<String, int>> mNoteLibrary;
    
    int mTotalSamples;
    int mSamplesPerBeat;
    int mSampleCounter;
 
    int eventTime;
    
    bool mIsPlaying;
    bool mKillNotes;
    
    int mRangeHigh;
    int mRangeLow;
    
    float mTempoScaler = 1.0f;
    int mScaledBPM;
    
    MidiMessage msgOn;
    MidiMessage msgOff;
    
};
