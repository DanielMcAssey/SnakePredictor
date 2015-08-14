#ifndef __SCREEN_MANAGER
#define __SCREEN_MANAGER

class ScreenManager
{
public:
	ScreenManager(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	~ScreenManager();

	SDL_Window* Initialize(const char *_SCREEN_TITLE);
	void UnloadAll();

	bool Loop();
	void Render();
private:
	int _sys_screenWidth;
	int _sys_screenHeight;
	bool _sys_gameRunning;
	SDL_Window* _sys_window;
	SDL_Surface* _sys_screenSurface;
	SDL_Event _sys_eventHandler;
};

#endif