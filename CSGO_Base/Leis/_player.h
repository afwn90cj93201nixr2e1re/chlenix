#pragma once

#include "../main.h"

struct weapon_data
{
	byte type;
	char name[25];
};

struct local_s
{
	int iTeam;
	int iIndex;

	int iHealth;
	int iArmor;
	int iFOV;

	int iShotsFired;
	int iCrossHairID;

	int Effects;
	int iFlags;
	int iClip1;
	int iItemDefinitionIndex;
	int m_c4timer;
	
	bool bAlive;
	bool bC4Planted;

	Vector vOrigin;
	Vector vViewOffset;
	Vector vEyeOrigin;
	
	QAngle EyeAngles;

	char name[MAX_PLAYER_NAME_LENGTH];
	weapon_data weapon;
	
	IClientEntity* pEntity;
	IClientEntity* pWeapon;
};

struct player_s
{
	int iTeam;
	int iIndex;

	int iHealth;
	int iArmor;

	int Effects;
	int iItemDefinitionIndex;
	int iFov;

	bool bAlive;
	bool bVisible;
	bool bAimFov;
	bool bTriggerFov;

	float fDistance;

	Vector vOrigin;
	Vector vAimOrigin;
	Vector vOldOrigin;

	QAngle EyeAngles;
	
	char name[MAX_PLAYER_NAME_LENGTH];
	weapon_data weapon;

	IClientEntity* pEntity;
};

class cPlayers
{
public:

	void UpdateLocalEntity();
	void UpdatePlayerInfo();
};

extern local_s g_Local;
extern player_s g_Player[ABSOLUTE_PLAYER_LIMIT];
extern cPlayers g_Players;