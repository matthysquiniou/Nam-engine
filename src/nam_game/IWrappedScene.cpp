#include "pch.h"
#include "IWrappedScene.h"

void IWrappedScene::InitGameObjectsSingle()
{

}

void IWrappedScene::InitGameObjectsNotSingle()
{

}

void IWrappedScene::Reset()
{
	if (mp_scene == nullptr)
	{
		return;
	}

	App* app = App::Get();

	DeleteGameObjectsNotSingle();
	InitGameObjectsNotSingle();
	mp_scene->Start();
}

void IWrappedScene::DeleteGameObjectsNotSingle()
{
	UnMap<u32, GameObject*> allGameObject = mp_scene->GetAllGameObject();
	for (auto it = allGameObject.begin(); it != allGameObject.end(); it++)
	{
		GameObject* gameObject = it->second;

		int tag = gameObject->GetTag();
		if (tag != (int)Tag::_None && tag != (int)Tag::_Camera && tag != (int)Tag::_Player)
		{
			gameObject->DestroyGameObject();
		}
	}
}