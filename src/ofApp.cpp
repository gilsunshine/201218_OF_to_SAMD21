#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    font.load("monospace", 24);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    int baud = 9600;

    serial.setup("/dev/cu.usbmodem1411301", baud);
    ofEnableSmoothing();
      ofEnableDepthTest();
      cam.setDistance(4);
      cam.setNearClip(0.0001);
      numIso = 0;
      res = 30;
      ofBackground(255);

}

//--------------------------------------------------------------
void ofApp::update(){
    if (serial.available() < 0) {        morph = 1.0;
    }
    else {
        while (serial.available() > 0) {
            byteData = serial.readByte();
            sensorValue = "value: " + ofToString(byteData);
        }
    }
    cout << sensorValue << endl; // output the sensorValue
    
    float time = ofGetElapsedTimef();
        ofPolyline outsideIso;
        ofPolyline insideIso;
        rings.clear();
        outsideIsos.clear();
        float oldMorph = morph;
        morph = ofMap(byteData,0,200, 0.0, 1.0);
        morph = oldMorph * 0.9 + morph * 0.1;
        
        int n = numIso;
        int m = res;
        float a = 1.2 ;
        float b = 1;
        float turns = 1;
        
        for (int i = 0; i <= numIso; i++) {
            float mis = 0;
            for (int j = 0; j <= res; j++) {
                
                float v1 = j * PI/res;
                float x1 = a * sin(v1) * cos(turns*v1);
                float y1 = a * sin(v1) * sin(turns*v1);
                float z1 = a * cos(v1);
                
                float x2 = b * sin(v1) * cos(turns*v1);
                float y2 = b * sin(v1) * sin(turns*v1);
                float z2 = b * cos(v1);
                
                float u2 = i * 2*PI;
                float v2 = j * 2*PI/res;
                
                float c = .75;
                float d = 0.375;
                float x3 = a * (c + (d * cos(v2))) * cos(u2);
                float y3 = a * (c + (d * cos(v2))) * sin(u2);
                float z3 = a * d * sin(v2);
                
                float x4 = b * (c + (d * cos(v2))) * cos(u2);
                float y4 = b * (c + (d * cos(v2))) * sin(u2);
                float z4 = b * d * sin(v2);
                
                float xa = x1 * morph + x3 * (1.0 - morph);
                float ya = y1 * morph + y3 * (1.0 - morph);
                float za = z1 * morph + z3 * (1.0 - morph);
                
                outsideIso.addVertex(ofVec3f(xa,ya,za));
                
            }
            outsideIsos.push_back(outsideIso);
        }
        float numSpi = 2 * PI / 18;
        for (float i = numSpi; i < 2 * PI; i+=numSpi){

            ofPolyline newOutsideIso;
            
            for(int j = 0; j < outsideIso.getVertices().size(); j++){
                ofVec3f newPt;
                newPt.set(outsideIso[j]);
                newPt = newPt.getRotatedRad(i, ofVec3f(0,0,1));
                newOutsideIso.addVertex(newPt);
            }
            
            outsideIsos.push_back(newOutsideIso);
        }

        for (int i = 0; i < outsideIsos[0].size(); i++){
            ofPolyline ring;
            for(int j = 0; j < outsideIsos.size(); j++){
                ring.addVertex(outsideIsos[j][i]);
            }
            rings.push_back(ring);
        }

}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.begin();
      cout << rings.size() << endl;
      ofPushMatrix();
      ofRotateXRad(PI/5);
      ofRotateYRad(PI/5);
      ofRotateZRad(ofGetElapsedTimef()/2);
      ofSetColor(0,0,255);
      ofSetLineWidth(1);
      for (int i = 0; i < outsideIsos.size(); i++){
          outsideIsos[i].draw();
      }

      for (int i = 0; i < rings.size(); i++){
          rings[i].draw();
      }
      
      ofPopMatrix();
      cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
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
