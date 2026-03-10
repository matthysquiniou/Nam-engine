#include "pch.h"
#include "Player.h"

#include "SceneTags.h"

#include "ParticleExplosion.h"

Player::Player()
{
	m_currentRail = 1;
	m_disFormerNextRail = 0;
}

void Player::OnInit()
{
	m_unloadTimer.Init(0.2f);
	SetBehavior();
	SetTag((int)Tag::_Player);
	AddComponent<TagPlayer>(TagPlayer());
}

void Player::OnStart()
{
	m_currentRail = 1;
	m_disFormerNextRail = 0;
	SetWorldPosition({ 0, 0, 0 });

	m_hp = m_maxHp;
}

void Player::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	XMFLOAT3 scalePlayer = GetWorldScale();
	float speed = SPEED_PLAYER * dt;

	XMFLOAT3 offsetOnRail = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 posPlayer = MoveOnRail(speed, offsetOnRail);
	SetWorldPosition(posPlayer);

	SceneManager& sm = App::Get()->GetSceneManager();

	UpdateHpUI();

	if (HandleDeath())
		return;

	HandleShoot();

	if (Input::IsKey('Z'))
	{
		MoveWorldForward(speed);
	}
	if (Input::IsKey('S'))
	{
		MoveWorldForward(-speed);
	}

	chrono.SetTimeWarp(1.f);

	if (Input::IsKey('A'))
	{
		chrono.SetTimeWarp(0.5f);
	}

	if (Input::IsKey(VK_SPACE))
	{
		XMFLOAT3 translation = { 0, speed, 0 };
		TranslateWorld(translation);
	}
	if (Input::IsKey(VK_LCONTROL))
	{
		XMFLOAT3 translation = { 0, -speed, 0 };
		TranslateWorld(translation);
	}

	if (Input::IsKeyDown(VK_LBUTTON))
	{
		XMFLOAT3 forward = GetWorldForward();
		XMFLOAT3 multiply = XMFLOAT3(2.f, 2.f, 2.f);
		XMFLOAT3 posShot;
		XMStoreFloat3(&posShot, XMVectorAdd((FXMVECTOR)XMVectorMultiply((FXMVECTOR)XMLoadFloat3(&forward), (FXMVECTOR)XMLoadFloat3(&multiply)), (FXMVECTOR)XMLoadFloat3(&posPlayer)));

		float bulletSize = 0.1f;

		Shot::CreateShot(GetScene(), posShot, GetWorldRotation(), XMFLOAT3(bulletSize, bulletSize, bulletSize), GetMeshShot(), SPEED_SHOT, LIFETIME_SHOT);
	}

	if (Input::IsKeyDown(VK_RSHIFT))
	{
		if (Scene* p_gameOver = sm.GetSceneByTag(_GameOverScene))
		{
			//TODO add a method to update the score from GameOverScene
			sm.SwitchCurrentScene(_CaveScene, _GameOverScene);
			p_gameOver->Start();

			GameOverScene* p_wrapped = WrappedSceneManager::Get<GameOverScene>();

			if (p_wrapped == nullptr)
				return;

			p_wrapped->UpdateScore(m_score->GetScore(), false);
		}
	}

	/*GameObject* gameObjectParticleEmitter = GetParticleEmitter();
	ParticleEmitersComponent& particleEmiters = gameObjectParticleEmitter->GetComponent<ParticleEmitersComponent>();
	particleEmiters.m_maxXYZ[INDEX_PARTICLE_PlAYER] = XMFLOAT3(posPlayer.x + OFFSET_CENTER_PARTICLE, posPlayer.y + OFFSET_CENTER_PARTICLE, posPlayer.z + OFFSET_CENTER_PARTICLE);
	particleEmiters.m_minXYZ[INDEX_PARTICLE_PlAYER] = XMFLOAT3(posPlayer.x - OFFSET_CENTER_PARTICLE, posPlayer.y - OFFSET_CENTER_PARTICLE, posPlayer.z - OFFSET_CENTER_PARTICLE);*/
}

void Player::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObject = App::Get()->GetGameObject(other);
	int tagOther = gameObject->GetTag();

	if (tagOther == (int)Tag::_Enemy)
	{
		m_hp--;

		gameObject->DestroyGameObject();

		return;
	}
}

void Player::OnDestroy()
{

}

XMFLOAT3 Player::MoveOnRail(float speed, XMFLOAT3 offsetPosition)
	{
	if (m_railGenerator == nullptr)
		return GetWorldPosition();
	XMFLOAT3 pos;
	UnMap<u64, Rail*>& allRails = m_railGenerator->GetMapRails();

	int nbCurrent = GetCurrentRail();
	int nbNext = nbCurrent + 1;
	if (nbCurrent > 0)
	{
		Rail* currentRail = allRails[nbCurrent];
		Rail* nextRail = allRails[nbNext];

		float scaleZ = currentRail->GetWorldScale().z;
		if (scaleZ == 0.f)
			scaleZ = 1.f;
		float dis = GetDisFormerNextRail() + speed / scaleZ;

		pos = GetNextPosOnRail(currentRail->GetWorldPosition(), nextRail->GetWorldPosition(), XMFLOAT3(dis, dis, dis), offsetPosition);
		pos.y += GetWorldScale().y * 2;
		ChangeCurrentRail(dis, nbNext);
	}
	else
	{
		pos = GetWorldPosition();
	}
	return pos;
}

