#include "pch.h"
#include "Window.h"

namespace nam
{
	Window::Window(HINSTANCE& hInst, std::wstring name)
	{
		m_hInstance = hInst;
		m_name = name;
	}
}