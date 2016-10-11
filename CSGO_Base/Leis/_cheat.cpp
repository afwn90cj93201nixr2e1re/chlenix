#include "_cheat.h"

cCheat g_Cheat;

bool cCheat::IsPlayerWeaponUseAmmo( int iIndex )
{
	if( g_Player[iIndex].weapon.type == WEAPON_TYPE_PISTOL || g_Player[iIndex].weapon.type == WEAPON_TYPE_SHOTGUN ||
		g_Player[iIndex].weapon.type == WEAPON_TYPE_SNIPER )
		return true;

	return false;
}

bool cCheat::IsLocalWeaponUseAmmo()
{
	if( g_Local.weapon.type == WEAPON_TYPE_PISTOL || g_Local.weapon.type == WEAPON_TYPE_SHOTGUN ||
		g_Local.weapon.type == WEAPON_TYPE_SNIPER )
		return true;

	return false;
}

bool cCheat::IsLocalWeaponSniper()
{
	return ( g_Local.weapon.type == WEAPON_TYPE_SNIPER );
}

bool cCheat::IsLocalWeaponKnife()
{
	return ( g_Local.weapon.type == WEAPON_TYPE_KNIFE );
}

void cCheat::ClearPlayers()
{
	nt_memset( &g_Player[0] , sizeof( g_Player ) , 0 );
}