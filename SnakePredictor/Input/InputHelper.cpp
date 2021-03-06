/*
// This file is part of SnakePredictor
//
//  (c) Daniel McAssey <hello@glokon.me>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.
*/
#include "stdafx.h"
#include "../stdafx.h"
#include "InputHelper.h"


InputHelper::InputHelper(Uint8 *keyboardState, Uint8 *keyboardLastState)
{
	_sys_keyboardState = keyboardState;
	_sys_keyboardLastState = keyboardLastState;
}


InputHelper::~InputHelper()
{
	_sys_keyboardState = NULL;
	delete _sys_keyboardLastState;
	_sys_keyboardLastState = nullptr;
}


bool InputHelper::IsPressed()
{
	typedef std::map<SDL_Keycode, bool>::iterator it_type;
	for (it_type iterator = _sys_keyboardKeys.begin(); iterator != _sys_keyboardKeys.end(); iterator++) {
		if (_sys_keyboardKeys[iterator->first]) // Is it wait for key to be released?
		{
			return (_sys_keyboardState[iterator->first] && !_sys_keyboardLastState[iterator->first]);
		}
		else
		{
			return _sys_keyboardState[iterator->first];
		}
	}
	return false;
}


void InputHelper::AddKeyboardInput(SDL_Keycode _key, bool isReleased)
{
	if (_sys_keyboardKeys.count(_key))
	{
		return;
	}

	_sys_keyboardKeys[_key] = isReleased;
}