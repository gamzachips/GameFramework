#include "pch.h"
#include "InputManager.h"

InputType InputManager::GetKey(int key)
{
	if (prevKeys[key] & KEYDOWN)
	{
		if (currKeys[key] & KEYDOWN)
		{
			return InputType::Down;
		}
		else
		{
			return InputType::Up;
		}
	}
	else
	{
		if (currKeys[key] & KEYDOWN)
			return InputType::Pressed;
	}

	return InputType::None;
}

void InputManager::Update()
{
	memcpy(prevKeys, currKeys, 256);
	if (GetKeyboardState(currKeys))
	{
		
	}
	
}
