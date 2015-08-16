#include "stdafx.h"
#include "../stdafx.h"
#include "GameScreen.h"

const int POINT_SIZE = 10;

GameScreen::GameScreen(String _name, InputManager* _input, SDL_Window* _window) : BaseScreen(_name, _input, _window)
{
}


GameScreen::~GameScreen()
{
}


void GameScreen::Load()
{
	BaseScreen::Load();

	int screenWidth, screenHeight;
	SDL_GetWindowSize(gWindow, &screenWidth, &screenHeight);

	// TODO: Create a grid system to act as a level for A* path finding
}


void GameScreen::Unload()
{
	BaseScreen::Unload();

}


void GameScreen::Update(float _DeltaTime)
{
	BaseScreen::Update(_DeltaTime);

}


void GameScreen::Render(SDL_Renderer* _Renderer)
{
	BaseScreen::Render(_Renderer);

	SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 0);
	SDL_Rect testRectangle = { 0, 0, POINT_SIZE, POINT_SIZE };
	SDL_RenderFillRect(_Renderer, &testRectangle);
}