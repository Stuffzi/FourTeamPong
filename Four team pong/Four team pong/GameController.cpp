/*
* Program name: "Four Team Pong"
* (c) ProgrammerStuff, 2023
* Governed under Apache 2.0, you are free to modify and use with minimal limitation.
* Refer to LICENSE.txt or http://www.apache.org/licenses/LICENSE-2.0.
*/

#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;


void GameController::init() 
{
	loading = true;
	currentLevel = 0;
	loading = false;
}


void GameController::loadInitialLevel(GameLevel* level) 
{
	loading = true;
	currentLevel = level;
	currentLevel->load();
	loading = false;
}


void GameController::ChangeLevel(GameLevel* level) 
{
	loading = true;
	currentLevel->unload();
	level->load();
	delete currentLevel;
	currentLevel = level;
	loading = false;
}


void GameController::update() 
{
	std::this_thread::sleep_for(16ms);
	if(!loading) currentLevel->update();
}


int GameController::render(MainGraphics* gameGraphics) 
{
	if (!loading) return currentLevel->render(gameGraphics); else return -1;
}