#pragma once
#include "ISystem.h"
#include "CollisionInfo.h"
#include "SpatialHash.h"

struct DirectX::BoundingOrientedBox;

namespace nam {
	struct BoxColliderComponent;
	struct TransformComponent;

	class ColliderSystem : public ISystem
	{
	private:
		u32 m_updateId = 0;
		SpatialHash m_spatialHash;
	public:
		void Update(Ecs& ecs) override;
	private:

		template<typename BoxType1, typename BoxType2>
		void CheckCollision(TransformComponent& transform1, TransformComponent& transform2, BoxType1& box1, BoxType2& box2, u32 entity1, u32 entity2, Vector<CollisionInfo>& collisions);

		CollisionInfo CalculateCollisionInfo(const DirectX::BoundingOrientedBox& box1, const DirectX::BoundingOrientedBox& box2);
		CollisionInfo CalculateCollisionInfo(const DirectX::BoundingOrientedBox& box,const DirectX::BoundingSphere& sphere);
		CollisionInfo CalculateCollisionInfo(const DirectX::BoundingSphere& sphere1,const DirectX::BoundingSphere& sphere2);
		
		void ProcessCollisionsIntersection(Ecs& ecs, Vector<CollisionInfo>& collisions);
		void ProcessCollisionsOnCollide(Vector<CollisionInfo>& collisions);
	};
}

#include "ColliderSystem.inl"