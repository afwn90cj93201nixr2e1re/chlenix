#include "_esp.h"

cEsp g_Esp;

Color cEsp::GetPlayerTeamColor( int iIndex )
{
	Color TeamColor;

	if ( g_Player[iIndex].iTeam == TEAM_TT || g_Player[iIndex].iTeam == TEAM_CT )
	{
		if ( g_Player[iIndex].iTeam == TEAM_TT )
			TeamColor = Color( 255 , 64 , 64 );
		else if ( g_Player[iIndex].iTeam == TEAM_CT )
			TeamColor = Color( 0 , 164 , 255 );
	}
	else
		TeamColor = Color( 255 , 255 , 0 );

	return TeamColor;
}

Color cEsp::GetPlayerTeamVisibleColor( int iIndex )
{
	Color TeamVisibleColor;

	if ( g_Player[iIndex].iTeam == TEAM_TT || g_Player[iIndex].iTeam == TEAM_CT )
	{
		if ( g_Player[iIndex].iTeam == TEAM_TT )
			TeamVisibleColor = Color( 255 , 64 , 64 );
		else if ( g_Player[iIndex].iTeam == TEAM_CT )
			TeamVisibleColor = Color( 0 , 164 , 255 );

		// Подсвечивать зелёным видимых:
		if ( cvar.esp_visible <= 1 && g_Player[iIndex].iTeam != g_Local.iTeam && g_Player[iIndex].bVisible ) // Противников
			TeamVisibleColor = Color( 30 , 180 , 0 );
		else if ( cvar.esp_visible == 2 && g_Player[iIndex].iTeam == g_Local.iTeam && g_Player[iIndex].bVisible ) // Своих
			TeamVisibleColor = Color( 30 , 180 , 0 );
		else if( cvar.esp_visible == 3 && g_Player[iIndex].bVisible && g_Player[iIndex].iTeam != TEAM_SPEC )
			TeamVisibleColor = Color( 30 , 180 , 0 ); // Всех
	}
	else
		TeamVisibleColor = Color( 255 , 255 , 0 );

	return TeamVisibleColor;
}

bool cEsp::GetPlayerCheckTeam( int iIndex )
{
	bool CheckTeam = false;

	if ( !g_Player[iIndex].pEntity )
		return CheckTeam;

	// Показываем esp только на:
	if ( cvar.esp_team <= 1 && g_Player[iIndex].iTeam != g_Local.iTeam ) // Противников
		CheckTeam = true;
	else if ( cvar.esp_team == 2 && g_Player[iIndex].iTeam == g_Local.iTeam ) // Своих
		CheckTeam = true;
	else if ( cvar.esp_team == 3 && g_Player[iIndex].iTeam != TEAM_SPEC ) // Всех
		CheckTeam = true;

	if ( cvar.esp_visible >= 4 && !g_Player[iIndex].bVisible )
		CheckTeam = false;

	return CheckTeam;
}

void cEsp::DrawHealthArmorAmmoWpnEsp( int x , int y , int iIndex , Color color )
{
	int iHpAmY = 3;

	if ( cvar.esp_health == 1 )
	{
		char szHealthValue[8];

		nt_strcpy( szHealthValue , ESP_HP );
		nt_strcat( szHealthValue , nt_itoa( g_Player[iIndex].iHealth ) );

		g_FontEsp.DrawString( x , y + iHpAmY , color , true , szHealthValue );

		iHpAmY += 10;
	}

	if ( cvar.esp_armor == 1 )
	{
		char szArmorValue[8];

		nt_strcpy( szArmorValue , ESP_AR );
		nt_strcat( szArmorValue , nt_itoa( g_Player[iIndex].iArmor ) );

		g_FontEsp.DrawString( x , y + iHpAmY , color , true , szArmorValue );

		iHpAmY += 10;
	}

	if( cvar.esp_weapon >= 1 )
	{
		g_FontEsp.DrawString( x , y + iHpAmY , color , true , g_Player[iIndex].weapon.name );
	}
}

