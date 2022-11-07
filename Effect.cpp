#include "Effect.h"
#include "Randam.h"
Effect::Effect(int num, int cooltime, Vec2 mindirection, Vec2 maxdirection, int minwidth, int maxwidth, float minspeed, float maxspeed, float addtheta , float smallspeed) {
	EffectNum = num;
	effectCooltime = cooltime;
	addEffectCooltime = cooltime;
	minDirection = mindirection;
	maxDirection = maxdirection;
	minWidth = minwidth;
	maxWidth = maxwidth;
	minSpeed = minspeed;
	maxSpeed = maxspeed;
	smallSpeed = smallspeed;
	addTheta = addtheta;
	particles = new effect[EffectNum];
}

Effect::~Effect() {
	delete[] particles;
}

void Effect::Update(bool isEmit, Quad pos) {
	if (isEmit == true) {
		Emit(pos);
	}
	EffectUpdate();
	Delete();
}
void Effect::Emit(Quad pos) {
	addEffectCooltime--;
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == false && addEffectCooltime <= 0) {
			//進む方向
			particles[i].direction = { Randam::RAND(minDirection.x,maxDirection.x) , Randam::RAND(minDirection.y,maxDirection.y) };
			particles[i].direction = particles[i].direction.Normalized();
			//横幅、出現場所
			int width = Randam::RAND(minWidth,maxWidth );
			particles[i].quad = { {Randam::RAND(pos.LeftTop.x - width / 2,pos.RightTop.x - width / 2),Randam::RAND(pos.LeftBottom.y + width / 2,pos.LeftTop.y + width / 2) }, width ,width };
			//スピードランダム
			particles[i].speed = { Randam::RAND(minSpeed,maxSpeed) };
			//アクティブフラグ
			particles[i].isActive = true;
			addEffectCooltime = effectCooltime;
			break;
		}
	}
}
void Effect::EffectUpdate() {
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {

			//更新処理
			particles[i].quad = particles[i].quad + particles[i].direction * particles[i].speed;
			particles[i].quad.WidthAdd(particles[i].quad, smallSpeed);
			particles[i].theta += addTheta;

		}
	}

}
void Effect::Delete() {
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {
			if (particles[i].quad.GetWidth() <= 1.0f) {
				particles[i].isActive = false;
			}
		}
	}
}
void Effect::Draw(Screen& screen , int srcW , int handle ,unsigned int color, BlendMode mode = kBlendModeNormal ) {
	Novice::SetBlendMode(mode);
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {
			screen.DrawQuad2(particles[i].quad.CenterRotate(particles[i].quad, particles[i].theta), 0, 0, srcW, srcW, handle, color);
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);
}