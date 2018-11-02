#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxLathePrimitive.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void drawRotating();

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
    void regenerateInt(int &s);
    void regenerate(float &s);
    void regenerateBool(bool &s);
    void restoreScale();

    void updateOffset(float &v);
    void updateScale(float &v);

    ofLight light;
    ofMaterial material;
    ofParameter<ofColor> diffuseColor;
    ofParameter<ofColor> emissiveColor;
    ofParameter<ofColor> lightColor;
    ofParameter<ofColor> specColor;
    ofParameter<ofColor> bgColor;
    ofParameter<ofColor> normalColor;
    ofEasyCam camera;
    ofColor lineColor;
    ofxLathePrimitive lathe;
    ofxPanel panel;
    ofParameterGroup lathePar;
    ofParameterGroup colors;

    ofParameterGroup deformationX;
    ofParameterGroup deformationY;
    ofParameterGroup deformationZ;

    ofParameter<float> amplitX;
    ofParameter<float> freqX;

    ofParameter<float> amplitY;
    ofParameter<float> freqY;

    ofParameter<float> amplitZ;
    ofParameter<float> freqZ;

    ofParameter<bool> deformOnAngle;

    ofParameter<float> freqDefX;
    ofParameter<float> freqDefY;
    ofParameter<float> freqDefZ;

    ofParameter<float> amplitScale;
    ofParameter<float> freqScale;
    ofParameter<bool> applyScale;

    ofParameter<bool> drawFaces;
    ofParameter<bool> drawNormal;
    ofParameter<bool> animate;
    ofParameter<bool> drawRotatingPoints;
    ofParameter<int> rotatingPointsSample;
    ofxButton resetScale;

    bool drawGui = true;

    ofNode parent;

};
