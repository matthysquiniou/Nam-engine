#pragma once
class Crystal : public GameObject
{
public:
	Crystal();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void TryAddLight();
	void SelectRandomMesh();

	static GameObject* Create(Scene* scene, const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& normal, float scale);
};

