// Raytracing application draws an image pixel by pixel onto
// a small plane in front of the render camera.
//
// By Victor La

#include "ofApp.h"

using namespace glm;

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetBackgroundColor(ofColor::black);
	bHideGUI = true;
	_currentCamera = 0;
	
	// Set up GUI
	gui.setup();
	//	gui.add(camDistance.setup("Camera Distance", 20, 10, 50));
	
	// Set up cameras
	cam.setDistance(20);
	theCam = &cam;
		// Side camera properties
	sideCam.setPosition(175, 0, 0);
	sideCam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
		// Preview camera properties
	previewCam.setPosition(renderCam.position);
	previewCam.setNearClip(0.7);

	// Set up render environment
	ball1 = new Sphere(vec3(3, 0, -1.1), 2.0f, ofColor(50, 40, 220));
	ball2 = new Sphere(vec3(-1.8, -1, -3.1), 3.0f, ofColor(200, 50, 50));
	ball3 = new Sphere(vec3(.3, -.5, 1.2), 1.5f, ofColor::gold);
	groundPlane = new Plane(vec3(0, -4, -2), vec3(0, 1, 0));
	scene.push_back(ball1);
	scene.push_back(ball2);
	scene.push_back(ball3);
	scene.push_back(groundPlane);
}

//--------------------------------------------------------------
void ofApp::update(){
	switch (_currentCamera) {
	case easy: theCam = &cam;
		break;
	case side: theCam = &sideCam;
		break;
	case preview: theCam = &previewCam;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the GUI
	if (!bHideGUI) gui.draw();

	theCam->begin();

		// Draw grid plane
		//ofPushMatrix();
		//ofRotate(90, 0, 0, 1);
		//ofSetLineWidth(1);
		//ofSetColor(ofColor::dimGrey);
		//ofDrawGridPlane();
		//ofPopMatrix();

		// Draw world axis
		drawAxis(glm::vec3(0, 0, 0));

		// Set drawing color to white
		ofSetColor(ofColor::white);

		// Draw objects in the scene
		ofNoFill();
		for (SceneObject *obj : scene)
			obj->draw();

		// Draw viewplane and view frustum
		ofSetColor(ofColor::blue);
		viewPlane.draw();
		renderCam.drawFrustum(viewPlane);

		// Draw Cameras
		ofSetColor(ofColor::white);
		cam.draw();
		sideCam.draw();
		renderCam.draw();

	// End drawing in the camera
	theCam->end();

	// Raytrace the scene onto an OfImage
	rayTrace();

	// Framerate
	string str;
	str += "Frame Rate: " + std::to_string(ofGetFrameRate());
	ofSetColor(ofColor::white);
	ofDrawBitmapString(str, ofGetWindowWidth() - 205, 15);
}

// Ray trace scene objects onto viewplane
//
void ofApp::rayTrace() {
	image.allocate(imageWidth, imageHeight, OF_IMAGE_COLOR);

	// Loop through the pixel indexes and set the color
	// according to the ray tracing values
	for (int i = 0; i < imageWidth; i++) {
		for (int j = 0; j < imageHeight; i++) {
			image.setColor(i, j, ofColor::white);
		}
	}

}

// Draw an XYZ axis in RGB at world location for reference.
//
void ofApp::drawAxis(glm::vec3 location) {

	ofPushMatrix();
	ofTranslate(location);

	ofSetLineWidth(1.0);

	// X Axis
	ofSetColor(ofColor(255, 0, 0));
	ofDrawLine(ofPoint(0, 0, 0), ofPoint(1, 0, 0));


	// Y Axis
	ofSetColor(ofColor(0, 255, 0));
	ofDrawLine(ofPoint(0, 0, 0), ofPoint(0, 1, 0));

	// Z Axis
	ofSetColor(ofColor(0, 0, 255));
	ofDrawLine(ofPoint(0, 0, 0), ofPoint(0, 0, 1));

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'C':
	case 'c':
		if (cam.getMouseInputEnabled()) cam.disableMouseInput();
		else cam.enableMouseInput();
		break;
	case 'B':
	case 'b':
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		bHideGUI = !bHideGUI;
		break;
	case 'T':
	case 't':
		changeCamera();
		break;
	case OF_KEY_F1:
		theCam = &cam;
		break;
	case OF_KEY_F2:
		theCam = &sideCam;
		break;
	case OF_KEY_F3:
		theCam = &previewCam;
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

// Swap between the cameras based on enumeration
//
void ofApp::changeCamera() {
	_currentCamera++;
	if (_currentCamera == 3)
		_currentCamera = 0;
}
