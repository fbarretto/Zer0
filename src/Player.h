//
//  Individuo.h
//  Pulso
//
//  Created by barretto on 12/01/14.
//
//


#pragma once

#include <iostream>
#include "ofMain.h"
#include <vector>
#include "Pulso.h"
#include "MidiPlayer.h"

class Player{
    public :
    
    Player();
    Player(ofPoint _position);
    void setup();
    void setMidiOut(MidiPlayer *midi);
    void start(ofPoint _position);
    bool update();
    void draw();
    void reset();
    bool kill();
    void generatePulse();
    void playNote(float velocity);
    bool isOffPlayZone();
    bool isOffScreenZone;
    void brownianMove();
    void follow(ofPoint _position);
    
    
    float radius, radiusOffset, radiusLimit, speed, timeOffset;
    ofPoint position, offset;
    int pattern[8];
    int patternIndex;
    int pulseCountdown;
    int baseTime;
    int lifespan;
    int color;
    int circleResolution;
    int score;
    int midiNote;
    std::vector<Pulso> pulsos;
    bool isActive;
    MidiPlayer* myMidi;
    
    
};

