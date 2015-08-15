#include "stdafx.h"
#include "../stdafx.h"
#include "ScreenManager.h"


ScreenManager::ScreenManager(int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	_sys_gameRunning = false;
	_sys_screenWidth = _SCREEN_WIDTH;
	_sys_screenHeight = _SCREEN_HEIGHT;
	_sys_window = NULL;
	_sys_screenSurface = NULL;
	_sys_deltaTime = 0.0f;
	_sys_lastFrameTime = 0;
	_sys_currentFrameTime = 0;
}


ScreenManager::~ScreenManager()
{
}


SDL_Window* ScreenManager::Initialize(const char *_SCREEN_TITLE)
{
	if (_sys_gameRunning) // Prevent re-initializing
		return NULL;

	printf("SDL INIT: Initializing\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL ERR: SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		printf("SDL INIT: Creating Window\n");
		_sys_window = SDL_CreateWindow(_SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _sys_screenWidth, _sys_screenHeight, SDL_WINDOW_SHOWN);
		if (_sys_window == NULL)
		{
			printf("SDL ERR: Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}

		SDL_ShowCursor(SDL_DISABLE);
		_sys_currentFrameTime = SDL_GetTicks();
	}

	printf("SDL INIT: Registering Inputs\n");
	// Initialize InputManager
	gInput = new InputManager();
	gInput->AddKeyboardInput("QUIT", SDL_SCANCODE_Q, true);
	gInput->AddKeyboardInput("ENTER", SDL_SCANCODE_RETURN, true);
	gInput->AddKeyboardInput("ENTER", SDL_SCANCODE_RETURN2, true);

	// Set game to running.
	_sys_gameRunning = true;
	return _sys_window;
}

// Unload everything that ScreenManager manages
void ScreenManager::UnloadAll()
{
	if (!_sys_gameRunning)
		return;

	// Unload everything and prepare for exit
}

// Update the screens
bool ScreenManager::Loop()
{
	if (_sys_window == NULL)
	{
		return false; // Window doesnt exist so exit the game forcefully.
	}
	else
	{
		// Update Delta Time
		_sys_lastFrameTime = _sys_currentFrameTime;
		_sys_currentFrameTime = SDL_GetTicks();
		_sys_deltaTime = (float)(_sys_currentFrameTime - _sys_lastFrameTime) / 1000;

		gInput->UpdateStates(); // Update input states

		if (gInput->IsPressed("QUIT"))
			_sys_gameRunning = false;

	}

	// Is game still running?
	return _sys_gameRunning;
}

// Render the screens
void ScreenManager::Render()
{
	if (_sys_window == NULL)
	{
		return; // Window does not exist, so no point in rendering.
	}
	else
	{
		// Do render

		_sys_screenSurface = SDL_GetWindowSurface(_sys_window);

		//Fill the surface white
		SDL_FillRect(_sys_screenSurface, NULL, SDL_MapRGB(_sys_screenSurface->format, 0xFF, 0xFF, 0xFF));

		SDL_UpdateWindowSurface(_sys_window);
	}
}