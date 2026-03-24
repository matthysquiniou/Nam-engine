#pragma once
#include "GameObject.h"

namespace nam
{
	template<typename Component>
	void GameObject::AddComponent(const Component& data)
	{
		return App::Get()->m_ecs.AddComponent(m_entity, data);
	}

	template<typename Component>
	const bool GameObject::HasComponent()
	{
		return App::Get()->m_ecs.HasComponent<Component>(m_entity);
	}

	template<typename Component>
	Component& GameObject::GetComponent()
	{
		return App::Get()->m_ecs.GetComponent<Component>(m_entity);
	}

	template<typename T>
	inline BehaviorComponent& GameObject::SetFunctionUpdate(T* owner, void(T::* Update)())
	{
		if (HasComponent<BehaviorComponent>() == false)
		{
			BehaviorComponent behavior;
			behavior.Update = [owner, Update]() {
				(owner->*Update)();
				};
			AddComponent(behavior);
		}
		else
		{
			BehaviorComponent& behavior = GetComponent<BehaviorComponent>();
			behavior.Update = [owner, Update]() {
				(owner->*Update)();
				};
		}
		return GetComponent<BehaviorComponent>();
	}

	template<typename T>
	inline BoxColliderComponent& GameObject::SetBoxCollider(T* owner, void(T::* Collide)(const SingleCollisionInfo& self, const SingleCollisionInfo& other))
	{
		if (HasComponent<BoxColliderComponent>() == false)
		{
			BoxColliderComponent boxCollider;
			boxCollider.OnCollision = [owner, Collide](const SingleCollisionInfo& self, const SingleCollisionInfo& other) {
				(owner->*Collide)(self, other);
				};

			AddComponent(boxCollider);
		}
		else
		{
			BoxColliderComponent& boxCollider = GetComponent<BoxColliderComponent>();
			boxCollider.OnCollision = [owner, Collide](const SingleCollisionInfo& self, const SingleCollisionInfo& other) {
				(owner->*Collide)(self, other);
				};
		}
		return GetComponent<BoxColliderComponent>();
	}

	template<typename T>
	inline SphereColliderComponent& GameObject::SetSphereCollider(T* owner, void(T::* Collide)(const SingleCollisionInfo& self, const SingleCollisionInfo& other))
	{
		if (HasComponent<BoxColliderComponent>() == false)
		{
			SphereColliderComponent sphereCollider;
			sphereCollider.OnCollision = [owner, Collide](const SingleCollisionInfo& self, const SingleCollisionInfo& other) {
				(owner->*Collide)(self, other);
				};

			AddComponent(sphereCollider);
		}
		else
		{
			SphereColliderComponent& sphereCollider = GetComponent<SphereColliderComponent>();
			sphereCollider.OnCollision = [owner, Collide](const SingleCollisionInfo& self, const SingleCollisionInfo& other) {
				(owner->*Collide)(self, other);
				};
		}
		return GetComponent<SphereColliderComponent>();
	}
	template<typename T>
	inline ControllerComponent& GameObject::SetController(T* owner, void(T::* Controller)())
	{
		if (HasComponent<ControllerComponent>() == false)
		{
			ControllerComponent controller;
			controller.OnController = [owner, Controller]() {
				(owner->*Controller)();
				};
			AddComponent(controller);
		}
		else
		{
			ControllerComponent& controller = GetComponent<ControllerComponent>();
			controller.OnController = [owner, Controller]() {
				(owner->*Controller)();
				};
		}
		return GetComponent<ControllerComponent>();
	}

	template<typename T>
	inline ButtonComponent& GameObject::SetButton(T* owner)
	{
		auto click = &GameObject::Click;
		auto hover = &GameObject::Hovered;
		auto left = &GameObject::Left;

		if (HasComponent<ButtonComponent>() == false)
		{
			ButtonComponent button;

			button.OnClick = [owner, click]() {
				(owner->*click)();
				};
			button.OnHovered = [owner, hover]() {
				(owner->*hover)();
				};
			button.OnLeft = [owner, left]() {
				(owner->*left)();
				};
			AddComponent(button);
		}
		else
		{
			ButtonComponent button;

			button.OnClick = [owner, click]() {
				(owner->*click)();
				};
			button.OnHovered = [owner, hover]() {
				(owner->*hover)();
				};
			button.OnLeft = [owner, left]() {
				(owner->*left)();
				};
		}
		return GetComponent<ButtonComponent>();
	}
}