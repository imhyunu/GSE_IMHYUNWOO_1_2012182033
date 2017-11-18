#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() {
	srand(time(NULL));
	g_Renderer = new Renderer(WIDTH, HEIGHT);
	team1_Char_CoolTime = 7.0f;
	team2_Char_CoolTime = 5.0f;
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
		objects[i] = NULL;

	for (int i = 0; i < 3; ++i) {
		input((i * 200) - 200, -330, BUILDING, TEAM_1);
	}
	for (int i = 0; i < 3; ++i) {
		input((i * 200) - 200, 330, BUILDING, TEAM_2);
	}
}

SceneMgr::~SceneMgr() {
	delete g_Renderer;
	delete[] objects;
}

bool SceneMgr::collision(Object* a, Object* b) {
	if (a->collBox[0] > b->collBox[1])	return false;
	if (a->collBox[1] < b->collBox[0])	return false;
	if (a->collBox[2] > b->collBox[3])	return false;
	if (a->collBox[3] < b->collBox[2])	return false;
	return true;
}

bool SceneMgr::myselfCollision(Object* a) {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if ( (objects[i] != NULL) && (a != objects[i]) && (objects[i]->type != BUILDING))
			if (collision(a, objects[i]))
				return true;
	}
	return false;
}

bool SceneMgr::team1_Char_CoolTimeOK() {
	if (team1_Char_CoolTime > 7.0f) {
		team1_Char_CoolTime = 0.0f;
		return true;
	}
	return false;
}

bool SceneMgr::team2_Char_CoolTimeOK() {
	if (team2_Char_CoolTime > 5.0f) {
		team2_Char_CoolTime = 0.0f;
		return true;
	}
	return false;
}

void SceneMgr::dieObject(int num) {
	if (objects[num] != NULL) {
		delete objects[num];
		objects[num] = NULL;
	}
}

void SceneMgr::input(float x, float y, int type, int team) {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] == NULL) {
			if (team == TEAM_1) {
				if (type == CHARATER) {
					objects[i] = new Object(x, y, 0, type, team, CHARATER_LIFE, CHARATER_SIZE, CHARATER_SPEED, 1, 0, 0, 1);
					return;
				}
				if (type == BUILDING) {
					objects[i] = new Object(x, y, 0, type, team, BUILDING_LIFE, BUILDING_SIZE, 0, 1, 1, 1, 1);
					return;

				}
				if (type == BULLET) {
					objects[i] = new Object(x, y, 0, type, team, BULLET_LIFE, BULLET_SIZE, BULLET_SPEED, 1, 0, 0, 1);
					return;
				}
				if (type == ARROW) {
					objects[i] = new Object(x, y, 0, type, team, ARROW_LIFE, ARROW_SIZE, ARROW_SPEED, 0.5, 0.2, 0.7, 1);
					return;
				}
			}
			else {
				if (type == CHARATER) {
					objects[i] = new Object(x, y, 0, type, team, CHARATER_LIFE, CHARATER_SIZE, CHARATER_SPEED, 0, 0, 1, 1);
					return;
				}
				if (type == BUILDING) {
					objects[i] = new Object(x, y, 0, type, team, BUILDING_LIFE, BUILDING_SIZE, 0, 1, 1, 1, 1);
					return;

				}
				if (type == BULLET) {
					objects[i] = new Object(x, y, 0, type, team, BULLET_LIFE, BULLET_SIZE, BULLET_SPEED, 0, 0, 1, 1);
					return;
				}
				if (type == ARROW) {
					objects[i] = new Object(x, y, 0, type, team, ARROW_LIFE, ARROW_SIZE, ARROW_SPEED, 1, 1, 0, 1);
					return;
				}
			}
		}
	}
}

void SceneMgr::draw() {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL) {
			if (objects[i]->type != BUILDING) {
				g_Renderer->DrawSolidRect(
					objects[i]->x, objects[i]->y, objects[i]->z,
					objects[i]->size, objects[i]->r,
					objects[i]->g, objects[i]->b, objects[i]->a
				);
			}
			if (objects[i]->type == BUILDING) {
				if (objects[i]->team == TEAM_1)
					buildingPng = g_Renderer->CreatePngTexture("./Resourses/building_Team2.png");
				else
					buildingPng = g_Renderer->CreatePngTexture("./Resourses/building_Team1.png");
				g_Renderer->DrawTexturedRect(
					objects[i]->x, objects[i]->y, objects[i]->z,
					objects[i]->size, objects[i]->r,
					objects[i]->g, objects[i]->b, objects[i]->a,
					buildingPng
				);
			}
		}
	}
}

void SceneMgr::update(float frame_time) {
	team1_Char_CoolTime += frame_time;
	team2_Char_CoolTime += frame_time;
	if (team2_Char_CoolTimeOK()) {
		float x = ((float)rand() / (float)RAND_MAX * WIDTH) - H_WIDTH;
		float y = ((float)rand() / (float)RAND_MAX * H_HEIGHT);
		input(x, y, CHARATER, TEAM_2);
	}
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL) {
			objects[i]->update(frame_time);
			if (objects[i]->type == BUILDING) {
				if (objects[i]->bulletCoolOK())
					input(objects[i]->x, objects[i]->y, BULLET, objects[i]->team);
			}
			if (objects[i]->type == CHARATER) {
				if (objects[i]->arrowCoolOK())
					input(objects[i]->x, objects[i]->y, ARROW, objects[i]->team);
			}
		}
	}

	collisionObject(CHARATER, BUILDING);
	collisionObject(CHARATER, BULLET);
	collisionObject(CHARATER, ARROW);
	collisionObject(BULLET, BUILDING);
	collisionObject(ARROW, BUILDING);
}

void SceneMgr::coll_Cha_Cha() {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL) {
			if (objects[i]->type != BUILDING) {
				if (myselfCollision(objects[i]))
					objects[i]->changeColor(1.0f, 0.0f, 0.0f);
				else
					objects[i]->changeColor(1.0f, 1.0f, 1.0f);
			}
		}
	}
}

void SceneMgr::coll_Cha_Bui() {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL && objects[i]->type != BUILDING) {
			for (int j = 0; j < MAX_PLAYER_COUNT; ++j) {
				if ((objects[j] != NULL) && (objects[j]->type == BUILDING)) {
					if (collision(objects[i], objects[j])) {
						objects[j]->damage(objects[i]->life);
						dieObject(i);
						if (objects[j]->lifeOff())
							dieObject(j);
						break;
					}
				}
			}
		}
	}
}

void SceneMgr::collisionObject(int type1, int type2) {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL && objects[i]->type == type1) {
			for (int j = 0; j < MAX_PLAYER_COUNT; ++j) {
				if ((objects[j] != NULL) && (objects[j]->type == type2) && (objects[i]->team != objects[j]->team)) {
					if (collision(objects[i], objects[j])) {
						objects[i]->damage(objects[j]->life);
						objects[j]->damage(objects[i]->life);
						if (objects[i]->lifeOff())
							dieObject(i);
						if (objects[j]->lifeOff())
							dieObject(j);
						break;
					}
				}
			}
		}
	}
}
