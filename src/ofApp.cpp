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



	if (displayInfo)
	{
		drawInfo();
		
	}

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	

	switch (key)
	{
	case 'i':
	case 'I':
		displayInfo = !displayInfo;
		break;
	case 'b':
	case 'B':
		cellBackgroud->boom();
		break;

	default:
		break;
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

void ofApp::drawInfo()
{
	ofSetColor(77, 77, 77, 180);
	ofDrawRectangle(0, 0, 300, 100);

	string info = "";
	info += "[i] - informacje\n";
	info += "FPS: "+ ofToString(ofGetFrameRate(),1) +"\n";
	info += "[b] - backgroud boom\n";

	ofSetColor(255, 255, 255);
	ofDrawBitmapString(info, 10, 15);
}