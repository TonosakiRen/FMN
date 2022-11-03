#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vec2.h"

class Quad {
public:
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
	float Width;
	float Height;
public:

	Quad();
	Quad(Vec2 LeftTop, int width, int height);
	Quad(Vec2 LeftTop, Vec2 RightTop, Vec2 LeftBottom, Vec2 RightBottom);
	Quad Scaling(Quad quad, float scale);
	Quad XScaling(Quad quad, float scale);
	Quad YScaling(Quad quad, float scale);
	Quad Rotate(Quad quad, float theta);
	Quad Translation(Quad quad, Vec2 position);

	Quad operator + (Vec2 s) const;
	Quad operator + (float s)const;

};

