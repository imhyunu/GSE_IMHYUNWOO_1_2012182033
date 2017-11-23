#include "stdafx.h"
#include "Object.h"


Object::Object(float pX, float pY, float pZ, float pType, int pTeam, float pLevel, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA) {
	x = pX;		y = pY;		z = pZ;
	type = pType;		life = pLife;
	size = pSize;		speed = pSpeed;		level = pLevel;
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
	bullet_Cooltime = BULLET_COOLTIME;
	arrow_Cooltime = ARROW_COOLTIME;
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

bool Object::bulletCoolOK() {
	if (bullet_Cooltime > BULLET_COOLTIME) {
		bullet_Cooltime = 0.0f;
		return true;
	}
	return false;
}

bool Object::arrowCoolOK() {
	if (arrow_Cooltime > ARROW_COOLTIME) {
		arrow_Cooltime = 0.0f;
		return true;
	}
	return false;
}

void Object::update(float frame_time) {
	x += (vx * frame_time * speed);
	y += (vy * frame_time * speed);
	bullet_Cooltime += frame_time;
	arrow_Cooltime += frame_time;
	if (outX()) {
		if (type == CHARACTER)
			vx *= -1;
		else
			life = 0;
	}
	if (outY())	{
		if (type == CHARACTER)
			vy *= -1;
		else
			life = 0;
	}
	float s = size / 2;
	collBox[ LEFT ] = x - s;		collBox[ RIGHT ] = x + s;
	collBox[ BOTTOM ] = y - s;		collBox[ TOP ] = y + s;
}