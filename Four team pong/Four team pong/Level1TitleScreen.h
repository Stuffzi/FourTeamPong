#pragma once
#include "GameLevel.h"
#include "GameController.h"
#include <cmath>

class Level1TitleScreen : public GameLevel
{
private:
	//ClickOutput* COutputPointer;


public:
	void load() override;
	void unload() override;
	void update() override;
	int render(MainGraphics* gameGraphics) override;
};

