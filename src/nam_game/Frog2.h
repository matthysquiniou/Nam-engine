#pragma once
class Frog2 : public nam::GameObject
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(nam::u32 self, nam::u32 other, const nam::CollisionInfo& collisionInfo) override;
};

