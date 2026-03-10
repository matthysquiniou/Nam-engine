#pragma once

constexpr int BEGIN_AMOUNT_SPAWN = 2;

class EnemySpawner : public GameObject
{
	int m_amountPerSpawn = BEGIN_AMOUNT_SPAWN;
	Timer m_spawnRate = {};

	float m_radius = 0;

	int m_waveCount = 0;

	GameObject* mp_ref = nullptr;

	Mesh* mp_enemyMesh = nullptr;
	Score* mp_score = nullptr;
public:
	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	void SetDatas(GameObject* p_ref, Score* p_score, float radius);
};

