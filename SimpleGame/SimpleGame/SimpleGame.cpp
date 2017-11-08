/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneMgr.h"

//Renderer *g_Renderer = NULL;
SceneMgr *sceneMgr = NULL;

enum {LEFT_MOUSE_DOWN, LEFT_MOSUE_UP, RIGHT_MOUSE_DOWN, RIGHT_MOUSE_UP};

int mousestate = LEFT_MOSUE_UP;
clock_t current_time = clock();
clock_t frame_time;

void RenderScene(void)
{
	frame_time = clock() - current_time;
	current_time += frame_time;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	sceneMgr->update((float)frame_time);

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
		mousestate = LEFT_MOUSE_DOWN;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && mousestate == LEFT_MOUSE_DOWN) {
		sceneMgr->input((float)(x - 250), (float)(250 - y), OBJECT_CHARACTER);
		mousestate = LEFT_MOSUE_UP;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		mousestate = RIGHT_MOUSE_DOWN;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP, mousestate == RIGHT_MOUSE_DOWN) {
		sceneMgr->input((float)(x - 250), (float)(250 - y), OBJECT_BULLET);
		mousestate = RIGHT_MOUSE_UP;
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

/*void Update(int value) {
	sceneMgr->update();
	glutTimerFunc(100, Update, 1);
}*/

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
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

