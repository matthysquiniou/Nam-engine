#include "pch.h"
#include "PauseHandlerObject.h"

#include "SceneTags.h"
#include "GameOverScene.h"

#include "WrappedSceneManager.h"

void PauseHandlerObject::OnInit()
{
	SetBehavior();
}

void PauseHandlerObject::OnStart()
{
}

void PauseHandlerObject::OnUpdate()
{
	App* p_app = App::Get();

	SceneManager& sm = p_app->GetSceneManager();

	if (Input::IsKeyDown(VK_ESCAPE))
	{
		if (Scene* p_pause = sm.GetSceneByTag(_PauseScene))
		{
			p_pause->Start();
			sm.AddCurrentScene(p_pause);
		}
	}
}

