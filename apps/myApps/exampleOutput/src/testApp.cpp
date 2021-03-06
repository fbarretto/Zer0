#include "testApp.h"
#include "Pulso.h"
#include "Individuo.h"


//--------------------------------------------------------------
void testApp::setup(){
    populationSize = 1;
    for (int i = 0 ; i < populationSize; i++) {
        population.push_back(Individuo());
    }
}

//--------------------------------------------------------------
void testApp::update(){
    //myPulse.update();
    //if(myPulse.kill()){
    //    cout << "Time to kill" << endl;
    //myPulse.reset();
    //}
    player.update();
    //detectPopulationCollisions();
    detectPlayerCollisions();
    
    player.follow(ofPoint(mouseX, mouseY));
    
    if (population.size()<populationSize){
        population.push_back(Individuo());
    }
    
    for(int i = population.size()-1 ; i >= 0; i--){
        if (population[i].kill()) {
            population.erase(population.begin()+i);
        } else {
            population[i].update();
        }
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //myPulse.draw();
    ofBackground(0,0,0);
    
    player.draw();
    
    for(int i = population.size()-1 ; i >= 0; i--){
        population[i].draw();
    }
    
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
    //myPulse.start(ofPoint(x, y), 1);
    //ind.start(ofPoint(x, y));
    population.push_back(Individuo());
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

void testApp::detectPopulationCollisions(){
    /*
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
                            if (!p2->hasColided) {
                                p2 = &ind2->pulsos.at(l);
                                
                                xDif = p1->position.x - p2->position.x;
                                yDif = p1->position.y - p2->position.y;
                                
                                distanceSquared = xDif * xDif + yDif * yDif;
                                collision = (distanceSquared < (p1->radius + p2->radius) * (p1->radius + p2->radius) );
                                
                                if (collision){
                                    ind1->playNote();
                                    ind2->playNote();
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
}

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
                    if (!p2->hasColided) {
                        p2 = &ind2->pulsos.at(l);
                        
                        xDif = p1->position.x - p2->position.x;
                        yDif = p1->position.y - p2->position.y;
                        
                        distanceSquared = xDif * xDif + yDif * yDif;
                        collision = (distanceSquared < (p1->radius + p2->radius) * (p1->radius + p2->radius) );
                        
                        if (collision){
                            ind1->playNote();
                            ind2->playNote();
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
