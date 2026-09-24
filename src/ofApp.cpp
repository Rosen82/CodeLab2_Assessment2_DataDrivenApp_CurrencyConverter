#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(950, 650);
	ofBackground(20, 24, 33); // Modern dark slate background theme

	// Initialize state variables
	conversionStatus = "Ready / Press [F] to fetch live market rates";
	convertedValue = 0.0f;
	lastUpdatedTime = "";

	// Load Windows TrueType system fonts for smooth text rendering
	titleFont.load("C:/Windows/Fonts/arial.ttf", 20, true, true);
	bodyFont.load("C:/Windows/Fonts/arial.ttf", 15, true, true);
	smallFont.load("C:/Windows/Fonts/arial.ttf", 12, true, true);

	// Configure API credentials and endpoint URL
	apiKey = "fca_live_D1Gc06mnwhmYzTbKVKUmfhjPNYx5dO2afHIQjNlY";
	apiUrl = "https://api.freecurrencyapi.com/v1/latest?apikey=" + apiKey + "&base_currency=USD&currencies=EUR";
}

//--------------------------------------------------------------
void ofApp::update() {
	// Background execution handled via user input triggers
}

//--------------------------------------------------------------
void ofApp::draw() {
	drawHeaderSection();
	drawResultCard();
	drawFooterControls();
}

//--------------------------------------------------------------
void ofApp::drawHeaderSection() {
	// Main Dashboard Header Title
	ofSetColor(255, 255, 255, 240);
	titleFont.drawString("LIVE CURRENCY EXCHANGE DASHBOARD", 50, 55);

	// Subtitle metadata description
	ofSetColor(100, 116, 139);
	smallFont.drawString("Data Source: freecurrencyapi.com | Base: USD -> Target: EUR", 50, 82);
}

//--------------------------------------------------------------
void ofApp::drawResultCard() {
	// Card Container Background Panel
	ofSetColor(30, 41, 59);
	ofDrawRectRounded(50, 115, 850, 310, 12);

	// Accent Top Border Line
	ofSetColor(59, 130, 246);
	ofDrawRectRounded(50, 115, 850, 4, 2);

	// Card Section Header
	ofSetColor(148, 163, 184);
	smallFont.drawString("CONVERSION RESULT", 80, 160);

	// Dynamic Content Rendering
	if (convertedValue > 0.0f) {
		ofSetColor(255);
		std::string mainRateStr = "1.00 USD  =  " + ofToString(convertedValue, 4) + " EUR";
		titleFont.drawString(mainRateStr, 80, 220);

		ofSetColor(34, 197, 94); // Success green indicator
		bodyFont.drawString("[ACTIVE RATE SYNCHRONIZED SUCCESSFULLY]", 80, 270);

		if (!lastUpdatedTime.empty()) {
			ofSetColor(148, 163, 184);
			smallFont.drawString("Last Updated Timestamp: " + lastUpdatedTime, 80, 320);
		}
	} else {
		ofSetColor(203, 213, 225);
		bodyFont.drawString("Waiting for live data feed... Press 'F' to load.", 80, 220);
	}
}

//--------------------------------------------------------------
void ofApp::drawFooterControls() {
	// Footer Action Banner Panel
	ofSetColor(30, 41, 59);
	ofDrawRectRounded(50, 455, 850, 135, 12);

	// Controls Instructions Header
	ofSetColor(255, 255, 255, 200);
	smallFont.drawString("USER CONTROLS & STATUS", 80, 490);

	// Key Action Prompt
	ofSetColor(59, 130, 246);
	bodyFont.drawString("-> Press [ F ] Key: Fetch or Refresh Exchange Rate", 80, 530);

	// Live Feedback Status Line
	ofSetColor(148, 163, 184);
	smallFont.drawString("System Status: " + conversionStatus, 80, 565);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// Trigger data retrieval when 'f' or 'F' is pressed
	if (key == 'f' || key == 'F') {
		fetchExchangeRate();
	}
}

//--------------------------------------------------------------
void ofApp::fetchExchangeRate() {
	conversionStatus = "Connecting to API endpoint...";

	// Execute synchronous network request to fetch JSON payload instantly
	ofHttpResponse response = ofLoadURL(apiUrl);

	if (response.status == 200) {
		bool parsingSuccessful = jsonResponse.parse(response.data.getText());

		if (parsingSuccessful) {
			// Safely parse JSON structure: root -> data -> EUR
			convertedValue = jsonResponse["data"]["EUR"].asFloat();
			conversionStatus = "Data successfully fetched and parsed";
			lastUpdatedTime = ofGetTimestampString("%H:%M:%S");
		} else {
			conversionStatus = "Error: Failed to parse incoming JSON structure.";
		}
	} else {
		conversionStatus = "Error: HTTP request failed with status code " + ofToString(response.status);
	}
}
