#include "pch.h"
#include "Frog2.h"

using namespace nam;
using namespace DirectX;

void Frog2::OnInit()
{
    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
    mrc.mp_mesh->BuildBox({ 1.f,1.f, 1.f }, { 0.5f,0.5f,0.5f,1.f });
    AddComponent<MeshRendererComponent>(mrc);

    TransformComponent tc;
    tc.SetWorldPosition({ 1.f,2.f,0.f });
    AddComponent<TransformComponent>(tc);

    AddComponent<PhysicComponent>(PhysicComponent());

    SetBoxCollider();
    SetBehavior();
}

void Frog2::OnUpdate()
{
    
}

void Frog2::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
}
