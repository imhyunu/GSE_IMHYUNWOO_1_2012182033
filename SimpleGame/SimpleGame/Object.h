#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>

#include "CollisionBox.h"

using namespace std;


enum { RED, WHITE };

class Object {
public:

	float x, y, z;
	float size = 10.0f;
	float r = 1.0f, g = 1.0f, b = 1.0f;
	float a = 0.0f;
	float veloc = 7;
	float life = 3;
	float nlife = 0;
	float bulletCooltime = 0.0f;
	float arrowCooltime = 0.0f;
	float colltime = 0.0f;
	int owner;
	pair<float, float> v{ 0.0f, 0.0f };
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
	void setOwner(int num) {
		owner = num;
	}

	float getLife() { return life; }
	void damageLife(float num) { life -= num; }
	bool lifeOff() { return (life < 0.0); }
	bool collisionOK() {
		if (colltime > 0.3f)
			return true;
		else
			return false;
	}
	bool arrowCoolOK() {
		if (arrowCooltime > 0.5f) {
			arrowCooltime = 0.0f;
			return true;
		}
		return false;
	}
	bool bulletCoolOK() {
		if (bulletCooltime > 0.5f) {
			bulletCooltime = 0.0f;
			return true;
		}
		return false;
	}
};