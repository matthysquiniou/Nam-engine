#pragma once

class Shot : public GameObject
{
private:
	float m_speed;
	Timer m_time;
public:
	Shot();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void SetSpeed(const float speed);
	float GetSpeed();

	void SetLifeTime(const float time);
	float GetLifeTimeProgress();
	Timer* GetTimer();

	static Shot* CreateShot(Scene* scene, const XMFLOAT3& position, const XMFLOAT4& rotation, const XMFLOAT3& scale, Mesh* mesh, const float speed, const float lifeTime);
	static Shot* CreateShot(Scene* scene, const XMFLOAT3& position, TransformComponent& transform, const XMFLOAT3& scale, Mesh* mesh, const float speed, const float lifeTime);
};