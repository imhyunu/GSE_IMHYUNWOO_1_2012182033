#include "Renderer.h"
#include "Sound.h"
#include "Object.h"

#define MAX_PLAYER_COUNT		100

class SceneMgr {
	Renderer *g_Renderer = NULL;
	Sound *m_sound = NULL;
	Object* objects[MAX_PLAYER_COUNT];
	GLuint buildingPng;
	GLuint characterPng;
	GLuint backgroundPng;
	GLuint particlePng;
	int soundBGM, bullet_soundBG;
	float team1_Char_CoolTime;
	float team2_Char_CoolTime;
public:
	SceneMgr();
	~SceneMgr();

	bool collision(Object* a, Object* b);
	bool myselfCollision(Object* a);
	bool team1_Char_CoolTimeOK();
	bool team2_Char_CoolTimeOK();

	void dieObject(int num);
	void input(float x, float y, int type, int team);
	void draw();
	void update(float frame_time);
	void coll_Cha_Cha();
	void coll_Cha_Bui();
	void collisionObject(int type1, int type2);
	void someoneTargetInRange(int type1, int type2);
};