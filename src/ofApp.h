#pragma once

#include "ofMain.h"
#include "CellBackgroud.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"

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

		void audioIn(float * input, int bufferSize, int nChannels);
		//---------------------------------------------------------------------------
		
		void drawInfo();
		void highSoundDetected();



		//---------------------------------------------------------------------------

		ofxBox2d box2d;

		vector <shared_ptr<ofxBox2dCircle> > circles;
		vector <shared_ptr<ofxBox2dEdge> > edges;

		//---------------------------------------------------------------------------

		
		CellBackgroud * cellBackgroud;
		ofVideoGrabber cam;
		ofVideoPlayer video;

		ofxCvColorImage image;
		ofxCvColorImage imageDecimated;

		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage blurred;
		ofxCvGrayscaleImage background;
		ofxCvGrayscaleImage diff;
		ofxCvGrayscaleImage mask;

		ofxCvContourFinder 	contourFinder;

		vector<ofPoint> contourPoints;	//punkty znalezione w konturze 

		ofSoundPlayer ding;
		ofSoundStream soundStream;

		bool displayInfo, displayBackground, displayCamera, displayVideo, detectConturs;
		bool mirrorImage;

		bool captureBackground;
		int width, height;
		int desWidth, desHeight, threshold;
		float scaleX, scaleY;
		float rmsDisplay, audioThreshold;

};
