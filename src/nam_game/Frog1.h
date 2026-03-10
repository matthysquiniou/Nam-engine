#pragma once
class Frog1 : public nam::GameObject
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(nam::u32 self, nam::u32 other, const nam::CollisionInfo& collisionInfo) override;
};

