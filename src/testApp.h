#pragma once

#include "ofMain.h"
#include "Pulso.h"
#include "Individuo.h"
#include "Player.h"
#include "MidiPlayer.h"
#include "ofxLeapMotion.h"





class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void detectPopulationCollisions();
    void detectPlayerCollisions();
    void exit();
    void updateHandInformation();
    
    ofPoint playerDestination;
    Pulso myPulse;
    Player player;
    std::vector<Individuo> population;
    int populationSize;
    int noHandCountdown;
    
    ofTrueTypeFont myfont;
    
    MidiPlayer midi;

    
    ofxLeapMotion leap;
	vector <Hand> simpleHands;
};
