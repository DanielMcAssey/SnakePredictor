#ifndef __SCREEN_MANAGER
#define __SCREEN_MANAGER

#include "ScreenList.h"

class ScreenManager
{
public:
	ScreenManager(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	~ScreenManager();

	SDL_Window* Initialize(String _SCREEN_TITLE);
	void UnloadAll();

	bool Loop();
	void Render();
protected:
	InputManager* gInput; // Global input manager accesable by all screens
private:
	int _sys_screenWidth;
	int _sys_screenHeight;
	bool _sys_gameRunning;

	SDL_Window* _sys_window;
	SDL_Surface* _sys_screenSurface;
	SDL_Event _sys_eventHandler;

	float _sys_deltaTime;
	int _sys_lastFrameTime;
	int _sys_currentFrameTime;

	std::vector<std::unique_ptr<BaseScreen>> _sys_screenList;
	std::vector<std::unique_ptr<BaseScreen>>::iterator _sys_screenList_itr;
};

#endif