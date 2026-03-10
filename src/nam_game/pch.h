#ifndef PCH_H
#define PCH_H

//lib

#pragma comment(lib, "../../ide/nam_engine/x64/Debug/nam_engine.lib")
#include <FrameworkEngine.h>


#include <windows.h>

using namespace nam;
using namespace DirectX;

#include "Tag.h"

#include "Camera.h"
#include "FPSDisplayer.h"
#include "Score.h"

#include "Rail.h"
#include "RailGenerator.h"

#include "PauseHandlerObject.h"
#include "IWrappedScene.h"
#include "WrappedSceneManager.h"

#include "Player.h"
#include "Shot.h"
#include "Enemy.h"

#include "CaveScene.h"
#include "GameOverScene.h"


#endif