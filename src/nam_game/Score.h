#pragma once

class Score : public GameObject
{
private:
	int m_score;
	Timer m_timer;

	TextRendererComponent* mp_textRender;
public:
	Score();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	void SetScore(int score);
	void IncreaseScore(int add);
	int GetScore();
};