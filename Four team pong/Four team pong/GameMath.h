#pragma once
#include <d2d1_1.h>
#include <math.h>
class GameMath
{
public:
	//Find x, y value at which you intercept a line.
	D2D1_VECTOR_2F findInterceptPoint(D2D1_VECTOR_2F linePos, D2D1_VECTOR_2F lineDirUnit, D2D1_VECTOR_2F pos, D2D1_VECTOR_2F vel);
};

