#include "pch.h"
#include "GameObject.h"

using namespace DirectX;

namespace nam
{
	GameObject::GameObject()
	{
		mp_scene = nullptr;
		m_entity = Entity();
		m_tag = -1;
	}

	void GameObject::Init(Scene* scene, Entity entity)
	{
		mp_scene = scene;
		m_entity = entity;
		OnInit();
	}

	void GameObject::Start()
	{
		OnStart();
	}

	void GameObject::Update()
	{
		OnUpdate();
	}

	void GameObject::Collider(u32 self, u32 other, const CollisionInfo& collisionInfo)
	{
		OnCollision(self, other, collisionInfo);
	}

	void GameObject::Controller()
	{
		OnController();
	}

	void GameObject::Destroy()
	{
		OnDestroy();
		mp_scene->DestroyEntity(m_entity);
	}

	void GameObject::OnInit()
	{
	}

	void GameObject::OnStart()
	{
	}

	void GameObject::OnUpdate()
	{
	}

	void GameObject::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
	{
	}

	void GameObject::OnController()
	{
	}

	void GameObject::OnDestroy()
	{
	}

	void GameObject::SetActiveEntity(bool active)
	{
		mp_scene->SetActiveEntity(m_entity, active);
	}

	void GameObject::DestroyGameObject()
	{
		mp_scene->DestroyGameObject(this);
	}

	void GameObject::SetBehavior()
	{
		SetFunctionUpdate(this, &GameObject::Update);
	}

	void GameObject::SetBoxCollider()
	{
		SetBoxCollider(this, &GameObject::Collider);
	}

	void GameObject::SetSphereCollider()
	{
		SetSphereCollider(this, &GameObject::Collider);
	}

	void GameObject::SetController()
	{
		SetController(this, &GameObject::Controller);
	}

	Entity* GameObject::GetEntity()
	{
		return &m_entity;
	}

	Scene* GameObject::GetScene()
	{
		return mp_scene;
	}
}