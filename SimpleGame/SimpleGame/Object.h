#pragma once
class Object
{
public:
	int type, team, level;
	float x, y, z;
	float targetX, targetY;
	float size, speed;
	float r, g, b, a;
	float vx, vy;
	float life;
	float collBox[4];
	float bullet_Cooltime;
	float arrow_Cooltime;
	float charater_Cooltime;
	float team1_char_ani_time, team2_char_ani_time;
	float team1_build_ani_time, team2_build_ani_time;
	int char_Team1_Draw, char_Team2_Draw[2];
	int build_Team1_Draw, build_Team2_Draw;
	float bullet_particle_time;
	float target_Range;
	float view_Range;
	int findState;
	Object* target_Object;
	Object(float pX, float pY, float pZ, float pType, int pTeam, float pLevel, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA);
	Object(float pX, float pY, float pZ, float tx, float ty, float pType, int pTeam, float pLevel, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA);

	bool outX();
	bool outY();
	bool lifeOff() { return (life <= 0.0f); }
	bool bulletCoolOK();
	bool arrowCoolOK();
	bool targetInRange(float oX, float oY);

	void damage(float num) { life -= num; }
	void changeColor(float pR, float pG, float pB) {
		r = pR;		g = pG;		b = pB;
	}
	void set_Target(Object* t);
	void update(float frame_time);
};

