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

ofColor lineColor = ofColor(1, 247, 236);
ofPolyline line;

private:
    void restart();


};
