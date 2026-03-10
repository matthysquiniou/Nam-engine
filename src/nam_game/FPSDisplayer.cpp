#include "pch.h"
#include "FPSDisplayer.h"

FPSDisplayer::FPSDisplayer()
{
	mp_textRender = nullptr;
	m_refreshTimer = {};
}

void FPSDisplayer::OnInit()
{
	SetBehavior();

	TextRendererComponent textRender;

	Text* p_text = textRender.CreateTextInstance();

	p_text->SetDatas({ 56, 56 }, 0.69f, { 1, 1, 1, 1 });
	p_text->SetText("FPS : ");
	p_text->MakeRainbowVertices();

	p_text->SetToDynamic(MAX_TEXT_VERTICES, MAX_TEXT_INDICES);

	XMFLOAT3 pos = { 20, 60, 0 };
	SetWorldPosition(pos);
	AddComponent(textRender);
	mp_textRender = &GetComponent<TextRendererComponent>();

	m_refreshTimer.Init(1.f);
	SetTag((int)Tag::_None);
}

void FPSDisplayer::OnStart()
{

}

void FPSDisplayer::OnUpdate()
{
	App* app = App::Get();
	int fpsCount = app->GetChrono().GetFPS();
	float dt = app->GetChrono().GetRealDeltaTime();

	Timer* p_timer = GetTimer();

	p_timer->Update(dt);

	if (p_timer->IsTargetReached())
	{
		p_timer->ResetProgress();

		std::string toDisplay = "FPS : " + std::to_string(fpsCount);
		mp_textRender->mp_text->SetText(toDisplay);
		mp_textRender->mp_text->MakeRainbowVertices();
	}
}

void FPSDisplayer::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void FPSDisplayer::OnDestroy()
{
}

Timer* FPSDisplayer::GetTimer()
{
	return &m_refreshTimer;
}

