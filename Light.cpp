#pragma region Include Statements
#include "Light.h"
#pragma endregion

Light::Light(LPDIRECT3DDEVICE9 device)
{
	// Initialise the graphics device
	d3ddevice = device;

	// Enable lighting
	d3ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

Light::~Light()
{

}

int Light::CreateLight()
{
	D3DLIGHT9* light = new D3DLIGHT9;

	light->Type = D3DLIGHT_POINT;

	// Ceate a light with full diffuse and specular lighting but no ambient lighting
	light->Diffuse.r = light->Diffuse.g = light->Diffuse.b = 1.0f;
	light->Specular.r = light->Specular.g = light->Specular.b = 1.0f;
	light->Ambient.r = light->Ambient.g = light->Ambient.b = 0.0f;
	light->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	light->Range = 60.0f;

	light->Attenuation0 = 1.0f;
	light->Attenuation1 = 0.0f;
	light->Attenuation2 = 0.0f;

	// Push the light onto the light vector
	lights.push_back((D3DLIGHT9*)light);

	// Enable the newly created light
	d3ddevice->SetLight((int)lights.size() - 1, (D3DLIGHT9*)lights[((int)lights.size() - 1)]);
	d3ddevice->LightEnable((int)lights.size() - 1, true);

	return ((int)lights.size() - 1);
}

void Light::EnableLight(int lightNum)
{
	// Enable a given light
	d3ddevice->LightEnable(lightNum, TRUE);
}

void Light::DisableLight(int lightNum)
{
	// Disable a given light
	d3ddevice->LightEnable(lightNum, FALSE);
}

void Light::SetDiffuse(int lightNum, float r, float g, float b)
{
	// Set the RGB diffuse lighting values
	lights[lightNum]->Diffuse.r = r;
	lights[lightNum]->Diffuse.g = g;
	lights[lightNum]->Diffuse.b = b;

	// Reset the light and add the newly set values
	d3ddevice->SetLight(lightNum, (D3DLIGHT9*)lights[lightNum]);
}

void Light::SetSpecular(int lightNum, float r, float g, float b)
{
	// Set the RGB specular lighting values
	lights[lightNum]->Specular.r = r;
	lights[lightNum]->Specular.g = g;
	lights[lightNum]->Specular.b = b;

	// Reset the light and add the newly set values
	d3ddevice->SetLight(lightNum, (D3DLIGHT9*)lights[lightNum]);
}

void Light::SetAmbient(int lightNum, float r, float g, float b)
{
	// Set the RGB ambient values
	lights[lightNum]->Ambient.r = r;
	lights[lightNum]->Ambient.g = g;
	lights[lightNum]->Ambient.b = b;

	// Reset the light and add the newly set values
	d3ddevice->SetLight(lightNum, (D3DLIGHT9*)lights[lightNum]);
}

void Light::SetPosition(int lightNum, D3DXVECTOR3 positionVect)
{
	// Set the position of the newly created light
	lights[lightNum]->Position = positionVect;

	// Reset the light and add the newly set position
	d3ddevice->SetLight(lightNum, (D3DLIGHT9*)lights[lightNum]);
}

void Light::SetRange(int lightNum, float range)
{
	// Set the range of the newly created light
	lights[lightNum]->Range = range;

	// Reset the light and add the newly set range
	d3ddevice->SetLight(lightNum, (D3DLIGHT9*)lights[lightNum]);
}