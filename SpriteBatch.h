#pragma region Include Statements
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#pragma endregion

class SpriteBatch
{
	public:

		SpriteBatch(void);

		virtual ~SpriteBatch(void);

		bool LoadTexture(LPDIRECT3DDEVICE9 device, std::string filename);

		void Render(LPDIRECT3DDEVICE9 device);

		void SetPosition(int x, int y);

		void SetSize(int percent);

		void SetSourceRect(int left, int top, int height, int width);

		void SetDestinationRect(int left, int top, int height, int width);

	private:

		IDirect3DSurface9* texture;

		RECT sourceRect;
		RECT destinationRect;

		int scale;
		int width;
		int height;
};