#pragma once
#include "GameLevel.h"
#include "GameController.h"
#include <cmath>

//title screen, automatically loaded
class level0 : public GameLevel
{
private:
	bool paused;
	POINT mousePos;
	//colors
	D2D1_VECTOR_4F lColor;	
	D2D1_VECTOR_4F tColor;
	D2D1_VECTOR_4F rColor;
	D2D1_VECTOR_4F bColor;
	int scores[4] = { 0, 0, 0, 0 }; //Left, top, right, bottom
	bool alivePaddles[4] = { true, true, true, true };


	//positions and vectors and stuff
	D2D1_VECTOR_2F ballPos;
	D2D1_VECTOR_4F ballColor;
	D2D1_VECTOR_2F ballVelocity;
	int ballCurrentTerritory; //1 = left, 2 = top, 3 = right, 4 = bottom, 0 = neutral/dead

	D2D1_VECTOR_2F lp;
	bool lpIsAlive;
	int lpScore;

	D2D1_VECTOR_2F tp;
	bool tpIsAlive;
	int tpScore;

	D2D1_VECTOR_2F rp;
	bool rpIsAlive;
	int rpScore;

	D2D1_VECTOR_2F bp;
	bool bpIsAlive;
	int bpScore;

	int paddlesAlive;
	int ballHoldTimer;
	int pauseDebounce;

public:
	void load() override;
	void unload() override;
	void update() override;
	int render(MainGraphics* gameGraphics) override;

};

