#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Projekt Dominik Tomasiewicz 41K9");
	ofSetFrameRate(60);
	ofEnableSmoothing();

	//--------------------------------------------------------------

	ding.loadSound("ding.mp3");

	//--------------------------------------------------------------
	ofBackground(0, 0, 0);
	displayCamera = true;
	displayBackground = true;
	displayInfo = true;

	desWidth = 320;
	desHeight = 240;

	width = desWidth * 3; //960
	height = desHeight * 3; //720

	cellBackgroud = new CellBackgroud(width, height, 25);
	cellBackgroud->setup();
	//--------------------------------------------------------------



	
	threshold = 20;
	captureBackground = true;

	scaleX = (float)width / (float)desWidth;
	scaleY = (float)height / (float)desHeight;


	cam.listDevices();
	cam.setDeviceID(1);
	//cam.setup(640, 480);
	//cam.setDesiredFrameRate(60);

	cam.setup(320, 240);
	cam.setDesiredFrameRate(30);


	//video.loadMovie("fruits.mov");
	//video.play();					


	imageDecimated.allocate(desWidth, desHeight);

}

//--------------------------------------------------------------
void ofApp::update() {
	cam.update();
	//video.update();

	//na pocz�tku obraz z kamery jest czarny
	//rozja�nia si� dopiero po pewnym czasie
	if (ofGetElapsedTimeMillis() < 2000)
	{
		captureBackground = true;
	}

	if (cam.isFrameNew())
	{
		//pobierz klatk�
		image.setFromPixels(cam.getPixelsRef());

		if (mirrorImage)
		{
			//odbicie obrazu w poziomie
			image.mirror(false, true);
		}
		
		//zmiejsz klatke
		imageDecimated.scaleIntoMe(image, CV_INTER_NN);

		//konwersja do skali szaro�ci
		grayImage = imageDecimated;

		//rozmycie obrazu
		blurred = grayImage;
		blurred.blurGaussian(9);

		//pobierz pierwsz� klatke jako klatke bazow�
		if (captureBackground)
		{
			background = blurred;
			captureBackground = false;
		}

		//r�nica klatki aktualnej i klatki bazowej
		diff = blurred;
		diff -= background;

		//binaryzacja r�znycy klatek
		//pr�g binaryzacji jest zmienny
		mask = diff;
		mask.threshold(threshold);

		//otwarcie
		mask.erode();
		mask.dilate();

		//zamkniecie
		mask.dilate();
		mask.erode();


		//znajdz kontury
		contourFinder.findContours(mask, 20, (320 * 240), 5, false);


		contourPoints.clear();
		/**/
		ofPoint point;
		for (int i = 0; i < contourFinder.blobs.size(); i++)
		{
			for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++)
			{
				point = contourFinder.blobs[i].pts[j];
				//skalowanie
				point.x = point.x * scaleX;
				point.y = point.y * scaleY;

				contourPoints.push_back(point);
			}
		}
		/**/
		//gdy wyst�pi� ruch u�yj punkt�w w przeciwnym wypadku uzyj randomowych
		if (contourPoints.size() > 0)
		{
			cellBackgroud->updateWithPoints(contourPoints);
		}
		else
		{
			cellBackgroud->updateWithRandomEnergy();
		}

	}
	else
	{
		//gdy nie by�o nowej klatki to i tak aktualizuj t�o
		cellBackgroud->update();
	}
	


	
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
		image.draw(ofGetWidth() - 320, 0, 320, 240);
		contourFinder.draw(ofGetWidth() - 320, 0, 320, 240);
	}
	if (displayVideo)
	{
		ofSetColor(255, 255, 255);
		imageDecimated.draw(0, 0);
		grayImage.draw(320, 0);
		blurred.draw(640, 0);
		diff.draw(0, 240);
		mask.draw(320, 240);
		background.draw(640, 240);

		contourFinder.draw(320, 240);
	}
	if (displayConturs)
	{
		ofSetColor(255, 255, 255, 64);
		image.draw(0, 0, width, height);
		contourFinder.draw(0, 0, width, height);
	}


	if (displayInfo)
	{
		drawInfo();
	}
}


/* Przyk�adowe klawisze do wykorzystania:
OF_KEY_F1, OF_KEY_F2, OF_KEY_F3, OF_KEY_F4, OF_KEY_F5, OF_KEY_F6, OF_KEY_F7,
OF_KEY_F8, OF_KEY_F9, OF_KEY_F10, OF_KEY_F11, OF_KEY_F12,
OF_KEY_LEFT, OF_KEY_UP, OF_KEY_RIGHT, OF_KEY_DOWN, OF_KEY_PAGE_UP,
OF_KEY_PAGE_DOWN, OF_KEY_HOME, OF_KEY_END, OF_KEY_INSERT, OF_KEY_RETURN, OF_KEY_ESC
*/
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	int n;

	switch (key)
	{
	case OF_KEY_UP:
		//zwi�kszanie progu binaryzacji
		threshold += 2;
		if (threshold > 255)
			threshold = 255;
		break;
	case OF_KEY_DOWN:
		//zmiejszanie progu binaryzacji
		threshold -= 2;
		if (threshold < 0)
			threshold = 0;
		break;
	case 'i':
	case 'I':
		//wy�wietlanie tabelki z inforacjami
		displayInfo = !displayInfo;
		break;
	case 'f':
	case 'F':
		//uruchamianie trybu pe�noekranowego ???
		ofToggleFullscreen();
		break;
	case 'k':
	case 'K':
		//rysowanie kontur�w na ekranie
		displayConturs = !displayConturs;
		break;
	case 'b':
	case 'B':
		//wy�wietlanie interaktywnego t�a
		displayBackground = !displayBackground;
		break;
	case 'c':
	case 'C':
		//wy�wietl aktualny obreaz kamery
		displayCamera = !displayCamera;
		break;
	case 'r':
	case 'R':
		//pobranie aktualnej klatki jako klatk� bazow�
		captureBackground = true;
		break;
	case 'v':
	case 'V':
		//wyswietlanie duzej liczy rzeczy xD
		displayVideo = !displayVideo;
		break;
	case 'm':
	case 'M':
		//odbicie obrazu
		mirrorImage = !mirrorImage;
		break;
	case 'z':
	case 'Z':
		//Debug
		n = 0;
		for (int i = 0; i < contourFinder.blobs.size(); i++)
		{
			n += contourFinder.blobs[i].nPts;
		}
		printf("%d\n", n);

		break;
	case ' ':
		//SPACJA - boom t�a 
		cellBackgroud->boom();
		ding.play();
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
	ofDrawRectangle(ofGetWidth() - 320, ofGetHeight() - 240, 320, 240);

	string info = "";
	info += "[i] - informacje\n";
	info += "FPS: " + ofToString(ofGetFrameRate(), 1) + "\n";
	info += "Threshold [Arrow up down]: " + ofToString(threshold) + "\n";
	info += "[r] - reset base frame to current\n";
	info += "[SPACE] - cell backgroud boom\n";
	info += "[b] - cell backgroud toggle\n";
	info += "[f] - fulscreen toggle\n";
	info += "[c] - camera toggle\n";
	info += "[k] - conturs toggle\n";
	info += "[m] - mirror image\n";

	ofSetColor(255, 255, 255);
	ofDrawBitmapString(info, ofGetWidth() - 310, ofGetHeight() - 220);
}