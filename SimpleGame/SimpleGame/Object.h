#pragma once
class Object
{
public:
	int type, team;
	float x, y, z;
	float size, speed;
	float r, g, b, a;
	float vx, vy;
	float life;
	float collBox[4];
	float bullet_Cooltime;
	float arrow_Cooltime;
	float charater_Cooltime;

	Object(float pX, float pY, float pZ, float pType, int pTeam, float pLife, float pSize, float pSpeed, float pR, float pG, float pB, float pA);

	bool outX();
	bool outY();
	bool lifeOff() { return (life <= 0.0f); }
	bool bulletCoolOK(){
		if (bullet_Cooltime > 5.0f) {
			bullet_Cooltime = 0.0f;
			return true;
		}
		return false;
	}
	bool arrowCoolOK(){
		if (arrow_Cooltime > 3.0f) {
			arrow_Cooltime = 0.0f;
			return true;
		}
		return false;
	}

	void damage(float num) { life -= num; }
	void changeColor(float pR, float pG, float pB) {
		r = pR;		g = pG;		b = pB;
	}
	void update(float frame_time);
};

