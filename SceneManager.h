#pragma region Include Statements
#include <Windows.h>
#pragma endregion

// forward declaration
class GraphicsManager;
class TextComponent;
class SpriteBatch;
class Model;
class Light;
class Camera;
class Animation;
class FrameManager;
class InputManager;
class MainMenu;
class GameScene;

class SceneManager
{
	public:

		// Constructor
		SceneManager(void);

		// Deconstructor
		~SceneManager(void);

		// Initialise the scene manager
		bool Init(HWND wndHandle, HINSTANCE hInstance);

		// Update the scene manager
		void Update(void);

		enum
		{
			null = 0,
			menuScene = 1,
			gameScene = 2
		};

	private:

		GraphicsManager* pGraphicsManager;

		TextComponent* pTextComponent;

		SpriteBatch* pSpriteBatch;

		Model* pModel;

		Light* pLights;

		Camera* pCamera;

		Animation* pAnimation;

		FrameManager* pFrameManager;

		InputManager* pInput;

		MainMenu* pMenu;

		GameScene* pGameScene;

		int IsActive;
};