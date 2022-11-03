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
	
	bool Collision::CircleToCirlce(Circle a,Circle b) {
		float distance = a.pos.DistanceFrom(b.pos);
		if (a.radius + b.radius >= distance) {
			return true;
		}
		return false;
	}

	bool Collision::CircleToQuad(Circle a, Quad b) {
		if (Collision::QuadToQuad({ b.LeftTop.x ,b.LeftTop.y + a.radius }, b.Width, b.Height + a.radius * 2, a.pos, 1, 1) ||
			Collision::QuadToQuad({ b.LeftTop.x + a.radius,b.LeftTop.y }, b.Width + a.radius * 2, b.Height, a.pos, 1, 1) ||
			Collision::CircleToCirlce(a, { b.LeftTop,a.radius }) ||
			Collision::CircleToCirlce(a, { b.RightTop,a.radius }) ||
			Collision::CircleToCirlce(a, { b.LeftBottom,a.radius }) ||
			Collision::CircleToCirlce(a, { b.RightBottom,a.radius })
			) {

			return true;
		}
		return false;
	}