int GetRank( int Index )
{
	DWORD dwTemp = *(PDWORD)( (DWORD)offset.dwClientModule + CSPlayerResource );
	return *(PINT)( (DWORD)dwTemp + m_iCompetitiveRanking + (int)Index * 4 );
}

enum
{
	NotRanked ,
	SilverI ,
	SilverII ,
	SilverIII ,
	SilverIV ,
	SilverElite ,
	SilverEliteMaster ,
	GoldNovaI ,
	GoldNovaII ,
	GoldNovaIII ,
	GoldNovaMaster ,
	MasterGuardianI ,
	MasterGuardianII ,
	MasterGuardianElite ,
	DistinguishedMasterGuardian ,
	LegendaryEagle ,
	LegendaryEagleMaster ,
	SupremeMasterFirstClass ,
	TheGlobalElite
};

char* rank_names[] =
{
	"NotRanked","SilverI","SilverII","SilverIII","SilverIV","SilverElite","SilverEliteMaster",
	"GoldNovaI","GoldNovaII","GoldNovaIII","GoldNovaMaster","MasterGuardianI",
	"MasterGuardianII","MasterGuardianElite","DistinguishedMasterGuardian",
	"LegendaryEagle","LegendaryEagleMaster","SupremeMasterFirstClass","TheGlobalElite"
};

void cEsp::DrawAllPlayerEsp( int iIndex )
{
	Color TeamColor = GetPlayerTeamColor( iIndex );
	Color TeamVisibleColor = GetPlayerTeamVisibleColor( iIndex );

	bool CheckTeam = GetPlayerCheckTeam( iIndex );

	if( cvar.weapon_settings[cvar.wpn].trigger_mode )
	{
		g_Trigger.TriggerShowStatus();
	}

	if ( g_Player[iIndex].bAlive && CheckTeam )
	{
		Vector vHead , vScreenHead , vOrigin , vScreenOrigin , vLineOrigin;

		if ( GetBonePosition( g_Player[iIndex].pEntity , vHead , 6 ) )
		{
			vOrigin = g_Player[iIndex].vOrigin;

			vHead.z += cvar.esp_size;
			vOrigin.z -= cvar.esp_size;

			if ( WorldToScreen( vHead , vScreenHead ) && WorldToScreen( vOrigin , vScreenOrigin ) )
			{
				float Height = vScreenOrigin.y - vScreenHead.y;
				float Width = Height / 2.f;
				float fDrawX = vScreenHead.x - Width / 2.f;

				vLineOrigin = vScreenHead;
				vLineOrigin.y += Height;

				if ( cvar.esp_size )
				{
					if ( cvar.esp_type <= 1 )
					{
						g_Draw.DrawOutlineBox( (int)fDrawX , (int)vScreenHead.y , (int)Width , (int)Height , TeamVisibleColor , true );
					}
					else if ( cvar.esp_type >= 2 )
					{
						g_Draw.DrawOutlineCoalBox( (int)fDrawX , (int)vScreenHead.y , (int)Width , (int)Height , TeamVisibleColor , true );
					}
				}

				if ( cvar.esp_name )
				{
					byte offset_draw = 13;

					if ( cvar.esp_rank && GetRank( iIndex ) )
						offset_draw = 26;

					g_FontEsp.DrawString( (int)vLineOrigin.x , (int)vScreenHead.y - offset_draw , TeamColor , true , g_Player[iIndex].name );
				}

				if ( cvar.esp_rank )
				{
					byte rank_index = GetRank( iIndex );

					byte offset_draw = 26;

					if ( cvar.esp_name )
						offset_draw = 13;

					if ( rank_index )
					{

						g_FontEsp.DrawString( (int)vLineOrigin.x , (int)vScreenHead.y - offset_draw , TeamColor , true , rank_names[rank_index] );
					}
				}

				int iHpAmY = 1;

				if ( cvar.esp_health == 2 )
				{
					g_Draw.DrawHorBar( (int)fDrawX , (int)vLineOrigin.y + iHpAmY , (int)Width , 5 ,
									   g_Player[iIndex].iHealth ,
									   Color( 0 , 255 , 0 ) , Color( 255 , 0 , 0 ) );

					iHpAmY += 6;
				}
				else if ( cvar.esp_health >= 3 )
				{
					g_Draw.DrawVerBar( (int)fDrawX - 6 , (int)vScreenHead.y , 5 , (int)Height ,
									   g_Player[iIndex].iHealth ,
									   Color( 0 , 255 , 0 ) , Color( 255 , 0 , 0 ) );
				}

				if ( cvar.esp_armor == 2 )
				{
					g_Draw.DrawHorBar( (int)fDrawX , (int)vLineOrigin.y + iHpAmY , (int)Width , 5 ,
									   g_Player[iIndex].iArmor ,
									   Color( 255 , 255 , 255 ) , Color( 255 , 0 , 0 ) );

					iHpAmY += 6;
				}
				else if ( cvar.esp_armor >= 3 )
				{
					g_Draw.DrawVerBar( (int)fDrawX + (int)Width + 1 , (int)vScreenHead.y , 5 , (int)Height ,
									   g_Player[iIndex].iArmor ,
									   Color( 255 , 255 , 255 ) , Color( 255 , 0 , 0 ) );
				}

				DrawHealthArmorAmmoWpnEsp( (int)vLineOrigin.x , (int)vLineOrigin.y + iHpAmY - 3 , iIndex , TeamColor );
			}
		}
	}
}

