#pragma once

#include "../main.h"

class cAimbot
{
public:

	byte bAimType;
	int iTargetID;
	bool bAttack;
	bool bAimAttack1;
	bool bAimAttack2;
	bool bAimEnable;
	DWORD dwShotTime;
	
	cAimbot()
	{
		bAimType = 0;
		iTargetID = 0;
		bAttack = false;
		bAimAttack1 = false;
		bAimAttack2 = false;
		bAimEnable = false;
		dwShotTime = 0;
	}

	Vector vCalcBoneOffset( int iIndex );

	int GetPlayerFov( int iIndex );
	bool CheckFov( Vector vScreen , int iFov );
	void AngleNormalize( float* angles );
	void SmoothAimAngles( Vector MyViewAngles , Vector AimAngles , Vector &OutAngles , float Smoothing );
	void UpdateTarget();
	void AimSet( CUserCmd* cmd , Vector vSmoothAngles );
	void AimUpd( CUserCmd* cmd );
	void Update( CUserCmd* cmd );
	void Aimbot( CUserCmd* cmd );
};

extern cAimbot g_Aimbot;