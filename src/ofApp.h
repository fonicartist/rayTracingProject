#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "RayTracer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void rayTrace();
		void drawAxis(glm::vec3);
		void drawGrid();

		// Boolean flags
		bool bHideGUI;
		bool bShowImage = false;

		// Camera properties
		enum CurrentCamera { easy, side, preview };
		int _currentCamera;
		ofCamera  *theCam;
		ofEasyCam cam;
		ofCamera previewCam, sideCam;
		void changeCamera();

		// Render properties
		RenderCam renderCam;
		ofImage image;
		vector<SceneObject *> scene;
		int imageWidth = 600;
		int imageHeight = 400;

		// Objects to be rendered
		Sphere *ball1,
			   *ball2,
			   *ball3;
		Plane *groundPlane;
		ViewPlane viewPlane;

		// Gui stuff
		ofxFloatSlider camDistance;
		ofxPanel gui;
		
};
