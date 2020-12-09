#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();

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

    ofTrueTypeFont font;
        
    ofSerial serial;
    string sensorValue;
    int byteData;
    string msg;
    
    ofEasyCam cam;
    ofMesh shape1, shape2;
    vector <ofMesh> outsideMeshes;
    vector <ofMesh> insideMeshes;
    vector <ofMesh> shingles;
    vector <ofPolyline> insideIsos;
    vector <ofPolyline> outsideIsos;
    vector <ofPolyline> rings;

    float morph;
    int mode;
    int numIso;
    int res;
};
