#include "pch.h"
#include "CaveScene.h"
#include "TextureTags.h"
#include "SceneTags.h"

#include <VoxelGrid.h>

#include <TextRendererComponent.h>

#include "PauseHandlerObject.h"
#include "CaveGenerator.h"
#include "CaveSectionParams.h"
#include "CaveGeneratorParams.h"
#include <RenderManager.h>
#include "MeshTag.h"
#include "Crystal.h"
#include <CaveManager.h>

#include "EnemySpawner.h"

void CaveScene::Init()
{
	App* app = App::Get();

	//start game
	{
		LoadTextures();

		LoadMesh();
		//creation caveScene
		mp_scene = app->CreateScene(_CaveScene);
		InitGameObjectsSingle();
		InitGameObjectsNotSingle();
	}
}

void CaveScene::InitGameObjectsSingle()
{
	App* app = App::Get();
	GameObject* appCamera = app->GetCamera();

	mp_score = mp_scene->CreateGameObject<Score>();

	//creation player
	mp_player = mp_scene->CreateGameObject<Player>();
	{
		MeshRendererComponent meshComp;
		float tall = 1.f;
		meshComp.CreateMeshInstance();
		meshComp.mp_mesh->BuildCylinder(0.5f, 20, tall, { 1,1,1,1 });
		meshComp.mp_mesh->SetTexture(_Stone);

		Mesh* mesh = app->CreateEmptyMesh();
		mesh->BuildUvSphere(1.f, 5, 5, { 1.f, 1.f, 1.f, 1.f });
		mesh->SetTexture(_Heart);

		XMFLOAT3 pos = XMFLOAT3(0.f, 0.f, 0.f);
		mp_player->SetWorldPosition(pos);
		mp_player->SetScore(mp_score);
		mp_player->SetMeshShot(mesh);
		mp_player->SetBoxCollider();
		mp_player->AddComponent(meshComp);
	}

	//creation Camera
	Camera* camera = mp_scene->CreateGameObject<Camera>();
	{
		camera->SetAppCamera(appCamera);
		camera->SetTarget(mp_player);
	}

	mp_fpsDisplayer = mp_scene->CreateGameObject<FPSDisplayer>();

	
}

void CaveScene::InitGameObjectsNotSingle()
{
	App* app = App::Get();

	//initialisation des objets
	if (mp_pauseHandler != nullptr)
	{
		mp_pauseHandler->DestroyGameObject();
	}
	mp_pauseHandler = mp_scene->CreateGameObject<PauseHandlerObject>();

	mp_fpsDisplayer = mp_scene->CreateGameObject<FPSDisplayer>();

	EnemySpawner* es = mp_scene->CreateGameObject<EnemySpawner>();
	es->SetDatas(mp_player, mp_score, 10.f);

	InitHpText();
	InitCave();
}

Text* CaveScene::GetHpText()
{
	return mp_hpText;
}

void CaveScene::LoadTextures()
{
	App* app = App::Get();

	app->LoadTexture(L"yellow.dds", _Yellow, true);
	app->LoadTexture(L"rainbow.dds", _Rainbow, true);
	app->LoadTexture(L"stone.dds", _Stone, true);
	app->LoadTexture(L"dirt.dds", _Dirt, true);

	app->LoadTexture(L"crepit.dds", _Crepit, true);
	app->LoadTexture(L"tuile.dds", _Tuile, true);
	app->LoadTexture(L"heart.dds", _Heart, true);
	app->LoadTexture(L"grass.dds", _Grass, true);
	app->LoadTexture(L"../../res/Assets/Bat/bat.dds", _Bat);
	app->LoadTexture(L"../../res/Assets/Crystal1/crystal.dds", _Crystal);
}

void CaveScene::LoadMesh()
{
	Mesh* crystal1 = Render->GetRenderItemManager().CreateRenderItem<Mesh>();
	crystal1->LoadObj(L"../../res/Assets/Crystal1/crystal1.obj");
	crystal1->SetTexture(_Crystal);
	Render->GetRenderItemManager().SetRenderItemTag(crystal1, (size)MeshTag::_Crystal1);

	Mesh* crystal2 = Render->GetRenderItemManager().CreateRenderItem<Mesh>();
	crystal2->LoadObj(L"../../res/Assets/Crystal2/crystal2.obj");
	crystal2->SetTexture(_Crystal);
	Render->GetRenderItemManager().SetRenderItemTag(crystal2, (size)MeshTag::_Crystal2);
}

void CaveScene::InitHpText()
{
	TextRendererComponent textComp;
	mp_hpText = textComp.CreateTextInstance();
	mp_hpText->SetDatas({ 56, 56 }, 0.75f, { 1, 1, 1, 1 });
	mp_hpText->SetToDynamic(MAX_TEXT_VERTICES, MAX_TEXT_INDICES);
	mp_hpText->SetText("HP : ");

	Window& window = App::Get()->GetWindow();

	XMFLOAT2 wSize = { (float)window.m_clientWidth,  (float)window.m_clientHeight };

	mp_hp = mp_scene->CreateGameObject<GameObject>();

	mp_hp->AddComponent(textComp);
	mp_hp->SetWorldPosition({ 56, wSize.y - 128, 0 });
}

void CaveScene::InitCave()
{
	CaveSectionParams csp;
	/*
	PlaceableElement pe;
	pe.SpawnFunc = &Crystal::Create;
	pe.m_minScale = 0.2f;
	pe.m_maxScale = 0.4f;
	csp.m_placeableElements.push_back(pe);
	*/
	csp.m_textureTag = _Stone;
	CaveGeneratorParams cgp;
	CaveManager::Create(mp_scene, cgp, csp);
}

