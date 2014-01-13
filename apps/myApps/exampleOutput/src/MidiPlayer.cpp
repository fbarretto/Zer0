//
//  MidiPlayer.cpp
//  Pulso
//
//  Created by barretto on 12/01/14.
//
//

#include "MidiPlayer.h"

MidiPlayer::MidiPlayer() {
    midiOut.listPorts(); // via instance
    midiOut.openPort(0);	// by number
    channel = 1;
	currentPgm = 0;
	note = 0;
	velocity = 0;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;
    noteCount=0;
}

void MidiPlayer::playNote(int _note) {
    note = _note;
    velocity = ofRandom(127);
    midiOut.sendNoteOn(channel, note,  velocity);
    
    cout<<"note on! "<<noteCount<<endl;
    noteCount++;
}

void MidiPlayer::stopNote(int _note) {
    note = _note;
    velocity = ofRandom(127);
    midiOut.sendNoteOff(channel, note,  velocity);
    
    noteCount--;
    cout<<"note off! "<<noteCount<<endl;

}

