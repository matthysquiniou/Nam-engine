#include "pch.h"
#include "LightManagerSystem.h"

#include "LightComponent.h"
#include "TransformComponent.h"

#include "Ecs.h"

#include <RenderManager.h>
#include <DataShader.h>

namespace nam
{
	void LightManagerSystem::Update(Ecs& ecs)
	{
		if (Render->IsFirstDraw())
			return;

		ecs.ForEach<LightComponent, TransformComponent>([&](uint32_t entity, LightComponent& lightComp, TransformComponent& transform)
		{
			transform.UpdateWorldData();

			Light* p_light = lightComp.mp_light;

			if (p_light == nullptr)
				return;

			p_light->SetByTransform(transform);
		});

		LightManager& lightManager = Render->GetLightManager();

		CBufferLights lights;
		lightManager.FillBufferLight(lights.m_lights);
		lights.lightsCount = lightManager.GetLightsCount();
		lights.m_ambientColor = DirectX::XMFLOAT3(1.f, 1.f, 1.f);

		Render->GetConstantBuffersDatas()->mp_lightCB->CopyData(0, lights);
	}
}
