#include "pch.h"
#include "CameraManagerSystem.h"

#include "RenderManager.h"

#include "TransformComponent.h"
#include "CameraComponent.h"

#include "DataShader.h"
#include "Entity.h"
#include "App.h"

namespace nam
{
	void CameraManagerSystem::Update(Ecs& ecs)
	{
		// 3D
		Handle3D();

		// 2D
		Handle2D();
	}

	void CameraManagerSystem::Handle3D()
	{
		GameObject* pGameObjectCam = App::Get()->GetCamera();

		if (pGameObjectCam == nullptr)
			return;

		TransformComponent& camTransform = pGameObjectCam->GetComponent<TransformComponent>();
		camTransform.UpdateWorldData();

		CameraComponent& cam = pGameObjectCam->GetComponent<CameraComponent>();

		CBufferViewProj3D viewProj;
		viewProj.m_cameraPos = camTransform.GetWorldPosition();

		DirectX::XMMATRIX camWorld = XMLoadFloat4x4(&camTransform.GetWorldMatrix());
		DirectX::XMMATRIX viewMat = XMMatrixInverse(nullptr, camWorld); // view = inverse of world

		XMStoreFloat4x4(&viewProj.m_view, XMMatrixTranspose(viewMat));

		DirectX::XMStoreFloat4x4(&viewProj.m_proj, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&cam.m_proj)));
		viewProj.time = static_cast<float>(App::Get()->GetChrono().GetScaledTotalTime());
		viewProj.deltaTime = static_cast<float>(App::Get()->GetChrono().GetScaledDeltaTime());

		Render->GetConstantBuffersDatas()->mp_viewProjCB->CopyData(0, viewProj);
	}

	void CameraManagerSystem::Handle2D()
	{
		Window* p_window = Render->GetWindow();

		DirectX::XMFLOAT2 windowSize = { (float)p_window->m_clientWidth, (float)p_window->m_clientHeight };

		if (windowSize.x <= 0 || windowSize.y <= 0)
			return;

		CBufferOrtho2D proj;
		DirectX::XMMATRIX ortho = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, windowSize.x, windowSize.y, 0.0f, 0.0f, 1.0f);

		DirectX::XMStoreFloat4x4(&proj.m_ortho, DirectX::XMMatrixTranspose(ortho));
		proj.time = static_cast<float>(App::Get()->GetChrono().GetScaledTotalTime());

		Render->GetConstantBuffersDatas()->mp_orthoCB->CopyData(0, proj);
	}
}