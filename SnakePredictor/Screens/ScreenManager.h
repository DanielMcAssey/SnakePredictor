/*
// This file is part of SnakePredictor
//
//  (c) Daniel McAssey <hello@glokon.me>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.
*/
#ifndef __SCREEN_MANAGER
#define __SCREEN_MANAGER

#include "ScreenList.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	SDL_Window* Initialize(String _SCREEN_TITLE, int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	void UnloadAll();

	bool Loop();
	void Render();
private:
	int _sys_screenWidth;
	int _sys_screenHeight;
	bool _sys_gameRunning;
	bool _sys_gamePaused;

	SDL_Window* _sys_window;
	SDL_Event _sys_eventHandler;
	SDL_Renderer* _sys_renderer;
	InputManager* _sys_input;

	float _sys_deltaTime;
	int _sys_lastFrameTime;
	int _sys_currentFrameTime;
	float _sys_fpsCounterUpdateTime;
	int _sys_fpsAccumulated;

	std::vector<std::unique_ptr<BaseScreen>> _sys_screenList;
	std::vector<std::unique_ptr<BaseScreen>>::iterator _sys_screenList_itr;
};

#endif