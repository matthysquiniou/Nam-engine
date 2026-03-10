#include "pch.h"
#include "main.h"
#include <FrameworkEngine.h>
#include <iostream>

#include "Mesh.h"
#include "App.h"

using namespace nam;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
	App* app = App::Get(hInstance, 1920, 1080);

	app->Run();

}
