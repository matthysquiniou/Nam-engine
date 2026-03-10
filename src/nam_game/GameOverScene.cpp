#include "pch.h"
#include "GameOverScene.h"

#include "TextureTags.h"
#include "SceneTags.h"

#include "Button.h"
#include "MenuBackground.h"

#include <TextRendererComponent.h>

void GameOverScene::Init()
{
	LoadTextures();

	App* p_app = App::Get();

	mp_scene = p_app->CreateScene(_GameOverScene);

	InitGameObjectsSingle();
}

void GameOverScene::UpdateScore(int newScore, bool save)
{
	if (newScore < 0)
		newScore = 0;

	m_score = newScore;

	std::ifstream file(PATH_SCORE);

	if (!file.is_open())
		return;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string prefix;

		ss >> prefix; //Read the following word and fill the variable

		if (prefix == "best")
		{
			ss >> m_bestScore;
		}
	}

	std::string newBest = "";

	if (m_score > m_bestScore)
	{
		m_bestScore = m_score;

		newBest = "New ";
	}

	//Override File

	if (save)
	{
		std::ofstream fileOut(PATH_SCORE, std::ios::trunc);
		if (!fileOut.is_open())
			return;

		fileOut << "best " << m_bestScore << "\n";

		fileOut.close();
	}

	std::string score = "Score : " + std::to_string(m_score);
	std::string best = std::string("\n") + newBest + std::string("Best : ") + std::to_string(m_bestScore);

	mp_scoreToDisplay->SetText(score + best);
	mp_scoreToDisplay->MakeRainbowVertices();
}

void GameOverScene::LoadTextures()
{
	App* p_app = App::Get();

	p_app->LoadTexture(L"bg.dds", _MenuBackground, true);

	p_app->LoadTexture(L"Buttons/Home/idle.dds", _HomeButtonIdle, true);
	p_app->LoadTexture(L"Buttons/Home/pressed.dds", _HomeButtonPressed, true);

	p_app->LoadTexture(L"Buttons/Restart/idle.dds", _RestartButtonIdle, true);
	p_app->LoadTexture(L"Buttons/Restart/pressed.dds", _RestartButtonPressed, true);
}

void GameOverScene::InitGameObjectsSingle()
{
	App* p_app = App::Get();

	mp_background = mp_scene->CreateGameObject<MenuBackground>();
	mp_background->SetColor({ 0.5, 0, 0, 1 });

	InitGameOverText(p_app);
	InitScoreText(p_app);
	InitRestartButton(p_app);
	InitHomeButton(p_app);
}

void GameOverScene::InitRestartButton(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	XMFLOAT3 pos = { wSize.x * 0.5f - 325.f,  wSize.y - 150, 0.f };

	mp_restart = mp_scene->CreateGameObject<Button>();

	SceneManager& sm = p_app->GetSceneManager();

	mp_restart->SetProperties(_RestartButtonIdle, _RestartButtonPressed,
		[p_app, &sm, this]() { sm.GetSceneByTag(_CaveScene)->Start(); p_app->SwitchCurrentScene(mp_scene->GetTag(), _CaveScene); });

	mp_restart->SetColor({ 1, 0.2f, 0.2f, 1 });

	mp_restart->SetWorldPosition(pos);
}

void GameOverScene::InitHomeButton(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	XMFLOAT3 pos = { wSize.x * 0.5f + 325.f, wSize.y - 150, 0.f };

	mp_home = mp_scene->CreateGameObject<Button>();

	mp_home->SetProperties(_HomeButtonIdle, _HomeButtonPressed,
		[p_app, this]() { p_app->RemoveCurrentScene(_CaveScene); p_app->RemoveCurrentScene(mp_scene); p_app->AddCurrentScene(_MenuScene); });

	mp_home->SetColor({ 1, 0.2f, 0.2f, 1 });

	mp_home->SetWorldPosition(pos);
}

void GameOverScene::InitGameOverText(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	mp_gameOverText = mp_scene->CreateGameObject<GameObject>();

	TextRendererComponent textComp;
	Text* p_text = textComp.CreateTextInstance();
	p_text->SetDatas({ 150, 150 }, 0.75f, { 1, 1, 1, 1 });
	p_text->SetText("GAME OVER !");
	p_text->SetColor({ 1, 0.5f, 0.5f, 1 });

	mp_gameOverText->AddComponent(textComp);
	mp_gameOverText->SetWorldPosition({ wSize.x * 0.5f - 150.f * (p_text->m_currentText.size() - 1) * p_text->GetKerning() * 0.5f, wSize.y * 0.4f, 0.f});
}

void GameOverScene::InitScoreText(App* p_app)
{
	Window& window = p_app->GetWindow();
	XMFLOAT2 wSize = { (float)window.m_clientWidth, (float)window.m_clientHeight };

	mp_gameOverText = mp_scene->CreateGameObject<GameObject>();

	TextRendererComponent textComp;
	mp_scoreToDisplay = textComp.CreateTextInstance();
	mp_scoreToDisplay->SetDatas({ 75, 75 }, 0.75f, { 1, 1, 1, 1 });
	mp_scoreToDisplay->SetText("Score :\nBest :");
	mp_scoreToDisplay->SetToDynamic(MAX_TEXT_VERTICES, MAX_TEXT_INDICES);
	mp_scoreToDisplay->MakeRainbowVertices();

	mp_gameOverText->AddComponent(textComp);
	mp_gameOverText->SetWorldPosition({ wSize.x * 0.5f - 75.f * 8.f * mp_scoreToDisplay->GetKerning(), wSize.y * 0.4f + 100.f, 0.f});
}
