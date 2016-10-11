#include "_radar.h"

cRadar g_Radar;

void cRadar::DrawGuiRadar( int x , int y )
{
	radar_x = x;
	radar_y = y;

	if ( cvar.radar_enable && bRadarHide )
	{
		bRadarHide = false;
	}
	else if ( !cvar.radar_enable && !bRadarHide )
	{
		bRadarHide = true;
	}

	g_Draw.FillArea( radar_x + 1 , cvar.radar_size / 2 + radar_y , cvar.radar_size - 2 , 1 , Color(255 , 255 , 255 , 120) );
	g_Draw.FillArea( cvar.radar_size / 2 + radar_x , radar_y + 1 , 1 , cvar.radar_size - 2 , Color(255 , 255 , 255 , 120) );
}

void cRadar::DrawRadarPlayer( int iIndex )
{
	byte r , g , b;

	int screenx = 0;
	int screeny = 0;

	if ( g_Player[iIndex].iTeam == TEAM_TT )
	{
		if ( g_Player[iIndex].bVisible && cvar.rad_visible == 1 )
		{
			r = 0; g = 255; b = 0;
		}
		else if ( g_Player[iIndex].bVisible && g_Local.iTeam != g_Player[iIndex].iTeam && cvar.rad_visible == 2 )
		{
			r = 0; g = 255; b = 0;
		}
		else
		{
			r = 255; g = 64; b = 64;
		}
	}
	else if ( g_Player[iIndex].iTeam == TEAM_CT )
	{
		if ( g_Player[iIndex].bVisible && cvar.rad_visible == 1 )
		{
			r = 0; g = 255; b = 0;
		}
		else if ( g_Player[iIndex].bVisible && g_Local.iTeam != g_Player[iIndex].iTeam && cvar.rad_visible == 2 )
		{
			r = 0; g = 255; b = 0;
		}
		else
		{
			r = 0; g = 164; b = 255;
		}
	}
	else
	{
		return;
	}

	CalcRadarPoint( g_Player[iIndex].vOrigin , screenx , screeny );

	if ( g_Player[iIndex].iTeam != g_Local.iTeam )
	{
		g_Draw.FillArea( screenx , screeny , 6 , 6 , Color( r , g , b , 255 ) );
	}
}

void cRadar::RadarRange( float* x , float* y , float range )
{
	if ( nt_fabs( ( *x ) ) > range || nt_fabs( ( *y ) ) > range )
	{
		if ( ( *y ) > ( *x ) )
		{
			if ( ( *y ) > -( *x ) ) { ( *x ) = range*( *x ) / ( *y ); ( *y ) = range; }
			else { ( *y ) = -range*( *y ) / ( *x ); ( *x ) = -range; }
		}
		else
		{
			if ( ( *y ) > -( *x ) ) { ( *y ) = range*( *y ) / ( *x ); ( *x ) = range; }
			else { ( *x ) = -range*( *x ) / ( *y ); ( *y ) = -range; }
		}
	}
}

void cRadar::CalcRadarPoint( Vector vOrigin , int& screenx , int& screeny )
{
	QAngle Angle;

	g_pEngine->GetViewAngles( Angle );

	float dx = vOrigin[0] - g_Local.vEyeOrigin[0];
	float dy = vOrigin[1] - g_Local.vEyeOrigin[1];

	float fYaw = float( Angle.y * ( M_PI / 180.0 ) );

	float fsin_yaw = nt_sin( fYaw );
	float fminus_cos_yaw = -nt_cos( fYaw );

	float x = dy*fminus_cos_yaw + dx*fsin_yaw;
	float y = dx*fminus_cos_yaw - dy*fsin_yaw;

	float range = (float)cvar.radar_zoom;

	RadarRange( &x , &y , range );

	int r_siz = cvar.radar_size;

	int x_max = r_siz + radar_x - 7;
	int y_max = r_siz + radar_y - 7;

	screenx = radar_x + ( r_siz / 2 + int( x / (float)range*float( r_siz ) ) );
	screeny = radar_y + ( r_siz / 2 + int( y / (float)range*float( r_siz ) ) );

	if ( screenx > x_max )
		screenx = x_max;
	if ( screenx < radar_x )
		screenx = radar_x + 1;
	if ( screeny > y_max )
		screeny = y_max;
	if ( screeny < radar_y )
		screeny = radar_y + 1;
}