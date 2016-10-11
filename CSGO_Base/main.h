#pragma once

#include <Windows.h>
#include <inttypes.h>
#include <iostream>
#include <vector>

using namespace std;

#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")

#include "SDK/sdk.h"

#include "str_mem.h"

#include "xorstr.h"
#include "hook.h"
#include "offset.h"
#include "utils.h"
#include "client.h"
#include "drawing.h"

#include "Leis/_utils.h"
#include "Leis/_cvar.h"
#include "Leis/_player.h"
#include "Leis/_esp.h"
#include "Leis/_cheat.h"
#include "Leis/_client.h"
#include "Leis/_menu.h"
#include "Leis/_radar.h"
#include "Leis/_aimbot.h"
#include "Leis/_trigger.h"
#include "Leis/_skins.h"

#define ERROR_TITLE	"Error"
#define ERROR_TEXT	"Error Find Modules"

extern cHookTable EngineTable;
extern cHookTable ClientTable;
extern cHookTable SoundTable;
extern cHookTable SurfaceTable;
extern cHookTable PanelTable;
extern cHookTable ClientModeTable;
extern cHookTable GameEventTable;
extern cHookTable ModelRenderTable;

extern PCHAR BaseDir;

BOOL WINAPI DllMain( HINSTANCE hinstDLL , DWORD fdwReason , LPVOID lpReserved );
DWORD WINAPI CheatThread( PVOID ThreadParameter );