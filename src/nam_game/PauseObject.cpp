#include "pch.h"
#include "PauseObject.h"

#include "SceneTags.h"

void PauseObject::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_None);
}

void PauseObject::OnStart()
{
	FreezeTime();
}

void PauseObject::OnUpdate()
{
	if (Input::IsKeyDown(VK_ESCAPE))
	{
		UnFreezeTime();
		App::Get()->GetSceneManager().RemoveCurrentScene(_PauseScene);
	}
}

void PauseObject::FreezeTime()
{
	App::Get()->GetChrono().SetFreezeState(true);
}

void PauseObject::UnFreezeTime()
{
	Window& w = App::Get()->GetWindow();
	Input::SetMousePosition({ (float)w.m_clientWidth * 0.5f, (float)w.m_clientHeight * 0.5f });
	App::Get()->GetChrono().SetFreezeState(false);
}
