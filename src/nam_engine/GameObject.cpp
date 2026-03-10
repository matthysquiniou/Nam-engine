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
		mp_transform = nullptr;
		m_canDeleteMesh = false;
	}

	void GameObject::Init(Scene* scene, Entity entity)
	{
		App* app = App::Get();
		mp_scene = scene;
		m_entity = entity;
		m_canDeleteMesh = false;

		TransformComponent transform = TransformComponent();
		transform.SetWorldPosition(XMFLOAT3(0.f, 0.f, 0.f));
		AddComponent(transform);

		//save le component
		//mp_transform = &GetComponent<TransformComponent>();

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

//private
	void GameObject::Destroy()
	{
		OnDestroy();

		if (m_canDeleteMesh && HasComponent<MeshRendererComponent>())
		{
			MeshRendererComponent& meshRenderer = GetComponent<MeshRendererComponent>();
			meshRenderer.DeleteMeshInstance();
			
		}

		mp_scene->DestroyEntity(m_entity);
	}
//public

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

	void GameObject::SetWorldPosition(const XMFLOAT3& position)
	{
		GetComponent<TransformComponent>().SetWorldPosition(position);
	}

	XMFLOAT3 GameObject::GetWorldPosition()
	{
		return GetComponent<TransformComponent>().GetWorldPosition();
	}

	void GameObject::SetLocalPosition(const XMFLOAT3& position)
	{
		GetComponent<TransformComponent>().SetLocalPosition(position);
	}

	XMFLOAT3 GameObject::GetLocalPosition()
	{
		return GetComponent<TransformComponent>().GetLocalPosition();
	}

	void GameObject::SetWorldRotation(const XMFLOAT4& quat)
	{
		GetComponent<TransformComponent>().SetWorldRotation(quat);
	}

	XMFLOAT4 GameObject::GetWorldRotation()
	{
		return GetComponent<TransformComponent>().GetWorldRotation();
	}

	void GameObject::SetLocalRotation(const XMFLOAT4& quat)
	{
		GetComponent<TransformComponent>().SetLocalRotation(quat);
	}

	XMFLOAT4 GameObject::GetLocalRotation()
	{
		return GetComponent<TransformComponent>().GetLocalRotation();
	}

	void GameObject::SetWorldScale(const XMFLOAT3& scale)
	{
		GetComponent<TransformComponent>().SetWorldScale(scale);
	}

	XMFLOAT3 GameObject::GetWorldScale()
	{
		return GetComponent<TransformComponent>().GetWorldScale();
	}

	void GameObject::SetLocalScale(const XMFLOAT3& scale)
	{
		GetComponent<TransformComponent>().SetLocalScale(scale);
	}

	XMFLOAT3 GameObject::GetLocalScale()
	{
		return GetComponent<TransformComponent>().GetLocalScale();
	}

	void GameObject::SetLocalYaw(const float yaw)
	{
		GetComponent<TransformComponent>().SetLocalYPR(yaw, 0.f, 0.f);
	}

	void GameObject::SetLocalPitch(const float pitch)
	{
		GetComponent<TransformComponent>().SetLocalYPR(0.f, pitch, 0.f);
	}

	void GameObject::SetLocalRoll(const float roll)
	{
		GetComponent<TransformComponent>().SetLocalYPR(0.f, 0.f, roll);
	}

	void GameObject::SetLocalYPR(const float yaw, const float pitch, const float roll)
	{
		GetComponent<TransformComponent>().SetLocalYPR(yaw, pitch, roll);
	}

	void GameObject::SetLocalYPR(const XMFLOAT3& yawPitchRoll)
	{
		GetComponent<TransformComponent>().SetLocalYPR(yawPitchRoll.x, yawPitchRoll.y, yawPitchRoll.z);
	}

	XMFLOAT3 GameObject::GetLocalYPR()
	{
		XMFLOAT3 yawPitchRoll;
		GetComponent<TransformComponent>().GetLocalYPR(yawPitchRoll.x, yawPitchRoll.y, yawPitchRoll.z);
		return yawPitchRoll;
	}

	void GameObject::SetWorldYaw(const float yaw)
	{
		GetComponent<TransformComponent>().SetWorldYPR(yaw, 0.f, 0.f);
	}

	void GameObject::SetWorldPitch(const float pitch)
	{
		GetComponent<TransformComponent>().SetWorldYPR(0.f, pitch, 0.f);
	}

	void GameObject::SetWorldRoll(const float roll)
	{
		GetComponent<TransformComponent>().SetWorldYPR(0.f, 0.f, roll);
	}

	void GameObject::SetWorldYPR(const float yaw, const float pitch, const float roll)
	{
		GetComponent<TransformComponent>().SetWorldYPR(yaw, pitch, roll);
	}

	void GameObject::SetWorldYPR(const XMFLOAT3& yawPitchRoll)
	{
		GetComponent<TransformComponent>().SetWorldYPR(yawPitchRoll.x, yawPitchRoll.y, yawPitchRoll.z);
	}

	XMFLOAT3 GameObject::GetWorldYPR()
	{
		XMFLOAT3 yawPitchRoll;
		GetComponent<TransformComponent>().GetWorldYPR(yawPitchRoll.x, yawPitchRoll.y, yawPitchRoll.z);
		return yawPitchRoll;
	}

	void GameObject::AddChild(TransformComponent* transform)
	{
		GetComponent<TransformComponent>().AddChild(transform);
	}

	void GameObject::RemoveChild(TransformComponent* transform)
	{
		GetComponent<TransformComponent>().RemoveChild(transform);
	}

	const Vector<TransformComponent*>& GameObject::GetAllChild()
	{
		return GetComponent<TransformComponent>().GetChildren();
	}

	TransformComponent* GameObject::GetParent()
	{
		return GetComponent<TransformComponent>().GetParent();
	}

	XMFLOAT3 GameObject::GetWorldForward()
	{
		return GetComponent<TransformComponent>().GetWorldForward();
	}

	void GameObject::TranslateLocal(const XMFLOAT3& offset)
	{
		GetComponent<TransformComponent>().TranslateLocal(offset);
	}

	void GameObject::TranslateWorld(const XMFLOAT3& offset)
	{
		GetComponent<TransformComponent>().TranslateWorld(offset);
	}

	void GameObject::RotateLocalYPR(const float yaw, const float pitch, const float roll)
	{
		GetComponent<TransformComponent>().RotateLocalYPR(yaw, pitch, roll);
	}

	void GameObject::RotateLocalYPR(const DirectX::XMFLOAT3& yawPitchRoll)
	{
		GetComponent<TransformComponent>().RotateLocalYPR(yawPitchRoll.x, yawPitchRoll.y, yawPitchRoll.z);
	}

	void GameObject::RotateWorldYPR(const float yaw, const float pitch, const float roll)
	{
		GetComponent<TransformComponent>().RotateWorldYPR(yaw, pitch, roll);
	}

	void GameObject::RotateWorldYPR(const XMFLOAT3& yawPitchRoll)
	{
		GetComponent<TransformComponent>().RotateWorldYPR(yawPitchRoll.x, yawPitchRoll.y, yawPitchRoll.z);
	}

	void GameObject::MoveLocalForward(const float dis)
	{
		GetComponent<TransformComponent>().MoveLocalForward(dis);
	}

	void GameObject::MoveWorldForward(const float dis)
	{
		GetComponent<TransformComponent>().MoveWorldForward(dis);
	}

	void GameObject::MoveLocalTowards(const XMFLOAT3& target, const float dis)
	{
		GetComponent<TransformComponent>().MoveLocalTowards(target, dis);
	}

	void GameObject::MoveWorldTowards(const XMFLOAT3& target, const float dis)
	{
		GetComponent<TransformComponent>().MoveWorldTowards(target, dis);
	}

	void GameObject::LookToLocal(const XMFLOAT3& direction)
	{
		GetComponent<TransformComponent>().LookToLocal(direction);
	}

	void GameObject::LookToWorld(const XMFLOAT3& direction)
	{
		GetComponent<TransformComponent>().LookToWorld(direction);
	}

	void GameObject::LookAtLocal(const XMFLOAT3& target)
	{
		GetComponent<TransformComponent>().LookAtLocal(target);
	}

	void GameObject::LookAtWorld(const XMFLOAT3& target)
	{
		GetComponent<TransformComponent>().LookAtWorld(target);
	}

	void GameObject::SetMesh(Mesh& mesh)
	{
		if (HasComponent<MeshRendererComponent>() == false)
		{
			MeshRendererComponent meshRenderer;
			meshRenderer.SetMeshInstance(&mesh);

			AddComponent(meshRenderer);
		}
		else
		{
			MeshRendererComponent& meshRenderer = GetComponent<MeshRendererComponent>();
			meshRenderer.SetMeshInstance(&mesh);
		}
	}
  
	void GameObject::SetMesh(Mesh* mesh)
	{
		if (HasComponent<MeshRendererComponent>() == false)
		{
			MeshRendererComponent meshRenderer;
			meshRenderer.SetMeshInstance(mesh);

			AddComponent(meshRenderer);
		}
		else
		{
			MeshRendererComponent& meshRenderer = GetComponent<MeshRendererComponent>();
			meshRenderer.SetMeshInstance(mesh);
		}
	}

	void GameObject::ActiveDeleteMesh(bool isActive)
	{
		m_canDeleteMesh = isActive;
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

	Entity* GameObject::GetEntity()
	{
		return &m_entity;
	}

	Scene* GameObject::GetScene()
	{
		return mp_scene;
	}

	void GameObject::SetTag(int tag)
	{
		m_tag = tag;
	}

	bool GameObject::IsTag(int tag) const
	{
		return m_tag == tag;
	}

	int GameObject::GetTag() const
	{
		return m_tag;
	}

	TransformComponent* GameObject::GetTransform()
	{
		return mp_transform;
	}
}