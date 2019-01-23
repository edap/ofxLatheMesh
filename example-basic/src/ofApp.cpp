#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    light.setAmbientColor(ofFloatColor::orange);
    light.setup();
    light.setPosition(200,200,200);
    light.enable();

    material.setAmbientColor(ofFloatColor::violet);

    gui.setup();
    gui.add(lathe.parameters);

// By default, ofxLathe already create some points. if you want to
// customize it, use setPoints.
//    vector<glm::vec2> points;
//    for (unsigned int i = 1; i < 100; i ++) {
//        float y = sin(i) /i+1;
//        points.push_back( glm::vec2( i*1.5, 40 - y*80 ));
//    }
//    lathe.setPoints(points);

    lathe.segments = 20;
    lathe.phiLength = TWO_PI/2;

}

//--------------------------------------------------------------
void ofApp::update(){
        lathe.clear();
        lathe.build();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofFloatColor::azure, ofFloatColor::aquamarine);
    ofEnableDepthTest();
    cam.begin();
    material.begin();

    lathe.mesh.draw();
    material.end();
    cam.end();
    ofDisableDepthTest();
    gui.draw();
}
