#include "pch.h"
#include "EnemySpawner.h"

#include "Enemy.h"
#include "TextureTags.h"

void EnemySpawner::OnInit()
{
	SetBehavior();

	m_spawnRate.Init(3.f);
	SetTag((int)Tag::_Other);

	mp_enemyMesh = App::Get()->CreateEmptyMesh();
	mp_enemyMesh->LoadObj(L"../../res/Assets/Bat/bat.obj");
	mp_enemyMesh->SetTexture(_Bat);
}

void EnemySpawner::OnStart()
{
	m_spawnRate.ResetProgress();
	m_waveCount = 0;

	m_amountPerSpawn = BEGIN_AMOUNT_SPAWN;
}

void EnemySpawner::OnUpdate()
{
	if (mp_ref == nullptr)
		return;

	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	XMFLOAT3 playerPos = mp_ref->GetWorldPosition();

	if (m_waveCount >= 3)
	{
		m_waveCount = 0;
		m_amountPerSpawn++;
		m_spawnRate.SetTargetTime(m_spawnRate.GetTargetTime() + 2.f);
	}

	m_spawnRate.Update(dt);

	if (m_spawnRate.IsTargetReached())
	{
		m_spawnRate.ResetProgress();

		for (size_t i = 0; i < m_amountPerSpawn; i++)
		{
			Enemy* p_enemy = GetScene()->CreateGameObject<Enemy>();

			MeshRendererComponent meshComp;
			float tall = 1.f;
			meshComp.SetMeshInstance(mp_enemyMesh);
			p_enemy->AddComponent(meshComp);

			Rng::Float(0, 1.f);

			float height = Rng::Float(0.f, 2.f);
			float angle = Rng::Float(0, XM_2PI);

			XMFLOAT3 pos = XMFLOAT3(cosf(angle) * m_radius, height, sinf(angle) * m_radius);
			XMFLOAT3 fPos;
			XMStoreFloat3(&fPos, XMVectorAdd(XMLoadFloat3(&pos), XMLoadFloat3(&playerPos)));
			float ran = Rng::Float(0.2f, 0.5f);
			XMFLOAT3 scale = XMFLOAT3(ran, ran, ran);

			p_enemy->SetLife(1);
			p_enemy->SetWorldPosition(fPos);
			p_enemy->SetWorldScale(scale);
			p_enemy->SetScore(mp_score);
			p_enemy->SetTarget(mp_ref);

			PhysicComponent pc;
			pc.m_useGravity = false;

			p_enemy->AddComponent(pc);
			p_enemy->SetSphereCollider();
			p_enemy->SetActiveEntity(true);
		}

		m_waveCount++;
	}
}

void EnemySpawner::OnDestroy()
{
}

void EnemySpawner::SetDatas(GameObject* p_ref, Score* p_score, float radius)
{
	mp_ref = p_ref;
	mp_score = p_score;
	m_radius = radius;
}
