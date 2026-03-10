#pragma once
#include "DirectXMath.h"
#include <DirectXCollision.h>

namespace nam
{
	struct TransformComponent;
	struct MeshRendererComponent;
	struct CollisionInfo;

	struct BoxColliderComponent
	{
		u32 m_updateId = 0;
		DirectX::BoundingOrientedBox m_box;
		bool m_noIntersectionPush = false;
		std::function<void(u32 self, u32 other, const CollisionInfo& collisionInfo)> OnCollision;
		void UpdateObbBox(TransformComponent& transform, const MeshRendererComponent& meshRenderer, u32 updateId);
	};
}
