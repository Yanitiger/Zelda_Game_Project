#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(	// <-------- setup the GL context	
		Handler::GAME_SCREEN.width,
		Handler::GAME_SCREEN.height + Handler::HUD_SCREEN.height, 
		OF_WINDOW
	);			

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
