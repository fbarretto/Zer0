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


class Individuo{
    public :
    
    Individuo();
    Individuo(MidiPlayer *midi);
    Individuo(ofPoint _position);
    void start(ofPoint _position);
    bool update(ofPoint _position);
    void draw();
    void reset();
    bool kill();
    void generatePulse();
    void playNote(float velocity);
    void move(ofPoint _position);
    
    
    float radius, radiusOffset, radiusLimit, speed,timeOffset;
    ofPoint position, offset, destination;
    int framecountOffset;
    int pattern[8];
    int patternIndex;
    int pulseCountdown;
    int baseTime;
    float lifespan;
    int color;
    int circleResolution;
    int score;
    int midiNote;
    std::vector<Pulso> pulsos;
    bool isActive;
    bool isOffScreen;
    bool isOffPlayZone;
    MidiPlayer* myMidi;
    
};

