#pragma once
#include <FrameworkCore.h>
namespace nam
{
	class Ecs;
	class Scene;
	class GameObject;

	class SceneManager final
	{
	private:
		UnMap<size, Scene*> m_scenes;
		Ecs* mp_ecs;

	public:
		SceneManager();
		~SceneManager();

		void Init();
		void Start();
		void Destroy();

		void CleanUpdate();

		void Clear();

		template<typename T>
		T& CreateOrGetScene(size scene);
		void ClearScene(size scene);
		void SetActiveScene(size scene, bool active);

	private:
		friend class Scene;
	};
}

#include "SceneManager.inl"

