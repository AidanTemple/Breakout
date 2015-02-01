#pragma region Include Statements
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#pragma endregion

class TextComponent
{
	public:

		// Constructor
		TextComponent(void);

		// Deconstructor
		~TextComponent(void);

		// Initialises the text component
		bool Init(DWORD size, LPDIRECT3DDEVICE9 device);

		// Used to output a string
		void DrawString(std::string text, int x, int y, int width, int height);

	private:

		ID3DXFont* g_font;
};