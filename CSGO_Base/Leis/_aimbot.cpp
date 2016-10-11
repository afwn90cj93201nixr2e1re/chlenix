#include "_aimbot.h"

cAimbot g_Aimbot;

Vector cAimbot::vCalcBoneOffset( int iIndex )
{
	int boneTarger = 0;
	float screenDist = 1000.f;
	Vector vBoneOrigin , vBoneScreen , vF , vR , vU , vOut;
	vOut = Vector( 0 , 0 , 0 );

	AngleVectors( g_Player[iIndex].EyeAngles , vF , vR , vU );

	IClientEntity* Ent = g_Player[iIndex].pEntity;

	if ( !g_Player[iIndex].bAlive )
		return vOut;

	int Bone = cvar.weapon_settings[cvar.wpn].aim_bone;

	if ( cvar.weapon_settings[cvar.wpn].aim_silent && g_Local.iShotsFired < 1 )
	{
		GetBonePosition( Ent , vBoneOrigin , 6 );
		vOut = vBoneOrigin + vF + vR + vU;
	}
	else
	{
		if ( Bone >= 1 && Bone <= 6 && cvar.weapon_settings[cvar.wpn].aim_smart <= 0 )
		{
			GetBonePosition( Ent , vBoneOrigin , Bone );
			vOut = vBoneOrigin + vF + vR + vU;
		}
		else if ( cvar.weapon_settings[cvar.wpn].aim_smart )
		{
			Vector vBoneArray[7];

			for ( int i = 1; i <= 6; i++ )
			{
				if ( GetBonePosition( Ent , vBoneOrigin , i ) && WorldToScreen( vBoneOrigin , vBoneScreen ) )
				{
					vBoneArray[i] = vBoneOrigin;

					Vector vDest;
					vDest.x = float( g_Screen.iWidth / 2 );
					vDest.y = float( g_Screen.iHeight / 2 );

					float fDist = CalcDistPlayerScreen( vDest.AsVector2D() , vBoneScreen.AsVector2D() );

					if ( fDist < screenDist )
					{
						screenDist = fDist;
						boneTarger = i;
					}
				}
				else
				{
					vBoneArray[i] = Vector( 0 , 0 , 0 );
				}
			}

			if ( boneTarger && vBoneArray[boneTarger].IsValid() )
				vOut = vBoneArray[boneTarger] + vF + vR + vU;
		}
	}

	return vOut;
}

int cAimbot::GetPlayerFov( int iIndex )
{
	int iFovVal = 0;

	if ( cvar.weapon_settings[cvar.wpn].aim_silent && g_Local.iShotsFired < 1 )
		iFovVal = cvar.weapon_settings[cvar.wpn].aim_silent_fov;
	else
		iFovVal = cvar.weapon_settings[cvar.wpn].aim_fov;

	int base_fov = pow( 60 + iFovVal , 2 ) * 90;
	int iFov = (int)( base_fov / ( g_Player[iIndex].fDistance * g_Local.iFOV ) );

	return iFov;
}

bool cAimbot::CheckFov( Vector vScreen , int iFov )
{
	Vector vDest;
	vDest.x = float( g_Screen.iWidth / 2 );
	vDest.y = float( g_Screen.iHeight / 2 );

	float fScrPos[2] =
	{
		nt_fabs( vDest.x - vScreen.x ),
		nt_fabs( vDest.y - vScreen.y )
	};

	return ( fScrPos[0] <= (float)iFov && fScrPos[1] <= (float)iFov );
}

void cAimbot::AngleNormalize( float* angles )
{
	if( angles[0] > 89.0f && angles[0] <= 180.0f )
		angles[0] = 89.0f;
	if( angles[0] > 180.f )
		angles[0] -= 360.f;
	if( angles[0] < -89.0f )
		angles[0] = -89.0f;
	if( angles[1] > 180.f )
		angles[1] -= 360.f;
	if( angles[1] < -180.f )
		angles[1] += 360.f;
	if( angles[2] != 0.0f )
		angles[2] = 0.0f;
}

void cAimbot::SmoothAimAngles( Vector MyViewAngles , Vector AimAngles , Vector &OutAngles , float Smoothing )
{
	VectorSubtract( AimAngles , MyViewAngles , OutAngles );

	AngleNormalize( OutAngles.Base() );

	OutAngles.x = OutAngles.x / Smoothing + MyViewAngles.x;
	OutAngles.y = OutAngles.y / Smoothing + MyViewAngles.y;

	AngleNormalize( OutAngles.Base() );
}

void cAimbot::UpdateTarget()
{
	float squareDist = 9999.9f;
	float center_screen[2];

	center_screen[0] = g_Screen.iWidth / 2;
	center_screen[1] = g_Screen.iHeight / 2;

	for( int i = 0; i < 32; i++ )
	{
		if( g_Local.iIndex == g_Player[i].iIndex || !g_Local.bAlive || !g_Player[i].bVisible || !g_Player[i].pEntity )
		{
			continue;
		}

		if( !g_Player[i].bAlive || g_Player[i].iTeam == g_Local.iTeam || !g_Player[i].vAimOrigin.IsValid() || !g_Player[i].bAimFov )
		{
			continue;
		}

		Vector vScreenPlayer;

		if( WorldToScreen( g_Player[i].vAimOrigin , vScreenPlayer ) )
		{
			float screen_dist = CalcDistPlayerScreen( center_screen , vScreenPlayer.AsVector2D() );

			if( screen_dist < squareDist )
			{
				squareDist = screen_dist;
				iTargetID = i;
			}
		}
	}
}

