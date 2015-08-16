#ifndef __SCREEN_BASE
#define __SCREEN_BASE

class BaseScreen
{
public:
	BaseScreen(std::string _name, InputManager* _input);
	~BaseScreen();
	virtual void Load();
	virtual void Unload();
	virtual void Update(float _DeltaTime);
	virtual void Render();
protected:
	InputManager* gInput;
	std::string gScreenName;
};

#endif