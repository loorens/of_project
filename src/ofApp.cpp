#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Projekt Dominik Tomasiewicz 41K9");
	ofSetFrameRate(60);
	ofEnableSmoothing();

	//--------------------------------------------------------------

	//ding.loadSound("ding.mp3");
	pop.loadSound("pop.mp3");
	bubble.loadSound("bubble.mp3");
	soundStream.printDeviceList();
	soundStream.setDeviceID(2);
	soundStream.setup(this, 0, 4, 44100, 256, 8);
	audioThreshold = 0.15;

	//--------------------------------------------------------------
	ofBackground(0, 0, 0);
	displayCamera = true;
	displayBackground = true;

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



	//--------------------------------------------------------------
	// Box2d
	box2d.init();
	box2d.enableEvents();
	box2d.setGravity(0, 1);
	box2d.createBounds(0, 0, width, height);
	box2d.setFPS(60.0);

	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);

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

		//wyczysc krawedzie
		edges.clear();

		for (int i = 0; i < contourFinder.blobs.size(); i++)
		{
			if (contourFinder.blobs[i].pts.size() > 3)
			{
				//przepisywanie i skalowanie
				vector <ofVec2f> p;
				for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++)
				{
					ofVec2f v = ofVec2f(contourFinder.blobs[i].pts[j].x * scaleX, contourFinder.blobs[i].pts[j].y * scaleY);
					p.push_back(v);
				}

				//dodwanie krawedzi
				edges.push_back(ofPtr<ofxBox2dEdge>(new ofxBox2dEdge));
				edges.back().get()->addVertexes(p);
				edges.back().get()->setPhysics(0.0, 5.1, 0.0);
				edges.back().get()->create(box2d.getWorld());
			}
		}

	}


	if (detectConturs)
	{
		contourPoints.clear();
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
		cellBackgroud->updateWithPoints(contourPoints);
	}
	cellBackgroud->updateWithCircles(circles);


	box2d.update();
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

	for (int i = 0; i < circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xc0dd3b);
		circles[i].get()->draw();
	}

	ofSetColor(255, 100, 100);
	ofNoFill();
	for (int i = 0; i < edges.size(); i++) {
		edges[i].get()->draw();
	}


	drawInfo();
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
	case 'f':
	case 'F':
		//uruchamianie trybu pe�noekranowego ???
		ofToggleFullscreen();
		break;
	case 'k':
	case 'K':
		//rysowanie kontur�w na ekranie
		detectConturs = !detectConturs;
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
	case 'x':
	case 'X':
		//czyszczenie listy kuleczek
		circles.clear();
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
		pop.play();
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

	if (button == 0) //Lewy
	{
		addBox2DCircle(x, y);

	}
	else if (button == 2) //Prawy
	{
		if (circles.size() > 0)
			circles.erase(circles.begin());
	}

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


void ofApp::audioIn(float * input, int bufferSize, int nChannels) {

	float rms = 0.0;
	int numCounted = 0;

	for (int i = 0; i < bufferSize; i++) {
		float leftSample = input[i * 2] * 0.5;
		float rightSample = input[i * 2 + 1] * 0.5;

		rms += leftSample * leftSample;
		rms += rightSample * rightSample;
		numCounted += 2;
	}

	rms /= (float)numCounted;
	rms = sqrt(rms);
	rmsDisplay = rms;

	if (rmsDisplay > audioThreshold)
		highSoundDetected();
}

void ofApp::highSoundDetected()
{
	cellBackgroud->boom();

	for (int i = 0; i < 1; i++)
	{
		addBox2DCircle(ofRandom(width), ofRandom(height));
	}
}
void ofApp::addBox2DCircle(int x, int y)
{
	shared_ptr<ofxBox2dCircle> c = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
	c.get()->setPhysics(0.5, 0.6, 0.00001);
	c.get()->setup(box2d.getWorld(), x, y, ofRandom(10, 30));
	c.get()->setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
	circles.push_back(c);
}


void ofApp::drawInfo()
{
	ofSetColor(77, 77, 77, 180);
	ofDrawRectangle(ofGetWidth() - 320, ofGetHeight() - 240, 320, 240);

	string info = "";
	info += "FPS: " + ofToString(ofGetFrameRate(), 1) + "\n";
	info += "Threshold [Arrow up down]: " + ofToString(threshold, 2) + "\n";
	info += "Volume: " + ofToString(rmsDisplay, 3) + "\n";
	info += "[r] - reset base frame to current\n";
	info += "[SPACE] - cell backgroud boom\n";
	info += "[b] - cell backgroud toggle\n";
	info += "[f] - fulscreen toggle\n";
	info += "[c] - camera toggle\n";
	info += "[k] - conturs toggle\n";
	info += "[m] - mirror image\n";
	info += "[x] - clear circles\n";
	info += "[Left mouse] - add circle\n";
	info += "[Rught mouse] - delete circle\n";



	ofSetColor(255, 255, 255);
	ofDrawBitmapString(info, ofGetWidth() - 310, ofGetHeight() - 220);
}


//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL)
	{
		if (e.a->GetType() == b2Shape::e_circle &&  e.b->GetType() == b2Shape::e_circle)
		{
			bubble.play();
		}
		else
		{
			pop.play();
		}

	}
}

