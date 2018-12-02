#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();

    colors.add(diffuseColor.set("diffuse color", ofColor(97, 217, 49), ofColor(0, 0), ofColor(255, 255)));
    colors.add(emissiveColor.set("emissive color", ofColor(213, 31, 19), ofColor(0, 0), ofColor(255, 255)));
    colors.add(lightColor.set("light color", ofColor(83, 255, 161), ofColor(0, 0), ofColor(255, 255)));
    colors.add(bgColor.set("bg color", ofColor(255, 206, 79), ofColor(0, 0), ofColor(255, 255)));
    colors.add(specColor.set("plane color", ofColor(97, 217, 49), ofColor(0, 0), ofColor(255, 255)));
    colors.add(normalColor.set("normal color", ofColor(200, 217, 49), ofColor(0, 0), ofColor(255, 255)));


    panel.add(colors);

    deformationX.setName("deformation X");
    deformationY.setName("deformation Y");
    deformationZ.setName("deformation Z");

    deformationX.add(amplitX.set("amplit X", 1, 0, 170));
    deformationY.add(amplitY.set("amplit Y", 1, 0, 170));
    deformationZ.add(amplitZ.set("amplit Z", 1, 0, 170));
    deformationX.add(freqX.set("freq X", 1, 1, 70));
    deformationY.add(freqY.set("freq Y", 1, 1, 70));
    deformationZ.add(freqZ.set("freq Z", 1, 1, 70));

    panel.add(deformationX);
    panel.add(deformationY);
    panel.add(deformationZ);
    panel.add(deformOnAngle.set("deform based on angle", true));

    panel.add(amplitScale.set("amplitScale", 1, 1, 10.));
    panel.add(freqScale.set("freqScale", 1, 0.01, 3.));
    panel.add(applyScale.set("applyScale", false));
    panel.add(resetScale.setup("resetScale"));

    lathe.parameters.setName("lathe params");
    panel.add(lathe.parameters);
    panel.add(rotatingPointsSample.set("rotating sample", 5, 1, 10));
    panel.add(drawNormal.set("draw normal", false));
    panel.add(drawFaces.set("draw faces", false));
    panel.add(drawRotatingPoints.set("draw rotating points", false));
    panel.add(animate.set("animate", false));

    lathe.segments.addListener(this, &ofApp::regenerateInt);
    lathe.phiStart.addListener(this, &ofApp::regenerate);
    lathe.phiLength.addListener(this, &ofApp::regenerate);
    lathe.flipNormals.addListener(this, &ofApp::regenerateBool);

    amplitX.addListener(this, &ofApp::updateOffset);
    amplitY.addListener(this, &ofApp::updateOffset);
    amplitZ.addListener(this, &ofApp::updateOffset);

    freqX.addListener(this, &ofApp::updateOffset);
    freqY.addListener(this, &ofApp::updateOffset);
    freqZ.addListener(this, &ofApp::updateOffset);

    freqScale.addListener(this, &ofApp::updateScale);
    amplitScale.addListener(this, &ofApp::updateScale);
    resetScale.addListener(this, &ofApp::restoreScale);

    lineColor = ofColor(250, 150, 10);


    vector<glm::vec2> points;
