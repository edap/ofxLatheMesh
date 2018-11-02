#pragma once

#include "ofMain.h"
#include "ofxLathePrimitive.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    ofxLathePrimitive lathe;
    ofEasyCam cam;

    ofColor red = ofColor(255, 206, 79);
    ofColor blue = ofColor(59,159,255);
    ofPolyline lineBig;
    ofPolyline lineSmall;

    ofColor bgOne;
    ofColor bgTwo;

};
