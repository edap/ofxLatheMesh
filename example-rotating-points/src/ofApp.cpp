#include "ofApp.h"

void ofApp::setup(){
    ofSetBackgroundColor(37, 203, 206);
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
    cam.begin();
    ofPushStyle();
    ofSetColor(yellow);
    lineBig.draw();
    ofSetColor(red);
    lineSmall.draw();
    ofPopStyle();
    cam.end();
}
