#include "pch.h"
#include "Menu.h"

#include "App.h"
#include "TextureTags.h"
#include "SceneTags.h"

#include "Button.h"
#include "MenuBackground.h"

#include <SpriteRendererComponent.h>

void Menu::Init()
{ 
	LoadTextures();

	App* p_app = App::Get();

	mp_scene = p_app->CreateScene(_MenuScene);

	InitGameObjectsSingle();

	mp_scene->Start();
	p_app->AddCurrentScene(mp_scene);
}

void Menu::LoadTextures()
{
	App* p_app = App::Get();

	p_app->LoadTexture(L"bg.dds", _MenuBackground, true);

	p_app->LoadTexture(L"Buttons/Play/idle.dds", _PlayButtonIdle, true);
	p_app->LoadTexture(L"Buttons/Play/pressed.dds", _PlayButtonPressed, true);
}

void Menu::InitGameObjectsSingle()
{
	App* p_app = App::Get();

	Window& window = App::Get()->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };
	XMFLOAT3 pos = { wSize.x * 0.5f, wSize.y * 0.7f, 0.f };

	mp_background = mp_scene->CreateGameObject<MenuBackground>();

	////////////////////////////////////////////////////

	mp_playButton = mp_scene->CreateGameObject<Button>();

	if (Scene* p_cave = p_app->GetSceneManager().GetSceneByTag(_CaveScene))
	{
		mp_playButton->SetProperties(_PlayButtonIdle, _PlayButtonPressed,
			[p_app, p_cave, this]() { p_app->AddCurrentScene(p_cave); p_cave->Start(); p_app->RemoveCurrentScene(mp_scene); });

		mp_playButton->SetWorldPosition(pos);
		mp_playButton->SetWorldScale({ 1.5f, 1.5f, 1.f });
	}
	else
	{
		_ASSERT(false && "CaveScene not initialized when Menu is Init");
	}
}