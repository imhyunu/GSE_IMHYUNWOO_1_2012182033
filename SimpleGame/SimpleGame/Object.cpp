#include "stdafx.h"
#include "Object.h"


Object::Object(float pX, float pY, float pZ, float pType, int pTeam, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA) {
	x = pX;		y = pY;		z = pZ;
	type = pType;		life = pLife;
	size = pSize;		speed = pSpeed;
	team = pTeam;
	vx = (float)rand() / (float)RAND_MAX;
	vy = (float)sqrt(1 - (vx * vx));
	if ((float)rand() / (float)RAND_MAX > 0.5f)
		vx *= -1;
	if ((float)rand() / (float)RAND_MAX > 0.5f)
		vy *= -1;
	r = pR;		g = pG;		b = pB;
	a = pA;
	float s = size / 2;
	bullet_Cooltime = 0.0f;
	arrow_Cooltime = 0.0f;
	collBox[0] = x - s;		collBox[1] = x + s;
	collBox[2] = y - s;		collBox[3] = y + s;
}

bool Object::outX(){
	float s = size / 2;
	if (x < (s - H_WIDTH)) {
		x = s - H_WIDTH;
		return true;
	}
	if (x > (H_WIDTH - s)) {
		x = H_WIDTH - s;
		return true;
	}
	return false;
}

bool Object::outY() {
	float s = size / 2;
	if (y < (s - H_HEIGHT)) {
		y = s - H_HEIGHT;
		return true;
	}
	if (y >(H_HEIGHT - s)) {
		y = H_HEIGHT - s;
		return true;
	}
	return false;
}

void Object::update(float frame_time) {
	x += (vx * frame_time * speed);
	y += (vy * frame_time * speed);
	bullet_Cooltime += frame_time;
	arrow_Cooltime += frame_time;
	if ( outX() )		vx *= -1;
	if ( outY() )		vy *= -1;
	float s = size / 2;
	collBox[0] = x - s;		collBox[1] = x + s;
	collBox[2] = y - s;		collBox[3] = y + s;
}