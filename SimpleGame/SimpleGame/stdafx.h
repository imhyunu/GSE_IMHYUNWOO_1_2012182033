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

#define CHARATER_SIZE		10
#define CHARATER_SPEED		300
#define CHARATER_LIFE		10

#define BUILDING_SIZE		100
#define BUILDING_LIFE		500

#define BULLET_SIZE			5
#define BULLET_SPEED		600
#define BULLET_LIFE			20

#define ARROW_SIZE			5
#define ARROW_SPEED			100
#define ARROW_LIFE			10

enum MouseState{ MOUSE_LEFT_UP, MOUSE_LEFT_DOWN };
enum ObjectType{ CHARATER, BUILDING, ARROW, BULLET };
enum Team{ TEAM_1, TEAM_2 };