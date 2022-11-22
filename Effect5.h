#pragma once
#include "Quad.h"
#include "Vec2.h"
#include <Novice.h>
#include "Screen.h"
class Effect5 {
public:
	int EffectNum;
	int effectCooltime;
	int addEffectCooltime;
	bool isFeedout;

	Vec2 target;
	Quad deleteQuad;

	int minWidth;
	int maxWidth;

	float minSpeed;
	float maxSpeed;

	float addTheta;

	float feedSpeed;

	int emitNum;
	int addEmitNum;

	struct effect {
		Quad quad;
		Vec2 direction;
		float speed;
		bool isActive = 0;
		float theta = 0.0f;
		float t = 0.0f;
	};

	effect* particles;
public:
	
	Effect5(int num, int cooltime, Vec2 target, int minwidth, int maxwidth, float minspeed, float maxspeed, float addtheta, float feedspeed, int emitnum);
	~Effect5();
	void Update(bool isEmit, Quad pos, float theta);
	void Update(bool isEmit,bool isfeedout, Quad pos , Vec2 target);
	void Emit(Quad pos, float theta);
	void Emit(Quad pos);
	void EffectUpdate(bool isemit);
	void Delete();
	void Draw(Screen& screen, int srcW, int handle, unsigned int color, BlendMode mode = kBlendModeNormal);
};