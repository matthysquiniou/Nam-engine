#include "pch.h"
#include "Transform2DComponent.h"

Transform2DComponent::Transform2DComponent()
{
	Reset();
}

void Transform2DComponent::Reset()
{
	m_pos = { 0, 0 };
}

void Transform2DComponent::SetPosition(DirectX::XMFLOAT2 pos)
{
	m_pos = pos;
}

void Transform2DComponent::Translate(DirectX::XMFLOAT2 vec)
{
	DirectX::XMVECTOR pos = DirectX::XMLoadFloat2(&m_pos);
	DirectX::XMVECTOR translation = DirectX::XMLoadFloat2(&vec);

	DirectX::XMStoreFloat2(&m_pos, DirectX::XMVectorAdd(pos, translation));
}
