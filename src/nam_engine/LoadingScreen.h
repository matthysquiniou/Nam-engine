#pragma once
#include "GameObject.h"
#include <BaseTypes.h>
#include <Timer.h>

namespace nam
{
	class LoadingScreen : public GameObject
	{
	public:
		bool m_spawn = true;

		Timer m_waitingTimer = {};
		Timer m_fadingTimer = {};
		float m_fadingSpeed = 1.f;

	public:
		void OnInit() override;
		void OnUpdate() override;

		void Activate(float minTimeToWait);
	};
}

