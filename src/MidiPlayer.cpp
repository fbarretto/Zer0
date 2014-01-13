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
}

void MidiPlayer::playNote(int _note, int _channel, int _velocity) {
    int velocity = ofRandom(127);
    midiOut.sendNoteOn(_channel, _note,  velocity);
    //cout<<"midi note on "<<_channel<<endl;
}

void MidiPlayer::stopNote(int _note, int _channel, int _velocity) {
    
    int velocity = ofRandom(127);
    midiOut.sendNoteOff(_channel, _note,  velocity);
    //cout<<"midi note off"<<endl;
}

void MidiPlayer::closePort(){
    midiOut.closePort();
}

