#include "ofApp.h"

void ofApp::setup(){
    ofSetBackgroundColor(255, 206, 79);
    vector<glm::vec2> points;
    float radius = 40;
    glm::vec2 offset = glm::vec2(80., 10.);
    for (float a = 0; a < TWO_PI; a += 0.1) {
        float x = offset.x + cos(a) * radius;
        float y = offset.y + sin(a) * radius;
        points.push_back(glm::vec2(x,y));
    }
    lathe.setPoints(points);
    int totPoints = points.size();

    lathe.editPoint = [offset](const vector<glm::vec2> points, float angle, int segIndex, int pointIndex){
        auto point = points.at(pointIndex);
        glm::vec2 newPoint;

        float a = ofMap(pointIndex, 0, points.size()-1, 0, TWO_PI);
        float rad = abs(sin(ofGetElapsedTimef()* 3.0)) * 20 + 10;
        newPoint.x = point.x + cos(a) * rad + offset.x;
        newPoint.y = point.y + sin(a) * rad + offset.y;

        return newPoint;
    };

    lathe.segments = 160;
    lathe.phiLength = 0;
    lathe.closed = true;
    lathe.build();
}

void ofApp::update(){
    if (lathe.phiLength >= TWO_PI - 0.1) {
        restart();
    } else {

        lathe.phiLength += 0.01;
        //auto nSeg = int(ofMap(lathe.phiLength, 60, 160, 0, TWO_PI));
        //lathe.segments =nSeg;
        lathe.build();
        for(auto p:lathe.getCurrentRotatingPoints()){
            line.addVertex(p);
        }
    }
}

void ofApp::draw(){
    cam.begin();
    ofPushStyle();

    ofSetColor(lineColor);
    line.draw();
    ofPopStyle();
    cam.end();

    ofDrawBitmapString("press a,s,d,e to change the torus", 10, 10);
}

void ofApp::keyPressed(int key){
    if(key == 'a'){
        restart();
        glm::vec2 offset = glm::vec2(80., 10.);

        lathe.editPoint = [offset](const vector<glm::vec2> points, float angle, int segIndex, int pointIndex){
            auto point = points.at(pointIndex);
            glm::vec2 newPoint;

            newPoint.x = point.x * cos(angle*4) * 0.3 + offset.x;
            newPoint.y = point.y * sin(angle*2) * 0.3 + offset.y;

            return newPoint;
        };
        lathe.build();

    }

    if(key == 's'){
        restart();
        glm::vec2 offset = glm::vec2(80., 10.);

        lathe.editPoint = [offset](const vector<glm::vec2> points, float angle, int segIndex, int pointIndex){
            auto point = points.at(pointIndex);
            glm::vec2 newPoint;

            newPoint.x = point.x * cos(angle*2) * 0.3 + offset.x;
            newPoint.y = point.y * sin(angle*2) * 0.3 + offset.y;

            return newPoint;
        };
        lathe.build();

    }

    if(key == 'd'){
        restart();
        lathe.editPoint = [](const vector<glm::vec2> points, float angle, int segIndex, int pointIndex){
            auto point = points.at(pointIndex);
            glm::vec2 newPoint;

            float a = ofMap(pointIndex, 0, points.size()-1, 0, TWO_PI);
            float rad = abs(sin(ofGetElapsedTimef())) * 20 + 10;
            newPoint.x = point.x + sin(a) * rad;
            newPoint.y = point.y + cos(a) * rad;

            return newPoint;
        };
        lathe.build();
    }

    if(key == 'f'){
        restart();
        glm::vec2 offset = glm::vec2(80., 10.);
        lathe.editPoint = [offset](const vector<glm::vec2> points, float angle, int segIndex, int pointIndex){
            auto point = points.at(pointIndex);
            glm::vec2 newPoint;

            float a = ofMap(pointIndex, 0, points.size()-1, 0, TWO_PI);
            float rad = abs(sin(ofGetElapsedTimef()*2) * 3) + 10;
            newPoint.x = point.x + sin(a) * rad + offset.x;
            newPoint.y = point.y + cos(a) * rad + offset.y;

            return newPoint;
        };
        lathe.build();
    }

    if(key == 'g'){
        restart();
        glm::vec2 offset = glm::vec2(80., 10.);

        lathe.editPoint = [offset](const vector<glm::vec2> points, float angle, int segIndex, int pointIndex){
            auto point = points.at(pointIndex);
            glm::vec2 newPoint;

            float a = ofMap(pointIndex, 0, points.size()-1, 0, TWO_PI);
            float rad = abs(sin(ofGetElapsedTimef()* 3.0)) * 20 + 10;
            newPoint.x = point.x + cos(a) * rad + offset.x;
            newPoint.y = point.y + sin(a) * rad + offset.y;

            return newPoint;
        };
        lathe.build();
    }
}

void ofApp::restart(){
    lathe.phiLength = 0;
    line.clear();
}
