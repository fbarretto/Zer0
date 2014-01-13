//
//  MidiPlayer.h
//  Pulso
//
//  Created by barretto on 12/01/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class MidiPlayer{
public:
    MidiPlayer();
    
    
    void playNote(int note, int _channel, int _velocity);
    void stopNote(int note, int _channel, int _velocity);
    void closePort();
    
    ofxMidiOut midiOut;
	int channel;
	
	unsigned int currentPgm;
	int note, velocity;
	int pan, bend, touch, polytouch;
    int noteCount;
};