#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Projekt Dominik Tomasiewicz 41K9");
	ofSetFrameRate(60);
	ofEnableSmoothing();

	//--------------------------------------------------------------
	ofBackground(0, 0, 0);
	displayBackground = true;
	cellBackgroud = new CellBackgroud(ofGetWidth(), ofGetHeight(), 25);
	cellBackgroud->setup();
	//--------------------------------------------------------------

	desWidth = 320;
	desHeight = 240;
	threshold = 40;
	captureBackground = true;

	cam.listDevices();
	cam.setDeviceID(1);
	//cam.setup(640, 480);
	//cam.setDesiredFrameRate(60);

	cam.setup(320, 240);
	cam.setDesiredFrameRate(30);


	video.loadMovie("fruits.mov");	//Load the video file
	video.play();					//Start the video to play	


	imageDecimated.allocate(desWidth, desHeight);



}

//--------------------------------------------------------------
void ofApp::update() {
	cam.update();
	video.update();


	if (video.isFrameNew())
	{
		//oblicz skalê o jak¹ nale¿y zmieniæ klatkê
		float scaleX = (float)desWidth / video.getWidth();
		float scaleY = (float)desHeight / video.getHeight();

		//pobierz klatkê
		image.setFromPixels(video.getPixelsRef());

		imageDecimated.scaleIntoMe(image, CV_INTER_NN);


		grayImage = imageDecimated;

		//Smoothing image
		blurred = grayImage;
		blurred.blurGaussian(9);

		//Store first frame to background image
		if (captureBackground)
		{
			background = blurred;
			captureBackground = false;
		}

		//Find difference of the frame and background
		diff = blurred;
		diff -= background;

		//Thresholding for obtaining binary image
		mask = diff;
		mask.threshold(threshold);
		//Here value 40 is the threshold parameter. 
		//It should be adjusted for good results when using another videos than in example.

		//Find contours
		contourFinder.findContours(mask, 10, 10000, 20, false);

		//Store objects' centers
		vector<ofxCvBlob>  &blobs = contourFinder.blobs;
		int n = blobs.size();	//Get number of blobs
		obj.resize(n);		//Resize obj array
		for (int i = 0; i < n; i++) {
			obj[i] = blobs[i].centroid;	//Fill obj array
		}



	}





	if (cam.isFrameNew())
	{

	}

	cellBackgroud->update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (displayBackground)
	{
		cellBackgroud->draw();
	}

	
	if (displayCamera)
	{
		ofSetColor(255, 255, 255);
		cam.draw(ofGetWidth() - 320 - 20, ofGetHeight() - 240 - 20, 320, 240);
	}
	if (displayVideo)
	{
		ofSetColor(255, 255, 255);
		video.draw(ofGetWidth() - 320 - 20, ofGetHeight() - 240 - 20, 320, 240);
	}

	ofSetColor(255, 255, 255);
	imageDecimated.draw(0, 0);
	grayImage.draw(320, 0);
	blurred.draw(640, 0);
	diff.draw(0, 240);
	mask.draw(320, 240);

	background.draw(640, 240);


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
void ofApp::keyPressed(int key) {

	switch (key)
	{
	case OF_KEY_UP: 
		//zwiêkszanie progu binaryzacji
		threshold += 5;
		if (threshold > 255)
			threshold = 255;
		break;
	case OF_KEY_DOWN: 
		//zmiejszanie progu binaryzacji
		threshold -= 5;
		if (threshold < 0)
			threshold = 0;
		break;
	case 'i':
	case 'I':
		//wyœwietlanie tabelki z inforacjami
		displayInfo = !displayInfo;
		break;
	case 'f':
	case 'F':
		//uruchamianie trybu pe³noekranowego ???
		ofToggleFullscreen();
		break;
	case 'z':
	case 'Z':
		//nic
		break;
	case 'b':
	case 'B':
		//wyœwietlanie interaktywnego t³a
		displayBackground = !displayBackground;
		break;
	case 'c':
	case 'C':
		//wyœwietl aktualny obreaz kamery
		displayCamera = !displayCamera;
		break;
	case 'r':
	case 'R':
		//pobranie aktualnej klatki jako klatkê bazow¹
		captureBackground = true;
		break;
	case 'v':
	case 'V':
		//?????????????????
		displayVideo = !displayVideo;
		break;
	case ' ':
		//SPACJA - boom t³a 
		cellBackgroud->boom();
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::drawInfo()
{
	ofSetColor(77, 77, 77, 180);
	ofDrawRectangle(0, 0, 300, 100);

	string info = "";
	info += "[i] - informacje\n";
	info += "FPS: " + ofToString(ofGetFrameRate(), 1) + "\n";
	info += "Threshold [Arrow up down]: " + ofToString(threshold) + "\n";
	info += "[r] - reset base frame to current\n";
	info += "[SPACE] - cell backgroud boom\n";
	info += "[b] - cell backgroud toggle\n";
	info += "[f] - fulscreen toggle\n";
	info += "[c] - camera toggle\n";

	ofSetColor(255, 255, 255);
	ofDrawBitmapString(info, 10, 15);
}