#pragma once

#define CAMERA_SPEED_MOVE 20.f
#define CAMERA_SPEED_UP 3.f

#define SENSITIVITY_CAMERA 0.002f

#define DEGREE_TO_RADIAN XM_PI / 360.0f
#define PITCH_MAX 170.f * DEGREE_TO_RADIAN
#define PITCH_MIN -170.f * DEGREE_TO_RADIAN

enum class Mode : int
{
	_No,
	_Rotate,
	_Debug,
	_DebugRotate,
};

class Camera : public GameObject
{
private:
	GameObject* mp_appCamera;
	GameObject* mp_target;
	XMFLOAT3 m_yawPitchRoll;
	bool m_rotateMode;
	bool m_debugMode;
public:
	Camera();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void MoveForward(const float dis);
	void TranslateWorld(const XMFLOAT3& translation);

	void SetRotateLocal(const float yaw, const float pitch, const float roll);
	void SetRotateWorld(const float yaw, const float pitch, const float roll);

	void RotateLocal(const float yaw, const float pitch, const float roll);
	void RotateLocal(const XMFLOAT3& yawPitchRoll);
	void RotateWorld(const float yaw, const float pitch, const float roll);
	void RotateWorld(const XMFLOAT3& yawPitchRoll);

	void SetAppCamera(GameObject* appCamera);
	GameObject* GetAppCamera();

	void SetTarget(GameObject* target);
	GameObject* GetTarget();

	void SetDebugMode(const bool debugMode);
	bool GetDebugMode();

	void SetRotateMode(const bool rotateMode);
	bool GetRotateMode();

	void SetMode(const Mode mode);
	bool IsMode(const Mode mode);
	Mode GetMode();

	void SetYawPitchRoll(const XMFLOAT3& yawPitchRoll);
	XMFLOAT3 GetYawPitchRoll();
};