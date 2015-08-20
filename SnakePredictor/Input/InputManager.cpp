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
#include "InputManager.h"


InputManager::InputManager()
{
	_sys_keyboardSDLState = SDL_GetKeyboardState(&_sys_keyboardStateLength);
	_sys_keyboardState = new Uint8[_sys_keyboardStateLength];
	_sys_keyboardLastState = new Uint8[_sys_keyboardStateLength];
}


InputManager::~InputManager()
{
	_sys_keyboardSDLState = NULL;
	delete[] _sys_keyboardState;
	_sys_keyboardState = nullptr;
	delete[] _sys_keyboardLastState;
	_sys_keyboardLastState = nullptr;
}


bool InputManager::IsPressed(String _action)
{
	if (!_sys_inputs.count(_action))
	{
		return false;
	}

	return _sys_inputs[_action]->IsPressed();
}


InputHelper* InputManager::NewInput(String _action)
{
	if (!_sys_inputs.count(_action))
	{
		_sys_inputs[_action] = new InputHelper(_sys_keyboardState, _sys_keyboardLastState);
	}

	return _sys_inputs[_action];
}


void InputManager::AddKeyboardInput(String _action, SDL_Keycode _key, bool _isReleased)
{
	this->NewInput(_action)->AddKeyboardInput(_key, _isReleased);
}


void InputManager::ResetAllInput()
{
	_sys_inputs.clear();
}


void InputManager::UpdateStates()
{
	std::memcpy(_sys_keyboardLastState, _sys_keyboardState, _sys_keyboardStateLength);
	SDL_PumpEvents(); // Update Input states and event queue
	std::memcpy(_sys_keyboardState, _sys_keyboardSDLState, _sys_keyboardStateLength);
}