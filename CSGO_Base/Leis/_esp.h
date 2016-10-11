#pragma once

#include "../main.h"

class cEsp
{
public:

	Color GetPlayerTeamColor( int iIndex );
	Color GetPlayerTeamVisibleColor( int iIndex );

	bool GetPlayerCheckTeam( int iIndex );

	void DrawHealthArmorAmmoWpnEsp( int x , int y , int iIndex , Color color );

	void DrawAllPlayerEsp( int iIndex );
	void DrawPlayersESP( int iIndex );
};

extern cEsp g_Esp;