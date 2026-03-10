#include "pch.h"
#include "MenuBackground.h"
#include <SpriteRendererComponent.h>
#include "TextureTags.h"

void MenuBackground::OnInit()
{
	SetBehavior();

	Window& window = App::Get()->GetWindow();

	m_width = (float)window.m_clientWidth;
	m_height = (float)window.m_clientHeight;

	XMFLOAT2 wSize = { m_width, m_height };

	SpriteRendererComponent spriteComp;
	mp_sprite = spriteComp.CreateSpriteInstance();
	mp_sprite->BuildRect(wSize, { 1, 1, 1, 1 });
	mp_sprite->BuildRect(wSize, { 1, 1, 1, 1 }, false, {wSize.x, 0.f});

	mp_sprite->SetTexture(_MenuBackground);
	mp_sprite->SetToDynamic(8, 12);

	AddComponent(spriteComp);
	XMFLOAT3 middle = { wSize.x * 0.5f, wSize.y * 0.5f, 0.f };
	SetWorldPosition(middle);
}

void MenuBackground::OnStart()
{
	XMFLOAT3 middle = { m_width * 0.5f, m_height * 0.5f, 0.f };
	SetWorldPosition(middle);
}

void MenuBackground::OnUpdate()
{
	if (Input::IsMouseVisible() == false)
		Input::ShowMouse();

	App* p_app = App::Get();

	float dt = p_app->GetChrono().GetRealDeltaTime();

	XMFLOAT3 pos = GetWorldPosition();

	XMFLOAT3 t = {};

	if (pos.x < -m_width * 0.5f)
	{
		t = { m_width, 0.f, 0.f };
	}
	else
	{
		t = { -dt * 100.f, 0.f, 0.f };
	}

	TranslateWorld(t);
}

void MenuBackground::OnDestroy()
{

}

void MenuBackground::SetColor(DirectX::XMFLOAT4 color)
{
	if (mp_sprite == nullptr)
		return;

	mp_sprite->SetColor(color);
}