//    for ( int i = 0; i < 12; i ++ ) {
//        points.push_back( glm::vec2( sin( i * 0.2 ) * 100 + 5, ( i + 2) * 20 ) );
//    }
    points.push_back(glm::vec2(96,251));
    points.push_back(glm::vec2(151.721,300.454));
    points.push_back(glm::vec2(198.354,340.636));
    points.push_back(glm::vec2(236.458,372.172));
    points.push_back(glm::vec2(266.592,395.688));
    points.push_back(glm::vec2(289.312,411.812));
    points.push_back(glm::vec2(305.178,421.172));
    points.push_back(glm::vec2(314.747,424.394));
    points.push_back(glm::vec2(318.576,422.104));
    points.push_back(glm::vec2(317.224,414.93));
    points.push_back(glm::vec2(311.25,403.5));
    points.push_back(glm::vec2(301.211,388.439));
    points.push_back(glm::vec2(287.664,370.376));
    points.push_back(glm::vec2(271.169,349.937));
    points.push_back(glm::vec2(252.282,327.748));
    points.push_back(glm::vec2(231.562,304.438));
    points.push_back(glm::vec2(209.568,280.632));
    points.push_back(glm::vec2(186.857,256.958));
    points.push_back(glm::vec2(163.986,234.044));
    points.push_back(glm::vec2(141.514,212.515));
    points.push_back(glm::vec2(120,193));
    points.push_back(glm::vec2(133.74,181.371));
    points.push_back(glm::vec2(143.401,170.71));
    points.push_back(glm::vec2(149.343,160.904));
    points.push_back(glm::vec2(151.928,151.84));
    points.push_back(glm::vec2(151.516,143.406));
    points.push_back(glm::vec2(148.467,135.49));
    points.push_back(glm::vec2(143.143,127.979));
    points.push_back(glm::vec2(135.904,120.76));
    points.push_back(glm::vec2(127.111,113.721));
    points.push_back(glm::vec2(117.125,106.75));
    points.push_back(glm::vec2(106.306,99.7338));
    points.push_back(glm::vec2(95.016,92.56));
    points.push_back(glm::vec2(83.6146,85.1162));
    points.push_back(glm::vec2(72.463,77.29));
    points.push_back(glm::vec2(61.9219,68.9688));
    points.push_back(glm::vec2(52.352,60.04));
    points.push_back(glm::vec2(44.1141,50.3912));
    points.push_back(glm::vec2(37.569,39.91));
    points.push_back(glm::vec2(33.0774,28.4838));
    points.push_back(glm::vec2(31,16));
    lathe.setPoints(points);

    lathe.computeColor = [points](float angle, int segmentIter, int pointIter) {
        auto totPoints = points.size();
        float amp = sin(angle) * 10.0;
        float hue = ofMap(sin(pointIter*amp), -1, 1, 125, 200);
        //float hue = ofMap(sin(pointIter* 4.0), 0, totPoints-1, 0, 255);
        return ofColor().fromHsb(hue, 255, 255);
    };
    lathe.segments = 200;
    lathe.build();
    lathe.setParent(parent);

    light.setup();
    light.setDirectional();
    light.setAmbientColor(lightColor.get());
    light.setSpotlight();
    light.setPosition(800,800,800);
    light.enable();

    material.setShininess(1.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    freqScale+= 0.005;
    //parent.rotateRad(0.003, glm::vec3(0,1,0));
    light.setAmbientColor(lightColor.get());
    material.setDiffuseColor(diffuseColor.get());
    material.setEmissiveColor(emissiveColor.get());
    material.setSpecularColor(specColor.get());
    ofSetBackgroundColor(ofColor(bgColor));

    if (animate) {
        lathe.phiLength.set(ofMap(sin(ofGetElapsedTimef()),-1,1,0,TWO_PI));
        if (applyScale) {
            lathe.setScale(ofMap(sin(ofGetElapsedTimef()),-1,1,1,3));
        }

        lathe.build();
    }
    if (freqScale >= 3.0) {
        freqScale = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    camera.begin();
    if (drawGui) {
        ofDrawAxis(300);
        light.draw();
        parent.draw();
    }

    if (drawFaces) {
        material.begin();
        lathe.draw();
        material.end();
    } else {
        lathe.drawWireframe();
    }
    if (drawRotatingPoints) {
        ofPushStyle();
        ofSetColor(normalColor);
        drawRotating();
        ofPopStyle();
    } else {
        lathe.drawWireframe();
    }
    if(drawNormal){
        ofPushStyle();
        ofSetColor(normalColor);
        lathe.drawNormals(20, false);
        ofPopStyle();
    }

    camera.end();
    ofDisableDepthTest();
    if (drawGui) {
        panel.draw();
    }
}

void ofApp::drawRotating(){
    for(int i = 0; i < lathe.getCurrentRotatingPoints().size()-1; i++){
        if(i%rotatingPointsSample == 0){
            ofDrawSphere(lathe.getCurrentRotatingPoints().at(i), 5);
        }
    }
}

void ofApp::regenerateInt(int &s){
    lathe.build();
}

void ofApp::regenerateBool(bool &s){
    lathe.build();
}

void ofApp::regenerate(float &s){
    lathe.build();
}
void ofApp::restoreScale(){
    lathe.editPoint = nullptr;
    lathe.build();
}

void ofApp::updateScale(float &v){
    float freq = freqScale.get();
    float amp = amplitScale.get();
    if (applyScale) {
//        lathe.editPoint = [amp, freq](const vector<glm::vec2> p, float angle, int segmentIndex, int pointIndex) {
//            auto p = points.at(pointIndex);
//            return p * sin(angle*freq) * amp;
//        };
    }
    lathe.build();
};

void ofApp::updateOffset(float &v){
    float frqX = freqX.get();
    float ampX = amplitX.get();
    float frqY = freqY.get();
    float ampY = amplitY.get();
    float frqZ = freqZ.get();
    float ampZ = amplitZ.get();

    if (deformOnAngle) {
        lathe.addOffset = [ampX, frqX, ampY, frqY, ampZ, frqZ](float angle, int segmentIndex, int pointIndex) {
            auto x = sin(angle*frqX) * ampX;
            auto y = sin(angle*frqY) * ampY;
            auto z = sin(angle*frqZ) * ampZ;
            return glm::vec3(x,y,z);
        };
    } else {
        lathe.addOffset = [ampX, frqX, ampY, frqY, ampZ, frqZ](float angle, int segmentIter, int pointIndex) {
            auto x = sin(segmentIter*frqX) * ampX;
            auto y = sin(segmentIter*frqY) * ampY;
            auto z = sin(segmentIter*frqZ) * ampZ;
            return glm::vec3(x,y,z);
        };
    }
    lathe.build();
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g') {
        drawGui = !drawGui;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
