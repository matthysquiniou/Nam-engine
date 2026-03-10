#pragma once

class Rail : public GameObject
{
private:

public:
	Rail();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
};