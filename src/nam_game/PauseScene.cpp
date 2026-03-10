#include "pch.h"
#include "PauseScene.h"
#include "TextureTags.h"
#include "SceneTags.h"

#include "PauseObject.h"
#include "Button.h"

#include <TextRendererComponent.h>

void PauseScene::Init()
{
	LoadTextures();

	App* p_app = App::Get();

	mp_scene = p_app->CreateScene(_PauseScene);

	InitGameObjectsSingle();
}

void PauseScene::LoadTextures()
{
	App* p_app = App::Get();

	p_app->LoadTexture(L"Buttons/Home/idle.dds", _HomeButtonIdle, true);
	p_app->LoadTexture(L"Buttons/Home/pressed.dds", _HomeButtonPressed, true);

	p_app->LoadTexture(L"Buttons/Back/idle.dds", _BackButtonIdle, true);
	p_app->LoadTexture(L"Buttons/Back/pressed.dds", _BackButtonPressed, true);

	p_app->LoadTexture(L"Buttons/Restart/idle.dds", _RestartButtonIdle, true);
	p_app->LoadTexture(L"Buttons/Restart/pressed.dds", _RestartButtonPressed, true);
}

void PauseScene::InitGameObjectsSingle()
{
	App* p_app = App::Get();

	mp_pauseObj = mp_scene->CreateGameObject<PauseObject>();

	InitPauseText(p_app);

	InitHomeButton(p_app);
	InitBackButton(p_app);
	InitRestartButton(p_app);
}

void PauseScene::InitPauseText(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	mp_pauseText = mp_scene->CreateGameObject<GameObject>();

	TextRendererComponent textComp;
	Text* p_text = textComp.CreateTextInstance();
	p_text->SetDatas({ 200, 200 }, 0.8f, { 1, 1, 1, 1 });
	p_text->SetText("PAUSE");

	mp_pauseText->AddComponent(textComp);
	mp_pauseText->SetWorldPosition({ wSize.x * 0.5f - 200.f * 4.f * 0.4f, wSize.y * 0.5f, 0.f });
}

void PauseScene::InitHomeButton(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	XMFLOAT3 pos = { wSize.x - 200, 125, 0.f };

	mp_home = mp_scene->CreateGameObject<Button>();

	mp_home->SetProperties(_HomeButtonIdle, _HomeButtonPressed,
		[p_app, this]() { mp_pauseObj->UnFreezeTime(); p_app->RemoveCurrentScene(_CaveScene); p_app->RemoveCurrentScene(mp_scene); p_app->AddCurrentScene(_MenuScene); });

	mp_home->SetWorldPosition(pos);
}

void PauseScene::InitBackButton(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	XMFLOAT3 pos = { wSize.x - 200, wSize.y - 125, 0.f };

	mp_back = mp_scene->CreateGameObject<Button>();

	mp_back->SetProperties(_BackButtonIdle, _BackButtonPressed,
		[p_app, this]() { p_app->RemoveCurrentScene(mp_scene); mp_pauseObj->UnFreezeTime(); });

	mp_back->SetWorldPosition(pos);
}

void PauseScene::InitRestartButton(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	XMFLOAT3 pos = { wSize.x - 550, 125, 0.f };

	mp_restart = mp_scene->CreateGameObject<Button>();

	SceneManager& sm = p_app->GetSceneManager();

	mp_restart->SetProperties(_RestartButtonIdle, _RestartButtonPressed,
		[p_app, &sm, this]() { mp_pauseObj->UnFreezeTime(); CaveScene* caveScene = WrappedSceneManager::Get<CaveScene>(); caveScene->Reset(); caveScene->mp_scene->SetActiveAllEntity(true); p_app->RemoveCurrentScene(mp_scene); });

	mp_restart->SetWorldPosition(pos);
}
