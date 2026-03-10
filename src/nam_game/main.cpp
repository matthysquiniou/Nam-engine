#include "pch.h"
#include "main.h"

#include "Menu.h"
#include "CaveScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

#include "TextureTags.h"

#include "WrappedSceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);

	Light* p_sun = app->GetLightManager().CreateLight();
	p_sun->SetToDirectionalLight(0.75f, { 0, -1, 0 }, { 1, 1, 1 });
	
	CaveScene caveScene;
	caveScene.Init();
	WrappedSceneManager::Add(&caveScene);

	Menu menu;
	menu.Init();
	WrappedSceneManager::Add(&menu);

	PauseScene pause;
	pause.Init();
	WrappedSceneManager::Add(&pause);

	GameOverScene gameOver;
	gameOver.Init();
	WrappedSceneManager::Add(&gameOver);
  
	//lancer le jeu
	app->Run();	
}
