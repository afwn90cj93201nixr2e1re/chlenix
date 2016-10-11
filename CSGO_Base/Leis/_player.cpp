#include "_player.h"

local_s g_Local;
player_s g_Player[ABSOLUTE_PLAYER_LIMIT];
cPlayers g_Players;

void cPlayers::UpdateLocalEntity()
{
	player_info_t info;
	IClientEntity* pLocalEntity = g_pClientEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );

	if ( !pLocalEntity )
		return;

	if ( g_pEngine->GetPlayerInfo( pLocalEntity->Index() , &info ) )
	{
		g_Local.iTeam = pLocalEntity->GetTeamNum();
		g_Local.iIndex = pLocalEntity->Index();

		g_Local.iHealth = pLocalEntity->GetHealth();
		g_Local.iArmor = pLocalEntity->GetArmorValue();
		g_Local.iFOV = pLocalEntity->GetLocalFovStart();

		g_Local.iShotsFired = pLocalEntity->GetShotsFired();
		g_Local.iCrossHairID = *reinterpret_cast<int*>( (DWORD)pLocalEntity + (DWORD)m_iCrossHairID );

		g_Local.Effects = pLocalEntity->GetEffects();
		g_Local.iFlags = pLocalEntity->GetFlags();
		
		IClientEntity* pWeaponEntity = g_pClientEntList->GetClientEntityFromHandle( pLocalEntity->GetAcitveWeapon() );

		if ( pWeaponEntity )
		{
			g_Local.pWeapon = pWeaponEntity;
			g_Local.iClip1 = *reinterpret_cast<int*>( (DWORD)pWeaponEntity + (DWORD)m_iClip1 );

			if ( g_Local.iClip1 < 0 )
				g_Local.iClip1 = 0;

			g_Local.iItemDefinitionIndex = *reinterpret_cast<int*>( (DWORD)pWeaponEntity + (DWORD)m_iItemDefinitionIndex );
		}

		g_Local.bAlive = ( pLocalEntity->GetlifeState() == LIFE_ALIVE && g_Local.Effects != EF_NODRAW );

		g_Local.vOrigin = pLocalEntity->GetOrigin();
		g_Local.vViewOffset = pLocalEntity->GetViewOffset();
		g_Local.vEyeOrigin = g_Local.vOrigin + g_Local.vViewOffset;
		g_Local.EyeAngles = pLocalEntity->GetEyeAngles();

		g_Local.weapon = GetWeaponData( g_Local.iItemDefinitionIndex );
		g_Local.pEntity = pLocalEntity;
	}
}

