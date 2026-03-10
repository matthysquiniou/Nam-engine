#include "pch.h"
#include "Scene.h"

namespace nam
{
//public
	Scene::Scene()
	{
		m_id = 0;
		mp_ecs = nullptr;
		m_isActive = false;
		Init();
	}

	void Scene::Init()
	{
		m_isActive = true;

		if ((int)m_allEntityActiveFalse.size() != 0)
		{
			m_allEntityActiveFalse.clear();
		}

		if ((int)m_allGameObject.size() != 0)
		{
			for (auto it = m_allGameObject.begin(); it != m_allGameObject.end(); it++)
			{
				m_allGameObject.erase(it->second->GetEntity()->m_id);
			}
			m_allGameObject.clear();
		}
	}

	void Scene::Start()
	{
		for (auto it = m_allGameObject.begin(); it != m_allGameObject.end(); it++)
		{
			it->second->Start();
		}
	}

	void Scene::CleanUpdate()
	{
		if(m_allGameObjectToDestroy.empty() == false)
		{
			for (auto it = m_allGameObjectToDestroy.begin(); it != m_allGameObjectToDestroy.end(); it++)
			{
				GameObject* gameObject = it->second;
				int idEntity = gameObject->GetEntity()->m_id;
				gameObject->Destroy();
				m_allGameObject.erase(idEntity);
				mp_allGameObjectInAllScene->erase(idEntity);
				delete gameObject;
			}
			m_allGameObjectToDestroy.clear();
		}
	}

	void Scene::Destroy()
	{
		DestroyAllGameObject();
		m_allEntityActiveFalse.clear();
	}

	void Scene::ResetScene()
	{
		Destroy();
		Init();
	}

	void Scene::DestroyGameObject(GameObject* gameObject)
	{
		u32 idEntity = gameObject->GetEntity()->m_id;
		auto it = m_allGameObjectToDestroy.find(idEntity);
		if (it == m_allGameObjectToDestroy.end())
		{
			m_allGameObjectToDestroy[idEntity] = gameObject;
		}
	}

	void Scene::SetActiveEntity(Entity& entity, bool active)
	{
		mp_ecs->SetEntityActive(entity, active);
		if (active)
		{
			//entity SetActive true
			m_allEntityActiveFalse.erase(entity.m_id);
		}
		else
		{
			//entity SetActive false
			m_allEntityActiveFalse[entity.m_id] = entity;
		}
	}

	void Scene::SetActiveAllEntity(bool active)
	{
		for (auto it = m_allGameObject.begin(); it != m_allGameObject.end(); it++)
		{
			GameObject* gameObject = it->second;
			mp_ecs->SetEntityActive(*gameObject->GetEntity(), active);
		}
	}

//protected

	void Scene::DestroyEntity(Entity& entity)
	{
		uint32_t id = entity.m_id;
		if (mp_ecs->IsEntityActive(id) == false)
		{
			m_allEntityActiveFalse.erase(id);
		}
		mp_ecs->DestroyEntity(entity);
	}

	void Scene::DestroyAllGameObject()
	{
		for (auto it = m_allGameObject.begin(); it != m_allGameObject.end(); it++)
		{
			DestroyGameObject(it->second);
		}
	}

	void Scene::SetAllGameObjectInAllScene(UnMap<u32, GameObject*>* allGameObjectInAllScene)
	{
		mp_allGameObjectInAllScene = allGameObjectInAllScene;
	}

//private

	void Scene::SetIsActive(bool isActive)
	{
		m_isActive = isActive;
		SetActiveAllEntity(isActive);
	}

//public

	const Entity Scene::GetEntity(uint32_t idEntity)
	{;
		auto it = m_allGameObject.find(idEntity);
		if (it != m_allGameObject.end())
			return *(it->second->GetEntity());
		return Entity();
	}

	GameObject* Scene::GetGameObject(Entity& entity)
	{
		auto it = m_allGameObject.find(entity.m_id);
		if (it != m_allGameObject.end())
			return it->second;
		return nullptr;
	}

	GameObject* Scene::GetGameObject(uint32_t idEntity)
	{
		auto it = m_allGameObject.find(idEntity);
		if (it != m_allGameObject.end())
			return it->second;
		return nullptr;
	}

	const UnMap<u32, GameObject*>& Scene::GetAllGameObject() const
	{
		return m_allGameObject;
	}

	void Scene::SetId(u32 id)
	{
		m_id = id;
	}

	u32 Scene::GetId() const
	{
		return m_id;
	}

	void Scene::SetEcs(Ecs* ecs)
	{
		mp_ecs = ecs;
	}

	/*Ecs* Scene::GetEcs()
	{
		return mp_ecs;
	}*/

	bool Scene::GetIsActive() const
	{
		return m_isActive;
	}

	const size& Scene::GetTag() const
	{
		return m_tag;
	}

	Scene::~Scene()
	{
		SetActiveAllEntity(false);
		Destroy();
	}

	

}


