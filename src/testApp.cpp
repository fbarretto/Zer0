#include "testApp.h"
#define DESLOCAMENTO_MAX 15
#define DEBUG false


//--------------------------------------------------------------
void testApp::setup(){
    populationSize = 100;
    for (int i = 0 ; i < populationSize; i++) {
        population.push_back(Individuo(&midi));
    }
    player.setMidiOut(&midi);
    ofSetFrameRate(30);
    
    playerDestination=ofPoint(ofGetScreenWidth()/2, ofGetScreenHeight()/2);
    
	leap.open();
}

//--------------------------------------------------------------
void testApp::update(){
    
    updateHandInformation();
    
    player.update();
    detectPopulationCollisions();
    detectPlayerCollisions();
    
    if (simpleHands.size()>0){
        player.follow(playerDestination);
    } else {
        player.follow(ofPoint(0, 0));
    }

    
    if ((population.size()<populationSize) && (ofRandom(1)>0.5) && simpleHands.size()>0){
        population.push_back(Individuo(&midi));
    }
    
    for(int i = population.size()-1 ; i >= 0; i--){
        if (population[i].kill()) {
            population.erase(population.begin()+i);
        } else {
            if (simpleHands.size()>0){
                population[i].update(playerDestination);
            } else {
                if(DEBUG){
                    population[i].update(ofPoint(mouseX, mouseY));
                } else {
                    population[i].update(ofPoint(0, 0));
                }
            }
        }
    }
    
    //cleaning MIDI lost buffer notes
    if (ofGetFrameNum()%2000==0){
        for (int i=0; i<127; i++) {
            midi.stopNote(i, 1, 100);
            midi.stopNote(i, 2, 100);
            cout<<"buffer cleaning"<<endl;
        }
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0,0,0);
    
    for(int i = population.size()-1 ; i >= 0; i--){
        population[i].draw();
    }
    
    player.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    population.push_back(Individuo(&midi));
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}

//Detect collision between population individuals pulses
void testApp::detectPopulationCollisions(){
    /*
     circle collision algorithm
     
     double xDif = x1 - x2;
     double yDif = y1 - y2;
     double distanceSquared = xDif * xDif + yDif * yDif;
     boolean collision = distanceSquared < (radius1 + radius2) * (radius1 + radius2);
     */
    
    Individuo *ind1, *ind2;
    Pulso *p1, *p2;
    double yDif, xDif;
    double distanceSquared;
    bool collision;
    int i,j,k,l;
    
    for(i = population.size()-1 ; i >= 0; i--){
        ind1 = &population[i];
        
        for(j = population.size()-1 ; j >= 0; j--){
            
            if (i!=j) {
                ind2 = &population[j];
                for (k = ind1->pulsos.size()-1; k>=0; k--){
                    
                    p1 = &ind1->pulsos.at(k);
                    if (!p1->hasColided) {
                        for (l = ind2->pulsos.size()-1; l>=0; l--){
                            p2 = &ind2->pulsos.at(l);
                            if (!p2->hasColided) {
                                
                                xDif = p1->position.x - p2->position.x;
                                yDif = p1->position.y - p2->position.y;
                                
                                distanceSquared = xDif * xDif + yDif * yDif;
                                collision = (distanceSquared < (p1->radius + p2->radius) * (p1->radius + p2->radius) );
                                
                                if (collision){
                                    ind1->playNote(float(p1->radius)/float(p1->radiusLimit));
                                    ind2->playNote(float(p2->radius)/float(p2->radiusLimit));
                                    p1->colision();
                                    p2->colision();
                                }
                                collision = false;
                            }
                        }
                    }
                }
                
            }
            
        }
    }
    ind1 = NULL;
    ind2 = NULL;
    p1 = p2 = NULL;
    
}

//Detect collisions between Player pulses and Individuals pulses;
void testApp::detectPlayerCollisions(){
    /*
     double xDif = x1 - x2;
     double yDif = y1 - y2;
     double distanceSquared = xDif * xDif + yDif * yDif;
     boolean collision = distanceSquared < (radius1 + radius2) * (radius1 + radius2);
     */
    
    Player *ind1;
    Individuo *ind2;
    Pulso *p1, *p2;
    double yDif, xDif;
    double distanceSquared;
    bool collision;
    int j,k,l;
    
    
    ind1 = &player;
    
    for(j = population.size()-1 ; j >= 0; j--){
        
        ind2 = &population[j];
        for (k = ind1->pulsos.size()-1; k>=0; k--){
            
            p1 = &ind1->pulsos.at(k);
            if (!p1->hasColided) {
                for (l = ind2->pulsos.size()-1; l>=0; l--){
                    p2 = &ind2->pulsos.at(l);
                    if (!p2->hasColided) {
                        xDif = p1->position.x - p2->position.x;
                        yDif = p1->position.y - p2->position.y;
                        
                        distanceSquared = xDif * xDif + yDif * yDif;
                        collision = (distanceSquared < (p1->radius + p2->radius) * (p1->radius + p2->radius) );
                        
                        if (collision){
                            ind1->playNote(float(p1->radius)/float(p1->radiusLimit));
                            ind2->playNote(float(p2->radius)/float(p2->radiusLimit));
                            p1->colision();
                            p2->colision();
                        }
                        collision = false;
                    }
                }
            }
        }
        
    }
    ind1 = NULL;
    ind2 = NULL;
    p1 = p2 = NULL;
    
}


//--------------------------------------------------------------
void testApp::exit() {
	midi.closePort();
    // let's close down Leap and kill the controller
    leap.close();
    for (int i=0; i<127; i++) {
        midi.stopNote(i, 1, 100);
        midi.stopNote(i, 2, 100);
        cout<<"buffer cleaning"<<endl;
    }
}

void testApp::updateHandInformation() {
    simpleHands = leap.getLeapHands();
    
    if( leap.isFrameNew() && simpleHands.size()>0 ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        for(int i = 0; i < simpleHands.size(); i++){
            Vector hand =  simpleHands[i].direction();
            Vector normalHand = simpleHands[i].palmNormal();
            float pitch, roll;
            pitch = (hand.pitch()/HALF_PI);
            roll = normalHand.roll()/HALF_PI; //Aqui
            
            pitch *= -DESLOCAMENTO_MAX;
            roll *= DESLOCAMENTO_MAX;
            
            //cout << "pitch: "<< pitch << endl;
            //cout << "roll: "<< roll << endl;
            playerDestination.x = roll;
            playerDestination.y = pitch;
        }
    }
    
	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.
	leap.markFrameAsOld();
}
