#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");
}

//--------------------------------------------------------------
void ofApp::update(){

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw(){

	this->draw_circles(ofPoint(ofGetWidth() / 2, ofGetHeight() / 2), 300, 600);
}

//--------------------------------------------------------------
void ofApp::draw_circles(ofPoint range_point, int range_radius, int number_of_circles) {

	ofPushMatrix();
	ofTranslate(range_point);

	int min = 3;
	int max = 35;

	vector<tuple<ofColor, ofPoint, float>> circles;
	while (circles.size() < number_of_circles) {

		ofPoint point = ofPoint(ofRandom(-range_radius, range_radius), ofRandom(-range_radius, range_radius));
		point *= 1 + ofNoise(point.x * 0.005, point.y * 0.005, ofGetFrameNum() * 0.005);
		if (point.length() > range_radius) {

			continue;
		}

		ofColor color;
		color.setHsb(ofRandom(0, 255), 239, 239);
		float radius = ofRandom(min, max);

		bool flag = true;
		for (int i = 0; i < circles.size(); i++) {

			while (radius > min) {

				if (point.distance(get<1>(circles[i])) < get<2>(circles[i]) + radius) {

					radius *= 0.9;
				}
				else {

					break;
				}
			}

			if (radius < min) {
				
				flag = false;
				break;
			}
		}

		if (flag) {

			circles.push_back(make_tuple(color, point, radius));
		}
	}

	for (int circles_index = 0; circles_index < circles.size(); circles_index++) {

		ofColor color = get<0>(circles[circles_index]);
		ofPoint point = get<1>(circles[circles_index]);
		float radius = get<2>(circles[circles_index]);

		ofSetColor(color);
		ofDrawCircle(point, radius);
	}

	ofPopMatrix();
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
