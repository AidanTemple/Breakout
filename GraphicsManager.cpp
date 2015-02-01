#pragma region Include Statements
#include "GraphicsManager.h"
#pragma endregion

GraphicsManager::GraphicsManager(void)
{
	D3D = NULL;
	D3DDevice = NULL;
}

GraphicsManager::~GraphicsManager(void)
{
	if(D3D != NULL)
	{
		D3D->Release();
		D3D = NULL;
	}

	if(D3DDevice != NULL)
	{
		D3DDevice->Release();
		D3DDevice = NULL;
	}
}

bool GraphicsManager::InitD3D(HWND hWnd, int width, int height, bool b_IsFullscreen)
{
	HRESULT hResult;

	D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if(D3D == NULL)
	{
		return false;
	}

	bool b_IsWindowed = true;

	// Determine whether or not the application is in fullscreen or not
	if(b_IsFullscreen)
	{
		b_IsWindowed = false;
	}

	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));

	D3Dpp.Windowed = b_IsWindowed; // Determines if windowed
	D3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Used to discard previous frames
	D3Dpp.BackBufferFormat = D3DFMT_R5G6B5; // Display format
	D3Dpp.BackBufferCount = 1; // Number of back buffers
	D3Dpp.BackBufferWidth = width; // Width of the back buffer
	D3Dpp.BackBufferHeight = height; // Height of the back buffer
	D3Dpp.hDeviceWindow = hWnd; // Handle to the application window
	D3Dpp.AutoDepthStencilFormat = D3DFMT_D16; // Stencil format
	D3Dpp.EnableAutoDepthStencil = TRUE; 
	D3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	D3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Create the graphics device
	hResult = D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3Dpp, &D3DDevice);

	if(FAILED(hResult))
	{
		return false;
	}

	// Used to normalise the normal values used when lighting the scene
	D3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	return true;
}

void GraphicsManager::SetupViewport()
{
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	// Used to determine the position and look at position of the application viewport
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 30.0f);
	D3DXVECTOR3 target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Set the aspect ratio, near, and far clipping planes of the view frustum
	float aspectRatio = 1.333f;
	float nearClip = 1.0f;
	float farClip = 1000.0f;

	// Setup the projection matrix
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4.0f, aspectRatio, nearClip, farClip);
	
	// Setup the projection
	D3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	
	// Setup the view
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	
	// Enable lighting within the application
	D3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	D3DLIGHT9 light;

	// Initialise and create a new light
	light.Type = D3DLIGHT_POINT;
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = 1.0f;
	light.Specular.r = light.Specular.g = light.Specular.b = 0.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = 0.3f;
	light.Position = D3DXVECTOR3(0.0f, 10.0f, 25.0f);
	light.Attenuation0 = light.Attenuation1 = light.Attenuation2 = 0.0f;
	light.Range = 60.0f;

	// Set and turn on the newly created light
	D3DDevice->SetLight(0, &light);
	D3DDevice->LightEnable(0, TRUE);
}

void GraphicsManager::Begin()
{
	if(NULL == D3DDevice)
	{
		return;
	}

	// Clear the back buffer
	D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(55, 55, 55), 1.0f, 0);

	D3DDevice->BeginScene();
}

void GraphicsManager::End()
{
	// Disable the render state and present the back buffer
	D3DDevice->EndScene();
	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GraphicsManager::InitD3DDevice()
{
	return D3DDevice;
}