void cEsp::DrawPlayersESP( int iIndex )
{
	Vector vAimOriginPos;

	bool aim_bone_fov = ( (bool)cvar.esp_aimbone || (bool)cvar.esp_drawfov );

	if ( cvar.weapon_settings[cvar.wpn].aim_enable && aim_bone_fov &&
		 g_Player[iIndex].vAimOrigin.IsValid() && g_Player[iIndex].bAlive &&  g_Player[iIndex].iTeam != g_Local.iTeam )
	{
		if ( WorldToScreen( g_Player[iIndex].vAimOrigin , vAimOriginPos ) )
		{
			if ( cvar.esp_aimbone )
			{
				g_Draw.DrawBox( vAimOriginPos.x , vAimOriginPos.y , 1 , 1 , Color( 255 , 255 , 255 ) );
			}

			if ( cvar.esp_drawfov )
			{
				int fov = g_Aimbot.GetPlayerFov( iIndex ) * 2;
				g_Draw.DrawBox( vAimOriginPos.x - g_Player[iIndex].iFov , vAimOriginPos.y - g_Player[iIndex].iFov , fov , fov , Color( 255 , 255 , 0 ) );
			}
		}
	}
		
	//g_FontEsp.DrawString( g_Screen.iWidth / 2 , 80 , Color( 0 , 255 , 0 ) , true , nt_itoa( g_Trigger.dwTriggerTime ) );
	//g_FontEsp.DrawString( g_Screen.iWidth / 2 , 95 , Color( 0 , 255 , 0 ) , true , nt_itoa( (int)g_Trigger.CheckPlayerTriggerPos() ) );
	//g_FontEsp.DrawString( g_Screen.iWidth / 2 , 80 , Color( 0 , 255 , 0 ) , true , nt_itoa( (int)g_Local.iShotsFired ) );
	//g_FontEsp.DrawString( g_Screen.iWidth / 2 , 95 , Color( 0 , 255 , 0 ) , true , nt_itoa( (int)g_Aimbot.bAimAttack1 ) );
	//g_FontEsp.DrawString( g_Screen.iWidth / 2 , 110 , Color( 0 , 255 , 0 ) , true , nt_itoa( (int)g_Aimbot.bAimAttack2 ) );
	

	if( cvar.radar_enable && g_Player[iIndex].bAlive && g_Local.bAlive )
		g_Radar.DrawRadarPlayer( iIndex );

	DrawAllPlayerEsp( iIndex );
}