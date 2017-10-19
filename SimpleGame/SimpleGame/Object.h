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
uniform_real_distribution<float> range2(-1.0, 1.0);

template<class T>
bool clamp(T min, T a, T max) {
	return (min < a < max);
}

class Object : public Renderer{
private:
	float x, y, z;
	float size = 10.0f;
	float r = 1.0f, g = 1.0f, b = 1.0f;
	float a = 0.0f;
	float veloc = 30;
	pair<float, float> v = {1, 1};
public:
	Object(float x, float y, float z) : Renderer(500, 500), x(x), y(y), z(z) {
		float sub = (range2(rnd));
		printf("%.5f", sub);
		v.first = sub * veloc;
		v.second = (sqrt(1 - (sub * sub))) * veloc;
		if (range2(rnd) < 0)
			v.second *= -1;
	}
	void draw() { this->DrawSolidRect(x, y, z, size, r, g, b, a); }
	void update() {
		x += v.first;
		y += v.second; 
		if ((x <= -250) || (x >= 250))
			v.first *= -1;
		if ((y <= -250) || (y >= 250))
			v.second *= -1;
	}
	float *collsion() {
		float collsionBox[4];
		collsionBox[0] = x - (size / 2);		// Left
		collsionBox[1] = x + (size / 2);		// Right
		collsionBox[2] = y - (size / 2);		// Bottom
		collsionBox[3] = y + (size / 2);		// Top
		return collsionBox; 
	}
	void changecolor(int key) {
		if (key == 1) {
			r = 1.0;
			g = 0.0;
			b = 0.0;
		}
		if (key == 2) {
			r = 1.0;
			g = 1.0;
			b = 1.0;
		}
	}

};