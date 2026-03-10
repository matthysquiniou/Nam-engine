#include "pch.h"
#include "Camera.h"

#include "SceneTags.h"

Camera::Camera()
{
	m_debugMode = false;
	m_rotateMode = false;
	mp_appCamera = nullptr;
	mp_target = nullptr;
}

void Camera::OnInit()
{
	mp_appCamera = nullptr;
	SetBehavior();
	SetTag((int)Tag::_Camera);
}

void Camera::OnStart()
{
	m_debugMode = false;
	m_rotateMode = true;
}

void Camera::OnUpdate()
{
	App* app = App::Get();

	SceneManager& sm = app->GetSceneManager();

	auto it = sm.GetCurrentScenes().find(sm.GetSceneByTag(_PauseScene)->GetId());

	if (it != sm.GetCurrentScenes().end())
	{
		Input::ShowMouse();
		return;
	}

	float dt = app->GetChrono().GetScaledDeltaTime();

	GameObject* appCamera = app->GetCamera();
	bool debugMode = GetDebugMode();
	bool rotateMode = GetRotateMode();

	if (debugMode)
	{
		//'Z' 'S' VK_UP VK_DOWN VK_SPACE VK_LCONTROL
		if (Input::IsKey('Z')) { MoveForward(CAMERA_SPEED_MOVE * dt); }
		if (Input::IsKey('S')) { MoveForward(-CAMERA_SPEED_MOVE * dt); }

		if (Input::IsKey(VK_SPACE)) { XMFLOAT3 translation = { 0, CAMERA_SPEED_UP * dt, 0 }; TranslateWorld(translation); }
		if (Input::IsKey(VK_LCONTROL)) { XMFLOAT3 translation = { 0, -CAMERA_SPEED_UP * dt, 0 }; TranslateWorld(translation); }
	}
	else
	{
		XMFLOAT3 posTarget = GetWorldPosition();
		GameObject* target = GetTarget();
		if (target != nullptr)
		{
			posTarget = target->GetWorldPosition();
			SetWorldPosition(posTarget);
		}
		appCamera->SetWorldPosition(posTarget);
	}

	if (Input::IsKeyDown(VK_SHIFT)) { SetDebugMode(!debugMode); }
	if (Input::IsKeyDown(VK_TAB)) { SetRotateMode(!rotateMode); }

	if (rotateMode)
	{
		Input::HideMouse();

		Window& window = app->GetWindow();
		XMFLOAT2 size = XMFLOAT2((float)window.m_clientWidth, (float)window.m_clientHeight);
		XMFLOAT2 centerSize = XMFLOAT2(size.x * 0.5f, size.y * 0.5f);
		Input::UpdateMouseDelta();
		XMFLOAT2 posMouse = Input::GetMousePostion();
		XMFLOAT2 delta = Input::GetMouseDelta();
		Input::SetMousePosition(centerSize);

		// Rotation
		XMFLOAT3 yawPitchRoll = GetYawPitchRoll();
		yawPitchRoll.x += (int)delta.x * SENSITIVITY_CAMERA;
		yawPitchRoll.y += (int)delta.y * SENSITIVITY_CAMERA;

		yawPitchRoll.y = std::clamp(yawPitchRoll.y, PITCH_MIN, PITCH_MAX);

		float angleZero = 0.f;
		GameObject* target = GetTarget();
		if (target != nullptr)
		{
			target->SetWorldYPR(yawPitchRoll.x, yawPitchRoll.y, angleZero);
		}
		SetRotateLocal(yawPitchRoll.x, yawPitchRoll.y, angleZero);
		SetYawPitchRoll(yawPitchRoll);

	}
	else
	{
		Input::ShowMouse();
	}
}

void Camera::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Camera::OnDestroy()
{

}

void Camera::MoveForward(const float dis)
{
	mp_appCamera->MoveWorldForward(dis);
}

void Camera::TranslateWorld(const XMFLOAT3& translation)
{
	mp_appCamera->TranslateWorld(translation);
}

void Camera::SetRotateLocal(const float yaw, const float pitch, const float roll)
{
	mp_appCamera->SetLocalYPR(yaw, pitch, roll);
}

void Camera::SetRotateWorld(const float yaw, const float pitch, const float roll)
{
	mp_appCamera->SetWorldYPR(yaw, pitch, roll);
}

void Camera::RotateLocal(const float yaw, const float pitch, const float roll)
{
	mp_appCamera->RotateLocalYPR(yaw, pitch, roll);
}

void Camera::RotateLocal(const XMFLOAT3& yawPitchRoll)
{
	mp_appCamera->RotateLocalYPR(yawPitchRoll);
}

void Camera::RotateWorld(const float yaw, const float pitch, const float roll)
{
	mp_appCamera->RotateWorldYPR(yaw, pitch, roll);
}

void Camera::RotateWorld(const XMFLOAT3& yawPitchRoll)
{
	mp_appCamera->RotateWorldYPR(yawPitchRoll);
}

void Camera::SetAppCamera(GameObject* appCamera)
{
	mp_appCamera = appCamera;
}

GameObject* Camera::GetAppCamera()
{
	return mp_appCamera;
}

void Camera::SetTarget(GameObject* target)
{
	mp_target = target;
}

GameObject* Camera::GetTarget()
{
	return mp_target;
}

void Camera::SetDebugMode(const bool debugMode)
{
	m_debugMode = debugMode;
}

bool Camera::GetDebugMode()
{
	return m_debugMode;
}

void Camera::SetRotateMode(const bool rotateMode)
{
	m_rotateMode = rotateMode;
}

bool Camera::GetRotateMode()
{
	return m_rotateMode;
}

void Camera::SetMode(const Mode mode)
{
	switch (mode)
	{
	case Mode::_No:
		m_rotateMode = false;
		m_debugMode = false;
		break;
	case Mode::_Rotate:
		m_rotateMode = true;
		m_debugMode = false;
		break;
	case Mode::_Debug:
		m_rotateMode = false;
		m_debugMode = true;
		break;
	case Mode::_DebugRotate:
		m_rotateMode = true;
		m_debugMode = true;
		break;
	}
}

bool Camera::IsMode(const Mode mode)
{
	return GetMode() == mode;
}

Mode Camera::GetMode()
{
	if (m_rotateMode)
	{
		if (m_debugMode)
		{
			return Mode::_DebugRotate;
		}
		else
		{
			return Mode::_Rotate;
		}
	}
	else
	{
		if (m_debugMode)
		{
			return Mode::_Debug;
		}
		else
		{
			return Mode::_No;
		}
	}
}

void Camera::SetYawPitchRoll(const XMFLOAT3& yawPitchRoll)
{
	m_yawPitchRoll = yawPitchRoll;
}

XMFLOAT3 Camera::GetYawPitchRoll()
{
	return m_yawPitchRoll;
}
