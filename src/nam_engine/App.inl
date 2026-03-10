#pragma once
#include "App.h"
#include "Scene.h"
namespace nam
{
	template<typename T>
	T* App::CreateGameObject(Scene* scene)
	{
		return scene->CreateGameObject<T>();
	}

	template<typename T>
	T* App::CreateGameObject(u32 idScene)
	{
		return m_sceneManager.GetScene(idScene)->CreateGameObject<T>();
	}

	/*template<typename Component>
	void App::AddComponent(Entity& entity, const Component& data)
	{
		m_ecs.AddComponent(entity, data);
	}

	//template<typename Component>
	//void App::RemoveComponent()
	//{
	//	m_ecs.
	//}

	template<typename Component>
	const bool App::HasComponent(Entity& entity) const
	{
		return m_ecs.HasComponent(entity);
	}

	template<typename Component>
	Component& App::GetComponent(Entity& entity)
	{
		return m_ecs.GetComponent(entity);
	}*/

	template<typename System, typename... Args>
	void App::AddSystem(Args&&... args)
	{
		m_ecs.AddSystem<System>(std::forward<Args>(args)...);
	}

	//template<typename System>
	//void App::RemoveSystem()
	//{
	//	m_ecs.
	//}

	template<typename System>
	void App::SetSystemEnabled(const bool enabled)
	{
		m_ecs.SetSystemEnabled(enabled);
	}
}