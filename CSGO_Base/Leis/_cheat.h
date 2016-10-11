#pragma once

#include "../main.h"

class cCheat
{
public:

	bool bLastDead;

	cCheat()
	{
		bLastDead = false;
	}

	bool IsPlayerWeaponUseAmmo( int iIndex );
	bool IsLocalWeaponUseAmmo();
	bool IsLocalWeaponSniper();
	bool IsLocalWeaponKnife();

	void ClearPlayers();
};

extern cCheat g_Cheat;