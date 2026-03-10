#pragma once
namespace nam
{
	class ControllerSystem : public ISystem
	{
	public:
		void Update(Ecs& ecs) override;
	};
}

