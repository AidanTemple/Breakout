#pragma region Include Statements
#include "InputManager.h"
#pragma endregion

InputManager::InputManager(void)
{
	input = NULL;
	mouse = NULL;
	keyboard = NULL;

	for(int i = 0; i < 256; i++)
	{
		KeyPressedState[i] = 0;
	}
}

InputManager::~InputManager(void)
{
	if(input)
	{
		if(mouse)
		{
			mouse->Unacquire();
			mouse->Release();
			mouse = NULL;
		}

		if(keyboard)
		{
			keyboard->Unacquire();
			keyboard->Release();
			keyboard = NULL;
		}

		input->Release();
		input = NULL;
	}
}

bool InputManager::Initialise(HINSTANCE hInstance, HWND wndHandle)
{
	HRESULT hResult;

	// Initialise and create a direct input object
	hResult = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&input, NULL);

	if(FAILED(hResult))
	{
		return FALSE;
	}

	// Creates a device to monitor the mouse
	if(FAILED(input->CreateDevice(GUID_SysMouse, &mouse, NULL)))
	{
		return FALSE;
	}

	if(FAILED(mouse->SetDataFormat(&c_dfDIMouse)))
	{
		return FALSE;
	}

	if(FAILED(mouse->SetCooperativeLevel(wndHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		return FALSE;
	}

	// Creates a deviceb to monitor the keyboard
	if(FAILED(input->CreateDevice(GUID_SysKeyboard, &keyboard, NULL)))
	{
		return false;
	}

	if(FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	if(FAILED(keyboard->SetCooperativeLevel(wndHandle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		return false;
	}

	if(FAILED(keyboard->Acquire()))
	{
		return false;
	}

	return true;
}

void InputManager::GetInput()
{
	HRESULT hResult;

	// Retrieve the current state of the mouse
	hResult = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);

	if(FAILED(hResult))
	{
		// Attempts to reacquire the mouse if lost
		mouse->Acquire();
	}

	// Retrieve the current state of the keyboard
	keyboard->GetDeviceState(sizeof(UCHAR[256]), (LPVOID)KeyState);

	if(FAILED(hResult))
	{
		// Attempts to reacquire the keyboard if lost
		keyboard->Acquire();
	}
}

int InputManager::GetMouseX()
{
	// Return the mouse state in the x axis
	return mouseState.lX;
}

int InputManager::GetMouseY()
{
	// Return the mouse state in the y axis
	return mouseState.lY;
}

bool InputManager::IsButtonPressed(int button)
{
	// Check the state of the mouse buttons
	if(mouseState.rgbButtons[button] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::KeyDown(DWORD key)
{
	// Determine if a key on the keyboard is currently pressed
	if(KeyState[key] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::KeyUp(DWORD key)
{
	// Determine if a key on the keyboard is not currently pressed
	if(KeyState[key] & 0x80)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool InputManager::KeyPress(DWORD key)
{
	// Check if a key is currently down
	if(KeyDown(key))
	{
		KeyPressedState[key] = 1;
	}

	// Check if a key is reaching the keydown state
	if(KeyPressedState[key] == 1)
	{
		// Check if a key is released
		if(KeyUp(key))
		{
			KeyPressedState[key] = 2;
		}
	}

	// Check if a key has been pressed and released
	if(KeyPressedState[key] == 2)
	{
		// Reset the key state
		KeyPressedState[key] = 0;

		return true;
	}

	return false;
}