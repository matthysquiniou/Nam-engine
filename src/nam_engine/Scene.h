#pragma once



namespace nam
{
	class Ecs;
	class SceneManager;
	class GameObject;

	class Scene
	{
	private:
		Ecs* mp_ecs;
		UnMap<u32, GameObject*> m_allGameObject;
		UnMap<u32, Entity> m_allEntityActiveFalse;
		UnMap<u32, GameObject*>* mp_allGameObjectInAllScene;
		UnMap<u32, GameObject*> m_allGameObjectToDestroy;
		uint32_t m_id;
		bool m_isActive;

		size m_tag = -1;
	private:
		Scene();

	public:

		virtual void Init();

		virtual void Start();

		virtual void CleanUpdate();

		virtual void Destroy();

		void ResetScene();

		template<typename T>
		T* CreateGameObject(bool active = true);

		void DestroyGameObject(GameObject* gameObject);

		void SetActiveEntity(Entity& entity, bool active);

		void SetActiveAllEntity(bool active);

	protected:

		void DestroyEntity(Entity& entity);
		void DestroyAllGameObject();

		void SetAllGameObjectInAllScene(UnMap<u32, GameObject*>* allGameObjectInAllScene);

	public:

		const Entity GetEntity(uint32_t idEntity);
		GameObject* GetGameObject(Entity& entity);
		GameObject* GetGameObject(uint32_t idEntity);

		const UnMap<u32, GameObject*>& GetAllGameObject() const;

		void SetId(u32 id);
		u32 GetId() const;

		void SetEcs(Ecs* ecs);
		//Ecs* GetEcs();

		bool GetIsActive() const;
		const size& GetTag() const;

		virtual ~Scene();

	private:

		void SetIsActive(bool isActive);

		friend class SceneManager;
		friend class GameObject;

	};
}
#include "Scene.inl"

