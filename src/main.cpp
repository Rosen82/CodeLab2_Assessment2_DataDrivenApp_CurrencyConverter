#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
	// Initialize the openFrameworks window context
	ofSetupOpenGL(950, 650, OF_WINDOW);

	// Launch the core ofApp application loop
	ofRunApp(new ofApp());
}
