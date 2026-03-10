#pragma once

class ParticleExplosion : public GameObject
{
public:
    DirectX::XMFLOAT3 m_startColor = { 0, 0, 0 };
    DirectX::XMFLOAT3 m_endColor = { 0, 0, 0 };

    Timer m_lifeTimer = {};

public:
    void OnInit() override;
    void OnStart() override;
    void OnUpdate() override;
    void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
    void OnDestroy() override;

    static void Create(Scene* p_scene, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 startColor, DirectX::XMFLOAT3 endColor, float lifeTime);
};
