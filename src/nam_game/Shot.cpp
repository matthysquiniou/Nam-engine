#include "pch.h"
#include "Shot.h"

Shot::Shot()
{
	m_speed = 1;
	m_time = {};
}

void Shot::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Shot);
}

void Shot::OnStart()
{
	m_time.Init(LIFETIME_SHOT, true, false);
	SetActiveEntity(true);
}

void Shot::OnUpdate()
{
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();
	m_time.Update(dt);
	MoveWorldForward(GetSpeed() * dt);
	if (m_time.IsTargetReached())
	{
		DestroyGameObject();
	}
}

void Shot::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObject = App::Get()->GetGameObject(other);
	int tagOther = gameObject->GetTag();

	if (tagOther == (int)Tag::_Enemy)
	{
		Enemy* p_enemy = (Enemy*)gameObject;

		p_enemy->RemoveHP(1);

		DestroyGameObject();
	}
}

void Shot::OnDestroy()
{

}

void Shot::SetSpeed(const float speed)
{
	m_speed = speed;
}

float Shot::GetSpeed()
{
	return m_speed;
}

void Shot::SetLifeTime(const float time)
{
	m_time.SetTargetTime(time);
}

float Shot::GetLifeTimeProgress()
{
	return m_time.GetProgress();
}

Timer* Shot::GetTimer()
{
	return &m_time;
}

Shot* Shot::CreateShot(Scene* scene, const XMFLOAT3& position, const XMFLOAT4& rotation, const XMFLOAT3& scale, Mesh* mesh, const float speed, const float lifeTime)
{
	Shot* shot = App::Get()->CreateGameObject<Shot>(scene);
	shot->SetWorldPosition(position);
	shot->SetWorldRotation(rotation);
	shot->SetWorldScale(scale);
	shot->SetMesh(mesh);
	shot->SetSpeed(speed);
	shot->SetLifeTime(lifeTime);
	shot->SetSphereCollider();
	shot->SetMesh(mesh);
	shot->Start();
	return shot;
}

Shot* Shot::CreateShot(Scene* scene, const XMFLOAT3& position, TransformComponent& rotation, const XMFLOAT3& scale, Mesh* mesh, const float speed, const float lifeTime)
{
	return Shot::CreateShot(scene, position, rotation.GetWorldRotation(), scale, mesh, speed, lifeTime);
}


