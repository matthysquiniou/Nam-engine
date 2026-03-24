#pragma once

//lib

#ifdef _DEBUG
#pragma comment(lib, "../nam_core/x64/Debug/nam_core.lib")
#pragma comment(lib, "../nam_render/x64/Debug/nam_render.lib")
#else
#pragma comment(lib, "../nam_core/x64/Release/nam_core.lib")
#pragma comment(lib, "../nam_render/x64/Release/nam_render.lib")
#endif

//
//Externe dependence
#include <iostream>
#include <DirectXMath.h>
#include <cstdint>
#include <cassert>
#include <vector>
#include <bitset>
#include <limits>
#include <chrono>
#include <windows.h>
#include <FrameworkCore.h>

//
//Interne dependence
#include "Input.h"
#include "TransformComponent.h"
#include "MeshRendererComponent.h"
#include "StateMachineComponent.h"
#include "BehaviorComponent.h"
#include "ParticleEmitersComponent.h"
#include "ButtonComponent.h"
#include "SpriteRendererComponent.h"
#include "CollisionInfo.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "PhysicComponent.h"
#include "CameraComponent.h"
#include "TextRendererComponent.h"
#include "ControllerComponent.h"
#include "LightComponent.h"
#include "EcsConfig.h"
#include "Entity.h"
#include "ISparseSet.h"
#include "ISystem.h"
#include "IView.h"
#include "ViewId.h"

#include "GameObject.h"
#include "RenderSystem.h"
#include "StateMachineSystem.h"
#include "LightManagerSystem.h"
#include "Utils.h"
#include "ComponentId.h"
#include "SystemId.h"
#include "EntityManager.h"
#include "SparseSet.h"

#include "Ecs.h"
#include "View.h"
#include "Scene.h"
#include "SceneManager.h"
#include "App.h"

#include "Mesh.h"
#include "Sprite.h"
#include "Text.h"
#include "Light.h"
#include "LightManager.h"


#include "VoxelGrid.h"
#include "PoissonDisc.h"





