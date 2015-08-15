#include "stdafx.h"
#include "../stdafx.h"
#include "InputHelper.h"


InputHelper::InputHelper(const Uint8 *keyboardState, Uint8 *keyboardLastState)
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
		if (_sys_keyboardKeys[iterator->first]) // Wait till is released
		{
			if (_sys_keyboardState[iterator->first] && !_sys_keyboardLastState[iterator->first])
			{
				return true;
			}
		}
		else
		{
			if (_sys_keyboardState[iterator->first])
			{
				return true;
			}
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