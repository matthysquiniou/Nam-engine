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

		// Pass the Window Settings the first time to Init the App, next times, just call Get() without anything in parameters !
		static App* Get(HINSTANCE hInst = 0, int startWindowWidth = -1, int startWindowHeight = -1);
		static void Destroy();

		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void Init();
		void Start();
		void Run();

		// To call before Run() | if usingTextureFolder true -> the path will remains in the Textures Folder
		void LoadTexture(std::wstring path, size uniqueTag, bool usingTextureFolder = false);

		int MainLoop();
		void Update();
		void Resize();

		void ToggleDebugConsole(bool state);
		
		void CreateCamera();
		void StartCamera();
		void CameraDefaultSettings(); 

		/*template<typename Component>
		void AddComponent(Entity& entity, const Component& data);
		//template<typename Component>
		//void RemoveComponent();
		template<typename Component>
		const bool HasComponent(Entity& entity) const;
		template<typename Component>
		Component& GetComponent(Entity& entity);*/

		template<typename System, typename... Args>
		void AddSystem(Args&&... args);
		//template<typename System>
		//void RemoveSystem();
		template<typename System>
		void SetSystemEnabled(const bool enabled);

		template<typename T>
		T* CreateGameObject(Scene* scene);
		template<typename T>
		T* CreateGameObject(u32 idScene);
		void DestroyGameObject(GameObject* gameObject, Scene* scene);
		void DestroyGameObject(GameObject* gameObject, u32 idScene);
		void SetActiveGameObject(Scene* scene, GameObject* gameObject, bool active);
		void SetActiveGameObject(u32 idScene, GameObject* gameObject, bool active);
		void SetActiveEntity(Scene* scene, Entity& entity, bool active);
		void SetActiveEntity(u32 idScene, Entity& entity, bool active);
		GameObject* GetGameObject(Scene* scene, u32 idEntity);
		GameObject* GetGameObject(Scene* scene, Entity& entity);
		GameObject* GetGameObject(u32 idScene, u32 idEntity);
		GameObject* GetGameObject(u32 idScene, Entity& entity);
		GameObject* GetGameObject(u32 idEntity);
		GameObject* GetGameObject(Entity& entity);

		Scene* CreateScene(size sceneTag);
		void DestroyScene(Scene* scene);
		void AddCurrentScene(u32 idScene);
		void AddCurrentScene(Scene* scene);
		void AddCurrentScene(size sceneTag);

		void RemoveCurrentScene(Scene* scene);
		void RemoveCurrentScene(u32 idScene);
		void RemoveCurrentScene(size sceneTag);

		void SwitchCurrentScene(Scene* sceneClose, Scene* sceneOpen);
		void SwitchCurrentScene(u32 idSceneClose, u32 idSceneOpen);
		void SwitchCurrentScene(size sceneTag1, size sceneTag2);
		//Use it if your mesh need to be used in many Objects;
		//After that, Use the SetMeshInstance in the MeshRendererComponent
		Mesh* CreateEmptyMesh();

		//Useful if your sprite need to be used in many Objects;
		//After that, Use the SetSpriteInstance in the SpriteRendererComponent
		Sprite* CreateEmptySprite();

		//Useful if your text need to be used in many Objects;
		//After that, Use the SetTextInstance in the TextRendererComponent
		Text* CreateEmptyText();

		Scene* GetScene(u32 idScene);
		Scene* GetScene(Entity& entity);

		Ecs& GetEcs();
		SceneManager& GetSceneManager();
    
		Window& GetWindow();

		AppChrono& GetChrono();
		GameObject* GetCamera();

		LightManager& GetLightManager();
	private:
		App(HINSTANCE hInst, int startWindowWidth, int startWindowHeight);

		void RenderFirstFrame();
		void LoadTextures();

		friend class GameObject;
	};
}

#include "App.inl"
