#ifndef PCH_H
#define PCH_H

//lib

#ifdef _DEBUG
#pragma comment(lib, "../nam_render/x64/Debug/nam_render.lib")
#else
#pragma comment(lib, "../nam_render/x64/Release/nam_render.lib")
#endif

#include <FrameworkRender.h>
//

#include <windows.h>

#endif