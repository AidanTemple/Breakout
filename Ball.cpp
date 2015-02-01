#pragma region Include Statements
#include "Ball.h"
#include "Paddle.h"
#include "Level.h"
#include "Model.h"
#include "TextComponent.h"
#pragma endregion

const float maxScreenX = 22.0f;
const float minScreenX = -22.0f;
const float maxScreenY = 15.0f;
const float minScreenY = -16.0f;

Ball::Ball()
{
	pBall = NULL;
}

Ball::~Ball()
{
	if(pBall != NULL)
	{
		delete pBall;
	}
}

bool Ball::Initialise(Level* level, Paddle* paddle, LPDIRECT3DDEVICE9 device)
{
	// Pointer to the paddle
	pPaddle = paddle;

	// Pointer to the level
	pLevel = level;

	// Number of balls player has to begin with
	ballCount = 4;

	// Determines number of blocks the ball has hit
	hitCounter = 0;

	// Used to output text to display remaining balls
	pText = new TextComponent();
	pText->Init(24, device);

	// Balls initial position
	ballX = 0.0f;
	ballY = 0.0f;

	// Balls initial velocity
	ballXVelocity = 0.0f;
	ballYVelocity = 0.0f;

	// Size of the paddle
	paddleSize = pPaddle->GetWidth();

	// Import and initialise a new ball model as well as setting its scale
	pBall = new Model();
	pBall->LoadModel(device, "ball.x");
	pBall->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

	return true;
}

void Ball::Render(LPDIRECT3DDEVICE9 device)
{
	// Set the position of the ball and display it on screen
	pBall->SetPosition(D3DXVECTOR3(ballX, ballY, 0.0f));
	pBall->Render(device);

	if(ballCount > -1)
	{
		char message[25] = "";

		// Output the remaining ball count
		sprintf(message, "Balls Remaining: %d", ballCount);
		pText->DrawString(message, 15, 15, 100, 50);
	}
	else
	{
		// Output a game over message if the player has no remaining balls
		pText->DrawString("Game Over", 350, 275, 100, 50);
	}
}

void Ball::Reset()
{
	// Reduce the number of remaining balls if a balls moves offscreen
	ballCount--;

	// Reset the block hit counter
	hitCounter = 0;

	// Reset the balls position
	ballX = 0.0f;
	ballY = 0.0f;

	// Reset the balls initial speed
	if(ballCount > -1)
	{
		ballXVelocity = -0.20f;
		ballYVelocity = -0.20f;
	}
	// Prevent the ball from moving if there are no balls remaining
	else
	{
		ballXVelocity = 0.0f;
		ballYVelocity = 0.0f;
	}
}

void Ball::Update(int framesToUpdate)
{
	// Update the balls position each frame and check for any form of collision
	for(int i = 0; i < framesToUpdate; i++)
	{
		CheckForCollision();
		
		ballX += ballXVelocity;
		ballY += ballYVelocity;
	}

	// Check if the hit count is greater than or equal to 8...
	if(hitCounter >= 8)
	{
		// ...If so then reset the hit counter and increase the balls velocity
		if((hitCounter % 8) == 0)
		{
			hitCounter = 0;

			ballXVelocity += 0.03f;
			ballYVelocity += 0.03f;
		}
	}

	// Check if the player has completed the level... 
	if(pLevel->LevelComplete())
	{
		// ...if so then move to the next level
		pLevel->LoadLevel("0.txt");
	}
}

void Ball::CheckForCollision()
{
	float newBallX = ballX + ballXVelocity;
	float newBallY = ballY + ballYVelocity;

	// Check if the ball has collided with either the left or right side of the screen
	if(newBallX > maxScreenX || newBallX < minScreenX)
	{
		// If so then reverse the velocity of the ball
		ballXVelocity = ballXVelocity * (-1);
	}

	// Check if the ball has collided with the top of the screen
	if(newBallY > maxScreenY)
	{
		// If so then reverse the velocity of the ball
		ballYVelocity = ballYVelocity * (-1);
	}

	// Check if the ball has went off the bottom of the screen
	if(newBallY < minScreenY)
	{
		// If so then reset the ball
		Reset();
	}

	int* tempX = new int;
	int* tempY = new int;

	// Check if the ball has hit a block, if so remove the block and reverse the balls velocity
	if(pLevel->GetTile(newBallX, ballY, tempX, tempY) != 0)
	{
		hitCounter++;

		ballXVelocity = ballXVelocity * (-1);

		pLevel->RemoveBlock(*tempX, *tempY);
	}
	else if(pLevel->GetTile(ballX, newBallY, tempX, tempY) != 0)
	{
		hitCounter++;

		ballYVelocity = ballYVelocity * (-1);

		pLevel->RemoveBlock(*tempX, *tempY);
	}

	float* paddleX = new float;
	float* paddleY = new float;

	// Retrieve the position of the paddle
	pPaddle->GetPaddlePosition(paddleX, paddleY);

	// Check whether or not the paddle and ball collide
	if(newBallY < *paddleY)
	{
		if(newBallX > (*paddleX - (paddleSize / 2.0f)) 
			&& newBallX < (*paddleX + (paddleSize / 2.0f)))
		{
			// If so reverse the balls velocity
			ballYVelocity = ballYVelocity * (-1);
		}
	}

	delete paddleX;
	delete paddleY;
	delete tempX;
	delete tempY;
}