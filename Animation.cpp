#pragma region Include Statements
#include "Animation.h"
#include "Model.h"
#pragma endregion

Animation::Animation()
{

}

Animation::~Animation()
{

}

bool Animation::Initialise(LPDIRECT3DDEVICE9 device)
{
	// Initialise and load a new model
	model = new Model();
	model->LoadModel(device, "sphere.x");

	if(!model)
	{
		return false;
	}

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->SetPosition(position);
	direction = 1;
}

void Animation::Update(int numOfFrames)
{
	for(int i = 0; i < numOfFrames; i++)
	{
		if(direction == 1)
		{
			position.x += 0.5f;
		}
		else
		{
			position.x -= 0.5f;
		}

		if(position.x > 25.0f || position.x < -25.0f)
		{
			direction = direction * -1;
		}
	}

	model->SetPosition(position);
}

void Animation::Render(LPDIRECT3DDEVICE9 device)
{
	model->Render(device);
}