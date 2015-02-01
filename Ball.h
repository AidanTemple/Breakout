#pragma region Include Statements
#include <d3d9.h>
#include <d3dx9tex.h>
#pragma endregion

class Model;
class Paddle;
class Level;
class TextComponent;

class Ball
{
	public:

		// Constructor
		Ball();

		// Deconstructor
		~Ball();

		// Used to initialise the ball
		bool Initialise(Level* level, Paddle* paddle, LPDIRECT3DDEVICE9 device);

		// Render the ball to the screen
		void Render(LPDIRECT3DDEVICE9 device);

		// Update the ball
		void Update(int framesToUpdate);

		// Reset the balls properties
		void Reset();

		// Check if the ball has collided with another game object
		void CheckForCollision();

	private:

		Level* pLevel;
		Paddle* pPaddle;
		Model* pBall;
		TextComponent* pText;

		int ballCount;
		int hitCounter;

		float ballX;
		float ballY;
		float ballXVelocity;
		float ballYVelocity;
		float paddleSize;
};