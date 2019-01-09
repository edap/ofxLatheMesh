#pragma once
#include "ofMain.h"

struct ofxLathePrimitiveOptions{
    vector<glm::vec2>points;
    int segments;
    float phiStart;
    float phiLength;
};

class ofxLatheMesh : public of3dPrimitive {
public:
    ofxLatheMesh();
    void setup(const vector<glm::vec2>points, const int segments, const float phiStart, const float phiLength);

    void build();
    void clear();
    void draw();

    void setPoints(vector<glm::vec2> _points);
    vector<glm::vec2> getPoints() const;
    vector<glm::vec3> getCurrentRotatingPoints() const;

    ofParameterGroup parameters;
    ofParameter<int> segments;
    ofParameter<float> phiStart;
    ofParameter<float> phiLength;
    ofParameter<bool> closed = false;
    ofParameter<bool> flipNormals = false;
    vector<glm::vec2> points;


    std::function<glm::vec3(const float, const int, const int)> addOffset;
    std::function<glm::vec2(const vector<glm::vec2> points, const float, const int, const int)> editPoint;
    std::function<ofColor(const float, const int, const int)> computeColor;

    ofVboMesh mesh;

private:
    void setupGui();
    void calcNormals(ofMesh &mesh);
    void fixNormalForClosedGeometry( ofMesh & mesh, const unsigned long pointSize, const unsigned int segments);
    vector<glm::vec3> rotatingPoints;


};
