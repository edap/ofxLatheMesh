#include "ofxLatheMesh.h"

static vector<glm::vec2> defaultPoints(){
    vector<glm::vec2> points;
    for (unsigned int i = 1; i < 100; i ++) {
        //float y = sin(i) /i+1;
        float y = sin(i*.4 ) /i*5.0 +1;
        points.push_back( glm::vec2( i*2, 40 - y*40 ));

    }
    return points;
}

static const ofxLathePrimitiveOptions defaultOptions = {
    defaultPoints(),
    6,
    1.0,
    1.0
};

ofxLatheMesh::ofxLatheMesh(){
    points = defaultOptions.points;
    segments = defaultOptions.segments;
    phiStart = defaultOptions.phiStart;
    phiLength = defaultOptions.phiLength;

    rotatingPoints.clear();
    rotatingPoints.resize(points.size());
    setupGui();
};

void ofxLatheMesh::setupGui(){
    parameters.clear();
    parameters.setName("lathe");
    parameters.add(segments.set("segments", segments.get(), 1, segments.get()* 20));
    parameters.add(phiStart.set("phiStart", phiStart.get(), 0, float(PI*2)));
    parameters.add(phiLength.set("phiLength", phiLength.get(), 0, float(PI*2)));
    parameters.add(flipNormals.set("flipNormals",false));
    parameters.add(closed.set("closed",false));

    rotatingPoints.clear();
    rotatingPoints.resize(points.size());
}

void ofxLatheMesh::setup(const vector<glm::vec2> _points, const int _segments, const float _phiStart, const float _phiLength){
    points = _points;
    segments = _segments;
    phiStart = _phiStart;
    phiLength = _phiLength;
    parameters.clear();
    setupGui();
}

void ofxLatheMesh::clear(){
    mesh.clear();
    currentSegment = 0;
    //rotatingPoints.clear();
    //points.clear();
};

void ofxLatheMesh::setPoints(vector<glm::vec2> _points){
    rotatingPoints.clear();
    points = _points;
    rotatingPoints.resize(_points.size());
};

vector<glm::vec2> ofxLatheMesh::getPoints() const {
    return points;
};

vector<glm::vec3> ofxLatheMesh::getCurrentRotatingPoints() const {
    return rotatingPoints;
};

void ofxLatheMesh::build(){
    // credits to
    // https://github.com/mrdoob/three.js/blob/master/src/geometries/LatheGeometry.js
    clear();
    unsigned int _segments = std::floor( segments.get()) > 0? segments.get() : defaultOptions.segments;
    float _phiLength = ofClamp(phiLength, 0, float(PI * 2));
    float _phiStart = ofClamp(phiStart, 0, float(PI * 2));
    bool almostClosed = ((PI * 2) - double(_phiLength)) < 0.01;

    // cached
    glm::vec3 vertex;
    glm::vec2 point;
    glm::vec3 offset;
    glm::vec2 uv;
    vector<glm::vec2> editedPoints;
    unsigned int i, j;

    float inverseSegments = float(1.) / float(_segments);

    for (i = 0; i <= _segments; i ++) {
        float phi = _phiStart + i * inverseSegments * _phiLength;
        float sinv = sin(phi);
        float cosv = cos(phi);

        for ( j = 0; j <= ( points.size() - 1 ); j ++ ) {
            // if the geometry is closed, the last vertices
            // on the rotation take the same position as that one that
            // made the first round.
            if (closed && i == _segments && almostClosed) {
                vertex = mesh.getVertices().at(0+j);
            } else {
                // deformations happen if lambdas are set.
                point = points[j];
                if (editPoint) {
                    vertex = editPoint(points, phi, i, j);
                }else{
                    if (addOffset) {
                        offset = addOffset(phi, i, j);
                    }

                    vertex.x = point.x * sinv + offset.x;
                    vertex.y = point.y + offset.y;
                    vertex.z = point.x * cosv + offset.z;
                }

            }

            mesh.addVertex(vertex);

            // add vertex color if present
            if (computeColor) {
                mesh.addColor(computeColor(phi, i, j));
            }

            // save current rotating points, useful for animation
            rotatingPoints[j].x = vertex.x;
            rotatingPoints[j].y = vertex.y;
            rotatingPoints[j].z = vertex.z;

            //rotatingPoints[j] = rotatingPoints[j]*this->getGlobalTransformMatrix();

            // uv
            uv.x = i / _segments;
            uv.y = j / ( points.size() - 1 );
            mesh.addTexCoord(uv);
        }
        currentSegment ++;
    }

    unsigned long base;
    // indices
    for ( i = 0; i < _segments; i ++ ) {
        for ( j = 0; j < ( points.size() - 1 ); j ++ ) {
            base = j + i * points.size();

            unsigned long a = base;
            unsigned long b = base + points.size();
            unsigned long c = base + points.size() + 1;
            unsigned long d = base + 1;

            // faces.
            // The direction of the faces may change depending
            // on the insertion order the of vertices in points array.
            // Therefore, an option to flip the normals was added.
            if (flipNormals) {
                mesh.addTriangle( a, b, d );
                mesh.addTriangle( b, c, d );
            } else {
                mesh.addTriangle( b, a, d );
                mesh.addTriangle( d, c, b );
            }
        }
    }

    calcNormals(mesh);
    if (almostClosed){
        // if the geometry is closed, we need to average the normals along the seam.
        // because the corresponding vertices are identical (but still have different UVs).
        fixNormalForClosedGeometry(mesh, points.size(), _segments);
    }

    mesh.enableNormals();
};

void ofxLatheMesh::calcNormals(ofMesh &mesh){
    mesh.getNormals().clear(); // per build segment, potresti aggiungere
    // i nuovi normals invece di pulire tutto
    for( unsigned int i=0; i < mesh.getVertices().size(); i++ ) mesh.addNormal(glm::vec3(0.0f,0.0f,0.0f));

    for ( unsigned int i=0; i < mesh.getIndices().size(); i+=3  ) {
        const unsigned int ia = mesh.getIndices()[i];
        const unsigned int ib = mesh.getIndices()[i+1];
        const unsigned int ic = mesh.getIndices()[i+2];

        glm::vec3 e1 = mesh.getVertices()[ia] - mesh.getVertices()[ib];
        glm::vec3 e2 = mesh.getVertices()[ic] - mesh.getVertices()[ib];

        glm::vec3 no;
        no =  glm::cross(e2, e1);

        mesh.getNormals()[ia] = glm::normalize(no + mesh.getNormals()[ia]);
        mesh.getNormals()[ib] = glm::normalize(no + mesh.getNormals()[ib]);
        mesh.getNormals()[ic] = glm::normalize(no + mesh.getNormals()[ic]);
    }
};
void ofxLatheMesh::fixNormalForClosedGeometry( ofMesh & mesh, const unsigned long pointSize, const unsigned int segments){
    // via https://github.com/mrdoob/three.js/blob/master/src/geometries/LatheGeometry.js

    auto n1 = glm::vec3();
    auto n2 = glm::vec3();
    auto n = glm::vec3();

    unsigned long base = segments * pointSize;
    for ( unsigned int i = 0; i < pointSize; i ++) {
        // select the normal of the vertex in the first line
        n1 = mesh.getNormals()[ i];

        // select the normal of the vertex in the last line
        n2 = mesh.getNormals()[ base + i];

        // average normals
        n = glm::normalize(n1 + n2);

        // assign the new values to both normals
        mesh.getNormals()[ i] = n;
        mesh.getNormals()[ base + i] = n;
    }
};


