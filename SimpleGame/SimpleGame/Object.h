#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>

#include "CollisionBox.h"

using namespace std;


enum { RED, WHITE };

class Object{
public:

	float x, y, z;
	float size = 10.0f;
	float r = 1.0f, g = 1.0f, b = 1.0f;
	float a = 0.0f;
	float veloc = 7;
	float life = 3;
	float nlife = 0;
	pair<float, float> v {0.0f, 0.0f};
	CollBox* collbox;

	Object(
		float oX, float oY, 
		float oSpeed, float oLife, float oSize,
		float oR, float oG, float oB
	);
	~Object();

	void update(float frame_time);

	CollBox* getCollBox();

	void changecolor(int key);

	float getLife() { return life; }
	void damageLife(float num) { life -= num; }
	bool lifeOff() { return (life < 0.0); }
};