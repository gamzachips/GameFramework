#pragma once

enum class InputType
{
	None, Pressed, Down, Up
};

#define KEYDOWN 0x80
#define KEYTOGGLE 0x01

class InputManager
{
	friend class Game;

public:
	InputType GetKey(int key);
private:
	void Update();
private:
	BYTE prevKeys[256];
	BYTE currKeys[256];
};

