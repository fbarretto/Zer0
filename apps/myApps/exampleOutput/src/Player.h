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

class Player{
    public :
    
    Player();
    Player(ofPoint _position);
    void start(ofPoint _position);
    bool update();
    void draw();
    void reset();
    bool kill();
    void generatePulse();
    void playNote();
    bool isOffPlayZone();
    bool isOffScreenZone;
    void brownianMove();
    void follow(ofPoint _position);

    
    float radius, radiusOffset, radiusLimit, speed;
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
    
    
};

