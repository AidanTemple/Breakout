#pragma region Include Statements
#include "Level.h"
#include "Model.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#pragma endregion

// Used to determine the levels size, width, and height
const int level_size = 128;
const int level_width = 16;
const int level_height = 8;

// Used to determine a blocks width and height
const float block_width = 2.5f;
const float block_height = 1.25f;

// Used to determine the initial x, y positon of a block
const float startX = -19.0f;
const float startY = 12.0f;

Level::Level()
{
	pRedBlock = NULL;
	pYellowBlock = NULL;
	pOrangeBlock = NULL;
}

Level::~Level()
{
	if(pRedBlock != NULL)
	{
		delete pRedBlock;
	}

	if(pYellowBlock != NULL)
	{
		delete pYellowBlock;
	}

	if(pOrangeBlock != NULL)
	{
		delete pOrangeBlock;
	}
}

bool Level::Initialise(std::string filename, LPDIRECT3DDEVICE9 device)
{
	// Initialise and load a red block
	pRedBlock = new Model;
	pRedBlock->LoadModel(device, "red_block.x");
	pRedBlock->SetScale(D3DXVECTOR3(0.25f, 0.25f, 0.25f));

	// Initialise and load a yellow block
	pYellowBlock = new Model;
	pYellowBlock->LoadModel(device, "yellow_block.x");
	pYellowBlock->SetScale(D3DXVECTOR3(0.25f, 0.25f, 0.25f));

	// Initialise and load an orange block
	pOrangeBlock = new Model;
	pOrangeBlock->LoadModel(device, "orange_block.x");
	pOrangeBlock->SetScale(D3DXVECTOR3(0.25f, 0.25f, 0.25f));

	LoadLevel(filename);

	return true;
}

bool Level::LoadLevel(std::string filename)
{
	// Used to contain an array of blocks
	int *pArray;

	// Level file object
	std::ifstream file;

	// Open the level file
	file.open(filename.c_str());

	if(!file.good())
	{
		return false;
	}

	// Buffer used to hold each line within the level file
	char lineBuffer[level_size];

	// Read each line into memory
	file.getline(lineBuffer, level_size);

	// Intialise the toekn to zero
	char* token = 0;

	// Used to split the string each time a space is found within the level file
	token = strtok(lineBuffer, " ");

	// Begin reading the level file data
	if(strstr(token, "begin"))
	{
		while(!file.eof())
		{
			file.getline(lineBuffer, level_size);
			token = strtok(lineBuffer, " ");

			// Stop reading the level file data
			if(strstr(token, "end"))
			{
				break;
			}

			// Create a temporary buffer and fill it with zeros
			pArray = new int[level_width];

			for(int i = 0; i < level_width; i++)
			{
				pArray[i] = 0;
			}

			// Place the first blocks data into the block array
			pArray[0] = atoi(token);

			if(pArray[0] != 0)
			{
				//Increase the block count
				numBlocks++;
			}

			// Fill the array with the remainder of the level data
			for(unsigned int n = 1; n < level_width; n++)
			{
				token = strtok(0, " ");

				if(!token)
				{
					break;
				}

				pArray[n] = atoi(token);

				if(pArray[n] != 0)
				{
					numBlocks++;
				}
			}

			levelData.push_back((int*)pArray);
		}
	}

	file.close();

	return true;
}

void Level::Render(LPDIRECT3DDEVICE9 device)
{
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Render a grid of blocks
	for(unsigned int i = 0; i < levelData.size(); i++)
	{
		for(int j = 0; j < level_width; j++)
		{
			position.x = startX + (float)j * block_width;
			position.y = startY - (float)i * block_height;

			switch(levelData[i][j])
			{
				case 0:
					{
						break;
					}
				case 1:
					{
						// Set the position and render each of the red blocks
						pRedBlock->SetPosition(position);
						pRedBlock->Render(device);

						break;
					}
				case 2:
					{
						// Set the position and render each of the yellow blocks
						pYellowBlock->SetPosition(position);
						pYellowBlock->Render(device);

						break;
					}
				case 3:
					{
						// Set the position and render each of the orange blocks
						pOrangeBlock->SetPosition(position);
						pOrangeBlock->Render(device);

						break;
					}
			}
		}
	}
}

int Level::GetTile(float x, float y, int* n1, int* n2)
{
	float halfBlockWidth = block_width / 2;
	float halfBlockHeight = block_height / 2;

	float blockLeftX;
	float blockRightX;
	float blockTopY;
	float blockBottomY;

	int blockLocation = 0;

	// Loop through each block within the level
	for(unsigned int i = 0; i < levelData.size(); i++)
	{
		// Calculate the top and bottom Y coordinates of each row
		blockTopY = startY - (i * block_height) + halfBlockHeight;
		blockBottomY = startY - (i * block_height) - halfBlockHeight;

		for(int j = 0; j < level_width; j++)
		{
			// Calculate the left and right x coordinates of each row 
			blockLeftX = (j * block_width) - halfBlockWidth + startX;
			blockRightX = (j * block_width) + halfBlockWidth + startX;

			if(x > blockLeftX && x < blockRightX)
			{
				if(y < blockTopY && y > blockBottomY)
				{
					blockLocation = levelData[i][j];

					*n1 = i;
					*n2 = j;
				}
			}
		}
	}

	return blockLocation;
}

void Level::RemoveBlock(int x, int y)
{
	// Remove a block at a given position and replace it with a zero i.e. empty space
	levelData[x][y] = 0;
	
	// Reduce the number of blocks
	numBlocks--;
}

bool Level::LevelComplete()
{
	// Check if the level is complete and no more blocks exist
	if(numBlocks == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}