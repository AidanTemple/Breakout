#pragma region Include Statements
#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#pragma endregion

class Model;

class Animation
{
	public: 

		// Constructor
		Animation();

		// Deconstructor
		~Animation();

		// Used to initialise the class and any variables
		bool Initialise(LPDIRECT3DDEVICE9 device);

		// Used to update the animation class
		void Update(int numFrames);

		// Render the results of the animation class
		void Render(LPDIRECT3DDEVICE9 device);

	private:

		Model* model;

		D3DXVECTOR3 position;

		int direction;
};