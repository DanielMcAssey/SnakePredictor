#include "stdafx.h"

int main(int argc, char* args[])
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const String SCREEN_TITLE = "Snake Predictor";
	const int SCREEN_FPS = 60;

	ScreenManager* _sys_screenManager = NULL;
	_sys_screenManager = new ScreenManager(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Window* _sys_window = _sys_screenManager->Initialize(SCREEN_TITLE);

	printf("SDL START: Running Main Loop\n");
	while (_sys_screenManager->Loop()) // Update game and check its still running
	{
		_sys_screenManager->Render(); // Render game
		SDL_Delay(1000 / SCREEN_FPS); // Lock to FPS
	}

	printf("SDL EXIT: Unloading Everything\n");
	// Game exited, so unload everything
	_sys_screenManager->UnloadAll();
	
	printf("SDL EXIT: Destroying Window and Quitting\n");
	SDL_DestroyWindow(_sys_window);
	SDL_Quit();

	return 0;
}