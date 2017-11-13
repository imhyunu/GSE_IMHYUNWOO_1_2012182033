#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() {
	g_Renderer = new Renderer(500, 500);
	arrowReload = 0.5f;
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		m_objects[i] = NULL;
	}
	buildingPNG = g_Renderer->CreatePngTexture("./Resourses/monster.png");
	objectPNG = g_Renderer->CreatePngTexture("./Resourses/Object.png");
	bulletPNG = g_Renderer->CreatePngTexture("./Resourses/Bullet.png");
	arrowPNG = g_Renderer->CreatePngTexture("./Resourses/Arrow.png");
	input(0, 0, OBJECT_BUILDING);
}

SceneMgr::~SceneMgr() {
	delete g_Renderer;
	delete*m_objects;
	delete m_building;
}

void SceneMgr::input(float x, float y, int type) {
	if ((type == OBJECT_BUILDING) && (m_building == NULL)) {
		m_building = new Object(x, y, 0, 500, 50, 1, 1, 0);
	}

	if (type == OBJECT_CHARACTER) {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if (m_objects[i] == NULL) {
				m_objects[i] = new Object(x, y, 300, 10, 10, 1, 1, 1);
				return;
			}
		}
	}

	if (type == OBJECT_BULLET) {
		for (int i = 0; i < 20; ++i) {
			if (m_bullet[i] == NULL) {
				m_bullet[i] = new Object(x, y, 300, 10, 3, 1, 0, 0);
				return;
			}
		}
	}

	if (type == OBJECT_ARROW) {
		for (int i = 0; i < 200; ++i) {
			if (m_arrow[i] == NULL) {
				m_arrow[i] = new Object(x, y, 300, 10, 3, 0, 1, 0);
				return;
			}
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
	if (m_building != NULL) {
		g_Renderer->DrawTexturedRect(
			m_building->x, m_building->y, m_building->z,
			m_building->size,
			m_building->r, m_building->g, m_building->b,
			m_building->a, buildingPNG
		);
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (m_objects[i] != NULL) {
			g_Renderer->DrawTexturedRect(
				m_objects[i]->x, m_objects[i]->y, m_objects[i]->z,
				m_objects[i]->size,
				m_objects[i]->r, m_objects[i]->g, m_objects[i]->b,
				m_objects[i]->a, objectPNG
			);
		}
	}
	for (int i = 0; i < 20; ++i) {
		if (m_bullet[i] != NULL) {
			g_Renderer->DrawTexturedRect(
				m_bullet[i]->x, m_bullet[i]->y, m_bullet[i]->z,
				m_bullet[i]->size,
				m_bullet[i]->r, m_bullet[i]->g, m_bullet[i]->b,
				m_bullet[i]->a, bulletPNG
			);
		}
	}
	for (int i = 0; i < 200; ++i) {
		if (m_arrow[i] != NULL) {
			g_Renderer->DrawTexturedRect(
				m_arrow[i]->x, m_arrow[i]->y, m_arrow[i]->z,
				m_arrow[i]->size,
				m_arrow[i]->r, m_arrow[i]->g, m_arrow[i]->b,
				m_arrow[i]->a, arrowPNG
			);
		}
	}
}

void SceneMgr::brokenBuilding() {
	if (m_building != NULL) {
		delete m_building;
		m_building = NULL;
	}
}

void SceneMgr::dieObject(int num) {
	if (m_objects[num] != NULL) {
		delete m_objects[num];
		m_objects[num] = NULL;
	}
}

void SceneMgr::dieArrow(int num) {
	if (m_arrow[num] != NULL) {
		delete m_arrow[num];
		m_arrow[num] = NULL;
	}
}

void SceneMgr::dieBullet(int num) {
	if (m_bullet[num] != NULL) {
		delete m_bullet[num];
		m_bullet[num] = NULL;
	}
}

void SceneMgr::update(float frame_time) {
	if (m_building != NULL) {
		m_building->update(frame_time);
		if (m_building->bulletCoolOK()) {
			input(m_building->x, m_building->y, OBJECT_BULLET);
		}
	}

	for (int i = 0; i < 20; ++i) {
		if (m_bullet[i] != NULL) {
			m_bullet[i]->update(frame_time);
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (m_objects[j] != NULL) {
					if (collision(m_bullet[i], m_objects[j])) {
						float num = m_bullet[i]->getLife();
						m_objects[j]->damageLife(num);
						dieBullet(i);
						if (m_objects[j]->lifeOff()) {
							dieObject(j);
						}
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (m_objects[i] != NULL) {
			m_objects[i]->update(frame_time);
			if (m_objects[i]->arrowCoolOK()) {
				input(m_objects[i]->x, m_objects[i]->y, OBJECT_ARROW);
			}
			if (m_building != NULL) {
				if (collision(m_building, m_objects[i])) {
					float num = m_objects[i]->getLife();
					m_building->damageLife(num);
					dieObject(i);
					if (m_building->lifeOff())
						brokenBuilding();
				}
			}
		}
	}

	for (int i = 0; i < 200; ++i) {
		if (m_arrow[i] != NULL) {
			m_arrow[i]->update(frame_time);
			if (m_building != NULL) {
				if (collision(m_arrow[i], m_building)) {
					float num = m_arrow[i]->getLife();
					m_building->damageLife(num);
					dieArrow(i);
					if (m_building->lifeOff())
						brokenBuilding();
				}
			}
			
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if ((m_objects[j] != NULL) && (m_arrow[i] != NULL)) {
					if (m_arrow[i]->collisionOK()) {
						if (collision(m_arrow[i], m_objects[j])) {
							float num = m_arrow[i]->getLife();
							m_objects[j]->damageLife(num);
							dieArrow(i);
							if (m_objects[j]->lifeOff())
								dieObject(j);
							break;
						}
					}
				}
			}
		}
	}
}
