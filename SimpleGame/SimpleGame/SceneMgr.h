#include "Renderer.h"
#include "Sound.h"
#include "Object.h"

#define MAX_PLAYER_COUNT		100

class SceneMgr {
	Renderer *g_Renderer = NULL;
	Sound *m_sound = NULL;
	Object* objects[MAX_PLAYER_COUNT];
	GLuint buildingPng1, buildingPng2;
	GLuint characterPng1, characterPng2;
	GLuint backgroundPng;
	GLuint particlePng1, particlePng2;
	GLuint m_texParticle;
	int soundBGM, bullet_soundBG;
	float team1_Char_CoolTime;
	float team2_Char_CoolTime;
	float cltime;
public:
	SceneMgr();
	~SceneMgr();

	bool collision(Object* a, Object* b);
	bool inViewRange(Object* a, Object* b);
	bool myselfCollision(Object* a);
	bool team1_Char_CoolTimeOK();
	bool team2_Char_CoolTimeOK();

	void dieObject(int num);
	void input(float x, float y, float tx, float ty, int type, int team);
	void draw();
	void update(float frame_time);
	void coll_Cha_Cha();
	void coll_Cha_Bui();
	void collisionObject(int type1, int type2);
	void someoneTargetInRange(int type1, int type2);
};