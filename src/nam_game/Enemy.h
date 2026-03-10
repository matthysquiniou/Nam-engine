#pragma once

#define DEFORMATION 0.5f

class Enemy : public GameObject
{
private:
	Score* m_score = nullptr;
	int m_life = -1;
	float m_speed = 0.f;

	Timer m_afkTimer = {};
	Timer m_lifeSpan = {};

	GameObject* mp_target = nullptr;
public:
	Enemy();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void SetScore(Score* score);
	void IncreaseGameScore(int add);
	Score* GetScore();

	void SetTarget(GameObject* p_target);
	
	void SetLife(int life);
	int GetLife();

	void RemoveHP(int amount);
};

#include "Enemy.inl"

