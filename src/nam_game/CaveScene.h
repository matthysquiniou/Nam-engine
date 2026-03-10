#pragma once
#include "IWrappedScene.h"

namespace nam
{
	class Scene;
}

class Player;
class FPSDisplayer;
class PauseHandlerObject;

class CaveScene : public IWrappedScene
{
public:

private:
	Player* mp_player = nullptr;
	FPSDisplayer* mp_fpsDisplayer = nullptr;
	Score* mp_score = nullptr;

	PauseHandlerObject* mp_pauseHandler = nullptr;

	Text* mp_hpText = nullptr;
	GameObject* mp_hp = nullptr;
public:
	void Init() override;
	void InitGameObjectsSingle() override;
	void InitGameObjectsNotSingle() override;

	Text* GetHpText();
private:
	void LoadTextures() override;
	void LoadMesh();

	void InitHpText();
	void InitCave();

};

