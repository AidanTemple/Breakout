#pragma region Include Statements
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <vector>
#pragma endregion

class Model;
class InputManager;

class Paddle
{
	public:

		// Constructor
		Paddle();

		// Deconstructor
		~Paddle();

		bool Initialise(InputManager* input, LPDIRECT3DDEVICE9 device);

		void Render(LPDIRECT3DDEVICE9 device);

		void Update();

		void GetPaddlePosition(float* x, float* y);

		float GetWidth();

	private:

		InputManager* pInput;

		Model* pPaddle;

		float paddleX;
};