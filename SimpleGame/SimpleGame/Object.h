#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>

#include "Dependencies\glew.h"
#include "Renderer.h"

using namespace std;

random_device rn;
mt19937_64 rnd(rn());
uniform_int_distribution<int> range(-20, 20);

class Object : public Renderer{
private:
	float x, y, z;
	float size = 20.0f;
	float r = 1.0f, g = 0.0f, b = 0.0f;
	float a = 0.0f;
	pair<float, float> v = {1, 1};
public:
	Object(float x, float y, float z) : Renderer(500, 500), x(x), y(y), z(z) {
		v.first = range(rnd);
		v.second = range(rnd);
	}
	bool out() { return (x < -250) || (x > 250) || (y < -250) || (y > 250); }
	void draw() { this->DrawSolidRect(x, y, z, size, r, g, b, a); }
	void update() { x += v.first; y += v.second; }
};