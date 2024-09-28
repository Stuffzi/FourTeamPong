#pragma once
#include "GameLevel.h"

//singleton class, only ment for one to be created
//hence why everything is static
class GameController
{
private:
	GameController();
	static GameLevel* currentLevel;
	static bool loading;

public:
	static void init();

	static void loadInitialLevel(GameLevel* level);
	static void ChangeLevel(GameLevel* level);
	static void update();
	static int render(MainGraphics* gameGraphics);
};

