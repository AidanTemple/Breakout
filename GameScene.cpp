#pragma region Include Statements
#include "SpriteBatch.h"
#include "InputManager.h"
#include "GameScene.h"
#include "Camera.h"
#include "Light.h"
#include "Level.h"
#include "Paddle.h"
#include "Ball.h"
#pragma endregion

GameScene::GameScene()
{
	pBackground = NULL;
}

GameScene::~GameScene()
{
	if(pBackground != NULL)
	{
		delete pBackground;
	}
}

bool GameScene::Initialise(InputManager* input, LPDIRECT3DDEVICE9 device)
{
	// Initialise the input manager
	pInput = input;
	state = null;

	// Initialise and load the background texture
	pBackground = new SpriteBatch();
	pBackground->LoadTexture(device, "background.jpg");
	
	// Initialise and load the level
	pLevel = new Level();
	pLevel->Initialise("0.txt", device);

	// Initialise the paddle
	pPaddle = new Paddle();
	pPaddle->Initialise(pInput, device);

	// Initialise the paddle
	pBall = new Ball();
	pBall->Initialise(pLevel, pPaddle, device);
	pBall->Reset();

	// Initialise and set the camera parameters
	pCamera = new Camera();
	pCamera->Initialise(device, 1.0f, 1000.0f);
	pCamera->SetLookAt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -40.0f));

	// Initialise and set the lighting parameters
	pLight = new Light(device);
	int light1 = pLight->CreateLight();
	pLight->SetPosition(light1, D3DXVECTOR3(0.0f, 10.0f, -20.0f));
	pLight->SetRange(light1, 100.0f);

	return true;
}

void GameScene::Update(int numOfFrames)
{
	// Update the paddle
	pPaddle->Update();

	// Update the ball
	pBall->Update(numOfFrames);

	// Check whether or not the user wants to exit the application
	if(pInput->KeyPress(DIK_ESCAPE))
	{
		state = quit;
	}
}

void GameScene::Render(LPDIRECT3DDEVICE9 device)
{
	// Render the background texture
	pBackground->Render(device);

	// Render the level
	pLevel->Render(device);

	// Render the ball
	pBall->Render(device);

	// Render the paddle
	pPaddle->Render(device);
}

int GameScene::GetState()
{
	// Used to return the state of the game
	return state;
}