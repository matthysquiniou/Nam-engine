#include "pch.h"
#include "LoadingScreen.h"
#include <SpriteRendererComponent.h>

#include "RenderManager.h"
#include <limits>

namespace nam
{
	void LoadingScreen::OnInit()
	{
		SpriteRendererComponent srComp;

		Sprite* p_sprite = srComp.CreateSpriteInstance();

		Window* p_window = Render->GetWindow();
		DirectX::XMFLOAT2 windowSize = {(float)p_window->m_clientWidth, (float)p_window->m_clientHeight};

		p_sprite->BuildRect(windowSize, { 1, 1, 1, 1 });
		p_sprite->SetTexture(_SplashScreen);
		p_sprite->SetToDynamic(4, 6);
		p_sprite->SetDrawLayer( (std::numeric_limits<int>::min)() );
		AddComponent(srComp);

		TransformComponent tc;
		tc.SetWorldPosition({ windowSize.x * 0.5f, windowSize.y * 0.5f, 0 });
		AddComponent<TransformComponent>(tc);

		m_waitingTimer.Init(0.1f);
		m_fadingTimer.Init(m_fadingSpeed);

		SetBehavior();
	}

	void LoadingScreen::OnUpdate()
	{
		App* app = App::Get();
		AppChrono& chrono = app->GetChrono();
		float dt = chrono.GetRealDeltaTime();

		Sprite* p_sprite = GetComponent<SpriteRendererComponent>().mp_sprite;

		if (m_spawn == true)
		{
			m_spawn = false;

			m_waitingTimer.ResetProgress();
			m_fadingTimer.ResetProgress();

			p_sprite->SetColor({ 1, 1, 1, 1 });
		}
		else
		{
			if (m_waitingTimer.IsTargetReached() == false)
			{
				chrono.SetFreezeState(true);
				m_waitingTimer.Update(dt);
				return;
			}

			if (m_fadingTimer.IsTargetReached())
				return;

			chrono.SetFreezeState(false);
			m_fadingTimer.Update(dt);

			float targetTime = m_fadingTimer.GetTargetTime();

			assert(targetTime != 0);

			float ratio = m_fadingTimer.GetProgress() / targetTime;

			p_sprite->SetColor({ 1, 1, 1, 1 - ratio });
		}
	}

	void LoadingScreen::Activate(float minTimeToWait)
	{
		m_waitingTimer.SetTargetTime(minTimeToWait);
		m_spawn = true;
	}
}
