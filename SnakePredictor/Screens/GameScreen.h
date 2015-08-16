#ifndef __SCREEN_GAME
#define __SCREEN_GAME



class GameScreen : public BaseScreen
{
public:
	GameScreen(String _name, InputManager* _input, SDL_Window* _window);
	~GameScreen();

	void Load();
	void Unload();
	void Update(float _DeltaTime);
	void Render(SDL_Renderer* _Renderer);
};

#endif