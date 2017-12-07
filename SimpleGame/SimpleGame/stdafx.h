#pragma once
#pragma comment(lib, "winmm.lib")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <math.h>
#include <time.h>

#define WIDTH		500
#define H_WIDTH		WIDTH / 2
#define HEIGHT		800
#define H_HEIGHT	HEIGHT / 2

#define LEVEL_GOD			0
#define LEVEL_SKY			0.1
#define LEVEL_GROUND					0.2
#define LEVEL_UNDERGROUND				0.3
#define LEVEL_BACKGROUND				1.0

#define CHARACTER_SIZE					70.0f
#define CHARACTER_SPEED					200.0f
#define CHARACTER_LIFE					100.0f
#define CHARACTER_GAUGE_WIDTH			30.0f
#define CHARACTER_GAUGE_HEIGHT			5.0f
#define TARGET_RANGE					100.0f

#define BUILDING_SIZE					100.0f
#define BUILDING_LIFE					500.0f
#define BUILDING_GAUGE_WIDTH			100.0f
#define BUILDING_GAUGE_HEIGHT			5.0f

#define BULLET_SIZE						4.0f
#define BULLET_SPEED					200.0f
#define BULLET_LIFE						15.0f

#define ARROW_SIZE						4.0f
#define ARROW_SPEED						100.0f
#define ARROW_LIFE						10.0f

#define PATICLE_SIZE					5

#define BULLET_COOLTIME					2.0f
#define ARROW_COOLTIME					1.0f
#define TEAM1_HARATER_COOLTIME			1.0f
#define TEAM2_HARATER_COOLTIME			1.0f
#define TEAM1_CHARACTHER_ANI_TIME		0.2f
#define TEAM2_CHARACTHER_ANI_TIME		0.05f
#define TEAM1_BUILDING_ANI_TIME			0.1f
#define TEAM2_BUILDING_ANI_TIME			0.1f


enum CollisionBOX{ LEFT, RIGHT, BOTTOM, TOP };
enum MouseState{ MOUSE_LEFT_UP, MOUSE_LEFT_DOWN };
enum ObjectType{ CHARACTER, BUILDING, ARROW, BULLET };
enum Team{ TEAM_1, TEAM_2 };