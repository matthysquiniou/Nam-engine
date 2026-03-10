#include "pch.h"
#include "PhysicComponent.h"

namespace nam
{
    void PhysicComponent::AddImpulse(const DirectX::XMFLOAT3& impulse)
    {
        m_velocity.x += impulse.x / m_mass;
        m_velocity.y += impulse.y / m_mass;
        m_velocity.z += impulse.z / m_mass;
    }
}
