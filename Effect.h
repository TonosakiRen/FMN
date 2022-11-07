#pragma once
#include "Quad.h"
#include "Vec2.h"
#include <Novice.h>
#include "Screen.h"
class Effect {
public:
	int EffectNum;
	int effectCooltime;
	int addEffectCooltime;

	Vec2 minDirection;
	Vec2 maxDirection;

	int minWidth;
	int maxWidth;

	float minSpeed;
	float maxSpeed;

	float addTheta;

	float smallSpeed;

	struct effect{
		Quad quad;
		Vec2 direction;
		float speed;
		bool isActive = 0;
		float theta = 0.0f;
	};

	effect* particles;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="num">�p�[�e�B�N���̐�</param>
	/// <param name="cooltime">���t���[���ň���������邩</param>
	/// <param name="middirection">-1�`1�̃x�N�g���𐳋K��</param>
	/// <param name="maxdirection">-1�`1�̃x�N�g���𐳋K��</param>
	/// <param name="minwidth">�G�t�F�N�g�̉����Əc���̍Œ�l</param>
	/// <param name="maxwidth">�G�t�F�N�g�̉����Əc���̍ō��l</param>
	/// <param name="minspeed">�G�t�F�N�g�̃X�s�[�h�̍Œ�l</param>
	/// <param name="maxspeed">�G�t�F�N�g�̃X�s�[�h�̍ō��l</param>
	/// <param name="addtheta">���Z����p�x</param>
	/// <param name="smallspeed">�ǂ̂��炢�̑����Œx���Ȃ邩</param>
	Effect(int num,int cooltime,Vec2 mindirection,Vec2 maxdirection,int minwidth, int maxwidth , float minspeed,float maxspeed , float addtheta,float smallspeed);
	~Effect();
	void Update(bool isEmit , Quad pos , float theta);
	void Update(bool isEmit, Quad pos);
		void Emit(Quad pos , float theta);
		void Emit(Quad pos);
		void EffectUpdate();
		void Delete();
	void Draw(Screen& screen , int srcW , int handle , unsigned int color , BlendMode mode );
};