XMFLOAT3 Player::GetNextPosOnRail(XMFLOAT3 posStart, XMFLOAT3 posEnd,  XMFLOAT3 disMultiply, XMFLOAT3 offsetPos)
{
	XMFLOAT3 pos;
	XMVECTOR posStartXM = XMLoadFloat3(&posStart);
	XMVECTOR posEndXM = XMLoadFloat3(&posEnd);
	XMVECTOR disStartEnd = XMVectorSubtract(posEndXM, posStartXM);
	XMVECTOR offsetPosXM = XMLoadFloat3(&offsetPos);
	XMStoreFloat3(&pos, XMVectorAdd((FXMVECTOR)offsetPosXM, XMVectorAdd((FXMVECTOR)posStartXM, XMVectorMultiply((FXMVECTOR)XMLoadFloat3(&disMultiply), (FXMVECTOR)disStartEnd))));
	//XMFLOAT3 forward;
	//XMStoreFloat3(&forward, XMVector3Normalize(disStartEnd));
	//LookToWorld(forward);
	return pos;
}

void Player::ChangeCurrentRail(float dis, int idNextRail)
{
	if (dis >= 1)
	{
		dis -= 1;
		SetCurrentRail(idNextRail);
	}
	SetDisFormerNextRail(dis);
}

void Player::SetParticleEmitter(GameObject* particleEmitter)
{
	mp_particleEmitter = particleEmitter;
}

GameObject* Player::GetParticleEmitter()
{
	return mp_particleEmitter;
}

void Player::SetCurrentRail(int currentRail)
{
	m_currentRail = currentRail;
}

int Player::GetCurrentRail()
{
	return m_currentRail;
}

void Player::SetDisFormerNextRail(float disFormerNextRail)
{
	m_disFormerNextRail = disFormerNextRail;
}

float Player::GetDisFormerNextRail()
{
	return m_disFormerNextRail;
}

void Player::SetRailGenerator(RailGenerator* rg)
{
	m_railGenerator = rg;
}

RailGenerator* Player::GetRailGenerator()
{
	return m_railGenerator;
}

void Player::SetScore(Score* score)
{
	m_score = score;
}

void Player::IncreaseGameScore(int add)
{
	m_score->IncreaseScore(add);
}

Score* Player::GetScore()
{
	return m_score;
}

void Player::SetMeshShot(Mesh* mesh)
{
	m_meshShot = mesh;
}

Mesh* Player::GetMeshShot()
{
	return m_meshShot;
}

bool Player::HandleDeath()
{
	SceneManager& sm = App::Get()->GetSceneManager();

	if (m_hp <= 0)
	{
		m_hp = 0;

		if (Scene* p_gameOver = sm.GetSceneByTag(_GameOverScene))
		{
			sm.SwitchCurrentScene(_CaveScene, _GameOverScene);
			p_gameOver->Start();

			GameOverScene* p_wrapped = WrappedSceneManager::Get<GameOverScene>();

			if (p_wrapped == nullptr)
				return false;

			p_wrapped->UpdateScore(m_score->GetScore(), true);

			return true;
		}
	}

	return false;
}

void Player::UpdateHpUI()
{
	CaveScene* p_cave = WrappedSceneManager::Get<CaveScene>();

	if (p_cave == nullptr)
		return;

	std::string txt = std::string("HP : ") + std::to_string(m_hp) + std::string("/") + std::to_string(m_maxHp);

	if(Text* p_text = p_cave->GetHpText())
		p_cave->GetHpText()->SetText(txt);
}

void Player::HandleShoot()
{
	if (Input::IsKeyDown(VK_LBUTTON))
	{
		XMFLOAT3 forward = GetWorldForward();
		XMFLOAT3 multiply = XMFLOAT3(1.f, 1.f, 1.f);
		XMFLOAT3 posShot;

		XMFLOAT3 playerPos = GetWorldPosition();

		XMStoreFloat3(&posShot, XMVectorAdd((FXMVECTOR)XMVectorMultiply((FXMVECTOR)XMLoadFloat3(&forward), (FXMVECTOR)XMLoadFloat3(&multiply)), (FXMVECTOR)XMLoadFloat3(&playerPos)));

		Shot::CreateShot(GetScene(), posShot, GetWorldRotation(), XMFLOAT3(m_bulletSize, m_bulletSize, m_bulletSize), GetMeshShot(), SPEED_SHOT, LIFETIME_SHOT);
	}
}
