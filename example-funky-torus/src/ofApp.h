#pragma once

#include "ofMain.h"
#include "ofxLathePrimitive.h"



class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

ofxLathePrimitive lathe;
ofEasyCam cam;

ofColor lineColor = ofColor(50, 10, 255);
ofPolyline lineSmall;

private:
    void restart();


};
