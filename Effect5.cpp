#include "Effect5.h"
#include "Randam.h"
#include "Easing.h"
#include "Collision.h"
#include "Feed.h"
Effect5::Effect5(int num, int cooltime, Vec2 target, int minwidth, int maxwidth, float minspeed, float maxspeed, float addtheta, float feedspeed, int emitnum = 1) {
	EffectNum = num;
	effectCooltime = cooltime;
	addEffectCooltime = cooltime;
	this->target = target;
	minWidth = minwidth;
	maxWidth = maxwidth;
	minSpeed = minspeed;
	maxSpeed = maxspeed;
	feedSpeed = feedspeed;
	addTheta = addtheta;
	emitNum = emitnum;
	addEmitNum = emitnum;
	isFeedout = false;
	particles = new effect[EffectNum];
}

Effect5::~Effect5() {
	delete[] particles;
}

void Effect5::Update(bool isEmit, Quad pos, float theta) {
	if (isEmit == true) {
		Emit(pos, theta);
	}
	EffectUpdate(isEmit);
	Delete();
}

void Effect5::Update(bool isEmit,bool isfeedout, Quad pos, Vec2 target ) {
	this->target = target;
	if (isEmit == true) {
		Emit(pos);
	}
	isFeedout = isfeedout;
	EffectUpdate(isEmit);
	Delete();
}

void Effect5::Emit(Quad pos, float theta) {
	addEffectCooltime--;
	for (int i = 0; i < EffectNum; i++) {

		if (particles[i].isActive == false && addEffectCooltime <= 0) {
			addEmitNum--;

			//横幅、出現場所
			int width = Randam::RAND(minWidth, maxWidth);
			Quad diagonalPos = pos.CenterRotate(pos, theta);

			Vec2 side = (diagonalPos.RightTop - diagonalPos.LeftTop).Normalized() * Easing::easing(Randam::RAND(0, 100) / 100.0f, 0.0f, diagonalPos.LeftTop.DistanceFrom(diagonalPos.RightTop));
			Vec2 vertical = (diagonalPos.LeftBottom - diagonalPos.LeftTop).Normalized() * Easing::easing(Randam::RAND(0, 100) / 100.0f, 0.0f, diagonalPos.LeftTop.DistanceFrom(diagonalPos.LeftBottom));
			Vec2 center = { diagonalPos.LeftTop + side + vertical };
			particles[i].quad = { {center.x - width / 2,center.y + width / 2 }, width ,width };

			//進む方向
			particles[i].direction = { target - center };
			particles[i].direction = particles[i].direction.Normalized();

			/*particles[i].quad = { {Randam::RAND(pos.LeftTop.x - width / 2,pos.RightTop.x - width / 2),Randam::RAND(pos.LeftBottom.y + width / 2,pos.LeftTop.y + width / 2) }, width ,width };*/
			//スピードランダム
			particles[i].speed = { Randam::RAND(minSpeed,maxSpeed) };
			//t
			particles[i].t = 0.0f;
			//アクティブフラグ
			particles[i].isActive = true;

		}
		if (addEmitNum <= 0) {
			addEmitNum = emitNum;
			addEffectCooltime = effectCooltime;
			break;
		}
	}
}
void Effect5::Emit(Quad pos) {
	addEffectCooltime--;
	for (int i = 0; i < EffectNum; i++) {

		if (particles[i].isActive == false && addEffectCooltime <= 0) {
			addEmitNum--;

			//横幅、出現場所
			int width = Randam::RAND(minWidth, maxWidth);
			Vec2 side = (pos.RightTop - pos.LeftTop).Normalized() * Easing::easing(Randam::RAND(0, 100) / 100.0f, 0.0f, pos.LeftTop.DistanceFrom(pos.RightTop));
			Vec2 vertical = (pos.LeftBottom - pos.LeftTop).Normalized() * Easing::easing(Randam::RAND(0, 100) / 100.0f, 0.0f, pos.LeftTop.DistanceFrom(pos.LeftBottom));
			Vec2 center = { pos.LeftTop + side + vertical };
			particles[i].quad = { {center.x - width / 2,center.y + width / 2 }, width ,width };

			//進む方向
			particles[i].direction = { target - center };
			particles[i].direction = particles[i].direction.Normalized();

			//スピードランダム
			particles[i].speed = { Randam::RAND(minSpeed,maxSpeed) };
			//t
			particles[i].t = 0.0f;
			//アクティブフラグ
			particles[i].isActive = true;

		}
		if (addEmitNum <= 0) {
			addEmitNum = emitNum;
			addEffectCooltime = effectCooltime;
			break;
		}
	}
}

void Effect5::EffectUpdate(bool isemit) {
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {

			//更新処理
			particles[i].direction = (target - particles[i].quad.GetCenter()).Normalized();
			if (isemit == true) {
				particles[i].quad = particles[i].quad + particles[i].direction * particles[i].speed;
			}
			particles[i].theta += addTheta;
			if (isFeedout == true) {
				particles[i].t += feedSpeed;
			}

		}
		
	}

}
void Effect5::Delete() {
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {
			if (particles[i].t >= 1.0f) {
				particles[i].isActive = false;
			}
		}
	}
}
void Effect5::Draw(Screen& screen, int srcW, int handle, unsigned int color, BlendMode mode) {
	Novice::SetBlendMode(mode);
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {
			if (isFeedout == false) {
				screen.DrawQuad2(particles[i].quad.CenterRotate(particles[i].quad, particles[i].theta), 0, 0, srcW, srcW, handle, color);
			}
			else {
				screen.DrawQuad2(particles[i].quad.CenterRotate(particles[i].quad, particles[i].theta), 0, 0, srcW, srcW, handle, Feed::Feedout(particles[i].t,feedSpeed,WHITE));
			}
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);
}