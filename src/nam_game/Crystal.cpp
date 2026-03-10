#include "pch.h"
#include "Crystal.h"
#include "MeshTag.h"
#include <RenderManager.h>

Crystal::Crystal()
{
}

void Crystal::OnInit()
{
}

void Crystal::OnStart()
{
}

void Crystal::OnUpdate()
{
}

void Crystal::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	// TODO destroy + emit explosion particle
}

void Crystal::OnDestroy()
{
}

void Crystal::TryAddLight()
{
	float lightProba = 0.1f;
	float roll = Rng::Float();
	if (roll < lightProba)
	{
		LightComponent lc;
		float range = 4.f;
		float intensity = 0.5f;
		XMFLOAT3 color = { Rng::Float(),Rng::Float(), Rng::Float() };
		lc.CreateLightInstance();
		lc.mp_light->SetToPointLight(intensity, { 0,0,0 }, range, color);
		AddComponent<LightComponent>(lc);
	}
}

void Crystal::SelectRandomMesh()
{
	MeshTag meshesTags[2] = { MeshTag::_Crystal1,MeshTag::_Crystal2 };
	int index = Rng::Int(0, 1);

	ARenderItem* renderItem = Render->GetRenderItemManager().GetRenderItemOfTag((size)meshesTags[index]);
	SetMesh((Mesh*)renderItem);
}

GameObject* Crystal::Create(Scene* scene, const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& normal, float scale)
{
	Crystal* crystal = scene->CreateGameObject<Crystal>();
	crystal->SetWorldScale({ scale,scale,scale });

	crystal->SelectRandomMesh();

	XMFLOAT3 fPos;
	XMStoreFloat3(&fPos, 
		XMVectorAdd(
			XMLoadFloat3(&pos),
			XMVectorScale(XMLoadFloat3(&normal), 2.f)
		)
	);

	crystal->SetWorldPosition(fPos);

	crystal->LookToWorld(normal);
	//crystal->RotateWorldYPR({ 0,0,XM_PI });

	return crystal;
}
