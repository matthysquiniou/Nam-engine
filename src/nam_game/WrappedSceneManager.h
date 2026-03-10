#pragma once

class IWrappedScene;

//A Manager to get any Wrapped Scene
class WrappedSceneManager
{
	static Vector<IWrappedScene*> m_wrappedScenes;

public:
	static void Add(IWrappedScene* p_s);

	template<typename T>
	static T* Get();
};

#include "WrappedSceneManager.inl"
