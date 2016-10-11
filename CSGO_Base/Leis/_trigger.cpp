#include "_trigger.h"

cTrigger g_Trigger;

void cTrigger::LeftClick()
{
	INPUT    Input;
	nt_memset( &Input , sizeof( INPUT ) , 0 );
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput( 1 , &Input , sizeof( INPUT ) );
	nt_memset( &Input , sizeof( INPUT ) , 0 );
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput( 1 , &Input , sizeof( INPUT ) );
}

void cTrigger::TriggerShowStatus()
{
	con_nprint_t print;
	print.index = 1;
	print.fixed_width_font = false;
	print.time_to_live = -1;

	if( cvar.weapon_settings[cvar.wpn].trigger_mode >= 2 )
	{
		if( GetTickCount() - dwTriggerStatusTime < 1000 )
		{
			if( bTrigger )
			{
				print.color[0] = 0.f;
				print.color[1] = 1.f;
				print.color[2] = 0.f;

				g_pEngine->Con_NXPrintf( &print , "%s" , CFG_TRIGGER_ENABLED );
			}
			else
			{
				print.color[0] = 1.f;
				print.color[1] = 0.f;
				print.color[2] = 0.f;

				g_pEngine->Con_NXPrintf( &print , "%s" , CFG_TRIGGER_DISABLED );
			}
		}
	}
	else if( bTrigger )
	{
		print.color[0] = 0.f;
		print.color[1] = 1.f;
		print.color[2] = 0.f;

		g_pEngine->Con_NXPrintf( &print , "%s" , CFG_TRIGGER_ENABLED );
	}
}

int cTrigger::TriggerCharToKey( char* Key )
{
	if( !nt_strcmp( Key , CFG_KEY_F1 ) ) return VK_F1;
	if( !nt_strcmp( Key , CFG_KEY_F2 ) ) return VK_F2;
	if( !nt_strcmp( Key , CFG_KEY_F3 ) ) return VK_F3;
	if( !nt_strcmp( Key , CFG_KEY_F4 ) ) return VK_F4;
	if( !nt_strcmp( Key , CFG_KEY_F5 ) ) return VK_F5;
	if( !nt_strcmp( Key , CFG_KEY_F6 ) ) return VK_F6;
	if( !nt_strcmp( Key , CFG_KEY_F7 ) ) return VK_F7;
	if( !nt_strcmp( Key , CFG_KEY_F8 ) ) return VK_F8;
	if( !nt_strcmp( Key , CFG_KEY_F9 ) ) return VK_F9;
	if( !nt_strcmp( Key , CFG_KEY_F10 ) ) return VK_F10;
	if( !nt_strcmp( Key , CFG_KEY_F11 ) ) return VK_F11;
	if( !nt_strcmp( Key , CFG_KEY_F12 ) ) return VK_F12;

	if( !nt_strcmp( Key , CFG_KEY_MOUSE3 ) ) return VK_MBUTTON;
	if( !nt_strcmp( Key , CFG_KEY_MOUSE4 ) ) return VK_XBUTTON1;
	if( !nt_strcmp( Key , CFG_KEY_MOUSE5 ) ) return VK_XBUTTON2;

	return 0;
}

bool cTrigger::CheckPlayerTriggerLine( int iIndex, CUserCmd* cmd )
{
	trace_t tr;
	Vector	vecStart , vecStop , vecFor , vecRig , vecUp;

	QAngle Angle;
	
	Angle.x = cmd->viewangles.x;
	Angle.y = cmd->viewangles.y;

	AngleVectors( Angle , vecFor , vecRig , vecUp );

	vecStart = g_Local.vEyeOrigin;
	vecStop = vecStart + vecFor * MAX_TRACE_LENGTH;

	UTIL_TraceLine( vecStart , vecStop , MASK_ALL , g_Local.pEntity , COLLISION_GROUP_PLAYER , &tr );

	if ( ( tr.m_pEnt->Index() == iIndex && !tr.allsolid ) || g_Local.iCrossHairID == iIndex )
		return true;
	else
		return false;
}

byte cTrigger::CheckPlayerTriggerPos()
{
	byte cnt = 0;

	for( int i = 0; i < 32; i++ )
	{
		if( g_Player[i].bTriggerFov )
			cnt++;
	}

	return cnt;
}

void cTrigger::TriggerBot( CUserCmd* cmd )
{
	if ( cvar.weapon_settings[cvar.wpn].trigger_mode >= 2 )
	{
		if ( KEY_DOWN( cvar.weapon_settings[cvar.wpn].trigger_key ) )
		{
			bTrigger = !bTrigger;
			dwTriggerStatusTime = GetTickCount();
		}
	}
	else if ( cvar.weapon_settings[cvar.wpn].trigger_mode == 1 )
	{
		if ( GetAsyncKeyState( cvar.weapon_settings[cvar.wpn].trigger_key ) )
			bTrigger = true;
		else
			bTrigger = false;
	}

	for( int i = 1; i < 32; i++ )
	{
		if ( !g_Player[i].pEntity || g_Local.iIndex == g_Player[i].iIndex || !bTrigger || !g_Local.bAlive || !g_Player[i].bVisible )
		{
			g_Player[i].bTriggerFov = false;
			continue;
		}

		if ( !g_Player[i].bAlive || g_Player[i].iTeam == g_Local.iTeam )
		{
			g_Player[i].bTriggerFov = false;
			continue;
		}

		if ( CheckPlayerTriggerLine( i , cmd ) )
			g_Player[i].bTriggerFov = true;
		else
			g_Player[i].bTriggerFov = false;
	}

	if ( CheckPlayerTriggerPos() )
	{
		DWORD currentCount = GetTickCount();

		if ( !dwTriggerTime )
			dwTriggerTime = currentCount;

		if ( cvar.weapon_settings[cvar.wpn].trigger_time <= 0 || ( dwTriggerTime + cvar.weapon_settings[cvar.wpn].trigger_time ) >= currentCount )
		{
			LeftClick();
		}
	}
	else
	{
		dwTriggerTime = 0;
	}
}