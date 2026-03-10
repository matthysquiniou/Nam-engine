#include "pch.h"
#include "Frog1.h"

using namespace nam;
using namespace DirectX;

void Frog1::OnInit()
{
    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
    mrc.mp_mesh->BuildBox({ 1.f,1.f, 1.f }, { 0.5f,0.5f,0.5f,1.f });
    AddComponent<MeshRendererComponent>(mrc);

    TransformComponent tc;
    tc.SetWorldPosition({ -1.f,2.f,0.f });
    AddComponent<TransformComponent>(tc);

    AddComponent<PhysicComponent>(PhysicComponent());

    SetBoxCollider();
	SetBehavior();
    SetController();
}

void Frog1::OnUpdate()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
}

void Frog1::OnController()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.UpdateWorldData();
    XMFLOAT3 pos = tc.GetWorldPosition();
    if (Input::IsKey('z')|| Input::IsKey('Z'))
    {
        pos.z += 1.f * dt;
    }
    tc.SetWorldPosition(pos);
}

void Frog1::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
}
