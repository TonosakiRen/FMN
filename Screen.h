#pragma once
#include <Novice.h>
#include <Vec2.h>
#include "Quad.h"
#include "Randam.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int Floor = 200;//�Ԃ����̂Ƃ��낪�����O���̃t���A�̒l��ς���Βn�ʂ̈ʒu���ς��


constexpr int kFrameMag = 2;

class Screen
{
public:

	Screen();

	int Width;
	int Height;
	Vec2 Worldcenter;
	Vec2 Scroll;
	Vec2 ScreenShake;
	float Scroll_Fixed_Value_X;
	bool Ishit;

	Vec2 Zoom;

	void Scroll_update(float playerX, float map_sheets_number);


	void Shake(int minX, int maxX, int minY, int maxY, bool is);


	/// <summary>
	/// �l�p�`��`�悷��
	/// </summary>
	/// <param name="x">�`�悷��l�p�`�̍�����W X</param>
	/// <param name="y">�`�悷��l�p�`�̍�����W Y</param>
	/// <param name="w">�`�悷��l�p�`�̉���</param>
	/// <param name="h">�`�悷��l�p�`�̏c��</param>
	/// <param name="angle">�`�悷��l�p�`�̉�]�p</param>
	/// <param name="color">�`�悷��l�p�`�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawBox(float x, float y, float w, float h, float angle, unsigned int color, FillMode fillMode);
	/// <summary>
	/// �O�p�`��`�悷��
	/// </summary>
	/// <param name="x1">�`�悷��O�p�`�̒��_1 X</param>
	/// <param name="y1">�`�悷��O�p�`�̒��_1 Y</param>
	/// <param name="x2">�`�悷��O�p�`�̒��_2 X</param>
	/// <param name="y2">�`�悷��O�p�`�̒��_2 Y</param>
	/// <param name="x3">�`�悷��O�p�`�̒��_3 X</param>
	/// <param name="y3">�`�悷��O�p�`�̒��_3 Y</param>
	/// <param name="color">�`�悷��O�p�`�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode);
	/// <summary>
	/// ����`�悷��
	/// </summary>
	/// <param name="x1">�`�悷����̎n�_���W X</param>
	/// <param name="y1">�`�悷����̎n�_���W Y</param>
	/// <param name="x2">�`�悷����̏I�_���W X</param>
	/// <param name="y2">�`�悷����̏I�_���W Y</param>
	/// <param name="color">�`�悷��O�p�`�̐F</param>
	void DrawLine(float x1, float y1, float x2, float y2, unsigned int color);
	/// <summary>
	/// �ȉ~��`�悷��
	/// </summary>
	/// <param name="x">�ȉ~�̒��S���W X</param>
	/// <param name="y">�ȉ~�̒��S���W Y</param>
	/// <param name="radiusX">�ȉ~�̔��a X</param>
	/// <param name="radiusY">�ȉ~�̔��a Y</param>
	/// <param name="angle">�ȉ~�̉�]�p(rad)</param>
	/// <param name="color">�ȉ~�̐F</param>
	void DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, unsigned int color, FillMode fillMode);
	/// <summary>
	/// �X�v���C�g��`�悷��
	/// </summary>
	/// <param name="x">�`�悷��X�v���C�g�̍�����W X</param>
	/// <param name="y">�`�悷��X�v���C�g�̍�����W Y</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� X</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� Y</param>
	/// <param name="angle">�`�悷��X�v���C�g�̉�]�p</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawSprite(int x, int y, int textureHandle, int scaleX, int scaleY, int angle, unsigned int color);
	/// <summary>
	/// �X�v���C�g�̎w���`�����݂̂�`���`�悷��
	/// </summary>
	/// <param name="destX">�`�悷��X�v���C�g�̍�����W X</param>
	/// <param name="destY">�`�悷��X�v���C�g�̍�����W X</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� X</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� Y</param>
	/// <param name="angle">�`�悷��X�v���C�g�̉�]�p</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawSpriteRect(int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, int scaleX, int scaleY, int angle, unsigned int color);
	/// <summary>
	/// �l�p�`�`��
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W X</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W Y</param>
	/// <param name="x2">�`�悷��l�p�`�̉E����W X</param>
	/// <param name="y2">�`�悷��l�p�`�̉E����W Y</param>
	/// <param name="x3">�`�悷��l�p�`�̍������W X</param>
	/// <param name="y3">�`�悷��l�p�`�̍������W Y</param>
	/// <param name="x4">�`�悷��l�p�`�̉E�����W X</param>
	/// <param name="y4">�`�悷��l�p�`�̉E�����W Y</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float srcX, float srcY, float srcW, float srcH, float textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad2(Quad quad, float srcX, float srcY, float srcW, float srcH, float textureHandle, unsigned int color, bool isFlip);
	void DrawQuad2(Quad quad, float srcX, float srcY, float srcW, float srcH, float textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad2Normal(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="quad">Quad�^�ϐ�</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X�i�ϐ��j</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="sheets">�摜����</param>
	/// <param name="frame">���t���[���Ő؂�ւ��邩</param>
	/// <param name="framehensuu">���Z���Ă���t���[���̕ϐ�</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad2Renban(Quad quad, int& srcX, int srcY, int srcW, int srcH, int sheets, int frame, int& framehensuu, int textureHandle, unsigned int color, bool isFlip);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="scroll">�X�N���[������l</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void Background(int x1, int y1, int quadw, int quadh, float scrollkakeru, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="renban">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="frame">���t���[���Ŏ��̘A�ԉ摜�Ɉڂ邩</param>
	/// <param name="framehensuu">�t���[���̕ϐ�</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	/// <param name="hanten">���]�����邩</param>
	void DrawQuad2NormalRenban(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH, int sheets, int frame, int& framehensuu, int textureHandle, unsigned int color, bool hanten);


};


