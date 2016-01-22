#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Projekt DT");
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofBackground(0, 0, 0);
	displayBackground = true;

	cellBackgroud = new CellBackgroud(ofGetWidth(), ofGetHeight(), 25);
	cellBackgroud->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	cellBackgroud->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	if (displayBackground)
	{
		cellBackgroud->draw();
	}

	if (displayInfo)
	{
		drawInfo();
	}
}

/* Przyk³adowe klawisze do wykorzystania:
OF_KEY_F1, OF_KEY_F2, OF_KEY_F3, OF_KEY_F4, OF_KEY_F5, OF_KEY_F6, OF_KEY_F7,
OF_KEY_F8, OF_KEY_F9, OF_KEY_F10, OF_KEY_F11, OF_KEY_F12,
OF_KEY_LEFT, OF_KEY_UP, OF_KEY_RIGHT, OF_KEY_DOWN, OF_KEY_PAGE_UP,
OF_KEY_PAGE_DOWN, OF_KEY_HOME, OF_KEY_END, OF_KEY_INSERT, OF_KEY_RETURN, OF_KEY_ESC
*/
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{
	case 'i':
	case 'I':
		displayInfo = !displayInfo;
		break;
	case 'f':
	case 'F':
		ofToggleFullscreen();
		break;
	case 'b':
	case 'B':
		displayBackground = !displayBackground;
		break;
	case ' ':
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
	info += "[SPACE] - backgroud boom\n";
	info += "[b] - backgroud toggle\n";
	info += "[f] - fulscreen toggle\n";

	ofSetColor(255, 255, 255);
	ofDrawBitmapString(info, 10, 15);
}