#include "pch.h"
#include "Button.h"

#include <SpriteRendererComponent.h>
#include <ButtonComponent.h>

void Button::OnInit()
{
	//SetBehavior();
	m_teleportTimer.Init(0.1f);
	SetTag((int)Tag::_None);
}

void Button::OnStart()
{
}

void Button::OnUpdate()
{
	//App* p_app = App::Get();
	//Window& window = p_app->GetWindow();

}

void Button::OnDestroy()
{
}

void Button::SetProperties(size textureIdle, size texturePressed, std::function<void()> onClick)
{
	if (HasComponent<SpriteRendererComponent>())
		return;

	m_textureIdle = textureIdle;
	m_texturePressed = texturePressed;
	m_onClick = onClick;

	SpriteRendererComponent spriteComp;
	mp_sprite = spriteComp.CreateSpriteInstance();
	mp_sprite->BuildRect({ 300, 150 }, { 1, 1, 1, 1 });
	mp_sprite->SetToDynamic(4, 6);
	mp_sprite->SetTexture(m_textureIdle);
	AddComponent(spriteComp);

	ButtonComponent buttonComp;
	buttonComp.OnHovered = [this]() { m_hovered = true; mp_sprite->SetTexture(m_texturePressed); };
	buttonComp.OnLeft = [this]() { m_hovered = false; mp_sprite->SetTexture(m_textureIdle); };
	buttonComp.OnClick = [this]() { m_hovered = false; m_onClick(); };
	AddComponent(buttonComp);
}

void Button::SetColor(DirectX::XMFLOAT4 color)
{
	if (mp_sprite == nullptr)
		return;

	mp_sprite->SetColor(color);
}
