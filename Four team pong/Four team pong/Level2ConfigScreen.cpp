#include "Level2ConfigScreen.h"



void Level2ConfigScreen::load()
{

}


void Level2ConfigScreen::unload()
{

}


void Level2ConfigScreen::update()
{

}


int Level2ConfigScreen::render(MainGraphics* gameGraphics)
{
	gameGraphics->clearScreen(D2D1::Vector3F(0.0f, 0.1f, 0.0f));

	if (gameGraphics->ClickButton(D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector2F(100.0f, 40.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true)->Clicked)
	{
		return 1;
	}

	if (gameGraphics->ClickButton(D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector2F(100.0f, 40.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true)->MouseHovering)
	{
		
	}

	gameGraphics->createSquare(D2D1::Vector2F(100.0f, 100.0f), D2D1::Vector2F(5.0f, 800.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true);
	gameGraphics->createSquare(D2D1::Vector2F(105.0f, 100.0f), D2D1::Vector2F(1454.0f, 5.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true);
	gameGraphics->createSquare(D2D1::Vector2F(1559.0f, 100.0f), D2D1::Vector2F(5.0f, 800.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true);
	gameGraphics->createSquare(D2D1::Vector2F(105.0f, 895.0f), D2D1::Vector2F(1454.0f, 5.0f), D2D1::Vector4F(0.4f, 1.0f, 0.4f, 1.0f), 1.0f, true);

	gameGraphics->drawText(D2D1::Vector2F(125.0f, 110.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test slider", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 160.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 210.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 260.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 310.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 360.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 410.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));
	gameGraphics->drawText(D2D1::Vector2F(125.0f, 460.0f), D2D1::Vector2F(200.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), 12, L"Test Setting", 1, 0, D2D1::Vector2F(125.0f, 110.0f));


	return -1;
}