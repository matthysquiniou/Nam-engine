#pragma once
struct CameraTag
{
};

class Camera : public nam::GameObject
{
private:
	nam::GameObject* entityToFollow = nullptr;
public:
	void OnInit() override;
	void OnUpdate() override;
};

