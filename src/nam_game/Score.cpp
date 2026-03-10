#include "pch.h"
#include "Score.h"

Score::Score()
{
}

void Score::OnInit()
{
	m_timer.Init(1.f);

	m_score = 0;

	TextRendererComponent textRender;

	Text* p_text = textRender.CreateTextInstance();

	p_text->SetDatas({ 40, 40 }, 0.5f, { 1, 1, 1, 1 });
	p_text->SetText("Score : ");

	p_text->SetTexture(_FontPusab);
	p_text->SetToDynamic(MAX_TEXT_VERTICES, MAX_TEXT_INDICES);

	XMFLOAT3 pos = { 20, 20, 0 };
	SetWorldPosition(pos);
	AddComponent(textRender);
	mp_textRender = &GetComponent<TextRendererComponent>();

	SetBehavior();
	SetTag((int)Tag::_None);
}

void Score::OnStart()
{
	m_score = 0;
}

void Score::OnUpdate()
{
	App* app = App::Get();
	float dt = app->GetChrono().GetScaledDeltaTime();

	m_timer.Update(dt);

	if (m_timer.IsTargetReached())
	{
		m_timer.ResetProgress();
		IncreaseScore(1);
	}

	std::string toDisplay = "Score : " + std::to_string(m_score);
	mp_textRender->mp_text->SetText(toDisplay);
	mp_textRender->mp_text->MakeRainbowVertices();
}

void Score::OnDestroy()
{

}

void Score::SetScore(int score)
{
	m_score = score;
}

void Score::IncreaseScore(int add)
{
	m_score += add;
}

int Score::GetScore()
{
	return m_score;
}


