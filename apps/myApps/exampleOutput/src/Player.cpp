//
//  Player.cpp
//  Pulso
//
//  Created by barretto on 12/01/14.
//
//

#include "Player.h"

Player::Player(ofPoint _position) {
    radius = 25;
    radiusLimit = 100;
    radiusOffset=10;
    position = _position;
    //offset;
    baseTime = 10;
    lifespan = 10000;
    color = 100;
    circleResolution = 3;
    score = 0;
    midiNote = 120;
    isActive = true;
    for (int i=0; i<8; i++) {
        pattern[i] = int(ofRandom(50, 150));
    }
    pulseCountdown = pattern[0];
    patternIndex=0;
}

Player::Player() {
    radius = 30;
    radiusLimit = 100;
    radiusOffset=10;
    position = ofPoint(100,100);
    //offset;
    baseTime = 10;
    lifespan = 10000;
    color = 255;
    circleResolution = 3;
    score = 0;
    midiNote = 120;
    isActive = true;
    for (int i=0; i<8; i++) {
        pattern[i] = int(ofRandom(50, 150));
    }
    pulseCountdown = pattern[0];
    patternIndex=0;
}

void Player::draw(){
    //std::cout << lifespan<<endl;
    if(isActive) {
        if (pulsos.size()>0) {
            for(int i = pulsos.size()-1 ; i >=0; i--){
                pulsos[i].draw();
                //std::cout << "draw pulse"<<endl;
            }
            
        }
        ofEnableAlphaBlending();    // turn on alpha blending
        ofSetColor(color,color, color,255); //sets the color to white with alfa relative to radius to radiusLimit ratio
        ofFill();
        ofSetCircleResolution(circleResolution);
        ofCircle(position, radius+radiusOffset); // draw circle with radius offset
        ofDisableAlphaBlending();
        
    }
}

bool Player::update(){
    if(isActive) {
        //        std::cout << "is active"<<endl;
        //radius += speed; //increase the radius with the defined speed
        isActive = !(lifespan < 0);
        
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
            Pulso p = Pulso(position,1, radius*4);
            //            p.start(position,1);
            pulsos.push_back(p);
            //std::cout << "added pulse " << pulsos.size()<<endl;
            patternIndex++;
            if (patternIndex>7) {
                patternIndex=0;
            }
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

void Player::playNote() {
    //cout<<"play note, dude!"<<endl;
}