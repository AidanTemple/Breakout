#pragma region Include Statements
#include <Windows.h>
#include "SceneManager.h"
#pragma endregion

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

HINSTANCE hInstance; // Holds an instance of the application
HWND wndHandle; // Gloabal window handle

bool InitWindow(HINSTANCE hInstance); 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Initialise Window
	if(!InitWindow(hInstance))
	{
		// Prevet the application from executing if no window is created
		return false;
	}

	// Create a new scene manager object
	SceneManager* pSceneManager = new SceneManager();

	// Initialise the scene manager object
	if(pSceneManager->Init(wndHandle, hInstance) == false)
	{
		return 0;
	}

	// Main message loop
	MSG msg = {0};
	ZeroMemory(&msg, sizeof(msg));

	while(msg.message != WM_QUIT)
	{
		// Dispatch incoming sent messages immediately, checks thread message queue for posted message, 
		// and retrieves any messages http://bit.ly/XqtGZb
		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			// Translates virtual-key messages into character messages. The character messages 
			// are posted to the calling thread's message queue, to be read the next time the 
			// thread calls the GetMessage or PeekMessage function. http://bit.ly/ZygJan
			TranslateMessage(&msg);

			// Dispatches a message to a window procedure. Used to dispatch a message retrieved 
			// by the GetMessage function. http://bit.ly/YqErEA
			DispatchMessage(&msg);
		}
		else
		{
			pSceneManager->Update();
		}
	}

	// Delete the scene manager object
	if(pSceneManager)
	{
		delete pSceneManager;
	}

	// Cast msg and return value
	return (int)msg.wParam;
}

bool InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	// Fill the WNDCLASSEX structure, this describes how the window will look to the system
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Breakout";
	wc.hIconSm = 0;

	if(!RegisterClassEx(&wc))
	{
		return false;
	}

	int width = 800;
	int height = 600;

	DWORD style = WS_POPUP | WS_VISIBLE;
	style = WS_OVERLAPPEDWINDOW;

	wndHandle = CreateWindow("Breakout", "Breakout", style, CW_USEDEFAULT, 
		CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

	if(!wndHandle)
	{
		return false;
	}

	// Sets a global instance handle
	hInstance = hInstance;

	// Display the application window
	ShowWindow(wndHandle, SW_SHOW);

	// Update the window
	UpdateWindow(wndHandle);

	return true;
}

// Main window procedure for the application
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check an available message in the queue
	switch(message)
	{
		// Check if the applications close button was pressed
		case WM_DESTROY:
			{
				// Exit the application
				PostQuitMessage(0);
				break;
			}
		case WM_KEYDOWN:
			{
				switch(wParam)
				{
					// Check if the escape key has been pressed
					case VK_ESCAPE:
						{
							// Exit the application
							PostQuitMessage(0);
							break;
						}
				}
			}
	}

	// Return message(s) to the default window procedure
	return DefWindowProc(hWnd, message, wParam, lParam);
}