#include "pch.h"
#include "ControllerSystem.h"
#include "ControllerComponent.h"

namespace nam
{
	void ControllerSystem::Update(Ecs& ecs)
	{
		Input::UpdateKeyStates();
		ecs.ForEach<ControllerComponent>([&](uint32_t entity, ControllerComponent& controller) {
			if (controller.OnController)
				controller.OnController();
		});
	}
}

