#ifndef __INPUT_HELPER
#define __INPUT_HELPER

class InputHelper
{
public:
	InputHelper(const Uint8 *keyboardState, Uint8 *keyboardLastState);
	~InputHelper();

	bool IsPressed();

	void AddKeyboardInput(SDL_Keycode _key, bool isReleased);
private:
	std::map<SDL_Keycode, bool> _sys_keyboardKeys;
	const Uint8 *_sys_keyboardState;
	Uint8 *_sys_keyboardLastState;
};

#endif