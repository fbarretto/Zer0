//
//  Player.cpp
//  Pulso
//
//  Created by barretto on 12/01/14.
//
//

#include "Player.h"

Player::Player(ofPoint _position) {
    position = _position;
    setup();
}

Player::Player() {
    setup();
}

void Player::setup(){
    radius = 30;
    radiusLimit = 100;
    radiusOffset=10;
    //offset;
    baseTime = 10;
    lifespan = 10000;
    color = 255;
    score = 0;
    circleResolution=int(score/25)+2;
    midiNote = 120;
    isActive = true;
    for (int i=0; i<8; i++) {
        pattern[i] = int(ofRandom(50, 150));
    }
    pulseCountdown = pattern[0];
    patternIndex=0;
    timeOffset = ofRandom(1000);
    position = ofPoint(ofGetScreenWidth()/2, ofGetScreenHeight()/2);
}

void Player::draw(){
 
    if(isActive) {
        //draw pulses, if any
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                pulsos[i].draw();
            }
        }
        
       
        ofEnableAlphaBlending();    // turn on alpha blending
        
        ofFill();
        ofSetColor(color,color, color,50); //sets the color to white
        ofSetCircleResolution(500);
        ofCircle(position, radius*2); // draw circle with radius offset
        
        //if player has less than 3 sides, it's a line. Therefore, it has no fill, only a stroke;
        if (circleResolution<3){
            ofSetLineWidth(2);
            ofNoFill();
        } else {
            ofSetLineWidth(0);
            ofFill();
        }

        ofSetColor(color,color, color,255); //sets the color to white
        ofSetCircleResolution(circleResolution);
        ofCircle(position, radius+radiusOffset); // draw circle with radius offset
        ofDisableAlphaBlending();
        ofSetLineWidth(1);
        
    }
}

bool Player::update(){
    if(isActive) {
  
        isActive = !(lifespan < 0);
        
        radiusOffset = sin(TWO_PI*((int)(timeOffset+ofGetElapsedTimeMillis())%1000)/1000)*5;
        
        //Countdown to generate a new pulse;
        pulseCountdown--;
  
        //update pulses, if any
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                //remove dead pulses and update all others;
                if (pulsos[i].kill()) {
                    pulsos.erase(pulsos.begin()+i);
                } else {
                    pulsos[i].update(position);
                }
            }
        }
        
        //If it's time for a new pulse, create a new pulse and add to vector. Stop last playing note.
        if (pulseCountdown==0) {
            Pulso p = Pulso(position,1+(score/100), radius*4, color);
            pulsos.push_back(p);
            myMidi->stopNote(midiNote,2,100);
            //get new countdown pattern index;
            patternIndex++;
            if (patternIndex>7) {
                patternIndex=0;
            }
            //update countdown
            pulseCountdown=pattern[patternIndex];
        }
        
        //lifespan--;
        
        if (lifespan<0)
            std::cout << "dead!" <<endl;
    }
    
    return isActive;
}

void Player::start(ofPoint _position){
    if(!isActive){
        position = _position;
        isActive = true;
        //std::cout << "started @ " << position.x << "\t" << position.y << "\t" << speed << std::endl;
    }
}

//follow behaviour
void Player::follow(ofPoint _position){
    if(isActive){
        position.x += (_position.x - position.x)*0.1;
        position.y += (_position.y - position.y)*0.1;
    }
}

void Player::reset(){
    radius = 0; //reset radius here
}

bool Player::kill(){
    return isActive;
}

//velocity normalized [0-1]
void Player::playNote(float velocity) {
    myMidi->playNote(midiNote,2, velocity*127);
    score++;
    circleResolution=int(score/25)+2;
}

//grab a midi player instance reference to play and stop midi notes
void Player::setMidiOut(MidiPlayer *midi) {
    myMidi=midi;
}