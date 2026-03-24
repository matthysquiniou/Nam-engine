#pragma once
#include "SparseSet.h"

namespace nam
{
	class Ecs;
	class SceneManager;
	class GameObject;

	class Scene
	{
	private:
		SparseSet<GameObject*>* mp_gameObjects;
		Ecs* mp_ecs;
		Vector<u32> m_gameObjectToDelete;
		bool m_active;

	protected:
		Scene();
		virtual ~Scene();

	public:
		virtual void Init();
		virtual void Start();
		virtual void Destroy();

		void CleanUpdate();

		void SetActive(bool isActive);

		void Clear();

		template<typename T>
		T& CreateGameObject(bool active = true);

		void DestroyGameObject(GameObject& gameObject);

		friend class SceneManager;
		friend class GameObject;
	};
}
#include "Scene.inl"

