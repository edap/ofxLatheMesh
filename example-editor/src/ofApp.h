#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxLathePrimitive.h"

typedef struct {
    float 	x;
    float 	y;
    bool 	bBeingDragged;
    bool 	bOver;
    float 	radius;

}draggableVertex;

class ofApp : public ofBaseApp{
//http://paulbourke.net/dataformats/pov37/t2_3.html
public:
    void setup();
    void update();
    void draw();
    void drawAxis();
    void regenerateInt(int &s);
    void regenerate(float &s);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void saveMesh();

    ofxPanel panel;
    ofParameter<bool> editCurve = false;
    ofParameter<bool> debug = false;
    ofxButton resetCurve;
    ofxButton exportMesh;

    ofEasyCam camera;
    vector<glm::vec2> points;
    ofxLathePrimitive lathe;
    ofPolyline path;

    int nCurveVertices = 7;
    draggableVertex curveVertices[7];
    void drawDraggablePoints();
    void createPath();

    glm::vec2 curveEditorOffset = glm::vec2(ofGetWidth()/2., 100);
    ofLight light;
    ofMaterial material;

private:
    void defaultCurve();
    ofColor lineColor;
    ofColor bgOne;
    ofColor bgTwo;

};
