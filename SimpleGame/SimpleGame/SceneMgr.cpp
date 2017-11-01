#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() {
	g_Renderer = new Renderer(500, 500);
	current_time = (float)timeGetTime();
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		m_objects[i] = NULL;
	}
}
SceneMgr::~SceneMgr() {
	delete g_Renderer;
	delete*m_objects;
}

void SceneMgr::input(float x, float y) {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (m_objects[i] == NULL) {
			m_objects[i] = new Object(x, y);
			return;
		}
	}
}

bool SceneMgr::collision(Object* a, Object* b) {
	CollBox* Ca = a->getCollBox();
	CollBox* Cb = b->getCollBox();
	if (Ca->left > Cb->right) return false;
	if (Ca->right < Cb->left) return false;
	if (Ca->top < Cb->bottom) return false;
	if (Ca->bottom > Cb->top) return false;
	return true;
}

bool SceneMgr::sub_coll(int num) {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if ((num != i) && (m_objects[i] != NULL)) {
			if (collision(m_objects[num], m_objects[i])) return false;
		}
	}
	return true;
}

void SceneMgr::draw() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (m_objects[i] != NULL) {
			g_Renderer->DrawSolidRect(
				m_objects[i]->x, m_objects[i]->y, m_objects[i]->z,
				m_objects[i]->size,
				m_objects[i]->r, m_objects[i]->g, m_objects[i]->b,
				m_objects[i]->a
			);
		}
	}
}

void SceneMgr::update() {
	frame_time = (float)timeGetTime() - current_time;
	current_time += frame_time;
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (m_objects[i] != NULL) {
			m_objects[i]->update(frame_time);
			if (sub_coll(i))
				m_objects[i]->changecolor(WHITE);
			else
				m_objects[i]->changecolor(RED);
		}
	}
}
