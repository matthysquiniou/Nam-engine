#pragma once


class Transform2DComponent
{
	DirectX::XMFLOAT2 m_pos = { 0, 0 };

public:
	Transform2DComponent();

	void Reset();

	void SetPosition(DirectX::XMFLOAT2 pos);
	void Translate(DirectX::XMFLOAT2 vec);

};

