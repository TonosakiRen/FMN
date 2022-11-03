#include "Boss.h"

Boss::Boss()
{
	Size = { 150,400 };

	Pos = { 1000,Size.y/2};
	LeftTop = { Pos.x - (Size.x / 2),Pos.y + (Size.y / 2)};
	LeftBottom = Vec2(Pos - (Size/2));
	RightTop= Vec2(Pos + (Size/2));
	RightBottom = { Pos.x + (Size.x / 2),Pos.y - (Size.y / 2) };
	Quad_Pos = { LeftTop,RightTop,LeftBottom,RightBottom};

	
}

void Boss::Draw(Screen& screen)
{
	screen.DrawQuad2Renban(Quad_Pos, SrcX, 0, 0, 0, 0, 60, AnimeFlame, 0, RED, 0);
	//screen.DrawQuad2(Quad_Pos, 0, 0, 0, 0, 0, RED);
	/*screen.DrawBox(Pos.x, Pos.y, Size.x, Size.y, 0, RED, kFillModeSolid);
	screen.DrawEllipse(Pos.x, Pos.y, Size.x, Size.y, 0, RED, kFillModeSolid);*/
	
}

Quad Boss::Get()
{
	return Quad(Quad_Pos);
}
