/*
// This file is part of SnakePredictor
//
//  (c) Daniel McAssey <hello@glokon.me>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.
*/
#ifndef __INPUT_MANAGER
#define __INPUT_MANAGER

#include "InputHelper.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool IsPressed(String _action);

	void AddKeyboardInput(String _action, SDL_Keycode _key, bool _isReleased);
	void ResetAllInput();
	void UpdateStates();
private:
	InputHelper* NewInput(String _action);

	std::map<String, InputHelper*> _sys_inputs;
	int _sys_keyboardStateLength;
	Uint8 *_sys_keyboardState;
	Uint8 *_sys_keyboardLastState;
	const Uint8 *_sys_keyboardSDLState;
};

#endif