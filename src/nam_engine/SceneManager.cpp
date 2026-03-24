#include "pch.h"
#include "SceneManager.h"
#include "App.h"

namespace nam
{
	SceneManager::SceneManager()
	{
		Init();
	}

	SceneManager::~SceneManager()
	{
		Destroy();
	}

	void SceneManager::Init()
	{
		mp_ecs = &App::Get()->GetEcs();
	}

	void SceneManager::Start()
	{
	}

	void SceneManager::Destroy()
	{
		for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			delete it->second;
		}
	}

	void SceneManager::CleanUpdate()
	{
		for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			it->second->CleanUpdate();
		}
	}

	void SceneManager::Clear()
	{
		for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
		{
			it->second->CleanUpdate();
		}
	}

	void SceneManager::ClearScene(size scene)
	{
		auto it = m_scenes.find(scene);
		if (it == m_scenes.end())
			return;
		it->second->Clear();
	}

	void SceneManager::SetActiveScene(size scene, bool active)
	{
		auto it = m_scenes.find(scene);
		if (it == m_scenes.end())
			return;
		it->second->SetActive(active);
	}

}



