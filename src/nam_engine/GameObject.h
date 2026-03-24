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
		Ecs* mp_ecs;

	public:

		GameObject();
		void Init(Scene* scene, Entity entity);
		void Start();

		void Update();// behaviorComponent

		void Collider(const SingleCollisionInfo& self, const SingleCollisionInfo& other); // colliderComponent

		void Controller();// controllerComponent

		// buttonComponent
		void Hovered();
		void Click();
		void Left();

		virtual void OnInit();
		virtual void OnStart();
		virtual void OnDestroy();

		virtual void OnUpdate(); // behaviorComponent
		virtual void OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other); // colliderComponent
		virtual void OnController(); // controllerComponent

		// buttonComponent
		virtual void OnHovered(); 
		virtual void OnClick();
		virtual void OnLeft();

		void SetActive(bool active);

		template<typename Component>
		void AddComponent(const Component& data);
		template<typename Component>
		const bool HasComponent();
		template<typename Component>
		Component& GetComponent();

		BehaviorComponent& SetBehavior();
		BoxColliderComponent& SetBoxCollider();
		SphereColliderComponent& SetSphereCollider();
		ControllerComponent& SetController();
		ButtonComponent& SetButton();

		Entity GetEntity();
		Scene* GetScene();
	private:
		void Destroy();

		template<typename T>
		BehaviorComponent& SetFunctionUpdate(T* owner, void (T::* Update)());
		template<typename T>
		BoxColliderComponent& SetBoxCollider(T* owner, void(T::* Collide)(const SingleCollisionInfo& self, const SingleCollisionInfo& other));
		template<typename T>
		SphereColliderComponent& SetSphereCollider(T* owner, void(T::* Collide)(const SingleCollisionInfo& self, const SingleCollisionInfo& other));
		template<typename T>
		ControllerComponent& SetController(T* owner, void(T::* Controller)());
		template<typename T>
		ButtonComponent& SetButton(T* owner);

		friend class App;
		friend class Scene;
	};
}

#include "GameObject.inl"