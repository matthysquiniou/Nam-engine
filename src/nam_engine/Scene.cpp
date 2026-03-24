#include "pch.h"
#include "Scene.h"

namespace nam
{
//public
	Scene::Scene()
	{
		Init();
	}


	Scene::~Scene()
	{
		Destroy();
	}

	void Scene::Init()
	{
		mp_gameObjects = new SparseSet<GameObject*>(EcsConfig::MAX_ENTITIES);
		mp_ecs = &App::Get()->GetEcs();
		m_active = true;
	}

	void Scene::Start()
	{
		for (u32 entity : mp_gameObjects->GetEntities())
		{
			mp_gameObjects->Get(entity)->Start();
		}
	}

	void Scene::Destroy()
	{
		for (u32 entity : mp_gameObjects->GetEntities())
		{
			GameObject* gameObject = mp_gameObjects->Get(entity);
			gameObject->Destroy();
			delete gameObject;
		}

		delete mp_gameObjects;
	}

	void Scene::CleanUpdate()
	{
		if (m_gameObjectToDelete.empty())
			return;

		for (u32 entity : m_gameObjectToDelete)
		{
			GameObject* gameObject = mp_gameObjects->Get(entity);
			gameObject->Destroy();
			mp_gameObjects->Remove(entity);
			delete gameObject;
		}

		m_gameObjectToDelete.clear();
	}


	void Scene::SetActive(bool isActive)
	{
		m_active = isActive;
		for (u32 entity : mp_gameObjects->GetEntities())
		{
			GameObject* gameObject = mp_gameObjects->Get(entity);
			gameObject->SetActive(isActive);
		}
	}

	void Scene::Clear()
	{
		m_gameObjectToDelete = mp_gameObjects->GetEntities();
	}

	void Scene::DestroyGameObject(GameObject& gameObject)
	{
		m_gameObjectToDelete.push_back(gameObject.GetEntity().m_id);
	}
}


