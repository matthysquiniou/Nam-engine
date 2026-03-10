#pragma once
#include "IWrappedScene.h"

namespace nam
{
	class Scene;
}

class PauseObject;
class Button;

class PauseScene : public IWrappedScene
{
public:

	Button* mp_home = nullptr;
	Button* mp_back = nullptr;
	Button* mp_restart = nullptr;

	PauseObject* mp_pauseObj = nullptr;

	GameObject* mp_pauseText = nullptr;
public:
	void Init() override;

private:
	void LoadTextures() override;
	void InitGameObjectsSingle() override;

	void InitPauseText(App* p_app);
	void InitHomeButton(App* p_app);
	void InitBackButton(App* p_app);
	void InitRestartButton(App* p_app);
};

