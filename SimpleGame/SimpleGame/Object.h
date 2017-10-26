#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>

#include "Dependencies\glew.h"
#include "Renderer.h"
#include "CollisionBox.h"

using namespace std;

random_device rn;
mt19937_64 rnd(rn());
uniform_real_distribution<float> range2(-1.0, 1.0);

enum { RED, WHITE };
enum { LIFE, DIE };

#define PIXELPERMETER 20

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
	float veloc = 7;
	float life = 3;
	float nlife = 0;
	int state = LIFE;
	pair<float, float> v = {1, 1};
	CollBox* collbox;
public:
	Object(float x, float y, float z) : Renderer(500, 500), x(x), y(y), z(z) {
		float sub = (range2(rnd));
		printf("%.5f", sub);
		v.first = sub * veloc *PIXELPERMETER;
		v.second = (sqrt(1 - (sub * sub))) * veloc * PIXELPERMETER;
		if (range2(rnd) < 0)
			v.second *= -1;
		state = LIFE;
	}
	void draw() { this->DrawSolidRect(x, y, z, size, r, g, b, a); }
	bool what_state() {
		if (state == LIFE)
			return false;
		return true;
	}
	void update(float frame_time) {
		nlife += (frame_time / 1000);
		if (nlife >= life) {
			nlife = 0;
			state = DIE;
		}
		x += (v.first * frame_time / 1000);
		y += (v.second * frame_time / 1000);
		if (x <= -250) {
			x = -245;
			v.first *= -1;
		}
		if (y <= -250) {
			y = -245;
			v.second *= -1;
		}
		if (x >= 250) {
			x = 245;
			v.first *= -1;
		}
		if (y >= 250) {
			y = 245;
			v.second *= -1;
		}
	}
	CollBox* getCollBox() {
		float num = size / 2;
		collbox = new CollBox(x - num, x+num, y + num, y - num);
		return collbox;
	}
	void changecolor(int key) {
		if (key == RED) {
			r = 1.0;
			g = 0.0;
			b = 0.0;
		}
		if (key == WHITE) {
			r = 1.0;
			g = 1.0;
			b = 1.0;
		}
	}

};