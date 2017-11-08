#include <cstdlib>
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT		10
#define RELOAD					0.5f

enum {OBJECT_BUILDING, OBJECT_CHARACTER, OBJECT_BULLET, OBJECT_ARROW};

class SceneMgr {
private:
	Renderer *g_Renderer = NULL;
	Object* m_objects[MAX_OBJECTS_COUNT];
	Object* m_building;
	Object* m_bullet[20];
	Object* m_arrow[20];
	float arrowReload = RELOAD;

public:
	SceneMgr();
	~SceneMgr();

	void input(float x, float y, int type);

	bool collision(Object* a, Object* b);

	bool sub_coll(int num);

	void draw();

	void update(float frame_time);

	void dieObject(int num);

	void dieArrow(int num);

	void brokenBuilding();
};