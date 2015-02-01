#pragma region Include Statements
#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <vector>
#pragma endregion

class Light
{
	public: 
		Light(LPDIRECT3DDEVICE9 device);

		~Light();

		void EnableLight(int lightNum);

		void DisableLight(int lightNum);

		int CreateLight();

		void SetDiffuse(int lightNum, float r, float g, float b);

		void SetSpecular(int lightNum, float r, float g, float b);

		void SetAmbient(int lightNum, float r, float g, float b);

		void SetPosition(int lightNum, D3DXVECTOR3 positionVect);

		void SetRange(int lightNum, float range);

	private:

		std::vector <D3DLIGHT9*> lights;

		LPDIRECT3DDEVICE9 d3ddevice;

		D3DLIGHT9 light;
};