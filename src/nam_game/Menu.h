#pragma once
#include "IWrappedScene.h"

namespace nam
{
	class Scene;
}

class Button;
class MenuBackground;

class Menu : public IWrappedScene
{
private:
	Button* mp_playButton = nullptr;

	MenuBackground* mp_background = nullptr;

public:
	void Init() override;

private:
	void LoadTextures() override;
	void InitGameObjectsSingle() override;

};

