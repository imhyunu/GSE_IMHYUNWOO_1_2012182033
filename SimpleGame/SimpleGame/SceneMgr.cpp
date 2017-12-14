#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() {
	srand(time(NULL));
	g_Renderer = new Renderer(WIDTH, HEIGHT);
	m_sound = new Sound();
	team1_Char_CoolTime = TEAM1_HARATER_COOLTIME;
	team2_Char_CoolTime = TEAM2_HARATER_COOLTIME;
	cltime = 0;
	characterPng1 = g_Renderer->CreatePngTexture("./Resourses/charAni_team1.png");
	characterPng2 = g_Renderer->CreatePngTexture("./Resourses/charAni_team2.png");
	particlePng1 = g_Renderer->CreatePngTexture("./Resourses/particle1.png");
	particlePng2 = g_Renderer->CreatePngTexture("./Resourses/particle2.png");
	backgroundPng = g_Renderer->CreatePngTexture("./Resourses/Background.png");
	buildingPng1 = g_Renderer->CreatePngTexture("./Resourses/buildingAni_Team1.png");
	buildingPng2 = g_Renderer->CreatePngTexture("./Resourses/buildingAni_Team2.png");
	m_texParticle = g_Renderer->CreatePngTexture("./Resourses/particle1.png");
	soundBGM = m_sound->CreateSound("./Dependencies/SoundSamples/TWICE-TT-320k.mp3");
	bullet_soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/8bit_gunloop_explosion.wav");
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
		objects[i] = NULL;

	for (int i = 0; i < 3; ++i) {
		input((i * 200) - 200, -330, 0, 0, BUILDING, TEAM_1);
	}
	for (int i = 0; i < 3; ++i) {
		input((i * 200) - 200, 330, 0, 0, BUILDING, TEAM_2);
	}
	m_sound->PlaySoundW(soundBGM, true, 0.2f);
}

SceneMgr::~SceneMgr() {
	delete g_Renderer;
	delete[] objects;
}

bool SceneMgr::collision(Object* a, Object* b) {
	if (a->collBox[ LEFT ] > b->collBox[ RIGHT ])	return false;
	if (a->collBox[ RIGHT ] < b->collBox[ LEFT ])	return false;
	if (a->collBox[ BOTTOM ] > b->collBox[ TOP ])	return false;
	if (a->collBox[ TOP ] < b->collBox[ BOTTOM ])	return false;
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
	if (team1_Char_CoolTime > TEAM1_HARATER_COOLTIME) {
		team1_Char_CoolTime = 0.0f;
		return true;
	}
	return false;
}

bool SceneMgr::team2_Char_CoolTimeOK() {
	if (team2_Char_CoolTime > TEAM2_HARATER_COOLTIME) {
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

void SceneMgr::input(float x, float y, float tx, float ty, int type, int team) {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] == NULL) {
			if (team == TEAM_1) {
				if (type == CHARACTER) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_GROUND, CHARACTER_LIFE, CHARACTER_SIZE, CHARACTER_SPEED, 1, 1, 1, 1);
					return;
				}
				if (type == BUILDING) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_SKY, BUILDING_LIFE, BUILDING_SIZE, 0, 1, 1, 1, 1);
					return;

				}
				if (type == BULLET) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_UNDERGROUND, BULLET_LIFE, BULLET_SIZE, BULLET_SPEED, 1, 0, 0, 1);
					return;
				}
				if (type == ARROW) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_UNDERGROUND, ARROW_LIFE, ARROW_SIZE, ARROW_SPEED, 0.5, 0.2, 0.7, 1);
					return;
				}
			}
			else if (team == TEAM_2) {
				if (type == CHARACTER) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_GROUND, CHARACTER_LIFE, CHARACTER_SIZE, CHARACTER_SPEED, 1, 1, 1, 1);
					return;
				}
				if (type == BUILDING) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_SKY, BUILDING_LIFE, BUILDING_SIZE, 0, 1, 1, 1, 1);
					return;

				}
				if (type == BULLET) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_UNDERGROUND, BULLET_LIFE, BULLET_SIZE, BULLET_SPEED, 0, 0, 1, 1);
					return;
				}
				if (type == ARROW) {
					objects[i] = new Object(x, y, 0, type, team, LEVEL_UNDERGROUND, ARROW_LIFE, ARROW_SIZE, ARROW_SPEED, 1, 1, 0, 1);
					return;
				}
			}
		}
	}
}

