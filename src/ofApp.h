#pragma once

#include "ofMain.h"
#include "CellBackgroud.h"
#include "ofxOpenCv.h"

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

		//---------------------------------------------------------------------------
		
		void drawInfo();


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

		bool displayInfo, displayBackground, displayCamera, displayVideo, displayConturs;
		bool mirrorImage;

		bool captureBackground;
		int width, height;
		int desWidth, desHeight, threshold;
		float scaleX, scaleY;
};
