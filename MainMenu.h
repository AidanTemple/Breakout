#pragma region Include Statements
#pragma once
#include <d3d9.h>
#pragma endregion

class InputManager;
class SpriteBatch;

class MainMenu
{
	public:

		// Constructor
		MainMenu();

		// Deconstructor
		~MainMenu();

		// Used to initialise the menu
		bool Initialise(InputManager* input, LPDIRECT3DDEVICE9 device);

		// Used to update the menu
		void Update();

		// Used to render the menu
		void Render(LPDIRECT3DDEVICE9 device);

		int GetState();

		// Main menu states
		enum
		{
			new_game = 1,
			exit = 2
		};

	private:

		// Used to handle user input
		InputManager* pInput;

		// Main menu background texture
		SpriteBatch* pBackground;

		// New game default menu option texture
		SpriteBatch* pNewGameDefault;

		// New game selected menu option texture
		SpriteBatch* pNewGameSelected;

		// Exit game default menu option texture
		SpriteBatch* pExitDefault;

		// Exit game selected menu option texture
		SpriteBatch* pExitSelected;

		int menuItemSelected;
		int state;
};