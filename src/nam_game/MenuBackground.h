#pragma once
#include <GameObject.h>

class MenuBackground : public GameObject
{
	Sprite* mp_sprite = nullptr;
	float m_width = 0;
	float m_height = 0;
public:
	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	void SetColor(DirectX::XMFLOAT4 color);
};

