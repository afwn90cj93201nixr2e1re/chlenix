#pragma once

#include "../main.h"

#define MAX_SOUND_ACTIVE 24

struct SCREENINFO
{
	int iWidth;
	int iHeight;
};

struct sound_s
{
	DWORD dwTime;
	Vector vOrigin;
};

class cSound
{
public:

	std::vector<sound_s> sound;

	void ClearSound();
	void AddSound( Vector vOrigin );
	void DrawSoundEsp();
};

class cLeis
{
public:
	
	void InitHack();
	void HUD_Redraw();
	void CL_AimbotMove( CUserCmd* cmd );
	void CL_CreateMove( float flInputSampleTime , CUserCmd* cmd );
};

extern SCREENINFO g_Screen;
extern cSound g_Sound;
extern cLeis g_Leis;