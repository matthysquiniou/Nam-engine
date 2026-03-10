#pragma once
#include <GameObject.h>

class PauseObject : public GameObject
{
public:
	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;

	void FreezeTime();
	void UnFreezeTime();
};

