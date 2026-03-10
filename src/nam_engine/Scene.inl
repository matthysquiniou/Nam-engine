#pragma once
#include "Scene.h"

namespace nam
{
	template<typename T>
	inline T* Scene::CreateGameObject(bool active)
	{
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		T* gameObject = new T();

		Entity entity = mp_ecs->CreateEntity();

		gameObject->Init(this, entity);
		gameObject->SetActiveEntity(active);

		int idEntity = entity.m_id;
		m_allGameObject[idEntity] = gameObject;
		(*mp_allGameObjectInAllScene)[idEntity] = gameObject;
		return gameObject;
	}

}