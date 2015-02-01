#pragma region Include Statements
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "SpriteBatch.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "Animation.h"
#include "FrameManager.h"
#include "InputManager.h"
#include "MainMenu.h"
#include "GameScene.h"
#pragma endregion

SceneManager::SceneManager(void)
{
	pGameScene = NULL;
}

SceneManager::~SceneManager(void)
{
	if(pGraphicsManager != NULL)
	{
		delete pGraphicsManager;
		pGraphicsManager = NULL;
	}
}

bool SceneManager::Init(HWND wndHandle, HINSTANCE hInstance)
{
	// Initialise and retrieve the direct3D manager
	pGraphicsManager = new GraphicsManager();
	pGraphicsManager->InitD3D(wndHandle, 800, 600, false);

	if(!pGraphicsManager)
	{
		return false;
	}

	// Initialise the input manager
	pInput = new InputManager();
	pInput->Initialise(hInstance, wndHandle);

	// Initialise and create the main menu
	pMenu = new MainMenu();
	pMenu->Initialise(pInput, pGraphicsManager->InitD3DDevice());
	IsActive = menuScene;

	// Initialise and create a new frame mamanger
	pFrameManager = new FrameManager();
	pFrameManager->Initialise(60);

	return true;
}

void SceneManager::Update(void)
{
	int framesToUpdate;

	// Used to call the update function
	framesToUpdate = pFrameManager->FramesToUpdate();

	// Update the main menu
	if(IsActive == menuScene)
	{
		pMenu->Update();

		if(pMenu->GetState() == MainMenu::new_game)
		{
			if(pGameScene != NULL)
			{
				delete pGameScene;
			}

			// Initialise the game scene
			pGameScene = new GameScene();
			pGameScene->Initialise(pInput, pGraphicsManager->InitD3DDevice());
			
			IsActive = gameScene;
		}

		if(pMenu->GetState() == MainMenu::exit)
		{
			IsActive = null;
			PostQuitMessage(0);
			delete pMenu;
		}
	}

	// Update the game screen
	if(IsActive == gameScene)
	{
		pGameScene->Update(framesToUpdate);

		if(pGameScene->GetState() == GameScene::quit)
		{
			IsActive = null;
			delete pGameScene;

			// Initialise the main menu
			pMenu = new MainMenu();
			pMenu->Initialise(pInput, pGraphicsManager->InitD3DDevice());
			IsActive = menuScene;
		}
	}

	// Begin rendering the scene
	pGraphicsManager->Begin();

	if(IsActive == menuScene)
	{
		// Render the main menu
		pMenu->Render(pGraphicsManager->InitD3DDevice());
	}

	if(IsActive == gameScene)
	{
		// Render the game scene
		pGameScene->Render(pGraphicsManager->InitD3DDevice());
	}

	// Stop rendering the scene
	pGraphicsManager->End();
}