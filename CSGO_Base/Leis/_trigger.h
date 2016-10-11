#pragma once

#include "../main.h"

class cTrigger
{
public:

	bool bTrigger;

	DWORD dwTriggerStatusTime;
	DWORD dwTriggerTime;

	cTrigger()
	{
		bTrigger = false;
		dwTriggerStatusTime = 0;
		dwTriggerTime = 0;
	}

	void LeftClick();

	void TriggerShowStatus();

	int TriggerCharToKey( char* Key );

	bool CheckPlayerTriggerLine( int iIndex, CUserCmd* cmd );
	byte CheckPlayerTriggerPos();

	void TriggerBot( CUserCmd* cmd );
};

extern cTrigger g_Trigger;