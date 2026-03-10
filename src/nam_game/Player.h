#pragma once

#define OFFSET_CENTER_PARTICLE 1.f
#define INDEX_PARTICLE_PlAYER 0

#define SPEED_PLAYER 0.6f
#define SPEED_SHOT 25.f
#define LIFETIME_SHOT 1.f

struct TagPlayer {};

class Player : public GameObject
{
private:
	int m_currentRail;
	float m_disFormerNextRail;
	RailGenerator* m_railGenerator;
	GameObject* mp_particleEmitter;
	Score* m_score;
	Mesh* m_meshShot;

	int m_maxHp = 20;
	int m_hp = m_maxHp;

	float m_bulletSize = 0.1f;
	Timer m_unloadTimer = {};
public:
	Player();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;
	
	XMFLOAT3 MoveOnRail(float speed, XMFLOAT3 offsetPosition);

	static XMFLOAT3 GetNextPosOnRail(XMFLOAT3 posStart, XMFLOAT3 posEnd, XMFLOAT3 disMultiply, XMFLOAT3 offsetPosition);

	void ChangeCurrentRail(float dis, int idNextRail);

	void SetCurrentRail(int currentRail);
	int GetCurrentRail();

	void SetDisFormerNextRail(float disFormerNextRail);
	float GetDisFormerNextRail();

	void SetRailGenerator(RailGenerator* rg);
	RailGenerator* GetRailGenerator();

	void SetParticleEmitter(GameObject* particleEmitter);
	GameObject* GetParticleEmitter();

	void SetScore(Score* score);
	void IncreaseGameScore(int add);
	Score* GetScore();
  
	void SetMeshShot(Mesh* mesh);
	Mesh* GetMeshShot();

	bool HandleDeath();

private:
	void UpdateHpUI();
	void HandleShoot();
};
