#include "pch.h"
#include "Timer.h"

namespace nam
{
	Timer::Timer(float targetTime, bool countdownMode, bool isPaused)
	{
		Init(targetTime, countdownMode, isPaused);
	}

	void Timer::Init(float targetTime, bool countdownMode, bool isPaused)
	{
		m_targetTime = targetTime;
		m_countdownMode = countdownMode;
		m_isPaused = isPaused;

		ResetProgress();
	}
	void Timer::Update(float dt)
	{
		if (m_isPaused)
			return;

		if (m_countdownMode == false)
		{
			if (m_progress > m_targetTime)
				m_progress = m_targetTime;
			else
				m_progress += dt;
		}
		else
		{
			if (m_progress < 0)
				m_progress = 0;
			else
				m_progress -= dt;
		}
	}

	void Timer::Pause()
	{
		m_isPaused = true;
	}
	void Timer::Resume()
	{
		m_isPaused = false;
	}

	const float Timer::GetProgress() const
	{
		return m_progress;
	}
	void Timer::ResetProgress()
	{
		(m_countdownMode) ? m_progress = m_targetTime : m_progress = 0.f;
	}

	const float Timer::GetTargetTime() const
	{
		return m_targetTime;
	}
	void Timer::SetTargetTime(float time)
	{
		ResetProgress();
		m_targetTime = time;
	}
	bool Timer::IsTargetReached() const
	{
		if (m_countdownMode == false)
			return m_progress >= m_targetTime;

		else
			return m_progress <= 0;
	}

	std::string Timer::GetDisplay() const
	{
		std::string txt = "";

		if (m_countdownMode == false)
		{
			txt = "Time : " + std::to_string(m_progress) + " / " + std::to_string(m_targetTime) + "\n";
		}
		else
		{
			txt = "Time Left : " + std::to_string(m_progress) + "\n";
		}

		return txt;
	}
}
