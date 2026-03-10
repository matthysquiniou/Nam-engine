#include "pch.h"
#include "App.h"
#include <RenderManager.h>

#include "RenderSystem.h"
#include "PhysicSystem.h"
#include "ColliderSystem.h"
#include "ParticleSystem.h"
#include "UISystem.h"
#include "BehaviorSystem.h"
#include "LightManagerSystem.h"

#include "CameraManagerSystem.h"
#include "CameraComponent.h"

#include "Window.h"

#include <Mesh.h>
#include <Sprite.h>
#include <Text.h>

#include "LoadingScreen.h"

using namespace DirectX;

namespace nam
{
	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return App::Get()->MsgProc(hwnd, msg, wParam, lParam);
	}

	LRESULT App::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msp_instance == nullptr)
			return DefWindowProc(hwnd, msg, wParam, lParam);

		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SIZE:
			m_window.m_clientWidth = LOWORD(lParam);
			m_window.m_clientHeight = HIWORD(lParam);

			if (Render->GetDevice())
			{
				if (wParam == SIZE_MINIMIZED)
				{
					m_minimized = true;
					m_maximized = false;
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					m_minimized = false;
					m_maximized = true;
					Resize();
				}
				else if (wParam == SIZE_RESTORED)
				{
					if (m_minimized)
					{
						m_minimized = false;
						Resize();
					}
					else if (m_maximized)
					{
						m_maximized = false;
						Resize();
					}
					else if (m_resizing)
					{
					}
					else
					{
						Resize();
					}
				}
			}
			return 0;

		case WM_LBUTTONDOWN:
			return 0;

		case WM_MBUTTONDOWN:
			return 0;

		case WM_RBUTTONDOWN:
			return 0;

		case WM_LBUTTONUP:
			return 0;

		case WM_MBUTTONUP:
			return 0;

		case WM_RBUTTONUP:
			return 0;

		case WM_MOUSEMOVE:
			return 0;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	App* App::msp_instance = nullptr;

	App::App(HINSTANCE hInst, int startWindowWidth, int startWindowHeight) : m_window(hInst, L"Test")
	{
		ToggleDebugConsole(true);

		m_window.Create(startWindowWidth, startWindowHeight, MainWndProc);

		RenderManager::Init(&m_window);
	}

	App::~App()
	{
		mp_camera->Destroy();
		delete mp_camera;
		m_sceneManager.Destroy();

		RenderManager::UnInit();
	}

	void App::Destroy()
	{
		if (msp_instance)
		{
			delete msp_instance;
		}
	}

	App* App::Get(HINSTANCE hInst, int startWindowWidth, int startWindowHeight)
	{
		if (msp_instance == nullptr && hInst != 0)
		{
			msp_instance = new App(hInst, startWindowWidth, startWindowHeight);
			msp_instance->Init();
		}

		return msp_instance;
	}

	void App::Init()
	{
		m_chrono.SetPauseState(true);

		Render->InitDirectX3D();
		Resize();

		m_sceneManager.SetEcs(&m_ecs);
		m_sceneManager.Start();

		m_ecs.AddSystem<RenderSystem>();
		m_ecs.AddSystem<PhysicSystem>();
		m_ecs.AddSystem<ColliderSystem>();
		m_ecs.AddSystem<CameraManagerSystem>();
		m_ecs.AddSystem<ParticleSystem>();
		m_ecs.AddSystem<UISystem>();
		m_ecs.AddSystem<BehaviorSystem>();
		m_ecs.AddSystem<LightManagerSystem>();
		m_ecs.AddSystem<StateMachineSystem>();

		CreateCamera();
		StartCamera();

		//Loading Screen first frame
		Scene* p_loadingScene = m_sceneManager.CreateScene(size(-1));

		mp_loadingScreen = p_loadingScene->CreateGameObject<LoadingScreen>();

		p_loadingScene->Start();
		AddCurrentScene(p_loadingScene);

		Render->BuildMinimal();

		RenderFirstFrame();
	}

	void App::Start()
	{
		Render->BuildOthers();
		LoadTextures();
		Render->EndInit();

		CameraDefaultSettings();
	}

	void App::Run()
	{
		Start();
		MainLoop();
	}

	void App::LoadTexture(std::wstring path, size uniqueTag, bool usingTextureFolder)
	{
		m_texturesDataToLoad.push_back(TextureData{ path, uniqueTag, usingTextureFolder });
	}

	int App::MainLoop()
	{
		m_chrono.SetPauseState(false);

		MSG msg = { 0 };

		while (msg.message != WM_QUIT)
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// Otherwise, do animation/game stuff.
			else
			{
				Update();

				Render->BeginFrame();
				Render->UpdateCompute();
				Render->Draw();
				Render->EndFrame();
			}
		}

		return (int)msg.wParam;
	}

	void App::Update()
	{
		m_chrono.Update();
		Input::UpdateKeyStates();
		m_ecs.Update();

		m_sceneManager.CleanUpdate();
		m_ecs.CleanUpdate();
	}

	void App::Resize()
	{
		if (mp_camera)
		{
			CameraComponent& cam = mp_camera->GetComponent<CameraComponent>();
			cam.UpdateAspectRatio(m_window.m_clientWidth, m_window.m_clientHeight);
		}

		Render->OnResize();
	}

	void App::CreateCamera()
	{
		if (mp_camera != nullptr)
		{
			delete mp_camera;
		}

		mp_camera = new GameObject();
		mp_camera->m_entity = m_ecs.CreateEntity();
		mp_camera->mp_scene = nullptr;

		mp_camera->Start();
	}

	void App::StartCamera()
	{
		mp_camera->AddComponent(TransformComponent());
		mp_camera->AddComponent(CameraComponent());
	}

	void App::CameraDefaultSettings()
	{
		if (mp_camera == nullptr)
			return;

		//si n'a aucun components
		if (mp_camera->HasComponent<TransformComponent>() == false)
		{
			//creer tout les components
			TransformComponent transform = TransformComponent();
			transform.SetWorldPosition(XMFLOAT3(0.f, 0.f, 0.f));
			mp_camera->AddComponent(transform);

			//save le component
			//mp_camera->mp_transform = &(mp_camera->GetComponent<TransformComponent>());
			mp_camera->AddComponent(CameraComponent());
		}

		TransformComponent& camTransform = mp_camera->GetComponent<TransformComponent>();

		XMFLOAT3 pos = { 0.f, 5.f, 0.f };

		camTransform.SetWorldPosition(pos);
		camTransform.SetWorldYPR(0.f, 0.f, 0.f);

	}

	void App::ToggleDebugConsole(bool state)
	{
		if (state == true)
		{
			AllocConsole();
			FILE* fp;

			freopen_s(&fp, "CONOUT$", "w", stdout);
			freopen_s(&fp, "CONOUT$", "w", stderr);
			freopen_s(&fp, "CONIN$", "r", stdin);
		}
		else
		{
			FreeConsole();
		}
	}

	void App::DestroyGameObject(GameObject* gameObject, Scene* scene)
	{
		scene->DestroyGameObject(gameObject);
	}

	void App::DestroyGameObject(GameObject* gameObject, u32 idScene)
	{
		m_sceneManager.GetScene(idScene)->DestroyGameObject(gameObject);
	}

	void App::SetActiveGameObject(Scene* scene, GameObject* gameObject, bool active)
	{
		scene->SetActiveEntity(*gameObject->GetEntity(), active);
	}

	void App::SetActiveGameObject(u32 idScene, GameObject* gameObject, bool active)
	{
		m_sceneManager.GetScene(idScene)->SetActiveEntity(*gameObject->GetEntity(), active);
	}

	void App::SetActiveEntity(Scene* scene, Entity& entity, bool active)
	{
		scene->SetActiveEntity(entity, active);
	}

	void App::SetActiveEntity(u32 idScene, Entity& entity, bool active)
	{
		m_sceneManager.GetScene(idScene)->SetActiveEntity(entity, active);
	}

	GameObject* App::GetGameObject(Scene* scene, u32 idEntity)
	{
		return scene->GetGameObject(idEntity);
	}

	GameObject* App::GetGameObject(Scene* scene, Entity& entity)
	{
		return scene->GetGameObject(entity);
	}

	GameObject* App::GetGameObject(u32 idScene, u32 idEntity)
	{
		return m_sceneManager.GetScene(idScene)->GetGameObject(idEntity);
	}

	GameObject* App::GetGameObject(u32 idScene, Entity& entity)
	{
		return m_sceneManager.GetScene(idScene)->GetGameObject(entity);
	}

	GameObject* App::GetGameObject(u32 idEntity)
	{
		return m_sceneManager.GetGameObjectInGame(idEntity);
	}

	GameObject* App::GetGameObject(Entity& entity)
	{
		return m_sceneManager.GetGameObjectInGame(entity);
	}

	Scene* App::CreateScene(size sceneTag)
	{
		return m_sceneManager.CreateScene(sceneTag);
	}

	void App::DestroyScene(Scene* scene)
	{
		m_sceneManager.DestroyScene(scene);
	}

	void App::AddCurrentScene(u32 idScene)
	{
		m_sceneManager.AddCurrentScene(idScene);
	}

	void App::AddCurrentScene(Scene* scene)
	{
		m_sceneManager.AddCurrentScene(scene);
	}

	void App::AddCurrentScene(size sceneTag)
	{
		m_sceneManager.AddCurrentScene(sceneTag);
	}

	void App::RemoveCurrentScene(Scene* scene)
	{
		m_sceneManager.RemoveCurrentScene(scene);
	}

	void App::RemoveCurrentScene(u32 idScene)
	{
		m_sceneManager.RemoveCurrentScene(idScene);
	}

	void App::RemoveCurrentScene(size sceneTag)
	{
		m_sceneManager.RemoveCurrentScene(sceneTag);
	}

	void App::SwitchCurrentScene(Scene* sceneClose, Scene* sceneOpen)
	{
		m_sceneManager.SwitchCurrentScene(sceneClose, sceneOpen);
	}

	void App::SwitchCurrentScene(u32 idSceneClose, u32 idSceneOpen)
	{
		m_sceneManager.SwitchCurrentScene(idSceneClose, idSceneOpen);
	}

	void App::SwitchCurrentScene(size sceneTag1, size sceneTag2)
	{
		m_sceneManager.SwitchCurrentScene(sceneTag1, sceneTag2);
	}

	Scene* App::GetScene(u32 idScene)
	{
		return m_sceneManager.GetScene(idScene);
	}

	Scene* App::GetScene(Entity& entity)
	{
		UnMap<u32, Scene*> allScene = m_sceneManager.GetAllScene();
		for (auto it1 = allScene.begin(); it1 != allScene.end(); it1++)
		{
			Entity entityFind = it1->second->GetEntity(entity.m_id);
			if (entityFind.m_id != -1)
			{
				return it1->second;
			}
		}
		return nullptr;
	}

	Window& App::GetWindow()
	{
		return m_window;
	}

	GameObject* App::GetCamera()
	{
		return mp_camera;
	}

	Ecs& App::GetEcs()
	{
		return m_ecs;
	}

	Mesh* App::CreateEmptyMesh()
	{
		return Render->GetRenderItemManager().CreateRenderItem<Mesh>();
	}

	Sprite* App::CreateEmptySprite()
	{
		return Render->GetRenderItemManager().CreateRenderItem<Sprite>();;
	}

	Text* App::CreateEmptyText()
	{
		return Render->GetRenderItemManager().CreateRenderItem<Text>();;
	}

	LightManager& App::GetLightManager()
	{
		return Render->GetLightManager();
	}

	SceneManager& App::GetSceneManager()
	{
		return m_sceneManager;
	}

	AppChrono& App::GetChrono()
	{
		return m_chrono;
	}

	//Private
	void App::RenderFirstFrame()
	{
		//A first Update to push the RenderItem in the RenderSystem Draw
		Update();

		Render->BeginFrame();
		Render->Draw();
		Render->EndFirstFrame();
	}

	void App::LoadTextures()
	{
		for (TextureData& td : m_texturesDataToLoad)
		{
			Render->LoadTexture(td.m_path, td.m_uniqueTag, td.m_usingTextureFolder);
		}
	}
}
