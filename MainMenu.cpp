#pragma region Include Statements
#include "SpriteBatch.h"
#include "InputManager.h"
#include "MainMenu.h"
#pragma endregion

MainMenu::MainMenu()
{
	pInput = NULL;
	pBackground = NULL;
	pNewGameDefault = NULL;
	pNewGameSelected = NULL;
	pExitDefault = NULL;
	pExitSelected = NULL;
}

MainMenu::~MainMenu()
{
	if(pInput != NULL)
	{
		delete pInput;
	}

	if(pBackground != NULL)
	{
		delete pBackground;
	}

	if(pNewGameDefault != NULL)
	{
		delete pNewGameDefault;
	}

	if(pNewGameSelected != NULL)
	{
		delete pNewGameSelected;
	}

	if(pExitDefault != NULL)
	{
		delete pExitDefault;
	}

	if(pExitSelected != NULL)
	{
		delete pExitSelected;
	}
}

bool MainMenu::Initialise(InputManager* input, LPDIRECT3DDEVICE9 device)
{
	pInput = input;

	menuItemSelected = 0;
	state = 0;

	// Initialise and load the background texture
	pBackground = new SpriteBatch();
	pBackground->LoadTexture(device, "background.jpg");

	// Intialise and load the default new game menu item
	pNewGameDefault = new SpriteBatch();
	pNewGameDefault->LoadTexture(device, "new_game_default.jpg");
	pNewGameDefault->SetPosition(326, 400);

	// Initialise and load the selected new game menu item
	pNewGameSelected = new SpriteBatch();
	pNewGameSelected->LoadTexture(device, "new_game_selected.jpg");
	pNewGameSelected->SetPosition(326, 400);

	// Initialise and load the default exit menu item
	pExitDefault = new SpriteBatch();
	pExitDefault->LoadTexture(device, "exit_default.jpg");
	pExitDefault->SetPosition(375, 450);

	// Initialise and load the selected exit menu item
	pExitSelected = new SpriteBatch();
	pExitSelected->LoadTexture(device, "exit_selected.jpg");
	pExitSelected->SetPosition(375, 450);

	return true;
}

void MainMenu::Update()
{
	pInput->GetInput();

	// Update the state of the menu when the user moves between menu items
	if(pInput->KeyPress(DIK_UP) || pInput->KeyPress(DIK_DOWN))
	{
		if(menuItemSelected == 0)
		{
			menuItemSelected = 1;
		}
		else
		{
			menuItemSelected = 0;
		}
	}

	// Proceed to the game scene or exit the application if the enter key is pressed
	if(pInput->KeyPress(DIK_RETURN))
	{
		switch(menuItemSelected)
		{
			case 0:
				{
					state = new_game;
					break;
				}
			case 1:
				{
					state = exit;
					break;
				}
		}
	}
}

void MainMenu::Render(LPDIRECT3DDEVICE9 device)
{
	// Render the background texture of the menu
	pBackground->Render(device);

	// Render both the default and selected menu states of each menu item
	if(menuItemSelected == 0)
	{
		pNewGameSelected->Render(device);
		pExitDefault->Render(device);
	}
	else
	{
		pNewGameDefault->Render(device);
		pExitSelected->Render(device);
	}
}

int MainMenu::GetState()
{
	// Return the state of the menu
	return state;
}