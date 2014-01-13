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
    bool update();
    void draw();
    void reset();
    bool kill();
    void generatePulse();
    void playNote(float velocity);
    bool isOffPlayZone();
    bool isOffScreenZone;
    void brownianMove();
    void move();
    
    
    float radius, radiusOffset, radiusLimit, speed;
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
    MidiPlayer* myMidi;
    
};

