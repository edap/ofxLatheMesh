#pragma once

#include "ofMain.h"
#include "ofxLatheMesh.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        ofxLatheMesh lathe;
        ofLight light;
        ofMaterial material;
        ofEasyCam cam;
        ofxPanel gui;

    ofParameter<bool> stop = {"stop when finished", false};
};
