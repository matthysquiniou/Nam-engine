#pragma once

class FPSDisplayer : public GameObject
{
private:
	Timer m_refreshTimer;
	TextRendererComponent* mp_textRender;
public:
	FPSDisplayer();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	Timer* GetTimer();
};

