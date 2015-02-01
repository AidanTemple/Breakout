#pragma region Include Statements
#include "Camera.h"
#pragma endregion

Camera::Camera(void)
{

}

Camera::~Camera(void)
{

}

bool Camera::Initialise(LPDIRECT3DDEVICE9 device, float nearView, float farView)
{
	d3ddevice = device;
	nearClip = nearView;
	farClip = farView;

	// Initialise the cameras position
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	// Initialise the cameras look at position
	target.x = 0.0f;
	target.y = 0.0f;
	target.z = 0.0f;

	// Set the cameras aspect ratio
	float aspectRatio = 1.333f;

	// Initialise a cameras field of view
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4.0f, aspectRatio, nearClip, farClip);

	d3ddevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	return true;
}

void Camera::SetPosition(D3DXVECTOR3 positionVect)
{
	// Set the position of the camera
	position = positionVect;
	Reset();
}

void Camera::SetLookAt(D3DXVECTOR3 targetVect)
{
	// Set the cameras look at position
	target = targetVect;
	Reset();
}

void Camera::Reset()
{
	// Used to reset the cameras view matrix, position, and look at position
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	d3ddevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}