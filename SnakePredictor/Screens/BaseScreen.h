#ifndef __SCREEN_BASE
#define __SCREEN_BASE

class BaseScreen
{
public:
	BaseScreen(String _name, InputManager* _input, SDL_Window* _window);
	~BaseScreen();
	virtual void Load();
	virtual void Unload();
	virtual void Update(float _DeltaTime);
	virtual void Render(SDL_Renderer* _Renderer);
protected:
	InputManager* gInput;
	SDL_Window* gWindow;
	std::string gScreenName;
};

#endif