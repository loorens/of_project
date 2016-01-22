#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Projekt DT");
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofBackground(0, 0, 0);
	
	cellBackgroud = new CellBackgroud(ofGetWidth(), ofGetHeight(), 25);
	cellBackgroud->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	cellBackgroud->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cellBackgroud->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	

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
