#include "Quad.h"

Quad::Quad() {

}

Quad::Quad(Vec2 LeftTop, int width, int height) {
	this->RightTop = { LeftTop.x + width, LeftTop.y };
	this->LeftTop = LeftTop;
	this->LeftBottom = { LeftTop.x,LeftTop.y - height };
	this->RightBottom = { LeftTop.x + width, LeftTop.y - height };

}

Quad::Quad(Vec2 LeftTop, Vec2 RightTop, Vec2 LeftBottom, Vec2 RightBottom) {
	this->LeftTop = LeftTop;
	this->RightTop = RightTop;
	this->LeftBottom = LeftBottom;
	this->RightBottom = RightBottom;

}

Quad Quad::Scaling(Quad quad, float scale) {
	return { {quad.LeftTop.x * scale,		quad.LeftTop.y * scale},
			 {quad.RightTop.x * scale,		quad.RightTop.y * scale},
			 {quad.LeftBottom.x * scale,	quad.LeftBottom.y * scale},
			 {quad.RightBottom.x * scale,	quad.RightBottom.y * scale}
	};
}
Quad Quad::XScaling(Quad quad, float scale) {
	return { {quad.LeftTop.x * scale,		quad.LeftTop.y},
			 {quad.RightTop.x * scale,		quad.RightTop.y},
			 {quad.LeftBottom.x * scale,	quad.LeftBottom.y},
			 {quad.RightBottom.x * scale,	quad.RightBottom.y}
	};
}
Quad Quad::YScaling(Quad quad, float scale) {
	return { {quad.LeftTop.x,		quad.LeftTop.y * scale},
			 {quad.RightTop.x,		quad.RightTop.y * scale},
			 {quad.LeftBottom.x,	quad.LeftBottom.y * scale},
			 {quad.RightBottom.x,	quad.RightBottom.y * scale}
	};
}
Quad Quad::Rotate(Quad quad, float theta) {
	float c = cosf(theta);
	float s = sinf(theta);
	return { {quad.LeftTop.x * c - quad.LeftTop.y * s ,			quad.LeftTop.y * c + quad.LeftTop.x * s },
			 {quad.RightTop.x * c - quad.RightTop.y * s ,		quad.RightTop.y * c + quad.RightTop.x * s },
			 {quad.LeftBottom.x * c - quad.LeftBottom.y * s ,	quad.LeftBottom.y * c + quad.LeftBottom.x * s },
			 {quad.RightBottom.x * c - quad.RightBottom.y * s , quad.RightBottom.y * c + quad.RightBottom.x * s }
	};
}
Quad Quad::Translation(Quad quad, Vec2 position) {
	return { {quad.LeftTop.x + position.x,        quad.LeftTop.y + position.y},
			 {quad.RightTop.x + position.x,       quad.RightTop.y + position.y},
			 {quad.LeftBottom.x + position.x,     quad.LeftBottom.y + position.y},
			 {quad.RightBottom.x + position.x,    quad.RightBottom.y + position.y}
	};
}

Quad Quad::CenterRotate(Quad quad, float theta) {

	Vec2 center{ quad.LeftTop.x + GetWidth() / 2 , quad.LeftTop.y - GetHeight() / 2 };
	Quad CenterQuad = quad - center;

	CenterQuad = CenterQuad.Rotate(CenterQuad, theta);
	return { CenterQuad + center };
}


Quad Quad::WidthAdd(Quad quad, float add) {
	Quad tmp = { quad };
	tmp.LeftTop.x = tmp.LeftTop.x - add / 2.0f;
	tmp.LeftTop.y = tmp.LeftTop.y + add / 2.0f;
	tmp.RightTop.x = tmp.RightTop.x + add / 2.0f;
	tmp.RightTop.y = tmp.RightTop.y + add / 2.0f;
	tmp.LeftBottom.x = tmp.LeftBottom.x - add / 2.0f;
	tmp.LeftBottom.y = tmp.LeftBottom.y - add / 2.0f;
	tmp.RightBottom.x = tmp.RightBottom.x + add / 2.0f;
	tmp.RightBottom.y = tmp.RightBottom.y - add / 2.0f;
	return { tmp };
}

Quad Quad:: operator+(Vec2 s) const {
	return{ this->LeftTop + s,this->RightTop + s ,this->LeftBottom + s ,this->RightBottom + s };
}

Quad Quad:: operator-(Vec2 s) const {
	return{ this->LeftTop - s,this->RightTop - s ,this->LeftBottom - s ,this->RightBottom - s };
}

Quad Quad:: operator+(float s) const {
	return{ this->LeftTop * s,this->RightTop * s ,this->LeftBottom * s ,this->RightBottom * s };
}