#pragma once
#include "GameLevel.h"
#include "GameController.h"

class Level2ConfigScreen : public GameLevel
{
private:

public:
	void load() override;
	void unload() override;
	void update() override;
	int render(MainGraphics* gameGraphics) override;
};

