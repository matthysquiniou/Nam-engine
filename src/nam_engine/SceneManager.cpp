#include "pch.h"
#include "SceneManager.h"
#include "App.h"

namespace nam
{
	SceneManager::SceneManager()
	{
		m_idNext = 0;
		Init();
	}

	void SceneManager::Init()
	{
		if ((int)m_allScene.size() != 0)
		{
			DestroyAllScene();
		}
		m_idNext = 0;
	}

	void SceneManager::Start()
	{
		for (auto it = m_allScene.begin(); it != m_allScene.end(); it++)
		{
			it->second->Start();
		}
	}

	void SceneManager::CleanUpdate()
	{
		for (auto it = m_allScene.begin(); it != m_allScene.end(); it++)
		{
			it->second->CleanUpdate();
		}
	}

	void SceneManager::Destroy()
	{
		DestroyAllScene();
		m_idNext = 0;
	}

	void SceneManager::Reset()
	{
		Destroy();
		Init();
	}

	void SceneManager::AddCurrentScene(Scene* scene)
	{
		SetActiveScene(scene, true);
		m_allCurrentScenesByTag[scene->GetTag()] = scene;
		m_allCurrentScene[scene->GetId()] = scene;
	}

	void SceneManager::AddCurrentScene(u32 idScene)
	{
		Scene* scene = GetScene(idScene);
		_ASSERT(scene && "AddCurrentScene() : idScene a ete invalide");
		if (scene != nullptr)
		{
			AddCurrentScene(scene);
		}
	}

	void SceneManager::AddCurrentScene(size sceneTag)
	{
		Scene* scene = GetSceneByTag(sceneTag);
		_ASSERT(scene && "AddCurrentScene() : idScene a ete invalide");
		if (scene != nullptr)
		{
			AddCurrentScene(scene);
		}
	}

	void SceneManager::RemoveCurrentScene(Scene* scene)
	{
		SetActiveScene(scene, false);
		m_allCurrentScenesByTag.erase(scene->GetTag());
		m_allCurrentScene.erase(scene->GetId());
	}

	void SceneManager::RemoveCurrentScene(u32 idScene)
	{
		Scene* scene = GetScene(idScene);
		_ASSERT(scene && "RemoveCurrentScene() : idScene a ete invalide");
		if (scene != nullptr)
		{
			RemoveCurrentScene(scene);
		}
	}

	void SceneManager::RemoveCurrentScene(size sceneTag)
	{
		Scene* scene = GetSceneByTag(sceneTag);
		_ASSERT(scene && "RemoveCurrentScene() : idScene a ete invalide");
		if (scene != nullptr)
		{
			RemoveCurrentScene(scene);
		}
	}

	void SceneManager::SwitchCurrentScene(Scene* sceneClose, Scene* sceneOpen)
	{
		RemoveCurrentScene(sceneClose);
		AddCurrentScene(sceneOpen);
	}

	void SceneManager::SwitchCurrentScene(u32 idSceneClose, u32 idSceneOpen)
	{
		RemoveCurrentScene(idSceneClose);
		AddCurrentScene(idSceneOpen);
	}

	void SceneManager::SwitchCurrentScene(size sceneTag1, size sceneTag2)
	{
		RemoveCurrentScene(sceneTag1);
		AddCurrentScene(sceneTag2);
	}

	Scene* SceneManager::CreateScene(size sceneTag)
	{
		Scene* scene = new Scene();
		scene->SetId(m_idNext);
		scene->SetEcs(mp_ecs);
		scene->SetAllGameObjectInAllScene(&m_allGameObjectInAllScene);
		scene->m_tag = sceneTag;
		IncreaseIdNext();

		m_allScene[scene->GetId()] = scene;
		m_allSceneByTag[sceneTag] = scene;

		SetActiveScene(scene, false);
		return scene;
	}

	void SceneManager::DestroyScene(Scene* scene)
	{
		u32 id = scene->GetId();
		if (scene->GetIsActive())
		{
			m_allCurrentScene.erase(id);
		}
		m_allScene.erase(id);
		delete scene;
	}

//private

	void SceneManager::SetActiveScene(Scene* scene, bool active)
	{
		SetActiveScene(scene->GetId(), active);
	}

	void SceneManager::SetActiveScene(u32 idScene, bool active)
	{
		Scene* scene = GetScene(idScene);
		_ASSERT(scene && "ActiveScene() : idScene a ete invalide");
		if (scene != nullptr)
		{
			scene->SetIsActive(active);
		}
	}

	void SceneManager::SetActiveAllScene(bool active)
	{
		for (auto it = m_allScene.begin(); it != m_allScene.end(); it++)
		{
			it->second->SetIsActive(active);
		}
	}

	void SceneManager::DestroyAllScene()
	{
		for (auto it = m_allScene.begin(); it != m_allScene.end(); it++)
		{
			delete it->second;
		}
		m_allScene.clear();
	}

	void SceneManager::IncreaseIdNext()
	{
		m_idNext++;
	}

//public
	Scene* SceneManager::GetSceneByTag(size sceneTag)
	{
		auto it = m_allSceneByTag.find(sceneTag);
		if (it != m_allSceneByTag.end())
		{
			return it->second;
		}

		return nullptr;
	}

	Scene* SceneManager::GetScene(u32 idScene)
	{
		auto it = m_allScene.find(idScene);
		if (it != m_allScene.end())
		{
			return it->second;
		}
		return nullptr;
	}

	GameObject* SceneManager::GetGameObjectInGame(Entity& entity)
	{
		auto it = m_allGameObjectInAllScene.find(entity.m_id);
		if (it != m_allGameObjectInAllScene.end())
		{
			return it->second;
		}
		return nullptr;
	}

	GameObject* SceneManager::GetGameObjectInGame(u32 idEntity)
	{
		auto it = m_allGameObjectInAllScene.find(idEntity);
		if (it != m_allGameObjectInAllScene.end())
		{
			return it->second;
		}
		return nullptr;
	}

	const UnMap<u32, Scene*>& SceneManager::GetAllScene() const
	{
		return m_allScene;
	}

	const UnMap<u32, GameObject*>& SceneManager::GetAllGameObjectInAllScene() const
	{
		return m_allGameObjectInAllScene;
	}

	const UnMap<u32, Scene*>& SceneManager::GetCurrentScenes() const
	{
		return m_allCurrentScene;
	}

	const UnMap<size, Scene*>& SceneManager::GetCurrentScenesByTag() const
	{
		return m_allCurrentScenesByTag;
	}

	void SceneManager::SetEcs(Ecs* ecs)
	{
		mp_ecs = ecs;
	}

	SceneManager::~SceneManager()
	{
		Destroy();
	}
}



