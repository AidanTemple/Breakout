#pragma region Include Statements
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <vector>
#pragma endregion

class Model;

class Level
{
	public:

		Level();

		~Level();

		bool Initialise(std::string filename, LPDIRECT3DDEVICE9 device);

		bool LoadLevel(std::string filename);

		void Render(LPDIRECT3DDEVICE9 device);

		int GetTile(float x, float y, int* i, int* j);

		void RemoveBlock(int x, int y);

		bool LevelComplete();

	private:

		std::vector<int*>levelData;

		Model* pRedBlock;
		Model* pYellowBlock;
		Model* pOrangeBlock;

		int numBlocks;
};