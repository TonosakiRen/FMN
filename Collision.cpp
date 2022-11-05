#include "Collision.h"


bool Collision::QuadToQuad(float x, float y, float quadw, float quadh, float x2, float y2, float quadw2, float quadh2) {
	if (x <= x2 + quadw2 && x + quadw >= x2 && y >= y2 - quadh2 && y - quadh <= y2) {
		return true;
	}

	return false;
}

bool Collision::QuadToQuad(Vec2 pos, float quadw, float quadh, Vec2 pos2, float quadw2, float quadh2) {
	if (pos.x <= pos2.x + quadw2 && pos.x + quadw >= pos2.x && pos.y >= pos2.y - quadh2 && pos.y - quadh <= pos2.y) {
		return true;
	}

	return false;
}

bool Collision::QuadToQuad(Quad pos, Quad pos2) {
	if (pos.LeftTop.x <= pos2.RightTop.x && pos.RightTop.x >= pos2.LeftTop.x && pos.LeftTop.y >= pos2.LeftBottom.y && pos.LeftBottom.y <= pos2.LeftTop.y) {
		return true;
	}

	return false;
}

bool Collision::DiagonalQuadToQuad(Quad pos, Quad diagonalPos) {
	Vec2 StartLeftBottom = diagonalPos.LeftBottom - diagonalPos.LeftTop;
	Vec2 StartLeftTop = diagonalPos.LeftTop - diagonalPos.RightTop;
	Vec2 StartRightTop = diagonalPos.RightTop - diagonalPos.RightBottom;
	Vec2 StartRightBottom = diagonalPos.RightBottom - diagonalPos.LeftBottom;

	Vec2 LeftTopToPoint = diagonalPos.LeftTop - pos.LeftTop;
	Vec2 RightTopToPoint = diagonalPos.RightTop - pos.LeftTop;
	Vec2 LeftBottomToPoint = diagonalPos.LeftBottom - pos.LeftTop;
	Vec2 RightBottomToPoint = diagonalPos.RightBottom - pos.LeftTop;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - pos.RightTop;
	RightTopToPoint = diagonalPos.RightTop - pos.RightTop;
	LeftBottomToPoint = diagonalPos.LeftBottom - pos.RightTop;
	RightBottomToPoint = diagonalPos.RightBottom - pos.RightTop;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - pos.LeftBottom;
	RightTopToPoint = diagonalPos.RightTop - pos.LeftBottom;
	LeftBottomToPoint = diagonalPos.LeftBottom - pos.LeftBottom;
	RightBottomToPoint = diagonalPos.RightBottom - pos.LeftBottom;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - pos.RightBottom;
	RightTopToPoint = diagonalPos.RightTop - pos.RightBottom;
	LeftBottomToPoint = diagonalPos.LeftBottom - pos.RightBottom;
	RightBottomToPoint = diagonalPos.RightBottom - pos.RightBottom;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	return false;
}

bool Collision::CircleToCirlce(Circle a, Circle b) {
	float distance = a.pos.DistanceFrom(b.pos);
	if (a.radius + b.radius >= distance) {
		return true;
	}
	return false;
}

bool Collision::CircleToQuad(Circle a, Quad b) {
	if (Collision::QuadToQuad({ b.LeftTop.x ,b.LeftTop.y + a.radius }, b.Width, b.Height + a.radius * 2, a.pos, 1, 1) ||
		Collision::QuadToQuad({ b.LeftTop.x - a.radius,b.LeftTop.y }, b.Width + a.radius * 2, b.Height, a.pos, 1, 1) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.LeftTop,a.radius }) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.RightTop,a.radius }) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.LeftBottom,a.radius }) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.RightBottom,a.radius })
		) {

		return true;
	}
	return false;
}
