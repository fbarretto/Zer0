//
//  Individuo.cpp
//  Pulso
//
//  Created by barretto on 12/01/14.
//
//

#include "Individuo.h"


Individuo::Individuo(MidiPlayer *midi) {
    myMidi=midi;
    radius = 0;
    radiusLimit = ofRandom(5,25);
    radiusOffset=10;
    position = ofPoint(ofRandom(-ofGetScreenWidth(), ofGetScreenWidth()),ofRandom(-ofGetScreenHeight(), ofGetScreenHeight()));
    baseTime = 10;
    lifespan = ofRandom(600,1200);
    color = ofRandom(0,255);
    circleResolution = int(ofRandom(2,15));
    score = ofRandom(25,100);
    midiNote = ofRandom(50,120);
    isActive = true;
    framecountOffset=ofRandom(-100,100);
    
    for (int i=0; i<8; i++) {
        pattern[i] = int(ofRandom(50, 150));
    }
    
    pulseCountdown = pattern[0];
    patternIndex=0;
    destination.x=position.x+ofRandom(-100,100);
    destination.y=position.y+ofRandom(-100,100);
    timeOffset = ofRandom(1000);
}

void Individuo::draw(){
    
    if(isActive && !isOffScreen) {
        
        //draw pulses, if any
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                pulsos[i].draw();
            }
        }
        
        //draw Individual
        ofEnableAlphaBlending();    // turn on alpha blending
        ofColor c = ofColor::fromHsb(color,255,255,int(255*(lifespan/1000)));
        ofSetColor(c);
        ofFill();
        ofSetCircleResolution(circleResolution);
        ofCircle(position, radius+radiusOffset); // draw circle with radius offset
        ofDisableAlphaBlending();
    }
}

bool Individuo::update(ofPoint _position){
    if(isActive) {
        //reduce radius according to lifespan
        radius -= (lifespan/10000);
        
        //updateOffset for pulsing
        radiusOffset = sin(TWO_PI*((int)(timeOffset+ofGetElapsedTimeMillis())%1000)/1000)*2;
        
        //grow behaviour when first instantiated
        if (radius < radiusLimit) {
            radius +=0.5;
        }
        
        isActive = !(lifespan < 0);
        
        
        //decrease countdown for a new pulse
        pulseCountdown--;
        
        //update pulses if any
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                //remove pulse if dead, update all others
                if (pulsos[i].kill()) {
                    pulsos.erase(pulsos.begin()+i);
                } else {
                    pulsos[i].update(position);
                }
            }
        }
        
        //If it's time for a new pulse, create a new pulse and add to vector. Stop last playing note.
        if (pulseCountdown==0) {
            Pulso p = Pulso(position,1+(lifespan/1000), radius*4, color);
            pulsos.push_back(p);
            myMidi->stopNote(midiNote,1,100);
            
            //get new countdown pattern index;
            patternIndex++;
            if (patternIndex>7) {
                patternIndex=0;
            }
            //set new countdown for a new pulse
            pulseCountdown=pattern[patternIndex];
        }
        
        //move to another position
        move(_position);
        
        //decrease lifespan;
        if (isOffPlayZone) {
            lifespan-=10;
        } else{
            lifespan--;
        }
    }
    
    return isActive;
}


void Individuo::start(ofPoint _position){
    if(!isActive){
        position = _position;
        isActive = true;
        //std::cout << "started @ " << position.x << "\t" << position.y << "\t" << speed << std::endl;
    }
}

void Individuo::move(ofPoint _position){
    if(isActive){
        if ((ofGetFrameNum()+framecountOffset)%100==0) {
            destination.x=position.x+ofRandom(-100,100);
            destination.y=position.y+ofRandom(-100,100);
        }
        
        position.x += (destination.x - position.x)*0.01;
        position.y += (destination.y - position.y)*0.01;
        
        position.x += _position.x;
        position.y += _position.y;
        
        isOffPlayZone = false;
        isOffScreen = false;
        
        if ( (position.x < (-1*ofGetScreenWidth())) || (position.x > (2*ofGetScreenWidth())) ||
            (position.y < (-1*ofGetScreenHeight())) || (position.x > (2*ofGetScreenHeight()))){
            isOffPlayZone = true;
        } 
        
        if ( (position.x < 0) || (position.x > ofGetScreenWidth()) ||
            (position.y < 0) || (position.y > ofGetScreenHeight())){
            isOffScreen = true;
            
        }
        
    }
}

void Individuo::reset(){
    radius = 0; //reset radius here
}

void Individuo::playNote(float velocity) {
    if (!isOffScreen) {
        myMidi->playNote(midiNote,1, velocity*127);
        score++;
        lifespan+=10;
        circleResolution=score/25+2; //increase circle resolution as it scores with interactions
    }
}

bool Individuo::kill(){
    if (!isActive) {
        myMidi->stopNote(midiNote,1,100);
    }
    return (!isActive); // verify if the radius exceedes the limit and is not active
}