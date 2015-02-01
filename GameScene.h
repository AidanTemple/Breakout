#pragma region Include Statements
#pragma once
#include <d3d9.h>
#pragma endregion

class InputManager;
class SpriteBatch;
class Camera;
class Light;
class Level;
class Paddle;
class Ball;

class GameScene
{
	public:

		// Constructor
		GameScene();

		// Deconstructor
		~GameScene();

		bool Initialise(InputManager* input, LPDIRECT3DDEVICE9 device);

		void Update(int numOfFrames);

		void Render(LPDIRECT3DDEVICE9 device);

		int GetState();

		enum
		{
			null = 0,
			game_over = 1,
			quit = 2
		};

	private:

		InputManager* pInput;

		SpriteBatch* pBackground;

		Camera* pCamera;

		Light* pLight;

		Level* pLevel;

		Paddle* pPaddle;

		Ball* pBall;

		int state;
};