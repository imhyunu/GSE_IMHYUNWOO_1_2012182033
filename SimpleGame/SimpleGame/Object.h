#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>

#include "CollisionBox.h"

using namespace std;


enum { RED, WHITE };

#define PIXELPERMETER 20.0f

class Object{
public:

	float x, y, z;
	float size = 10.0f;
	float r = 1.0f, g = 1.0f, b = 1.0f;
	float a = 0.0f;
	float veloc = 7;
	float life = 3;
	float nlife = 0;
	pair<float, float> v {1.0f, 1.0f};
	CollBox* collbox;

	Object(float ox, float oy);

	void update(float frame_time);

	CollBox* getCollBox();

	void changecolor(int key);

};