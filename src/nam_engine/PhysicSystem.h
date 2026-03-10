#pragma once
#include "ISystem.h"
namespace nam
{
	class PhysicSystem : public ISystem
	{
	private:
		float m_gravity = 0.1f;
	public:
		void Update(Ecs& ecs) override;
	};
}