void SceneMgr::draw() {
	g_Renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 0.7, backgroundPng, LEVEL_BACKGROUND);
	g_Renderer->DrawTextW(-30, -150, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, "TEAM 1");
	g_Renderer->DrawTextW(-30, 150, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, "TEAM 2");
	g_Renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, m_texParticle, cltime, 0.01);
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL) {
			if (objects[i]->type != BUILDING) {
				if (objects[i]->type == CHARACTER) {
					if (objects[i]->team == TEAM_1) {
						g_Renderer->DrawSolidRectGauge(
							objects[i]->x, objects[i]->y + CHARACTER_SIZE, objects[i]->z,
							CHARACTER_GAUGE_WIDTH, CHARACTER_GAUGE_HEIGHT,
							0.0f, 0.0f, 1.0f, 1.0f,
							objects[i]->life / CHARACTER_LIFE,
							LEVEL_GROUND
						);


						g_Renderer->DrawTexturedRectSeq(
							objects[i]->x, objects[i]->y, objects[i]->z,
							objects[i]->size, objects[i]->r,
							objects[i]->g, objects[i]->b, objects[i]->a,
							characterPng1, objects[i]->char_Team1_Draw,
							3, 4, 4,
							objects[i]->level
						);
					}
					else {
						g_Renderer->DrawSolidRectGauge(
							objects[i]->x, objects[i]->y + CHARACTER_SIZE, objects[i]->z,
							CHARACTER_GAUGE_WIDTH, CHARACTER_GAUGE_HEIGHT,
							1.0f, 0.0f, 0.0f, 1.0f,
							objects[i]->life / CHARACTER_LIFE,
							LEVEL_GROUND
						);

						g_Renderer->DrawTexturedRectSeq(
							objects[i]->x, objects[i]->y, objects[i]->z,
							objects[i]->size, objects[i]->r,
							objects[i]->g, objects[i]->b, objects[i]->a,
							characterPng2, objects[i]->char_Team2_Draw[0], 
							objects[i]->char_Team2_Draw[1], 4, 4,
							objects[i]->level
						);
					}
				}
				else {
					g_Renderer->DrawSolidRect(
						objects[i]->x, objects[i]->y, objects[i]->z,
						objects[i]->size, objects[i]->r,
						objects[i]->g, objects[i]->b, objects[i]->a,
						objects[i]->level
					);
					if (objects[i]->type == BULLET) {
						if (objects[i]->team == TEAM_1) {
							g_Renderer->DrawParticle(
								objects[i]->x, objects[i]->y, objects[i]->z,
								PATICLE_SIZE, 1, 1, 1, 1, -(objects[i]->vx), -(objects[i]->vy),
								particlePng1, objects[i]->bullet_particle_time, LEVEL_PARTICLE
							);
						}
						else {
							g_Renderer->DrawParticle(
								objects[i]->x, objects[i]->y, objects[i]->z,
								PATICLE_SIZE, 1, 1, 1, 1, -(objects[i]->vx), -(objects[i]->vy),
								particlePng2, objects[i]->bullet_particle_time, LEVEL_PARTICLE
							);
						}
					}
				}
			}
			if (objects[i]->type == BUILDING) {
				if (objects[i]->team == TEAM_1) {
					g_Renderer->DrawSolidRectGauge(
						objects[i]->x, objects[i]->y + (BUILDING_SIZE / 1.5), objects[i]->z,
						BUILDING_GAUGE_WIDTH, BUILDING_GAUGE_HEIGHT,
						0.0f, 0.0f, 1.0f, 1.0f,
						objects[i]->life / BUILDING_LIFE,
						LEVEL_SKY
					);
					g_Renderer->DrawTexturedRectSeq(
						objects[i]->x, objects[i]->y, objects[i]->z,
						objects[i]->size, objects[i]->r,
						objects[i]->g, objects[i]->b, objects[i]->a,
						buildingPng1, objects[i]->build_Team1_Draw, 3, 4, 4,
						objects[i]->level
					);
				}
				else {
					g_Renderer->DrawSolidRectGauge(
						objects[i]->x, objects[i]->y + (BUILDING_SIZE / 1.5), objects[i]->z,
						BUILDING_GAUGE_WIDTH, BUILDING_GAUGE_HEIGHT,
						1.0f, 0.0f, 0.0f, 1.0f,
						objects[i]->life / BUILDING_LIFE,
						LEVEL_SKY
					);
					g_Renderer->DrawTexturedRectSeq(
						objects[i]->x, objects[i]->y, objects[i]->z,
						objects[i]->size, objects[i]->r,
						objects[i]->g, objects[i]->b, objects[i]->a,
						buildingPng2, objects[i]->build_Team2_Draw, 0, 4, 4,
						objects[i]->level
					);
				}
			}
		}
	}
}

