#ifndef __SCREEN_GAME
#define __SCREEN_GAME



class GameScreen : public BaseScreen
{
public:
	GameScreen(String _name, InputManager* _input);
	~GameScreen();

	void Load();
	void Unload();
	void Update(float _DeltaTime);
	void Render();
};

#endif