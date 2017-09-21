#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "Renderer.h"

class Object{
private:
	float size = 5.0f;
	float r = 1.0f, g = 0.0f, b = 0.0f;
	float a = 0.0f;
	Renderer* o_Renderer = NULL;
public:
	Object() { o_Renderer = new Renderer(500, 500); }
	void draw(float x, float y, float z) { o_Renderer->DrawSolidRect(x, y, z, size, r, g, b, a); }
};