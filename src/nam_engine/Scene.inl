#pragma once
#include "Scene.h"

namespace nam
{
	template<typename T>
	inline T& Scene::CreateGameObject(bool active)
	{
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		T* gameObject = new T();

		Entity entity = mp_ecs->CreateEntity();

		gameObject->Init(this, entity);
		gameObject->SetActive(active);

		u32 idEntity = entity.m_id;
		mp_gameObjects->Add(idEntity, gameObject);
		return *static_cast<T*>(gameObject);
	}

}