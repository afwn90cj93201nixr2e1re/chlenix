#include "_client.h"

SCREENINFO g_Screen;
cSound g_Sound;
cLeis g_Leis;

#define GRENADE_DECOY_STR		"decoy"
#define GRENADE_HE_FLASH_STR	"he/flash"
#define GRENADE_MOLOTOV_STR		"molotov"
#define GRENADE_SENSOR_STR		"sensor"
#define GRENADE_SMOKE_STR		"smoke"

int GrenadeEspClassID[5] =
{
	CC_CDecoyProjectile,
	CC_CBaseCSGrenadeProjectile,
	CC_CMolotovProjectile,
	CC_CSensorGrenadeProjectile,
	CC_CSmokeGrenadeProjectile
};

char* GrenadeEpsName[5] =
{
	GRENADE_DECOY_STR,GRENADE_HE_FLASH_STR,
	GRENADE_MOLOTOV_STR,GRENADE_SENSOR_STR,
	GRENADE_SMOKE_STR
};

int WeaponsEspClassID[33] =
{
	// охярнкерш - 0 - 9
	CC_CDEagle,CC_CWeaponElite,CC_CWeaponFiveSeven,
	CC_CWeaponGlock,CC_CWeaponHKP2000,CC_CWeaponP250,
	CC_CWeaponUSP,CC_CWeaponP250,CC_CDEagle,
	// юбрнлюрш - 9 - 28
	CC_CAK47,CC_CWeaponAug,CC_CWeaponFamas,CC_CWeaponGalilAR,
	CC_CWeaponM249,CC_CWeaponM4A1,CC_CWeaponM4A1,CC_CWeaponMAC10,
	CC_CWeaponP90,CC_CWeaponUMP45,CC_CWeaponXM1014,CC_CWeaponBizon,
	CC_CWeaponMag7,CC_CWeaponNegev,CC_CWeaponSawedoff,CC_CWeaponTec9,
	CC_CWeaponMP7,CC_CWeaponMP9,CC_CWeaponNOVA,CC_CWeaponSG556,
	// ямюиоепйх  - 29 - 32
	CC_CWeaponAWP,CC_CWeaponG3SG1,CC_CSCAR17,CC_CWeaponSSG08
};

#define GRENADE_ID_DATA_SIZE ( sizeof( GrenadeEspClassID ) / sizeof( *GrenadeEspClassID ) )
#define WEAPONS_ID_DATA_SIZE ( sizeof( WeaponsEspClassID ) / sizeof( *WeaponsEspClassID ) )

void cSound::AddSound( Vector vOrigin )
{
	if ( sound.size() < MAX_SOUND_ACTIVE )
	{
		sound_s entry;

		entry.dwTime = GetTickCount();
		entry.vOrigin = vOrigin;

		sound.push_back( entry );
	}
	else
		ClearSound();
}

void cSound::ClearSound()
{
	sound.clear();
}

void cSound::DrawSoundEsp()
{
	for( size_t i = 0; i < g_Sound.sound.size(); i++ )
	{
		if( g_Sound.sound[i].dwTime + 800 <= GetTickCount() )
		{
			g_Sound.sound[i].dwTime = 0;
			g_Sound.sound[i].vOrigin = Vector( 0 , 0 , 0 );
		}
		else
		{
			Vector vScreen;

			if( WorldToScreen( g_Sound.sound[i].vOrigin , vScreen ) )
			{
				g_Draw.DrawBox( (int)vScreen.x , (int)vScreen.y , 10 , 10 , Color( 255 , 255 , 255 ) );
			}
		}
	}
}

void cLeis::InitHack()
{
	g_FontEsp.dwFontId = 0;
	g_FontMenu.dwFontId = 0;

	g_FontEsp.SetFont( CFG_VERDANA , 12 , 7 , FONTFLAG_OUTLINE );
	g_FontMenu.SetFont( CFG_VERDANA , 12 , 7 , FONTFLAG_NONE );

	g_Local.iTeam = TEAM_SPEC;
	g_Local.bAlive = false;

	g_Local.bC4Planted = false;

	g_Cheat.ClearPlayers();
	g_Sound.ClearSound();
}

