#pragma region Include Statements
#include "SpriteBatch.h"
#pragma endregion

SpriteBatch::SpriteBatch(void)
{
	texture = NULL;
}

SpriteBatch::~SpriteBatch(void)
{
	if(texture != NULL)
	{
		texture->Release();
		texture = NULL;
	}
}

bool SpriteBatch::LoadTexture(LPDIRECT3DDEVICE9 device, std::string filename)
{
	// Set the scale of a texture to 100%
	scale = 100;

	HRESULT hResult;

	// Retrieve the width and height of a texture
	D3DXIMAGE_INFO info;
	hResult = D3DXGetImageInfoFromFile(filename.c_str(), &info);

	if(FAILED(hResult))
	{
		return false;
	}

	height = info.Height;
	width = info.Width;

	// Create an offscreen texture
	hResult = device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &texture, NULL);

	if(FAILED(hResult))
	{
		return false;
	}

	// Load a texture from an external file
	hResult = D3DXLoadSurfaceFromFile(texture, NULL, NULL, filename.c_str(), 
		NULL, D3DX_DEFAULT, 0, NULL);

	if(FAILED(hResult))
	{
		return false;
	}

	// Set the destination rectangle of a texture
	destinationRect.left = 0;
	destinationRect.top = 0;
	destinationRect.bottom = destinationRect.top + height;
	destinationRect.right = destinationRect.left + width;

	// Set the source rectangle of a texture
	sourceRect.left = 0;
	sourceRect.top = 0;
	sourceRect.bottom = destinationRect.top + height;
	sourceRect.right = destinationRect.left + width;

	return true;
}

void SpriteBatch::Render(LPDIRECT3DDEVICE9 pDevice)
{
	// Scale and render the texture by sending it to the back buffer
	destinationRect.bottom = destinationRect.top + (int)(height * (scale / 100));
	destinationRect.right = destinationRect.left + (int)(width * (scale / 100));

	IDirect3DSurface9* backbuffer = NULL;
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	pDevice->StretchRect(texture, &sourceRect, backbuffer, &destinationRect, D3DTEXF_NONE);
}

void SpriteBatch::SetPosition(int x, int y)
{
	// Set the position of the texture
	destinationRect.left = x;
	destinationRect.top = y;
	destinationRect.bottom = destinationRect.top + height;
	destinationRect.right = destinationRect.left + width;
}

void SpriteBatch::SetSize(int percent)
{
	// Set the scale of the texture
	scale = percent;
}

void SpriteBatch::SetSourceRect(int left, int top, int width, int height)
{
	// Set the position of the textures source rectangle
	sourceRect.left = left;
	sourceRect.top = top;
	sourceRect.bottom = sourceRect.top + height;
	sourceRect.right = sourceRect.left + width;
}

void SpriteBatch::SetDestinationRect(int left, int top, int width, int height)
{
	// Set the position of the textures destination rectangle
	destinationRect.left = left;
	destinationRect.top = top;
	destinationRect.bottom = destinationRect.top + height;
	destinationRect.right = destinationRect.left + width;
}