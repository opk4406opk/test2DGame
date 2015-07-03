// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

#include "d3dUtility.h"
#include "Game2DSprite.h"
#include "GameMap.h"
#include "TMXParser.h"
#include "tinyxml2.h"
#include"CharacterAnimation.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerFactory.h"
#include "Camera.h"
