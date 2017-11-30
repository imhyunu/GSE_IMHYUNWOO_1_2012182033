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
	if (team == TEAM_2)
		vy *= -1;
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
		if (type == CHARACTER)
			vy *= -1;
		else
			life = 0;
	}
	float s = size / 2;
	collBox[ LEFT ] = x - s;		collBox[ RIGHT ] = x + s;
	collBox[ BOTTOM ] = y - s;		collBox[ TOP ] = y + s;
}