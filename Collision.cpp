#include "Collision.h"
#include "Vec2.h"
namespace Collision {
	bool QuadToQuad(float x, float y, float quadw, float quadh, float x2, float y2, float quadw2, float quadh2) {
		if (x <= x2 + quadw2 && x + quadw >= x2 && y >= y2 - quadh2 && y - quadh <= y2) {
			return true;
		}

		return false;
	}
	bool QuadToQuad(Vec2 pos, float quadw, float quadh, Vec2 pos2, float quadw2, float quadh2) {
		if (pos.x <= pos2.x + quadw2 && pos.x + quadw >= pos2.x && pos.y >= pos2.y - quadh2 && pos.y - quadh <= pos2.y) {
			return true;
		}

		return false;
	}
	bool EllipseToEllipse(float x, float y, float quadw, float quadh, float x2, float y2, float quadw2, float quadh2) {
		if (x <= x2 + quadw2 && x + quadw >= x2 && y >= y2 - quadh2 && y - quadh <= y2) {
			return true;
		}

		return false;
	}
}