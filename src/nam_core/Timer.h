#pragma once

namespace nam
{
	class AppChrono;

	class Timer
	{
		float m_targetTime = -1.f;
		float m_progress = 0.f;

		bool m_countdownMode = false; // time's decreasing until 0, resetted to targetTime
		bool m_isPaused = false; // pause the timer

	public:
		Timer() = default;
		Timer(float targetTime, bool countdownMode = false, bool isPaused = false);

		void Init(float targetTime, bool countdownMode = false, bool isPaused = false);
		void Update(float dt);

		void Pause();
		void Resume();

		const float GetProgress() const;
		void ResetProgress();

		const float GetTargetTime() const;
		void SetTargetTime(float time);
		bool IsTargetReached() const;

		std::string GetDisplay() const;
	};
}