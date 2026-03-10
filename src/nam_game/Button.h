#pragma once
#include "GameObject.h"

class Button : public GameObject
{
	Sprite* mp_sprite = nullptr;

	bool m_hovered = true;

	std::function<void()> m_onClick = nullptr;

	size m_textureIdle = -1;
	size m_texturePressed = -1;

	Timer m_teleportTimer = {};
public:
	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	void SetProperties(size textureIdle, size texturePressed, std::function<void()> onClick);

	void SetColor(DirectX::XMFLOAT4 color);
};

