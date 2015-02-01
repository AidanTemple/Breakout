#pragma region Include Statements
#include "Model.h"
#pragma endregion

Model::Model(void)
{
	mesh = NULL;
}

Model::~Model(void)
{
	if(mesh)
	{
		// Delete model
		mesh->Release();
	}

	if(matBuffer)
	{
		// Delete material buffer
		matBuffer->Release();
	}

	if(material)
	{
		// Delete material array
		delete[] material;
	}

	if(texture)
	{
		// Delete texture array
		delete[] texture;
	}
}

bool Model::LoadModel(LPDIRECT3DDEVICE9 device, std::string filename)
{
	HRESULT hResult;

	// Set the scale of a model
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// Set the position of a model
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Set the rotation of a model
	torque = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Load the model and its material data
	hResult = D3DXLoadMeshFromX((LPCSTR)filename.c_str(), D3DXMESH_SYSTEMMEM,
		device, NULL, &matBuffer, NULL, &matCount, &mesh);

	if(FAILED(hResult))
	{
		return false;
	}

	// Get the pointer to the material buffer
	D3DXMATERIAL* modelMaterial = (D3DXMATERIAL*)matBuffer->GetBufferPointer();

	// Create a series of arrays to hold the textures and materials
	material = new D3DMATERIAL9[matCount];
	texture = new LPDIRECT3DTEXTURE9[matCount];

	// Load each of the materials and textures into each of the newly created arrays
	for(DWORD i = 0; i < matCount; i++)
	{
		// Store the material in the array
		material[i] = modelMaterial[i].MatD3D;

		// Load a external texture
		hResult = D3DXCreateTextureFromFile(device, modelMaterial[i].pTextureFilename, &texture[i]);

		if(FAILED(hResult))
		{
			texture[i] = NULL;
		}
	}

	// Delete the material buffer when the application is finished with it
	if(matBuffer)
	{
		matBuffer->Release();
	}

	return true;
}

void Model::Render(LPDIRECT3DDEVICE9 device)
{
	DWORD i;

	// Set the scale matrix
	D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, scale.z);

	// Set the translation matrix
	D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);

	// Set the rotation matrix
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, torque.x, torque.y, torque.z);

	// Multiply both the rotation and scale matrix by the translation matrix and update the translation matrix
	D3DXMatrixMultiply(&translationMatrix, &rotationMatrix, &translationMatrix);
	D3DXMatrixMultiply(&translationMatrix, &scaleMatrix, &translationMatrix);

	device->SetTransform(D3DTS_WORLD, &translationMatrix);

	// Render a model
	for(i = 0; i < matCount; i++)
	{
		// Set the material of a model
		device->SetMaterial(&material[i]);

		// Apply a texture if one exists
		if(texture[i] != NULL)
		{
			device->SetTexture(0, texture[i]);
		}
		else
		{
			device->SetTexture(0, NULL);
		}

		// Draw the subset
		mesh->DrawSubset(i);
	}
}

void Model::SetPosition(D3DXVECTOR3 positionVect)
{
	// Set the position of a model
	position = positionVect;
}

void Model::UpdatePosition(D3DXVECTOR3 positionVect)
{
	// Update the position of a model
	position = position + positionVect;
}

void Model::SetRotation(D3DXVECTOR3 rotationVect)
{
	// Set the rotation value of a model
	torque = rotationVect;
}

void Model::SetScale(D3DXVECTOR3 scaleVect)
{
	// Set the scale of a model
	scale = scaleVect;
}