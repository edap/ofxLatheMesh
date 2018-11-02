#include "ofApp.h"

void ofApp::setup(){
    bgOne = ofColor(37, 203, 206);
    bgTwo = ofFloatColor::yellow;
}

void ofApp::update(){
    lathe.phiLength += 0.01;
    if (lathe.phiLength >= TWO_PI - 0.01) {
        lathe.phiLength = 0;
        lineSmall.clear();
        lineBig.clear();
    }
    lathe.build();

    for(auto p:lathe.getCurrentRotatingPoints()){
        if (int(lathe.phiLength*10)% 4 == 0) {
            p *= 2.5;
            lineBig.addVertex(p);
        } else {
            lineSmall.addVertex(p);
        }
    }
}

void ofApp::draw(){
    ofBackgroundGradient(bgOne, bgTwo);
    cam.begin();
    ofPushStyle();
    ofSetColor(blue);
    lineBig.draw();
    ofSetColor(red);
    lineSmall.draw();
    ofPopStyle();
    cam.end();
}
