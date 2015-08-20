/*
// This file is part of SnakePredictor
//
//  (c) Daniel McAssey <hello@glokon.me>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.
*/
#ifndef __INPUT_HELPER
#define __INPUT_HELPER

class InputHelper
{
public:
	InputHelper(Uint8 *keyboardState, Uint8 *keyboardLastState);
	~InputHelper();

	bool IsPressed();

	void AddKeyboardInput(SDL_Keycode _key, bool isReleased);
private:
	std::map<SDL_Keycode, bool> _sys_keyboardKeys;
	Uint8 *_sys_keyboardState;
	Uint8 *_sys_keyboardLastState;
};

#endif