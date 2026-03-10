#pragma once

constexpr int INPUT_AMOUNT = 256;
namespace nam
{
	class Input
	{
		enum
		{
			NONE,
			PRESSED,
			DOWN,
			UP
		};

	private:
		static u8 ms_keys[INPUT_AMOUNT];
		static DirectX::XMFLOAT2 ms_lastMousePosition;
		static DirectX::XMFLOAT2 ms_mouseDelta;

		static bool m_isMouseVisible;
	public:
		static void Reset();

		static bool IsKeyDown(int key);
		static bool IsKey(int key);
		static bool IsKeyUp(int key);

		static void UpdateKeyStates();

		static void UpdateMouseDelta();

		static void SetMousePosition(DirectX::XMFLOAT2 position, bool updateMouseDelta = true);
		static DirectX::XMFLOAT2 GetMousePostion();
		static DirectX::XMFLOAT2 GetMouseDelta();
		static void HideMouse();
		static void ShowMouse();
		static const bool IsMouseVisible();
	};
}


