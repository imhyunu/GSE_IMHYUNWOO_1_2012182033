#include "stdafx.h"
#include "Object.h"


Object::Object(float pX, float pY, float pZ, float tRange, float pType, int pTeam, float pLevel, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA) {
	x = pX;		y = pY;		z = pZ;
	type = pType;		life = pLife;
	size = pSize;		speed = pSpeed;		level = pLevel;
	team = pTeam;
	target_Range = tRange;
	target_Object = NULL;
	findState = 0;

	if (team == TEAM_1) {
		vx = 0.0f;
		vy = 1.0f;
	}
	else {
		vx = 0.0f;
		vy = -1.0f;
	}
	r = pR;		g = pG;		b = pB;
	a = pA;
	float s = size / 2;
	bullet_Cooltime = BULLET_COOLTIME;
	arrow_Cooltime = ARROW_COOLTIME;
	team1_char_ani_time = 0.0f;
	team2_char_ani_time = 0.0f;
	team1_build_ani_time = 0.0f;
	team2_build_ani_time = 0.0f;
	char_Team2_Draw[0] = 0;
	char_Team2_Draw[1] = 0;
	build_Team1_Draw = build_Team2_Draw = 0;
	bullet_particle_time = 0;
	if (pType == CHARACTER) {
		view_Range = CHARACTER_VIEW;
	}
	else if(pType == BUILDING){
		view_Range = BUILDING_VIEW;
	}
	collBox[0] = x - s;		collBox[1] = x + s;
	collBox[2] = y - s;		collBox[3] = y + s;
}

Object::Object(float pX, float pY, float pZ, float tx, float ty, float pType, int pTeam, float pLevel, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA) {
	x = pX;		y = pY;		z = pZ;
	type = pType;		life = pLife;
	size = pSize;		speed = pSpeed;		level = pLevel;
	team = pTeam;
	target_Object = NULL;
	findState = 0;
	vx = tx;
	vy = ty;
	r = pR;		g = pG;		b = pB;
	a = pA;
	float s = size / 2;
	bullet_Cooltime = BULLET_COOLTIME;
	arrow_Cooltime = ARROW_COOLTIME;
	team1_char_ani_time = 0.0f;
	team2_char_ani_time = 0.0f;
	team1_build_ani_time = 0.0f;
	team2_build_ani_time = 0.0f;
	char_Team2_Draw[0] = 0;
	char_Team2_Draw[1] = 0;
	build_Team1_Draw = build_Team2_Draw = 0;
	bullet_particle_time = 0;
	if (pType == CHARACTER) {
		view_Range = CHARACTER_VIEW;
	}
	else if (pType == BUILDING) {
		view_Range = BUILDING_VIEW;
	}
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
	if (bullet_Cooltime > BULLET_COOLTIME && findState == 1) {
		bullet_Cooltime = 0.0f;
		return true;
	}
	return false;
}

bool Object::arrowCoolOK() {
	if (arrow_Cooltime > ARROW_COOLTIME && findState == 1) {
		arrow_Cooltime = 0.0f;
		return true;
	}
	return false;
}

bool Object::targetInRange(float oX, float oY) {
	float num = ((oX - x) * (oX - x)) + ((oY - y) * (oY - y));
	if (num > (target_Range * target_Range)) {
		return false;
	}
	return true;
}

void Object::set_Target(Object* t) {
	target_Object = t;
}

void Object::die_Target() {
	target_Object = NULL;
	delete target_Object;
	findState = 0; 
	if (team == TEAM_1)
		vy = 1.0f;
	else
		vy = -1.0f;
}

void Object::update(float frame_time) {
	if (target_Object != NULL) {
		float num = sqrt(
			((target_Object->x - x) * (target_Object->x - x)) +
			((target_Object->y - y) * (target_Object->y - y))
		);
		targetX = (target_Object->x - x) / num;
		targetY = (target_Object->y - y) / num;
	}
	if (findState == 0) {
		x += (vx * frame_time * speed);
		y += (vy * frame_time * speed);
	}
	bullet_Cooltime += frame_time;
	arrow_Cooltime += frame_time;
	if(team != TEAM_1 || findState == 0)
		team1_char_ani_time += frame_time;
	team1_build_ani_time += frame_time;
	team2_build_ani_time += frame_time;
	bullet_particle_time += frame_time;
	if (char_Team2_Draw[0] < 3 || char_Team2_Draw[1] < 3)
		team2_char_ani_time += frame_time;

	if (team1_char_ani_time > TEAM1_CHARACTHER_ANI_TIME) {
		team1_char_ani_time = 0;
		if (char_Team1_Draw < 3)
			++char_Team1_Draw;
		else
			char_Team1_Draw = 0;
	}
	if (team2_char_ani_time > TEAM2_CHARACTHER_ANI_TIME) {
		team2_char_ani_time = 0.0f;
		if (char_Team2_Draw[0] < 3)
			++char_Team2_Draw[0];
		else if(char_Team2_Draw[1] < 3){
			++char_Team2_Draw[1];
			char_Team2_Draw[0] = 0;
		}
	}
	if (team1_build_ani_time > TEAM1_BUILDING_ANI_TIME) {
		team1_build_ani_time = 0;
		if (build_Team1_Draw < 3)
			build_Team1_Draw++;
		else
			build_Team1_Draw = 0;
	}
	if (team2_build_ani_time > TEAM2_BUILDING_ANI_TIME) {
		team2_build_ani_time = 0;
		if (build_Team2_Draw < 3)
			build_Team2_Draw++;
		else
			build_Team2_Draw = 0;
	}
	if (outX()) {
		if (type == CHARACTER)
			vx *= -1;
		else
			life = 0;
	}
	if (outY())	{
		if (type == CHARACTER) {
			vy = (float)rand() / RAND_MAX;
			vx = sqrt(1 - (vy * vy));
			if (((float)rand() / RAND_MAX) > 0.5)
				vx *= -1;
		}
		else
			life = 0;
	}
	float s = size / 2;
	collBox[ LEFT ] = x - s;		collBox[ RIGHT ] = x + s;
	collBox[ BOTTOM ] = y - s;		collBox[ TOP ] = y + s;
}