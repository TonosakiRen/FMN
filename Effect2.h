#pragma once
#include "Quad.h"
#include "Vec2.h"
#include <Novice.h>
#include "Screen.h"
class Effect2 {
public:
	int EffectNum;
	int effectCooltime;
	int addEffectCooltime;

	Vec2 target;
	Quad deleteQuad;

	int minWidth;
	int maxWidth;

	float minSpeed;
	float maxSpeed;

	float addRotate;

	float smallSpeed;

	int emitNum;
	int addEmitNum;

	struct effect {
		Quad quad;
		Vec2 direction;
		float speed;
		bool isActive = 0;
		int rotate = 0;
		float theta = 0.0f;
	};

	effect* particles;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="num">パーティクルの数</param>
	/// <param name="cooltime">何フレームで一つ発生させるか</param>
	/// <param name="middirection">-1～1のベクトルを正規化</param>
	/// <param name="maxdirection">-1～1のベクトルを正規化</param>
	/// <param name="minwidth">エフェクトの横幅と縦幅の最低値</param>
	/// <param name="maxwidth">エフェクトの横幅と縦幅の最高値</param>
	/// <param name="minspeed">エフェクトのスピードの最低値</param>
	/// <param name="maxspeed">エフェクトのスピードの最高値</param>
	/// <param name="addtheta">加算する角度</param>
	/// <param name="smallspeed">どのくらいの速さで遅くなるか</param>
	/// <param name="emitnum">どのくらいの速さで遅くなるか</param>
	Effect2(int num, int cooltime, Vec2 target, Quad deleteQuad, int minwidth, int maxwidth, float minspeed, float maxspeed, float addrotate, float smallspeed, int emitnum);
	~Effect2();
	void Update(bool isEmit, Quad pos, float theta);
	void Update(bool isEmit, Quad pos);
	void Emit(Quad pos, float theta);
	void Emit(Quad pos);
	void EffectUpdate();
	void Delete();
	void Draw(Screen& screen, int srcW, int handle, unsigned int color, BlendMode mode);
};