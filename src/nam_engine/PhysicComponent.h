#pragma once
namespace nam
{
    struct PhysicComponent
    {
        float m_mass = 1.0f;
        float m_gravityScale = 1.0f;

        DirectX::XMFLOAT3 m_velocity = { 0.f,0.f,0.f };
        float m_collisionRestitution = 0.3f;

        bool m_useGravity = true;

        void AddImpulse(const DirectX::XMFLOAT3& impulse);
    };
}

