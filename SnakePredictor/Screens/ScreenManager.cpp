#include "stdafx.h"
#include "../stdafx.h"
#include "ScreenManager.h"


ScreenManager::ScreenManager()
{
	_sys_gameRunning = false;
	_sys_screenWidth = 0;
	_sys_screenHeight = 0;
	_sys_window = NULL;
	_sys_deltaTime = 0.0f;
	_sys_lastFrameTime = 0;
	_sys_currentFrameTime = 0;
	_sys_fpsCounterUpdateTime = 0.0f;
}


ScreenManager::~ScreenManager()
{
}


SDL_Window* ScreenManager::Initialize(String _SCREEN_TITLE, int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	if (_sys_gameRunning) // Prevent re-initializing
		return NULL;

	// Initialize SDL
	printf("SDL INIT: Initializing\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL ERR: SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// SDL Init is OK, create window
		printf("SDL INIT: Creating Window\n");
		_sys_screenWidth = _SCREEN_WIDTH;
		_sys_screenHeight = _SCREEN_HEIGHT;
		_sys_window = SDL_CreateWindow(_SCREEN_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _sys_screenWidth, _sys_screenHeight, SDL_WINDOW_SHOWN);
		if (_sys_window == NULL)
		{
			printf("SDL ERR: Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return NULL;
		}

		printf("SDL INIT: Creating Renderer\n");
		SDL_ShowCursor(SDL_DISABLE);
		_sys_currentFrameTime = SDL_GetTicks();
		_sys_renderer = SDL_CreateRenderer(_sys_window, 0, SDL_RENDERER_ACCELERATED);

		printf("SDL INIT: Registering Inputs\n");
		// Initialize InputManager
		_sys_input = new InputManager();
		_sys_input->AddKeyboardInput("QUIT", SDL_SCANCODE_Q, true);
		_sys_input->AddKeyboardInput("QUIT", SDL_SCANCODE_ESCAPE, true);
		_sys_input->AddKeyboardInput("ENTER", SDL_SCANCODE_RETURN, true);
		_sys_input->AddKeyboardInput("ENTER", SDL_SCANCODE_RETURN2, true);

		printf("SDL INIT: Registering Default Screens\n");
		// Add initial screens
		_sys_screenList.push_back(std::unique_ptr<BaseScreen>(new GameScreen("Game", _sys_input, _sys_window)));

		printf("SDL INIT: Loading Default Screens Content\n");
		// Load the screen content
		for (_sys_screenList_itr = _sys_screenList.begin(); _sys_screenList_itr != _sys_screenList.end(); ++_sys_screenList_itr) {
			printf("SDL INIT->SCREEN: Loading '%s' Screen, please wait...\n", (*_sys_screenList_itr)->GetScreenName().c_str());
			(*_sys_screenList_itr)->Load();
		}

		// Set game to running.
		_sys_gameRunning = true;
	}

	return _sys_window;
}

// Unload everything that ScreenManager manages
void ScreenManager::UnloadAll()
{
	if (_sys_gameRunning)
		return; // Dont exit if game is running

	printf("SDL EXIT: Preparing for Exit\n");
	printf("SDL EXIT: Unloading Screens\n");
	// Unload all screens
	for (_sys_screenList_itr = _sys_screenList.begin(); _sys_screenList_itr != _sys_screenList.end(); ++_sys_screenList_itr) {
		printf("SDL EXIT->SCREEN: Unloading '%s' Screen, please wait...\n", (*_sys_screenList_itr)->GetScreenName().c_str());
		(*_sys_screenList_itr)->Unload();
	}
	_sys_screenList.clear();

	printf("SDL EXIT: Misc. Tasks\n");
	delete _sys_input;
	_sys_input = nullptr;
}

// Update the screens
bool ScreenManager::Loop()
{
	if (_sys_window == NULL || !_sys_gameRunning)
	{
		printf("SDL ERR: Window does not exist or program exited prematurely! SDL_Error: %s\n", SDL_GetError());
		return false; // Window doesnt exist so exit the game forcefully.
	}
	else
	{
		// Update Delta Time
		_sys_lastFrameTime = _sys_currentFrameTime;
		_sys_currentFrameTime = SDL_GetTicks();
		_sys_deltaTime = (float)(_sys_currentFrameTime - _sys_lastFrameTime) / 1000;
		_sys_fpsCounterUpdateTime += _sys_deltaTime;

		if (_sys_fpsCounterUpdateTime >= 2.0f)
		{
			// TODO: Not accurate, external tools mention different FPS than this
			printf("SDL INFO: FPS %f\n", (1.0f / _sys_deltaTime));
			_sys_fpsCounterUpdateTime = 0.0f;
		}

		while (SDL_PollEvent(&_sys_eventHandler)) {
			if (_sys_eventHandler.type == SDL_QUIT)
				_sys_gameRunning = false;
		}

		_sys_input->UpdateStates(); // Update input states

		if (_sys_input->IsPressed("QUIT")) // Global quit input
			_sys_gameRunning = false;

		for (_sys_screenList_itr = _sys_screenList.begin(); _sys_screenList_itr != _sys_screenList.end(); ++_sys_screenList_itr) {
			(*_sys_screenList_itr)->Update(_sys_deltaTime);
		}
	}

	// Is game still running?
	return _sys_gameRunning;
}

// Render the screens
void ScreenManager::Render()
{
	if (_sys_window == NULL)
	{
		printf("SDL ERR: Window does not exist! SDL_Error: %s\n", SDL_GetError());
		return; // Window does not exist, so no point in rendering.
	}
	else
	{
		SDL_SetRenderDrawColor(_sys_renderer, 101, 156, 239, 255); // Screen clear
		SDL_RenderClear(_sys_renderer);

		for (_sys_screenList_itr = _sys_screenList.begin(); _sys_screenList_itr != _sys_screenList.end(); ++_sys_screenList_itr) {
			(*_sys_screenList_itr)->Render(_sys_renderer);
		}

		// Copy Render buffer to screen
		SDL_RenderPresent(_sys_renderer);
	}
}