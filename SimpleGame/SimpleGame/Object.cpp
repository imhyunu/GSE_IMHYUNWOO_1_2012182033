#include "stdafx.h"
#include "Object.h"

/*Object::Object(float ox, float oy) {
	x = ox; y = oy; z = 0;
	float sub = (float)rand() / (float)RAND_MAX;
	if ((float)rand() / (float)RAND_MAX < 0.5)		sub *= -1;
	v.first = sub * veloc * PIXELPERMETER;
	v.second = (sqrt(1 - (sub * sub))) * veloc * PIXELPERMETER;
	if ((float)rand() / (float)RAND_MAX < 0.5)		v.second *= -1;
}*/

Object::Object(
	float oX, float oY, 
	float oSpeed, float oLife, float oSize,
	float oR, float oG, float oB
	) {
	x = oX; y = oY; z = 0;
	veloc = oSpeed;		size = oSize;	life = oLife;
	r = oR;				g = oG;			b = oB;

	float  sub = (float)rand() / (float)RAND_MAX;
	if ((float)rand() / (float)RAND_MAX < 0.5)		sub *= -1;
	v.first = sub * veloc;
	v.second = (sqrt(1 - (sub * sub))) * veloc;
	if ((float)rand() / (float)RAND_MAX < 0.5)		v.second *= -1;
	
}

Object::~Object() {
	delete collbox;
}

void Object::update(float frame_time) {
	x += (v.first * frame_time / 1000);
	y += (v.second * frame_time / 1000);
	life -= (frame_time / 1000);
	if (x <= -250) {
		x = -245;
		v.first *= -1;
	}
	if (y <= -250) {
		y = -245;
		v.second *= -1;
	}
	if (x >= 250) {
		x = 245;
		v.first *= -1;
	}
	if (y >= 250) {
		y = 245;
		v.second *= -1;
	}
}

CollBox* Object::getCollBox() {
	float num = size / 2;
	collbox = new CollBox(x - num, x + num, y + num, y - num);
	return collbox;
}

void Object::changecolor(int key) {
	if (key == RED) {
		r = 1.0;
		g = 0.0;
		b = 0.0;
	}
	if (key == WHITE) {
		r = 1.0;
		g = 1.0;
		b = 1.0;
	}
}