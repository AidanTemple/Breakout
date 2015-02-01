#pragma region Include Statements
#include <d3d9.h>
#include <d3dx9tex.h>
#pragma endregion

class GraphicsManager
{
	public:

		// Constructor
		GraphicsManager(void); 

		// Deconstructor
		~GraphicsManager(void); 

		// Initialise Direct3D interface
		bool InitD3D(HWND hWnd, int widt, int height, bool b_IsFullscreen); 

		// Render the scene
		void Begin(void);

		// Stop rendering the scene
		void End(void);

		// Initialise the Direct3D device
		LPDIRECT3DDEVICE9 InitD3DDevice();

		void SetupViewport();

	private:

		// Direct3D object
		LPDIRECT3D9 D3D;

		// Direct3D device object
		LPDIRECT3DDEVICE9 D3DDevice;
};