void SceneMgr::update(float frame_time) {
	team1_Char_CoolTime += frame_time;
	team2_Char_CoolTime += frame_time;
	cltime += frame_time;
	if (team2_Char_CoolTimeOK()) {
		float x = ((float)rand() / (float)RAND_MAX * WIDTH) - H_WIDTH;
		float y = ((float)rand() / (float)RAND_MAX * (H_HEIGHT / 4.0f)) + 300.0f;
		input(x, y, 0, 0, CHARACTER, TEAM_2);
	}
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL) {
			objects[i]->update(frame_time);
			if (objects[i]->type == BUILDING) {
				if (objects[i]->bulletCoolOK()) {
					m_sound->PlaySoundW(bullet_soundBG, false, 0.2f);
					input(objects[i]->x, objects[i]->y, 0, 0, BULLET, objects[i]->team);
				}
			}
			if (objects[i]->type == CHARACTER) {
				if (objects[i]->arrowCoolOK())
					input(objects[i]->x, objects[i]->y, 0, 0, ARROW, objects[i]->team);
			}
			if (objects[i]->type == BULLET || objects[i]->type == ARROW) {
				if (objects[i]->lifeOff())
					dieObject(i);
			}
		}
	}

	someoneTargetInRange(CHARACTER, CHARACTER);
	someoneTargetInRange(CHARACTER, BUILDING);
	collisionObject(CHARACTER, BUILDING);
	collisionObject(CHARACTER, BULLET);
	collisionObject(CHARACTER, ARROW);
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

void SceneMgr::someoneTargetInRange(int type1, int type2) {
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i) {
		if (objects[i] != NULL && objects[i]->type == type1 && objects[i]->team == TEAM_2) {
			for (int j = 0; j < MAX_PLAYER_COUNT; ++j) {
				if (objects[j] != NULL && objects[j]->type == type2 && (objects[i]->team != objects[j]->team)) {
					if (objects[i]->targetInRange(objects[j]->x, objects[j]->y)) {
						objects[i]->set_Target(objects[j]);
						objects[i]->findState = 1;
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
						float damageI = objects[i]->life;
						float damageJ = objects[j]->life;
						objects[i]->damage(damageJ);
						objects[j]->damage(damageI);
						if (objects[i]->lifeOff()) {
							dieObject(i);
						}
						if (objects[j]->lifeOff()) {
							dieObject(j);
						}
						break;
					}
				}
			}
		}
	}
}