void cPlayers::UpdatePlayerInfo()
{
	g_Players.UpdateLocalEntity();
	
	for ( int i = 1; i <= g_pEngine->GetMaxClients(); i++ )
	{
		player_info_t info;
		IClientEntity* pEntity = g_pClientEntList->GetClientEntity( i );

		if ( !pEntity || IsBadReadPtr( (PVOID)pEntity , sizeof( IClientEntity ) ) )
			continue;

		if ( pEntity->IsDormant() )
			continue;

		if ( pEntity->Index() == g_Local.iIndex )
			continue;

		if ( pEntity->GetClientClass()->m_ClassID == CC_CCSPlayer )
		{
			g_Player[i].iTeam = pEntity->GetTeamNum();
			g_Player[i].iIndex = pEntity->Index();

			g_Player[i].iHealth = pEntity->GetHealth();
			g_Player[i].iArmor = pEntity->GetArmorValue();

			g_Player[i].Effects = pEntity->GetEffects();

			IClientEntity* pWeaponEntity = g_pClientEntList->GetClientEntityFromHandle( pEntity->GetAcitveWeapon() );

			if ( pWeaponEntity )
			{
				g_Player[i].iItemDefinitionIndex = *reinterpret_cast<int*>( (DWORD)pWeaponEntity + (DWORD)m_iItemDefinitionIndex );
			}

			g_Player[i].bAlive = ( pEntity->GetlifeState() == LIFE_ALIVE && g_Player[i].Effects != EF_NODRAW && g_Player[i].iHealth > 0 );

			Vector vBoneVis , vTriggerChest;

			GetBonePosition( pEntity , vBoneVis , 6 );
			GetBonePosition( pEntity , vTriggerChest , 2 );

			bool bBoneVisible = GetVisible( g_Local.vEyeOrigin , vBoneVis );
			bool bChestVisible = GetVisible( g_Local.vEyeOrigin , vTriggerChest );

			g_Player[i].bVisible = ( bBoneVisible || bChestVisible );
	
			g_Player[i].vOrigin = pEntity->GetOrigin();
			g_Player[i].EyeAngles = pEntity->GetEyeAngles();
									
			if ( g_pEngine->GetPlayerInfo( i , &info ) )
				nt_strcpy( g_Player[i].name , info.m_szPlayerName );

			g_Player[i].weapon = GetWeaponData( g_Player[i].iItemDefinitionIndex );
			g_Player[i].pEntity = pEntity;

			g_Player[i].fDistance = g_Local.vOrigin.DistTo( g_Player[i].vOrigin );
			g_Player[i].bAimFov = false;

			if ( g_Player[i].bAlive && !g_Player[i].bVisible && cvar.esp_glow && !g_pEngine->IsTakingScreenshot() )
			{
				DWORD dwGlowArr = (DWORD)offset.dwClientModule + (DWORD)m_dwGlowObject;
				DWORD dwGlowCnt = *(PDWORD)( dwGlowArr + 4 );
				
				for ( DWORD g = 0; g < dwGlowCnt; g++ )
				{
					GlowObjectDefinition_t* dwGlowObj = (GlowObjectDefinition_t*)( *(PDWORD)dwGlowArr + g * sizeof( GlowObjectDefinition_t ) );

					if ( dwGlowObj && dwGlowObj->pEntity && dwGlowObj->pEntity == g_Player[i].pEntity )
					{
						float r , g , b;

						if ( g_Player[i].iTeam == TEAM_TT )
						{
							r = 255.f , g = 0.f , b = 0.f;
						}
						else if ( g_Player[i].iTeam == TEAM_CT )
						{
							r = 0 , g = 197.f , b = 205.f;
						}

						dwGlowObj->a = 255.f / 255.f;
						dwGlowObj->r = r / 255.f;
						dwGlowObj->g = g / 255.f;
						dwGlowObj->b = b / 255.f;
						dwGlowObj->m_bRenderWhenOccluded = true;
						dwGlowObj->m_bRenderWhenUnoccluded = true;
						dwGlowObj->m_bFullBloom = false;
					}
				}
			}

			if ( cvar.weapon_settings[cvar.wpn].aim_enable && g_Player[i].bVisible )
			{
				g_Player[i].vAimOrigin = g_Aimbot.vCalcBoneOffset( i );

				if ( g_Player[i].vAimOrigin.IsValid() )
				{
					Vector vAimScreen;

					int iFovVal = g_Aimbot.GetPlayerFov( i );

					if ( g_Local.iFOV == 90 )
						g_Player[i].iFov = iFovVal;
					else if ( g_Local.iFOV == 40 )
						g_Player[i].iFov = iFovVal * 2;
					else if ( g_Local.iFOV <= 15 )
						g_Player[i].iFov = iFovVal * 3;

					if ( WorldToScreen( g_Player[i].vAimOrigin , vAimScreen ) && g_Aimbot.CheckFov( vAimScreen , g_Player[i].iFov ) )
						g_Player[i].bAimFov = true;
					else
					{
						g_Player[i].vOldOrigin = Vector( 0 , 0 , 0 );
					}
				}
				else
				{
					g_Player[i].vAimOrigin = Vector( 0 , 0 , 0 );
					g_Player[i].vOldOrigin = Vector( 0 , 0 , 0 );
				}
			}
			else
			{
				g_Player[i].vAimOrigin = Vector( 0 , 0 , 0 );
				g_Player[i].vOldOrigin = Vector( 0 , 0 , 0 );
			}

			g_Esp.DrawPlayersESP( i );
		}
		else
		{
			g_Player[i].pEntity = nullptr;
		}
	}
}