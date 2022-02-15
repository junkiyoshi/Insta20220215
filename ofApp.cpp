#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetColor(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> location_list;
	vector<float> deg_list;
	vector<bool> flag_list;
	vector<int> near_index_list;

	for (int i = 0; i < 65; i++) {

		location_list.push_back(glm::vec2(ofRandom(50, ofGetWidth() - 50), ofRandom(50, ofGetHeight() - 50)));
		deg_list.push_back(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, -360, 360));
		flag_list.push_back(false);
	}

	for (int i = 0; i < location_list.size(); i++) {

		ofNoFill();
		for (int k = i + 1; k < location_list.size(); k++) {

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 80) {

				auto handle_1 = location_list[i] + glm::vec2(50 * cos(deg_list[i] * DEG_TO_RAD), 50 * sin(deg_list[i] * DEG_TO_RAD));
				auto handle_2 = location_list[k] + glm::vec2(50 * cos(deg_list[k] * DEG_TO_RAD), 50 * sin(deg_list[k] * DEG_TO_RAD));

				ofBeginShape();
				ofVertex(location_list[i]);
				ofBezierVertex(handle_1, handle_2, location_list[k]);
				ofEndShape();

				flag_list[i] = true;
				flag_list[k] = true;
			}
		}

		ofFill();
		ofDrawCircle(location_list[i], 5);
	}

	ofNoFill();
	for (int i = 0; i < location_list.size(); i++) {

		if (flag_list[i] == false) {

			float min_distance = ofGetWidth() + ofGetHeight();
			int min_index = 0;
			for (int k = 0; k < location_list.size(); k++) {

				if (i == k) { continue; }
				auto distance = glm::distance(location_list[i], location_list[k]);
				if (distance < min_distance) {

					min_distance = distance;
					min_index = k;
				}
			}

			auto handle_1 = location_list[i] + glm::vec2(50 * cos(deg_list[i] * DEG_TO_RAD), 50 * sin(deg_list[i] * DEG_TO_RAD));
			auto handle_2 = location_list[min_index] + glm::vec2(50 * cos(deg_list[min_index] * DEG_TO_RAD), 50 * sin(deg_list[min_index] * DEG_TO_RAD));

			ofBeginShape();
			ofVertex(location_list[i]);
			ofBezierVertex(handle_1, handle_2, location_list[min_index]);
			ofEndShape();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}