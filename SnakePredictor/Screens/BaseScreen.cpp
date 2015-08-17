#include "stdafx.h"
#include "../stdafx.h"
#include "BaseScreen.h"


BaseScreen::BaseScreen(String _name, InputManager* _input, SDL_Window* _window)
{
	gInput = _input;
	gWindow = _window;
	gScreenName = _name;
}


BaseScreen::~BaseScreen()
{
}


String BaseScreen::GetScreenName()
{
	return gScreenName;
}


// Virtual Methods
void BaseScreen::Load()
{

}


void BaseScreen::Unload()
{

}


void BaseScreen::Update(float _DeltaTime)
{

}


void BaseScreen::Render(SDL_Renderer* _Renderer)
{

}