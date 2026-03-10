#include "pch.h"
#include "CameraComponent.h"
#include "App.h"
#include "Window.h"

namespace nam
{
	CameraComponent::CameraComponent(float fovY, float nearPlane, float farPlane)
	{
		m_fovY = fovY;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;

		UpdateAspectRatio();
	}
	void CameraComponent::UpdateAspectRatio(int clientWidth, int clientHeight)
	{
		if (clientWidth == -1 || clientHeight == -1 || clientHeight == 0)
		{
			Window& win = App::Get()->GetWindow();
			m_aspectRatio = (float)win.m_clientWidth / (float)win.m_clientHeight;
		}
		else
			m_aspectRatio = (float)clientWidth / (float)clientHeight;

		CalculateProj();
	}
	void CameraComponent::SetFov(float fovY)
	{
		m_fovY = fovY;
		CalculateProj();
	}
	void CameraComponent::SetNearPlane(float nearPlane)
	{
		m_nearPlane = nearPlane;
		CalculateProj();
	}
	void CameraComponent::SetFarPlane(float farPlane)
	{
		m_farPlane = farPlane;
		CalculateProj();
	}
	void CameraComponent::SetProperties(float fovY, float nearPlane, float farPlane)
	{
		m_fovY = fovY;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;

		CalculateProj();
	}
	void CameraComponent::CalculateProj()
	{
		DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(m_fovY, m_aspectRatio, m_nearPlane, m_farPlane);
		DirectX::XMStoreFloat4x4(&m_proj, proj);
	}
}

