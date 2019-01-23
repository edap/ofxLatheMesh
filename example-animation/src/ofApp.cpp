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
    gui.add(deltaTime);

    // By default, ofxLathe already create some points. if you want to
    // customize it, use setPoints.
    vector<glm::vec2> points;
    for (unsigned int i = 1; i < 100; i ++) {
        float y = sin(i) /i+1;
        points.push_back( glm::vec2( i*2, 40 - y*40 ));
    }
    lathe.setPoints(points);
    lathe.segments = 20;
    lathe.phiLength = 0.1;

    lathe.computeColor = [points](float angle, int segmentIter, int pointIter) {
        auto totPoints = points.size();
        float amp = sin(angle) * 10.0;
        float hue = ofMap(sin(pointIter)* totPoints, 0, totPoints-1, 0, 255);
        return ofColor().fromHsb(hue, 255, 255);
    };

    float Yamp = 60.0f;
    float YFreq = 2;
    lathe.addOffset = [Yamp, YFreq](float angle, int segmentIndex, int pointIndex) {
        auto y = sin(angle*YFreq) * Yamp;
        return glm::vec3(0,y,0);
    };
}

//--------------------------------------------------------------
void ofApp::update(){
    actualTime = ofGetElapsedTimeMillis();
    if (actualTime - sucessTimer > deltaTime) {
        if(lathe.phiLength >=TWO_PI){
            lathe.phiLength = 0.0f;
        }else{
            lathe.phiLength = lathe.phiLength+0.05;
        }
        lathe.segments = 20 * lathe.phiLength;
        sucessTimer = actualTime;
        lathe.clear();
        lathe.build();
    }
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
