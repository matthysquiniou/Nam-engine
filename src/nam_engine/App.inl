#pragma once
#include "App.h"
#include "Scene.h"

namespace nam
{
	template<typename System, typename... Args>
	inline void App::AddSystem(Args&&... args)
	{
		m_ecs.AddSystem<System>(std::forward<Args>(args)...);
	}

	template<typename System>
	inline void App::SetSystemEnabled(const bool enabled)
	{
		m_ecs.SetSystemEnabled(enabled);
	}

	template<typename T>
	inline T& App::CreateGameObject(size scene, bool active)
	{
		return m_sceneManager.CreateOrGetScene<Scene>(scene).CreateGameObject<T>(active);
	}

	template<typename T>
	inline T& App::CreateOrGetScene(size scene)
	{
		return m_sceneManager.CreateOrGetScene<T>(scene);
	}
}