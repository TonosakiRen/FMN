#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include<cstdlib>


/*�@�x��������ƃ��W�A���ɕϊ�����֐��@*/
float Degree(float degree) {
	return degree * (M_PI / 180);
}
/*�@���W�A��������Ɠx���ɕϊ�����֐��@*/
float Radian(float radian) {
	return radian * (180 / M_PI);
}
