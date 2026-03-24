#include "pch.h"
#include "main.h"

#include "Frog1.h"

using namespace nam;
using namespace DirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);

  	app->Run();	
}