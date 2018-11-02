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

    ofColor red = ofFloatColor::red;
    ofColor yellow = ofFloatColor::yellow;
    ofPolyline lineBig;
    ofPolyline lineSmall;
		
};
