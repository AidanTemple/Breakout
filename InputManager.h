#pragma region Include Statements
#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma endregion

class InputManager
{
	public:

		InputManager(void);

		~InputManager(void);

		bool Initialise(HINSTANCE hInstance, HWND wndHandle);

		void GetInput();

		bool IsButtonPressed(int button);

		int GetMouseX();
		int GetMouseY();

		bool KeyDown(DWORD key);
		bool KeyUp(DWORD key);
		bool KeyPress(DWORD key);

	private:

		LPDIRECTINPUT8 input;
		LPDIRECTINPUTDEVICE8 mouse;
		LPDIRECTINPUTDEVICE8 keyboard;

		DIMOUSESTATE mouseState;

		UCHAR KeyState[256];
		UCHAR KeyPressedState[256];
};