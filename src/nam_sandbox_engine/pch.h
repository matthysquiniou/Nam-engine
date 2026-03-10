#ifndef PCH_H
#define PCH_H

//lib


#ifdef _DEBUG
#pragma comment(lib, "../nam_engine/x64/Debug/nam_engine.lib")
#else
#pragma comment(lib, "../nam_engine/x64/Release/nam_engine.lib")
#endif

#include <FrameworkEngine.h>

#include <windows.h>

#endif