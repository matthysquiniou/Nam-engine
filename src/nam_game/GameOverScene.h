#pragma once
#include "IWrappedScene.h"

namespace nam
{
	class Scene;
}

class Button;
class MenuBackground;

inline std::wstring PATH_SCORE = L"../../src/nam_game/data.txt";

class GameOverScene : public IWrappedScene
{
private:
	int m_score = 69;
	int m_bestScore = 0;

	Text* mp_scoreToDisplay = nullptr;

	GameObject* mp_gameOverText = nullptr;
	GameObject* mp_scoreText = nullptr;
	MenuBackground* mp_background = nullptr;

	Button* mp_restart = nullptr;
	Button* mp_home = nullptr;

public:
	void Init() override;

	void UpdateScore(int newScore, bool save);
private:
	void LoadTextures() override;
	void InitGameObjectsSingle() override;

	void InitRestartButton(App* p_app);
	void InitHomeButton(App* p_app);
	void InitGameOverText(App* p_app);
	void InitScoreText(App* p_app);
};

