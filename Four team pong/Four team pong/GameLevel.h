#pragma once
#include "MainGraphics.h"

class GameLevel
{
private:
	struct ClickOutput {
		bool Hovering;
		bool Clicked;
	};
public:
	virtual void load();
	virtual void unload();
	virtual void update();
	virtual int render(MainGraphics* gameGraphics);
};

