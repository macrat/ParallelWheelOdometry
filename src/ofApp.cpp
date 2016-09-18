#include "ofApp.h"

#define WHEEL_WIDTH  64
#define POWER_MAX    10


void ofApp::setup(){
	position.set(ofGetWidth()/2, ofGetHeight()/2);
	heading = 0;
	left_power = right_power = 0;

	ofSetBackgroundColor(ofColor::black);
}


void ofApp::draw(){
	ofFill();
	ofSetColor(ofColor::skyBlue);
	ofDrawRectangle(0, ofGetHeight()-POWER_MAX*10, 20, -left_power*10);
	ofSetColor(ofColor::pink);
	ofDrawRectangle(20, ofGetHeight()-POWER_MAX*10, 20, -right_power*10);

	ofNoFill();
	ofSetColor(ofColor::skyBlue);
	ofDrawRectangle(0, ofGetHeight()-POWER_MAX*20, 20, POWER_MAX*20);
	ofSetColor(ofColor::pink);
	ofDrawRectangle(20, ofGetHeight()-POWER_MAX*20, 20, POWER_MAX*20);

	ofPushMatrix();
	ofTranslate(position);
	ofRotate(heading * 180 / PI);

	ofSetColor(ofColor::skyBlue);
	ofNoFill();
	ofDrawRectangle(-WHEEL_WIDTH/2-10, -30, 20, 60);
	ofFill();
	ofDrawRectangle(-WHEEL_WIDTH/2-10, 0, 20, -left_power*30.0/POWER_MAX);

	ofSetColor(ofColor::pink);
	ofNoFill();
	ofDrawRectangle(WHEEL_WIDTH/2-10, -30, 20, 60);
	ofFill();
	ofDrawRectangle(WHEEL_WIDTH/2-10, 0, 20, -right_power*30.0/POWER_MAX);

	ofSetColor(ofColor::white);
	ofDrawLine(-WHEEL_WIDTH/2, 0, WHEEL_WIDTH/2, 0);

	ofPopMatrix();

	if(left_power == right_power){
		position.x -= cos(PI/2 + heading) * left_power;
		position.y -= sin(PI/2 + heading) * left_power;
	}else{
		const double rate = (double)left_power / (double)right_power;
		const double center_distance = (-1 - 1/(rate-1)) * WHEEL_WIDTH + WHEEL_WIDTH/2.0;

		if(center_distance == 0){
			const double run_angle = left_power / (WHEEL_WIDTH/2.0);

			heading += run_angle;

			ofSetColor(ofColor::green);
			ofNoFill();
			ofDrawCircle(position, 8);
		}else{
			const double run_distance = (left_power + right_power) / 2.0;
			const double run_angle = run_distance / center_distance;

			const ofPoint center(
				position.x - cos(heading)*center_distance,
				position.y - sin(heading)*center_distance
			);

			ofSetColor(ofColor::green);
			ofNoFill();
			ofDrawLine(position, center);
			ofDrawCircle(center, 8);

			ofSetColor(ofColor::red);
			ofDrawLine(
				center.x,
				center.y,
				center.x - cos(PI + heading - run_angle)*center_distance,
				center.y - sin(PI + heading - run_angle)*center_distance
			);

			position.set(
				center.x - cos(PI + heading - run_angle)*center_distance,
				center.y - sin(PI + heading - run_angle)*center_distance
			);
			heading -= run_angle;
		}
	}
}


void ofApp::keyPressed(int key){
	switch(key){
	case 'a':
		left_power++;
		break;
	case 'z':
		left_power--;
		break;
	case 'd':
		right_power++;
		break;
	case 'c':
		right_power--;
		break;
	case 's':
		left_power++;
		right_power++;
		break;
	case 'x':
		left_power--;
		right_power--;
		break;
	case ' ':
		setup();
	}
	left_power = max(-POWER_MAX, min(POWER_MAX, left_power));
	right_power = max(-POWER_MAX, min(POWER_MAX, right_power));
}
