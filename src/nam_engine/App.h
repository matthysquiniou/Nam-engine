#pragma once
#include "Ecs.h"
#include "SceneManager.h"
#include "AppChrono.h"
#include "Entity.h"
#include "Window.h"

#include <TextureManager.h>

namespace nam
{
	class RenderManager;
	class Scene;
	class LightManager;
	class GameObject;
  
	struct Mesh;
	struct Sprite;
	struct Text;

	class LoadingScreen;

	class App final
	{
	private:
		static App* msp_instance;
		Window m_window;
		Ecs m_ecs;
		SceneManager m_sceneManager;

		GameObject* mp_camera = nullptr;
		AppChrono m_chrono;
		RenderManager* mp_renderManager = nullptr;

		bool m_minimized = false;
		bool m_maximized = false;
		bool m_resizing = false;
		bool m_fullscreen = false;

		struct TextureData
		{
			std::wstring m_path = L"";
			size m_uniqueTag = 0;
			bool m_usingTextureFolder = false;
		};

		Vector<TextureData> m_texturesDataToLoad;
		LoadingScreen* mp_loadingScreen = nullptr;
	public:
		~App();
		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// Pass the Window Settings the first time to Init the App, next times, just call Get() without anything in parameters !
		static App* Get(HINSTANCE hInst = 0, int startWindowWidth = -1, int startWindowHeight = -1);
		static void Destroy();

		void Run();

		// To call before Run() | if usingTextureFolder true -> the path will remains in the Textures Folder
		void LoadTexture(std::wstring path, size uniqueTag, bool usingTextureFolder = false);

		void ToggleDebugConsole(bool state);

		template<typename System, typename... Args>
		void AddSystem(Args&&... args);
		template<typename System>
		void SetSystemEnabled(const bool enabled);

		template<typename T>
		T& CreateGameObject(size scene, bool active = true);

		template<typename T>
		T& CreateOrGetScene(size scene);
		void ClearScene(size scene);
		void SetSceneActive(size scene, bool active);

		Ecs& GetEcs();
		SceneManager& GetSceneManager();
		Window& GetWindow();
		AppChrono& GetChrono();
		LightManager& GetLightManager();

	private:
		void Init();
		void Start();

		int MainLoop();
		void Update();
		void Resize();

		App(HINSTANCE hInst, int startWindowWidth, int startWindowHeight);

		void RenderFirstFrame();
		void LoadTextures();

		friend class GameObject;
	};
}

#include "App.inl"
