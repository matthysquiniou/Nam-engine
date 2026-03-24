#pragma once

namespace nam
{
	template<typename T>
	inline T& SceneManager::CreateOrGetScene(size scene)
	{
		static_assert(std::is_base_of<Scene, T>::value, "T must derive from Scene");

		auto it = m_scenes.find(scene);

		if (it == m_scenes.end())
		{

			T* p_scene = new T();
			p_scene->Init();
			m_scenes.emplace(scene, p_scene);
			return *static_cast<T*>(p_scene);
		}
		else
		{
			return *static_cast<T*>(it->second);
		}
	}

}