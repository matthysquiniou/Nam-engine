#include "pch.h"
#include "main.h"

#include "Frog1.h"

using namespace nam;
using namespace DirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);
    Scene* scene = app->CreateScene(0);

    // sun
    {
        GameObject* go = scene->CreateGameObject<GameObject>();
        LightComponent lc;
        lc.CreateLightInstance();
        lc.mp_light->SetToDirectionalLight(0.8f, { 0.f,-1.f,0.f }, { 1.f,0.99f,0.88f });
        go->AddComponent<LightComponent>(lc);
    }

    // plane / ground
    {
        GameObject* go = scene->CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildPlane({ 50.f,50.f }, { 0.2f,1.f,0.2f,1.f });
        go->AddComponent<MeshRendererComponent>(mrc);
        go->AddComponent<TransformComponent>(TransformComponent());
        go->SetBoxCollider();
    }

    //player 
    {
        Frog1* frog = scene->CreateGameObject<Frog1>();
    }

  	app->Run();	
}