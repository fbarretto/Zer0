//
//  Pulso.h
//  Pulso
//
//  Created by Benoit Espinola on 11/01/14.
//
//

//#ifndef __Pulso__Pulso__
//#define __Pulso__Pulso__

#pragma once

#include <iostream>
#include "ofMain.h"


class Pulso{
    public :
    
    Pulso();
    Pulso(ofPoint _position, float _speed, float _radiusLimit, int color);
    void start(ofPoint _position, float _speed);
    bool update(ofPoint _position);
    void draw();
    void reset();
    void colision();
    
    bool kill();
    
    float radius, radiusOffset, radiusLimit, speed;
    ofPoint position;
    bool isActive;
    bool hasColided;
    int color;
    
};


//#endif /* defined(__Pulso__Pulso__) */
