#pragma once

template<typename T>
T* WrappedSceneManager::Get()
{
	for (IWrappedScene* p_wrapped : m_wrappedScenes)
	{
		if (T* t = dynamic_cast<T*>(p_wrapped))
		{
			return t;
		}
	}

	return nullptr;
}