#include "pch.h"
#include "Rail.h"
#include "RailGenerator.h"

Rail::Rail()
{

}

void Rail::OnInit()
{
	//SetBehavior();
	SetTag((int)Tag::_Rail);
}

void Rail::OnStart()
{

}

void Rail::OnUpdate()
{
	//App* app = App::Get();
	//float dt = app->GetChrono().GetScaledDeltaTime();
}

void Rail::OnDestroy()
{

}




