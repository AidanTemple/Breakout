#pragma region Include Statements
#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#pragma endregion

class Camera
{
	public:

		Camera(void);

		~Camera(void);

		bool Initialise(LPDIRECT3DDEVICE9 device, float nearView, float farView);

		void SetLookAt(D3DXVECTOR3 targetVect);

		void SetPosition(D3DXVECTOR3 positionVect);

		void Reset();

	private:

		D3DXMATRIX viewMatrix;
		D3DXMATRIX projectionMatrix;

		D3DXVECTOR3 target;
		D3DXVECTOR3 position;

		float nearClip;
		float farClip;

		LPDIRECT3DDEVICE9 d3ddevice;
};