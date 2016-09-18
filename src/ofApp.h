#pragma once

#include <vector>

#include <ofMain.h>


class ofApp : public ofBaseApp{
private:
	ofPoint position;
	double heading;

	int left_power, right_power;

public:
	void setup();
	void draw();

	void keyPressed(int key);
};
