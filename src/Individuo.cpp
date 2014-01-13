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
    position = ofPoint(ofRandomWidth(),ofRandomHeight());
    //offset;
    baseTime = 10;
    lifespan = ofRandom(700,1200);
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
    // destination=ofPoint(ofRandomWidth(), ofRandomHeight());
    destination.x=position.x+ofRandom(-100,100);
    destination.y=position.y+ofRandom(-100,100);
}

void Individuo::draw(){
    //std::cout << lifespan<<endl;
    if(isActive) {
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                pulsos[i].draw();
                //std::cout << "draw pulse"<<endl;
            }
            
        }
        ofEnableAlphaBlending();    // turn on alpha blending
        ofColor c = ofColor::fromHsb(color,255,255,int(255*(lifespan/1000)));
        ofSetColor(c);
        ofFill();
        ofSetCircleResolution(circleResolution);
        ofCircle(position, radius+radiusOffset); // draw circle with radius offset
        ofDisableAlphaBlending();
    }
}

bool Individuo::update(){
    if(isActive) {
        //        std::cout << "is active"<<endl;
        radius -= (lifespan/10000);
        if (radius < radiusLimit) {
            radius +=0.5;
        }
        
        isActive = !(lifespan < 0);
        
        //position.x += (ofRandomWidth() - position.x)*0.1;
        //position.y += (ofRandomHeight() - position.y)*0.1;
        
        
        pulseCountdown--;
        //std::cout << "countdown " << pulseCountdown<<endl;
        //std::cout << "pulses " << pulsos.size()<<endl;
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                if (pulsos[i].kill()) {
                    pulsos.erase(pulsos.begin()+i);
                    //std::cout << "dead pulse " << pulsos.size()<<endl;
                } else {
                    pulsos[i].update(position);
                    //                    std::cout << "update pulse " << pulsos.size()<<endl;
                }
            }
        }
        
        if (pulseCountdown==0) {
            Pulso p = Pulso(position,1+(lifespan/1000), radius*4, color);
            //            p.start(position,1);
            pulsos.push_back(p);
                myMidi->stopNote(midiNote,1,100);
         //   MidiPlayer::stopNote(midiNote);
            //std::cout << "added pulse " << pulsos.size()<<endl;
            patternIndex++;
            if (patternIndex>7) {
                patternIndex=0;
            }
            pulseCountdown=pattern[patternIndex];
        }
        move();
        lifespan--;
        //if (lifespan<0)
        //std::cout << "dead!" <<endl;
        
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

void Individuo::move(){
    if(isActive){
        if ((ofGetFrameNum()+framecountOffset)%100==0) {
            destination.x=position.x+ofRandom(-100,100);
            destination.y=position.y+ofRandom(-100,100);
        }
        
        position.x += (destination.x - position.x)*0.01;
        position.y += (destination.y - position.y)*0.01;
    }
}

void Individuo::reset(){
    
    radius = 0; //reset radius here
    
}

void Individuo::playNote(float velocity) {
    //cout<<"play note, dude!"<<endl;
  //  MidiPlayer::playNote(midiNote);
    myMidi->playNote(midiNote,1, velocity*127);
    score++;
    lifespan+=10;
    circleResolution=score/25+2;
}

bool Individuo::kill(){
    //cout<<isActive<<endl;
    return (!isActive); // verify if the radius exceedes the limit and is not active
}