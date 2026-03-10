#include "pch.h"
#include "WrappedSceneManager.h"

Vector<IWrappedScene*> WrappedSceneManager::m_wrappedScenes = {};

void WrappedSceneManager::Add(IWrappedScene* p_s)
{
	m_wrappedScenes.push_back(p_s);
}
