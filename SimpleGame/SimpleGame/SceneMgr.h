#include <cstdlib>
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT		50

class SceneMgr {
private:
	Renderer *g_Renderer = NULL;
	Object* m_objects[MAX_OBJECTS_COUNT];
	int maxcount = MAX_OBJECTS_COUNT;
	float current_time = (float)timeGetTime();
	float frame_time;

public:
	SceneMgr();
	~SceneMgr();

	void input(float x, float y);

	bool collision(Object* a, Object* b);

	bool sub_coll(int num);

	void draw();

	void update();
};