void cAimbot::AimSet( CUserCmd* cmd , Vector vSmoothAngles )
{
	if ( !dwShotTime )
		dwShotTime = GetTickCount();

	cmd->viewangles = vSmoothAngles;

	if ( cvar.weapon_settings[cvar.wpn].aim_delay )
	{
		if ( dwShotTime + cvar.weapon_settings[cvar.wpn].aim_delay >= GetTickCount() )
		{
			cmd->buttons &= ~IN_ATTACK;
		}
	}
}

void cAimbot::AimUpd( CUserCmd* cmd )
{
	QAngle qAimAngles;
	Vector vAimAngles , vSmoothAngles;

	if ( !g_Player[iTargetID].vAimOrigin.IsValid() )
		return;

	if ( !g_Player[iTargetID].vOldOrigin.IsValid() && cvar.weapon_settings[cvar.wpn].aim_smart && bAimType == 2 && !( cmd->buttons & IN_ATTACK ) )
	{
		g_Player[iTargetID].vOldOrigin = g_Player[iTargetID].vAimOrigin;
	}

	if ( cvar.weapon_settings[cvar.wpn].aim_smart && !cvar.weapon_settings[cvar.wpn].aim_silent )
	{
		if ( g_Player[iTargetID].vOldOrigin.IsValid() && bAimType == 2 )
		{
			VectorAnglesNew( ( g_Player[iTargetID].vOldOrigin - g_Local.vEyeOrigin ).Base() , qAimAngles.Base() );
		}
		else
		{
			VectorAnglesNew( ( g_Player[iTargetID].vAimOrigin - g_Local.vEyeOrigin ).Base() , qAimAngles.Base() );
		}
	}
	else
	{
		VectorAnglesNew( ( g_Player[iTargetID].vAimOrigin - g_Local.vEyeOrigin ).Base() , qAimAngles.Base() );
	}

	if ( ( cvar.weapon_settings[cvar.wpn].aim_rcsx || cvar.weapon_settings[cvar.wpn].aim_rcsy ) && g_Local.iShotsFired > 0 )
	{
		Vector vAimPunch = g_Local.pEntity->GetAimPunch();

		if ( cvar.weapon_settings[cvar.wpn].aim_rcsx )
			qAimAngles.x -= vAimPunch.x * ( cvar.weapon_settings[cvar.wpn].aim_rcsx * 0.2 );

		if ( cvar.weapon_settings[cvar.wpn].aim_rcsy )
			qAimAngles.y -= vAimPunch.y * ( cvar.weapon_settings[cvar.wpn].aim_rcsy * 0.2 );
	}

	vAimAngles.x = qAimAngles.x;
	vAimAngles.y = qAimAngles.y;

	AngleNormalize( vAimAngles.Base() );
	
	if ( cvar.weapon_settings[cvar.wpn].aim_smooth && !cvar.weapon_settings[cvar.wpn].aim_silent )
		SmoothAimAngles( cmd->viewangles , vAimAngles , vSmoothAngles , cvar.weapon_settings[cvar.wpn].aim_smooth );
	else
		vSmoothAngles = vAimAngles;

	AngleNormalize( vSmoothAngles.Base() );
	
	AimSet( cmd , vSmoothAngles );
}

void cAimbot::Update( CUserCmd* cmd )
{
	bAttack = ( cmd->buttons & IN_ATTACK );

	if ( !bAttack )
	{
		dwShotTime = 0;
		iTargetID = 0;
	}

	UpdateTarget();
}

void cAimbot::Aimbot( CUserCmd* cmd )
{
	Update( cmd );
	
	bAimType = 0;
	bAimEnable = true;

	if ( g_Local.weapon.type == WEAPON_TYPE_SHOTGUN )
		bAimType = 1; // mouse1 + fov
	else if ( g_Local.weapon.type == WEAPON_TYPE_PISTOL || g_Local.weapon.type == WEAPON_TYPE_SNIPER ) // fov + mouse1
	{
		bAimType = 2;

		if ( g_Local.iShotsFired == 1 )
			bAimEnable = false;
	}

	if ( iTargetID && bAimType && g_Local.iClip1 && bAimEnable )
	{
		switch ( bAimType )
		{
			case 1:
				if ( bAttack && g_Player[iTargetID].bAimFov )
					bAimAttack2 = true;
				else
					bAimAttack2 = false;
				break;
			case 2:
				if ( g_Player[iTargetID].bAimFov && !bAttack )
					bAimAttack1 = true;
				else if ( !g_Player[iTargetID].bAimFov && !bAttack )
					bAimAttack1 = false;
				else if ( !g_Player[iTargetID].bAimFov && bAttack )
					bAimAttack1 = false;
				
				if ( bAimAttack1 && g_Player[iTargetID].bAimFov )
					bAimAttack2 = true;
				else
					bAimAttack2 = false;

				break;
			default:
				bAimAttack1 = false;
				bAimAttack2 = false;
				break;
		}

		if ( bAimAttack2 && bAttack )
		{
			AimUpd( cmd );
		}
	}
}