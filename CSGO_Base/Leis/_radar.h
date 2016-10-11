#pragma once

#include "../main.h"

class cRadar
{
public:

	bool bRadarHide;

	int radar_x;
	int radar_y;

	cRadar()
	{
		bRadarHide = true;

		radar_x = 0;
		radar_y = 0;
	}

	void DrawGuiRadar( int x , int y );
	void DrawRadarPlayer( int iIndex );
	void RadarRange( float* x , float* y , float range );
	void CalcRadarPoint( Vector vOrigin , int& screenx , int& screeny );
};

extern cRadar g_Radar;