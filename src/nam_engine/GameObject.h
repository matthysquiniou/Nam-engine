#pragma once

namespace nam
{
	class App;
	class Scene;

	class GameObject
	{
	private:
		Entity m_entity;
		Scene* mp_scene;
		int m_tag;

	public:

		GameObject();
		void Init(Scene* scene, Entity entity);
		void Start();
		void Update();
		void Collider(u32 self, u32 other, const CollisionInfo& collisionInfo);
		void Controller();

		virtual void OnInit();
		virtual void OnStart();
		virtual void OnUpdate();
		virtual void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo);
		virtual void OnController();
		virtual void OnDestroy();

		void SetActiveEntity(bool active);
		void DestroyGameObject();

		template<typename Component>
		void AddComponent(const Component& data);
		template<typename Component>
		const bool HasComponent();
		template<typename Component>
		Component& GetComponent();

		void SetBehavior();
		void SetBoxCollider();
		void SetSphereCollider();
		void SetController();

		Entity* GetEntity();
		Scene* GetScene();
	private:
		void Destroy();

		template<typename T>
		void SetFunctionUpdate(T* owner, void (T::* Update)());
		template<typename T>
		void SetBoxCollider(T* owner, void(T::* Collide)(u32 self, u32 other, const CollisionInfo& collisionInfo));
		template<typename T>
		void SetSphereCollider(T* owner, void(T::* Collide)(u32 self, u32 other, const CollisionInfo& collisionInfo));
		template<typename T>
		void SetController(T* owner, void(T::* Controller)());

		friend class App;
		friend class Scene;
	};
}

#include "GameObject.inl"