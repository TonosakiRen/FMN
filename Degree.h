#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include<cstdlib>


/*　度数を入れるとラジアンに変換する関数　*/
float Degree(float degree) {
	return degree * (M_PI / 180);
}
/*　ラジアンを入れると度数に変換する関数　*/
float Radian(float radian) {
	return radian * (180 / M_PI);
}
