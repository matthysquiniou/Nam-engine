#pragma once
#include "TransformComponent.h"

namespace nam
{
    struct SingleCollisionInfo
    {
        u32 m_entity;
        TransformComponent* m_transform;
        size m_tag;

        float m_penetrationDepth;
        DirectX::XMFLOAT3 m_normal;
        DirectX::XMFLOAT3 m_contactPoint;
    };

    struct CollisionInfo
    {
        u32 m_entity1;
        u32 m_entity2;

        TransformComponent* m_transform1;
        TransformComponent* m_transform2;

        std::function<void(const SingleCollisionInfo& self, const SingleCollisionInfo& other)> OnCollision1;
        std::function<void(const SingleCollisionInfo& self, const SingleCollisionInfo& other)> OnCollision2;

        bool m_noIntersectionPush1 = false;
        bool m_noIntersectionPush2 = false;

        size m_tag1;
        size m_tag2;

        float m_penetrationDepth;
        DirectX::XMFLOAT3 m_normal;
        DirectX::XMFLOAT3 m_contactPoint;

        SingleCollisionInfo GetSingleInfo(u32 entity);
    };
}
