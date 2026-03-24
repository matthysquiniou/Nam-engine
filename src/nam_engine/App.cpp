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
#include <ControllerSystem.h>

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

		m_sceneManager.Start();

		m_ecs.AddSystem<StateMachineSystem>();
		m_ecs.AddSystem<BehaviorSystem>();
		m_ecs.AddSystem<ControllerSystem>();
		m_ecs.AddSystem<PhysicSystem>();
		m_ecs.AddSystem<ColliderSystem>();
		m_ecs.AddSystem<CameraManagerSystem>();
		m_ecs.AddSystem<ParticleSystem>();
		m_ecs.AddSystem<UISystem>();
		m_ecs.AddSystem<LightManagerSystem>();
		m_ecs.AddSystem<RenderSystem>();

		//Loading Screen first frame
		Scene& loadingScene = m_sceneManager.CreateOrGetScene<Scene>(size(-1));

		mp_loadingScreen = &loadingScene.CreateGameObject<LoadingScreen>();

		loadingScene.Start();


		Render->BuildMinimal();

		RenderFirstFrame();
	}

	void App::Start()
	{
		Render->BuildOthers();
		LoadTextures();
		Render->EndInit();
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
		m_ecs.Update();

		m_sceneManager.CleanUpdate();
		m_ecs.CleanUpdate();
	}

	void App::Resize()
	{
		m_ecs.ForEach<CameraComponent>(
			[&](u32 e, CameraComponent& c) {
				c.UpdateAspectRatio(m_window.m_clientWidth, m_window.m_clientHeight);
			}
		);

		Render->OnResize();
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

	void App::ClearScene(size scene)
	{
		m_sceneManager.ClearScene(scene);
	}

	void App::SetSceneActive(size scene, bool active)
	{
		m_sceneManager.SetActiveScene(scene, active);
	}

	Window& App::GetWindow()
	{
		return m_window;
	}

	Ecs& App::GetEcs()
	{
		return m_ecs;
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
