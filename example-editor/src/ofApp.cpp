#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bgOne = ofColor(37, 203, 206);
    bgTwo = ofFloatColor::yellow;
    lineColor = ofColor(250, 150, 10);
    panel.setup();

    panel.add(lathe.parameters);
    panel.add(editCurve.set("2D view curve editor", false));
    panel.add(debug.set("debug", false));
    panel.add(exportMesh.setup("export mesh to file"));
    panel.add(resetCurve.setup("reset curve"));

    lathe.segments.addListener(this, &ofApp::regenerateInt);
    lathe.phiStart.addListener(this, &ofApp::regenerate);
    lathe.phiLength.addListener(this, &ofApp::regenerate);
    resetCurve.addListener(this, &ofApp::defaultCurve);
    exportMesh.addListener(this, &ofApp::saveMesh);

    defaultCurve();

    auto offset = glm::vec2(curveEditorOffset.x,
                            ofGetHeight()-curveEditorOffset.y);
    path.translate(-offset);
    path.rotateDeg(180, glm::vec2(1,0));

    vector<glm::vec2> updPoints;
    for (auto p:path.getVertices()) {
        updPoints.push_back(glm::vec2(p.x, p.y));
    }

    lathe.points = updPoints;
    lathe.build();
    camera.setDistance(800);

    light.setup();
    light.setAmbientColor(ofColor(250,250,255));
    light.setPosition(600,600,600);
    light.enable();

    material.setSpecularColor(ofFloatColor::azure);
    material.setShininess(1.0);
    material.setAmbientColor(ofFloatColor::orange);
}

//--------------------------------------------------------------
void ofApp::update(){
    path.clear();
    createPath();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(bgOne, bgTwo);
    if (editCurve) {
        camera.disableMouseInput();
        drawAxis();
        drawDraggablePoints();

        ofPushStyle();
        ofSetColor(lineColor);
        path.draw();
        ofPopStyle();
    } else {
        camera.enableMouseInput();
        ofEnableDepthTest();
        camera.begin();
        ofDrawAxis(300);
        ofPushStyle();
        ofSetColor(lineColor);
        if (debug) {
            light.draw();
            material.begin();
            lathe.draw();
            material.end();
        } else {
            lathe.drawWireframe();
            lathe.drawNormals(20, false);
        }
        ofPopStyle();
        
        camera.end();
        ofDisableDepthTest();
    }

    panel.draw();
}

void ofApp::regenerateInt(int &s){
    lathe.build();
}

void ofApp::regenerate(float &s){
    lathe.build();
}

void ofApp::defaultCurve(){
    nCurveVertices = 7;

    curveVertices[0].x = 50 + curveEditorOffset.x;
    curveVertices[0].y = 80 + curveEditorOffset.y;

    curveVertices[1].x = 200 + curveEditorOffset.x;
    curveVertices[1].y = 0 + curveEditorOffset.y;
    curveVertices[2].x = 200 + curveEditorOffset.x;
    curveVertices[2].y = 150 + curveEditorOffset.y;
    curveVertices[3].x = 50 + curveEditorOffset.x;
    curveVertices[3].y = 250 + curveEditorOffset.y;

    curveVertices[4].x = 200 + curveEditorOffset.x;
    curveVertices[4].y = 350 + curveEditorOffset.y;
    curveVertices[5].x = 200 + curveEditorOffset.x;
    curveVertices[5].y = 450 + curveEditorOffset.y;
    curveVertices[6].x = 50 + curveEditorOffset.x;
    curveVertices[6].y = 520 + curveEditorOffset.y;


    for (int i = 0; i < nCurveVertices; i++){
        curveVertices[i].bOver 			= false;
        curveVertices[i].bBeingDragged 	= false;
        curveVertices[i].radius = 8;
    }

    createPath();
}

void ofApp::drawAxis(){
    ofPushStyle();
    ofSetColor(255,0,0);
    ofDrawLine(curveEditorOffset.x , ofGetHeight()-curveEditorOffset.y,
               ofGetWidth(), ofGetHeight()-curveEditorOffset.y);
    ofSetColor(0);
    ofDrawBitmapString("x axis", curveEditorOffset.x ,
                       ofGetHeight()-curveEditorOffset.y+20);
    ofPopStyle();

    ofPushStyle();
    ofSetColor(0,255,0);
    ofDrawLine(curveEditorOffset.x ,ofGetHeight()-curveEditorOffset.y,
               curveEditorOffset.x, 0);
    ofSetColor(0);
    ofDrawBitmapString("rotation axis on y", curveEditorOffset.x-200 ,
                       ofGetHeight()/2);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

void ofApp::drawDraggablePoints(){
    for (int i = 0; i < nCurveVertices; i++){
        auto p1 = curveVertices[i];
        ofPushStyle();
        if (i< 3) {
            ofSetColor(255, 0, 200, 90);
        } else {
            ofSetColor(0, 0, 255, 90);
        }
        ofDrawCircle(p1.x, p1.y, p1.radius);
        if (i < nCurveVertices-1) {
            auto p2 = curveVertices[i+1];
            ofDrawLine(p1.x, p1.y, p2.x, p2.y);
        }
        ofPopStyle();
    }
}

//------------- -------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if(editCurve){
        for (int i = 0; i < nCurveVertices; i++){
            float diffx = x - curveVertices[i].x;
            float diffy = y - curveVertices[i].y;
            float dist = sqrt(diffx*diffx + diffy*diffy);
            if (dist < curveVertices[i].radius){
                curveVertices[i].bOver = true;
            } else {
                curveVertices[i].bOver = false;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(editCurve){
        for (int i = 0; i < nCurveVertices; i++){
            if (curveVertices[i].bBeingDragged == true){
                curveVertices[i].x = x;
                curveVertices[i].y = y;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(editCurve){
        for (int i = 0; i < nCurveVertices; i++){
            float diffx = x - curveVertices[i].x;
            float diffy = y - curveVertices[i].y;
            float dist = sqrt(diffx*diffx + diffy*diffy);
            if (dist < curveVertices[i].radius){
                curveVertices[i].bBeingDragged = true;
            } else {
                curveVertices[i].bBeingDragged = false;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (editCurve) {
        for (int i = 0; i < nCurveVertices; i++) {
            curveVertices[i].bBeingDragged = false;
        }

        auto offset = glm::vec2(curveEditorOffset.x,
                            ofGetHeight()-curveEditorOffset.y);
        path.translate(-offset);
        path.rotateDeg(180, glm::vec2(1,0));

        vector<glm::vec2> updPoints;
        for (auto p:path.getVertices()) {
            updPoints.push_back(glm::vec2(p.x, p.y));
        }

        lathe.points = updPoints;
        lathe.build();
    }

}

void ofApp::createPath(){
    path.addVertex(ofPoint(curveVertices[0].x, curveVertices[0].y));
    path.bezierTo(curveVertices[1].x, curveVertices[1].y,
                  curveVertices[2].x, curveVertices[2].y,
                  curveVertices[3].x, curveVertices[3].y);

    path.bezierTo(curveVertices[4].x, curveVertices[4].y,
                  curveVertices[5].x, curveVertices[5].y,
                  curveVertices[6].x, curveVertices[6].y);
}

void ofApp::saveMesh(){
    string randomFilename = ofGetTimestampString() + ".ply";
    lathe.getMesh().save(randomFilename);
}


//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
