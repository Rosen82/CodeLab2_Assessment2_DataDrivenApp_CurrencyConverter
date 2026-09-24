#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp {
public:
	// Core openFrameworks lifecycle methods
	void setup() override;
	void update() override;
	void draw() override;

	// Input event handling
	void keyPressed(int key) override;

private:
	// API credentials and endpoint string
	std::string apiKey;
	std::string apiUrl;

	// Application state variables
	std::string conversionStatus;
	std::string lastUpdatedTime;
	float convertedValue;

	// JSON data parser instance
	ofxJSONElement jsonResponse;

	// Typography (TrueType fonts for high legibility)
	ofTrueTypeFont titleFont;
	ofTrueTypeFont bodyFont;
	ofTrueTypeFont smallFont;

	// Modular UI layout helper functions
	void drawHeaderSection();
	void drawResultCard();
	void drawFooterControls();

	// Network request helper
	void fetchExchangeRate();
};
