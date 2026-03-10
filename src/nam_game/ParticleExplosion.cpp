#include "pch.h"
#include "ParticleExplosion.h"

#include <ParticleEmitersComponent.h>

void ParticleExplosion::OnInit()
{
	SetTag((int)Tag::_Particles);
}

void ParticleExplosion::OnStart()
{
	if (HasComponent<ParticleEmitersComponent>())
		return;

	ParticleEmitersComponent peComp;
	peComp.AddEmiter({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }, { -1, -1, -1 }, m_startColor, m_endColor, 2.f, 1.f, 1.f, 10'000.f);

	AddComponent(peComp);
}

void ParticleExplosion::OnUpdate()
{
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	m_lifeTimer.Update(dt);

	if (m_lifeTimer.IsTargetReached())
	{
		DestroyGameObject();
	}
}

void ParticleExplosion::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
}

void ParticleExplosion::OnDestroy()
{
}

void ParticleExplosion::Create(Scene* p_scene, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 startColor, DirectX::XMFLOAT3 endColor, float lifeTime)
{
	ParticleExplosion* p = p_scene->CreateGameObject<ParticleExplosion>();

	p->m_lifeTimer.Init(lifeTime);
	p->m_startColor = startColor;
	p->m_endColor = endColor;

	p->SetWorldPosition(pos);
	p->SetActiveEntity(true);
	p->SetBehavior();

	p->OnStart();
}
