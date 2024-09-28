#include "Level1TitleScreen.h"

void Level1TitleScreen::load() {
	//COutputPointer = new ClickOutput{ false, false };
}


void Level1TitleScreen::unload() {
	//delete COutputPointer;
}


void Level1TitleScreen::update() {

}


int Level1TitleScreen::render(MainGraphics* gameGraphics) {
	gameGraphics->clearScreen(D2D1::Vector3F(0.0f, 0.1f, 0.0f));

	//play button
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 220.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->Clicked)
	{
		return 0; //Switch to game level (level 0)
	}

	//Q-play button
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 270.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->Clicked)
	{
		return 0; //Switch to game level (level 0)
	}

	//Config.
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 320.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->Clicked)
	{
		return 2; //Switch to configuration menu (level 2)
	}

	//Ach.
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 370.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->Clicked)
	{
		return 0; //Switch to game level (level 0)
	}

	//**********

	//play button
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 220.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->MouseHovering)
	{
		gameGraphics->createSquare(D2D1::Vector2F(120.0f, 205.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(0.f, 0.85f, 0.5f, 0.75f), 1.0f, true);
	}

	//Quick play button
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 270.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->MouseHovering)
	{
		gameGraphics->createSquare(D2D1::Vector2F(120.0f, 255.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(0.f, 0.85f, 0.5f, 0.75f), 1.0f, true);
	}

	//Configuration button
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 320.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->MouseHovering)
	{
		gameGraphics->createSquare(D2D1::Vector2F(120.0f, 305.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(0.f, 0.85f, 0.5f, 0.75f), 1.0f, true);
	}

	//Achievements button (I can't spell)
	if (gameGraphics->ClickButton(D2D1::Vector2F(120.0f, 370.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, true)->MouseHovering)
	{
		gameGraphics->createSquare(D2D1::Vector2F(120.0f, 355.0f), D2D1::Vector2F(300.0f, 40.0f), D2D1::Vector4F(0.f, 0.85f, 0.5f, 0.75f), 1.0f, true);
	}

	gameGraphics->drawText(D2D1::Vector2F(100.0f, 100.0f), D2D1::Vector2F(600.0f, 50.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 14, L"Four Team Pong", 0, 0.0f, D2D1::Vector2F(100.0f, 200.0f));
	gameGraphics->drawText(D2D1::Vector2F(120.0f, 200.0f), D2D1::Vector2F(300.0f, 30.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 9, L"> Play...", 1, 0.0f, D2D1::Vector2F(100.0f, 200.0f));
	gameGraphics->drawText(D2D1::Vector2F(120.0f, 250.0f), D2D1::Vector2F(300.0f, 30.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 15, L"> QuickPlay:tm:", 1, 0.0f, D2D1::Vector2F(100.0f, 200.0f));
	gameGraphics->drawText(D2D1::Vector2F(120.0f, 300.0f), D2D1::Vector2F(300.0f, 30.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 19, L"> Configuration...", 1, 0.0f, D2D1::Vector2F(100.0f, 200.0f));
	gameGraphics->drawText(D2D1::Vector2F(120.0f, 350.0f), D2D1::Vector2F(300.0f, 30.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 17, L"> Achievements...", 1, 0.0f, D2D1::Vector2F(100.0f, 200.0f));
	gameGraphics->drawText(D2D1::Vector2F(50.0f, 1000.0f), D2D1::Vector2F(300.0f, 30.0f), D2D1::Vector4F(0.2f, 0.6f, 0.2f, 1.0f), 12, L"Version 24B1", 2, 0.0f, D2D1::Vector2F(50.0f, 1000.0f));

	gameGraphics->createSquare(D2D1::Vector2F(80.0f, 100.0f), D2D1::Vector2F(5.0f, 325.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true);
	return -1;
}