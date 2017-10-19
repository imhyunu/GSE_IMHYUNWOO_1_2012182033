#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>

#include "Dependencies\glew.h"
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT		50

class SceneMgr {
private:
	Object* m_objects[MAX_OBJECTS_COUNT];
	int count = 0;
	int maxcount = MAX_OBJECTS_COUNT;
public:
	SceneMgr() {}
	void input(float x, float y) {
		if (count < MAX_OBJECTS_COUNT) {
			m_objects[count] = new Object(x, y, 0);
			count++;
		}
	}
	void draw() {
		for (int i = 0;i < count;++i)
			m_objects[i]->draw();
	}
	void update() {
		for (int i = 0; i < count; ++i)
			m_objects[i]->update();
	}
	int size() const { return count; }
	bool collsion(Object& a, Object& b) {
		float *aBox = a.collsion();
		float *bBox = b.collsion();
		if (aBox[0] > bBox[1])
			return false;
		if (aBox[1] < bBox[0])
			return false;
		if (aBox[3] > bBox[4])
			return false;
		if (aBox[4] < bBox[3])
			return false;
		return true;
	}
	void objectscolorchange(int key) {
		for (int i = 0; i < count; ++i)
			m_objects[i]->changecolor(key);
	}
};