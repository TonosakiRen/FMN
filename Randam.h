#pragma once
#include<cstdlib>
#include<ctime>

namespace Randam{

	/// <summary>
	/// —”
	/// </summary>
	/// <param name="min">Å¬’l</param>
	/// <param name="max">Å‘å’l</param>
	/// <returns>intŒ^</returns>
	int RAND(int min, int max);

	float RAND(float min, float max);

	void SRAND();
	///srand((unsingned)time(NULL));
}