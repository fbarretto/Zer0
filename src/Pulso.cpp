//
//  Pulso.cpp
//  Pulso
//
//  Created by Benoit Espinola on 11/01/14.
//
//

#include "Pulso.h"

Pulso::Pulso(){
    radiusOffset = 10; //initial offset for radius is set here
    radiusLimit = 100; //initial limit of radius is set here
    isActive = true;
    radius = 0;
    speed = 1+ofRandom(1);
    hasColided=false;
}


Pulso::Pulso(ofPoint _position, float _speed, float _radiusLimit, int _color){
    radiusOffset = 10; //initial offset for radius is set here
    radiusLimit = 100; //initial limit of radius is set here
    position = _position;
    speed = _speed;
    isActive = true;
    radius = 0;
    hasColided=false;
    color = _color;
    // std::cout << "started @ " << position.x << "\t" << position.y << "\t" << speed << std::endl;
}

void Pulso::draw(){
    if(isActive) {
        //std::cout << "draw pulse"<<endl;
        //std::cout << int(255*(1-radius/radiusLimit)) << std::endl;
        ofEnableAlphaBlending();    // turn on alpha blending
        ofColor c = ofColor::fromHsb(color,255,255,int(255*(1-radius/radiusLimit)));
        ofSetColor(c);
        ofNoFill();
        ofSetCircleResolution(100);
        ofCircle(position, radius+radiusOffset); // draw circle with radius offset
        ofDisableAlphaBlending();
    }
}

bool Pulso::update(ofPoint _position){
    
    if(isActive) {
        position = _position;
        radius += speed; //increase the radius with the defined speed
        // std::cout << "update pulse " <<radius<< endl;
        isActive = !(radius > radiusLimit);
        //std::cout << "is active"<<endl;
    }
    return isActive;
}

void Pulso::start(ofPoint _position, float _speed){
    if(!isActive){
        position = _position;
        speed = _speed;
        isActive = true;
        //std::cout << "started @ " << position.x << "\t" << position.y << "\t" << speed << std::endl;
    }
}

void Pulso::reset(){
    
    radius = 0; //reset radius here
    
}

void Pulso::colision(){
    isActive=false;
    hasColided=true;
}

bool Pulso::kill(){
    return ((radius > radiusLimit)&& !isActive); // verify if the radius exceedes the limit and is not active
}