void cLeis::HUD_Redraw()
{
	g_Menu.DrawMenu( g_Screen.iWidth / 2 - MENU_ALL_WIDTH , 70 , true );

	if ( cvar.radar_enable && g_Local.bAlive )
		g_Radar.DrawGuiRadar( cvar.rad_x , cvar.rad_y );

	if( cvar.esp_sound && g_Local.bAlive )
		g_Sound.DrawSoundEsp();

	g_Players.UpdatePlayerInfo();

	if ( cvar.esp_bomb || cvar.esp_bombtimer )
	{
		for ( int i = 0; i <= g_pClientEntList->GetHighestEntityIndex(); i++ )
		{
			CBaseAttributableItem* pEntity = (CBaseAttributableItem*)g_pClientEntList->GetClientEntity( i );

			if ( !pEntity || IsBadReadPtr( (PVOID)pEntity , sizeof( CBaseAttributableItem ) ) )
				continue;

			if ( cvar.esp_w_weapon )
			{
				for ( int w = 0; w < WEAPONS_ID_DATA_SIZE; w++ )
				{
					if ( pEntity->GetClientClass()->m_ClassID == WeaponsEspClassID[w] )
					{
						Vector vWeaponsPos;

						if ( WorldToScreen( pEntity->GetAbsOrigin() , vWeaponsPos ) && *pEntity->GetOwnerEntity() == -1 )
						{
							if ( w == 0 && pEntity->GetClientClass()->m_ClassID == CC_CDEagle && *pEntity->GetItemDefinitionIndex() == WEAPON_DEAGLE )
							{
								g_FontEsp.DrawString( vWeaponsPos.x , vWeaponsPos.y , Color( 255 , 255 , 255 ) , true , pWeaponData[w] );
							}
							else if ( w == 5 && pEntity->GetClientClass()->m_ClassID == CC_CWeaponP250 && *pEntity->GetItemDefinitionIndex() == WEAPON_P250 )
							{
								g_FontEsp.DrawString( vWeaponsPos.x , vWeaponsPos.y , Color( 255 , 255 , 255 ) , true , pWeaponData[w] );
							}
							else if ( w == 7 && pEntity->GetClientClass()->m_ClassID == CC_CWeaponP250 && *pEntity->GetItemDefinitionIndex() == WEAPON_CZ75A )
							{
								g_FontEsp.DrawString( vWeaponsPos.x , vWeaponsPos.y , Color( 255 , 255 , 255 ) , true , pWeaponData[w] );
							}
							else if ( w == 8 && pEntity->GetClientClass()->m_ClassID == CC_CDEagle && *pEntity->GetItemDefinitionIndex() == WEAPON_REVOLVER )
							{
								g_FontEsp.DrawString( vWeaponsPos.x , vWeaponsPos.y , Color( 255 , 255 , 255 ) , true , pWeaponData[w] );
							}
							else if ( w != 0 && w != 5 && w != 7 && w != 8 )
							{
								g_FontEsp.DrawString( vWeaponsPos.x , vWeaponsPos.y , Color( 255 , 255 , 255 ) , true , pWeaponData[w] );
							}

							//g_pRenderer->RenderText( vWeaponsPos.x , vWeaponsPos.y + 15 , Color( 255 , 255 , 255 ) , true , nt_itoa( pEntity->GetClientClass()->m_ClassID ) );
						}
					}
				}
			}

			if ( cvar.esp_w_grenade )
			{
				for ( int g = 0; g < GRENADE_ID_DATA_SIZE; g++ )
				{
					if ( pEntity->GetClientClass()->m_ClassID == GrenadeEspClassID[g] )
					{
						Vector vGrenadePos( 0 , 0 , 0 );

						if ( WorldToScreen( pEntity->GetAbsOrigin() , vGrenadePos ) )
						{
							g_FontEsp.DrawString( vGrenadePos.x , vGrenadePos.y , Color( 255 , 140 , 0 ) , true , GrenadeEpsName[g] );
						}
					}
				}
			}

			if ( pEntity->GetClientClass()->m_ClassID == CC_CPlantedC4 || pEntity->GetClientClass()->m_ClassID == CC_CC4 )
			{
				Vector vPlantPos = Vector( 0 , 0 , 0 );

				if ( cvar.esp_bomb && WorldToScreen( pEntity->GetAbsOrigin() , vPlantPos ) )
				{
					if ( pEntity->GetClientClass()->m_ClassID == CC_CC4 && *pEntity->GetOwnerEntity() == -1 )
					{
						g_FontEsp.DrawString( vPlantPos.x , vPlantPos.y , Color( 255 , 255 , 255 ) , true , "c4" );
					}

					if ( pEntity->GetClientClass()->m_ClassID == CC_CPlantedC4 && g_Local.bC4Planted )
					{
						g_FontEsp.DrawString( vPlantPos.x , vPlantPos.y , Color( 255 , 255 , 255 ) , true , "c4_p" );
					}
				}

				if ( cvar.esp_bombtimer && g_Local.bC4Planted )
				{
					char szTimer1[20] = { 0 };
					static cTimer BombTimer;

					if ( BombTimer.delay( 1000 ) )
					{
						g_Local.m_c4timer--;
						BombTimer.reset();
					}

					lstrcpyA( szTimer1 , XorStr( "bomb time: " ) );
					lstrcatA( szTimer1 , nt_itoa( g_Local.m_c4timer ) );

					g_FontEsp.DrawString( g_Screen.iWidth / 2 , 50 , Color( 255 , 255 , 255 ) , true , szTimer1 );
				}
			}
		}
	}
}

void cLeis::CL_AimbotMove( CUserCmd* cmd )
{
	if ( g_Cheat.IsLocalWeaponUseAmmo() )
	{
		if ( cvar.weapon_settings[cvar.wpn].aim_enable )
			g_Aimbot.Aimbot( cmd );
	}
}

void cLeis::CL_CreateMove( float flInputSampleTime , CUserCmd* cmd )
{
	if ( !g_Local.bAlive && !g_Cheat.bLastDead )
	{
		g_Cheat.bLastDead = true;
	}
	else
	{
		if ( g_Cheat.bLastDead && g_Local.bAlive )
		{
			g_Cheat.ClearPlayers();
			g_Cheat.bLastDead = false;
		}
	}

	if( g_Cheat.IsLocalWeaponUseAmmo() )
	{
		cvar.wpn = cvar.GetIndexSettingsFromWeapon();

		if( cvar.weapon_settings[cvar.wpn].trigger_mode )
			g_Trigger.TriggerBot( cmd );
	}

	if ( cvar.misc_Bhop )
	{
		if ( cmd->buttons & IN_JUMP && !( g_Local.iFlags & FL_ONGROUND ) )
		{
			cmd->buttons &= ~IN_JUMP;
		}
	}
}