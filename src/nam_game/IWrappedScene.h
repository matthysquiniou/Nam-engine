#pragma once

class IWrappedScene
{
public:
	Scene* mp_scene = nullptr;

	virtual void Init() = 0;

public:
	void Reset();
	void DeleteGameObjectsNotSingle();

private:
	virtual void LoadTextures() = 0;
	virtual void InitGameObjectsSingle();
	virtual void InitGameObjectsNotSingle();

};

