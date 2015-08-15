#ifndef __INPUT_MANAGER
#define __INPUT_MANAGER

#include "InputHelper.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool IsPressed(std::string _action);

	void AddKeyboardInput(std::string _action, SDL_Keycode _key, bool _isReleased);
	void ResetAllInput();
	void UpdateStates();
private:
	InputHelper* NewInput(std::string _action);

	std::map<std::string, InputHelper*> _sys_inputs;
	int _sys_keyboardStateLength;
	Uint8 *_sys_keyboardState;
	Uint8 *_sys_keyboardLastState;
	const Uint8 *_sys_keyboardSDLState;
};

#endif