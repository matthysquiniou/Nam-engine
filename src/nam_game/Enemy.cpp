#include "pch.h"
#include "Enemy.h"

#include "ParticleExplosion.h"

Enemy::Enemy()
{
	m_life = 1;
}

void Enemy::OnInit()
{
	m_afkTimer.Init(Rng::Float(0.2f,0.5f));
	m_lifeSpan.Init(1.f);

	m_life = 1;
	m_speed = 20.f;
	SetBehavior();
	SetTag((int)Tag::_Enemy);
}

void Enemy::OnStart()
{
}

void Enemy::OnUpdate()
{
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	XMFLOAT3 t = mp_target->GetWorldPosition();
	LookAtWorld(t);

	m_lifeSpan.Update(dt);

	if (m_lifeSpan.IsTargetReached())
	{
		m_lifeSpan.ResetProgress();

		m_speed *= 1.1f;
	}

	if (m_afkTimer.IsTargetReached())
	{
		if (mp_target)
		{
			MoveWorldForward(m_speed * dt);
		}
	}
	else
	{
		m_afkTimer.Update(dt);
	}

	if (m_life <= 0)
	{
		DestroyGameObject();
		return;
	}
}

void Enemy::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
}

void Enemy::OnDestroy()
{
	ParticleExplosion::Create(GetScene(), GetWorldPosition(), { 1, 0, 0 }, { 0.2f, 0, 0 }, 0.2f);
	IncreaseGameScore(5);
}

void Enemy::SetLife(int life)
{
	m_life = life;
}

void Enemy::SetScore(Score* score)
{
	m_score = score;
}

void Enemy::IncreaseGameScore(int add)
{
	m_score->IncreaseScore(add);
}

Score* Enemy::GetScore()
{
	return m_score;
}

void Enemy::SetTarget(GameObject* p_target)
{
	mp_target = p_target;
}

int Enemy::GetLife()
{
	return m_life;
}

void Enemy::RemoveHP(int amount)
{
	m_life -= amount;
}


