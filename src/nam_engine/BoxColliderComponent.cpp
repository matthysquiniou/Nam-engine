#include "pch.h"
#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "MeshRendererComponent.h"

using namespace DirectX;

namespace nam
{
	void BoxColliderComponent::UpdateObbBox(TransformComponent& transform, const MeshRendererComponent& meshRenderer, u32 updateId)
	{
		if (updateId == m_updateId)
			return;

		const Mesh* p_mesh = meshRenderer.mp_mesh;
		XMFLOAT3 worldPosition = transform.GetWorldPosition();
		XMFLOAT3 worldCenter;
		XMStoreFloat3(&worldCenter,
			XMVectorAdd(
				XMLoadFloat3(&p_mesh->m_center),
				XMLoadFloat3(&worldPosition)
			));

		XMFLOAT3 scaledExtend;
		XMFLOAT3 worldScale = transform.GetWorldScale();
		XMStoreFloat3(
			&scaledExtend,
			XMVectorMultiply(
				XMLoadFloat3(&p_mesh->m_extend),
				XMLoadFloat3(&worldScale)
			)
		);

		m_box = BoundingOrientedBox(worldCenter, scaledExtend, transform.GetWorldRotation());
		m_updateId = updateId;
		m_dirty = false;
	}

	void BoxColliderComponent::UpdateObbBox(TransformComponent& transform, u32 updateId)
	{
		if (updateId == m_updateId)
			return;

		XMFLOAT3 worldPosition = transform.GetWorldPosition();
		XMFLOAT3 worldCenter;
		XMStoreFloat3(&worldCenter,
			XMVectorAdd(
				XMLoadFloat3(&m_customPosOffset),
				XMLoadFloat3(&worldPosition)
			));

		XMFLOAT3 scaledExtend;
		XMFLOAT3 worldScale = transform.GetWorldScale();
		XMStoreFloat3(
			&scaledExtend,
			XMVectorMultiply(
				XMLoadFloat3(&m_customExtends),
				XMLoadFloat3(&worldScale)
			)
		);

		m_box = BoundingOrientedBox(worldCenter, scaledExtend, transform.GetWorldRotation());
		m_updateId = updateId;
		m_dirty = false;
	}
}
