#pragma region Include Statements
#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#pragma endregion

class Model
{
	public:

		// Constructor
		Model(void);

		// Deconstructor
		virtual ~Model(void);

		bool LoadModel(LPDIRECT3DDEVICE9 device, std::string filename);

		void Render(LPDIRECT3DDEVICE9 device);

		void SetPosition(D3DXVECTOR3 position);

		void UpdatePosition(D3DXVECTOR3 position);

		void SetRotation(D3DXVECTOR3 rotation);

		void SetScale(D3DXVECTOR3 scale);

	private:

		// Used to represent the model mesh
		LPD3DXMESH mesh;

		// Returns the number of materials when loading them into the project
		DWORD matCount;

		LPDIRECT3DTEXTURE9* texture;

		D3DMATERIAL9* material;

		LPD3DXBUFFER matBuffer;

		D3DXMATRIX translationMatrix;

		D3DXMATRIX rotationMatrix;

		D3DXMATRIX scaleMatrix;

		D3DXVECTOR3 scale;

		D3DXVECTOR3 position;

		D3DXVECTOR3 torque;
};