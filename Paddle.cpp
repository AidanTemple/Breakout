#pragma region Include Statements
#include "Paddle.h"
#include "Model.h"
#include "InputManager.h"
#pragma endregion

const float paddleY = -15.0f;
const float maxPaddleX = 20;
const float minPaddleX = -20;
const float paddleWidth = 3.0f;

Paddle::Paddle()
{
	pPaddle = NULL;
}

Paddle::~Paddle()
{
	if(pPaddle != NULL)
	{
		delete pPaddle;
	}
}

bool Paddle::Initialise(InputManager* input, LPDIRECT3DDEVICE9 device)
{
	pInput = input;

	paddleX = 0;

	// Initialise and load the paddle model
	pPaddle = new Model();
	pPaddle->LoadModel(device, "paddle.x");
	pPaddle->SetScale(D3DXVECTOR3(0.25f, 0.25f, 0.25f));

	return true;
}

void Paddle::Render(LPDIRECT3DDEVICE9 device)
{
	// Set the position and render the paddle
	pPaddle->SetPosition(D3DXVECTOR3(paddleX, paddleY, 0.0f));
	pPaddle->Render(device);
}

void Paddle::Update()
{
	// Update user input
	pInput->GetInput();

	// Update the position of the paddle
	paddleX += pInput->GetMouseX() / 10;

	// Prever the paddle from going off either the left or right side of the screen
	if(paddleX > maxPaddleX)
	{
		paddleX = maxPaddleX;
	}
	else if(paddleX < minPaddleX)
	{
		paddleX = minPaddleX;
	}
}

void Paddle::GetPaddlePosition(float* x, float* y)
{
	// Retrieve the x and y position of the paddle
	*x = paddleX;
	*y = paddleY;
}

float Paddle::GetWidth()
{
	// Return the width of the paddle
	return paddleWidth;
}