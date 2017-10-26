#include <string>
#include <cstdlib>
#include "Dependencies\glew.h"
#include "Object.h"

#pragma comment(lib, "winmm.lib")

#define MAX_OBJECTS_COUNT		50

float current_time = (float)timeGetTime();

class SceneMgr {
private:
	Object* m_objects[MAX_OBJECTS_COUNT];
	int count = 0;
	int maxcount = MAX_OBJECTS_COUNT;
	float stime, ntime;
	float frame_time;
public:
	SceneMgr() : count(0) { current_time = (float)timeGetTime(); }
	~SceneMgr() {
		delete* m_objects;
	}
	void input(float x, float y) {
		if (count < MAX_OBJECTS_COUNT) {
			m_objects[count] = new Object(x, y, 0);
			count++;
		}
	}

	bool collision(Object* a, Object* b) {
		CollBox* Ca = a->getCollBox();
		CollBox* Cb = b->getCollBox();
		if (Ca->left > Cb->right) return false;
		if (Ca->right < Cb->left) return false;
		if (Ca->top < Cb->bottom) return false;
		if (Ca->bottom > Cb->top) return false;
		return true;
	}

	bool sub_coll(Object* a) {
		for (int i = 0; i < count; ++i) {
			if (a != m_objects[i]) {
				if (collision(a, m_objects[i])) return false; 
			}
		}
		return true;
	}

	void draw() {
		for (int i = 0; i < count; ++i) {
			m_objects[i]->draw();
			if (sub_coll(m_objects[i]))
				m_objects[i]->changecolor(WHITE);
			else
				m_objects[i]->changecolor(RED);
		}
	}

	void update() {
		frame_time = (float)timeGetTime() - current_time;
		current_time += frame_time;
		for (int i = 0; i < count; ++i) {
			if (m_objects[i]->what_state()) {
				//del(i);
			}
			m_objects[i]->update(frame_time);
		}
	}
	void del(int key) {
		for (int i = key; i < count; ++i) {
			m_objects[key] = m_objects[key + 1];
		}
	}
	int size() const { return count; }
};