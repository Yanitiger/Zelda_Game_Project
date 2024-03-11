#pragma once

#include "ofMain.h"

class Animation {

private:
	int speed, index, timer;
	bool end, loop;
	vector<ofImage> frames;

public:
	Animation(int speed, vector<ofImage> frames, bool loop = true)
	{
		this->speed = speed;
		this->frames = frames;
		this->loop = loop;
		this->reset();
	}

	void update();
	void draw(int x, int y, int w, int h);
	void reset();

	ofImage getCurrentFrame();
	bool hasEnded() { return end; }
	void setLoop(bool loop) { this->loop = loop; }
	int getIndex() { return index; }
	void setSpeed(int speed) { this->speed = speed; }

};