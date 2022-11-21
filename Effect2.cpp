#include "Effect2.h"
#include "Randam.h"
#include "Easing.h"
#include "Collision.h"
Effect2::Effect2(int num, int cooltime, Vec2 target, Quad deleteQuad, int minwidth, int maxwidth, float minspeed, float maxspeed, float addtheta, float smallspeed, int emitnum = 1) {
	EffectNum = num;
	effectCooltime = cooltime;
	addEffectCooltime = cooltime;
	this->target = target;
	this->deleteQuad = deleteQuad;
	minWidth = minwidth;
	maxWidth = maxwidth;
	minSpeed = minspeed;
	maxSpeed = maxspeed;
	smallSpeed = smallspeed;
	addTheta = addtheta;
	emitNum = emitnum;
	addEmitNum = emitnum;
	particles = new effect[EffectNum];
}

Effect2::~Effect2() {
	delete[] particles;
}

void Effect2::Update(bool isEmit, Quad pos, float theta) {
	if (isEmit == true) {
		Emit(pos, theta);
	}
	EffectUpdate();
	Delete();
}

void Effect2::Update(bool isEmit, Quad pos) {
	if (isEmit == true) {
		Emit(pos);
	}
	EffectUpdate();
	Delete();
}

void Effect2::Emit(Quad pos, float theta) {
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
			particles[i].quad = { {center.x - width / 2.0f,center.y + width / 2.0f }, width ,width };

			//進む方向
			particles[i].direction = { target - center };
			particles[i].direction = particles[i].direction.Normalized();

			/*particles[i].quad = { {Randam::RAND(pos.LeftTop.x - width / 2,pos.RightTop.x - width / 2),Randam::RAND(pos.LeftBottom.y + width / 2,pos.LeftTop.y + width / 2) }, width ,width };*/
			//スピードランダム
			particles[i].speed = { Randam::RAND(minSpeed,maxSpeed) };
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
void Effect2::Emit(Quad pos) {
	addEffectCooltime--;
	for (int i = 0; i < EffectNum; i++) {

		if (particles[i].isActive == false && addEffectCooltime <= 0) {
			addEmitNum--;

			//横幅、出現場所
			int width = Randam::RAND(minWidth, maxWidth);
			Vec2 side = (pos.RightTop - pos.LeftTop).Normalized() * Easing::easing(Randam::RAND(0, 100) / 100.0f, 0.0f, pos.LeftTop.DistanceFrom(pos.RightTop));
			Vec2 vertical = (pos.LeftBottom - pos.LeftTop).Normalized() * Easing::easing(Randam::RAND(0, 100) / 100.0f, 0.0f, pos.LeftTop.DistanceFrom(pos.LeftBottom));
			Vec2 center = { pos.LeftTop + side + vertical };
			particles[i].quad = { {center.x - width / 2.0f,center.y + width / 2.0f }, width ,width };

			//進む方向
			particles[i].direction = { target - center };
			particles[i].direction = particles[i].direction.Normalized();

			//スピードランダム
			particles[i].speed = { Randam::RAND(minSpeed,maxSpeed) };
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

void Effect2::EffectUpdate() {
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {

			//更新処理
			particles[i].quad = particles[i].quad + particles[i].direction * particles[i].speed;
			particles[i].quad.WidthAdd(particles[i].quad, smallSpeed);
			particles[i].theta += addTheta;

		}
	}

}
void Effect2::Delete() {
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {
			if (particles[i].quad.GetWidth() < 1.0f || Collision::QuadToQuad(deleteQuad, particles[i].quad) || particles[i].quad.GetCenter().y >= SCREEN_WIDTH -Floor + particles[i].quad.GetWidth()) {
				particles[i].isActive = false;
			}
		}
	}
}
void Effect2::Draw(Screen& screen, int srcW, int handle, unsigned int color, BlendMode mode = kBlendModeNormal) {
	Novice::SetBlendMode(mode);
	for (int i = 0; i < EffectNum; i++) {
		if (particles[i].isActive == true) {
			screen.DrawQuad2(particles[i].quad.CenterRotate(particles[i].quad, particles[i].theta), 0, 0, srcW, srcW, handle, color);
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);
}