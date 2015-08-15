#include "stdafx.h"
#include "../stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
	_sys_keyboardState = SDL_GetKeyboardState(NULL);
}


InputManager::~InputManager()
{
	_sys_keyboardState = NULL;
	delete _sys_keyboardLastState;
	_sys_keyboardLastState = nullptr;
}


bool InputManager::IsPressed(std::string _action)
{
	if (!_sys_inputs.count(_action))
	{
		return false;
	}

	return _sys_inputs[_action]->IsPressed();
}


InputHelper* InputManager::NewInput(std::string _action)
{
	if (!_sys_inputs.count(_action))
	{
		_sys_inputs[_action] = new InputHelper(_sys_keyboardState, _sys_keyboardLastState);
	}

	return _sys_inputs[_action];
}


void InputManager::AddKeyboardInput(std::string _action, SDL_Keycode _key, bool _isReleased)
{
	this->NewInput(_action)->AddKeyboardInput(_key, _isReleased);
}


void InputManager::ResetAllInput()
{
	_sys_inputs.clear();
}


void InputManager::UpdateStates()
{
	//std::memcpy(_sys_keyboardLastState, _sys_keyboardState, sizeof(_sys_keyboardState)); // TODO: BROKEN, need to get correct size of array
}