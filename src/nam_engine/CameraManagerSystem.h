#pragma once
#include "ISystem.h"

namespace nam
{
	class RenderManager;

	class CameraManagerSystem : public ISystem
	{
	public:
		void Update(Ecs& ecs) override;
		void Handle3D();
		void Handle2D();
	};
}

