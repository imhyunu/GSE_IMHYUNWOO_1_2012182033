/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"

SceneMgr* sceneMgr = NULL;

float current_time = (float)timeGetTime() * 0.001f;
float frame_time;
int mouse_State = MOUSE_LEFT_UP;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	frame_time = ((float)timeGetTime() * 0.001f) - current_time;
	current_time += frame_time;

	sceneMgr->update(frame_time);

	sceneMgr->draw();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mouse_State == MOUSE_LEFT_UP) {
			mouse_State = MOUSE_LEFT_DOWN;
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (mouse_State == MOUSE_LEFT_DOWN) {
			mouse_State = MOUSE_LEFT_UP;
			if ( y > H_HEIGHT && sceneMgr->team1_Char_CoolTimeOK())
				sceneMgr->input(x - H_WIDTH, H_HEIGHT - y, 0, 0, CHARACTER, TEAM_1);
		}
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	sceneMgr = new SceneMgr();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();


    return 0;
}

