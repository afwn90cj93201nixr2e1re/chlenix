#pragma once

#include "_cvar.h"

#include <unordered_map>

struct EconomyItemCfg
{
	int iItemDefinitionIndex = 0;
	int nFallbackPaintKit = 0;
	int iEntityQuality = 4;
	float flFallbackWear = 0.1f;
};

extern std::unordered_map<int , EconomyItemCfg> g_SkinChangerCfg;
extern std::unordered_map<int , const char*> g_ViewModelCfg;
extern std::unordered_map<const char* , const char*> g_KillIconCfg;

void SetSkinConfig();
void SetModelConfig();
void SetKillIconCfg();

bool ApplyCustomSkin( CBaseAttributableItem* pWeapon , int nWeaponIndex );
bool ApplyCustomModel( IClientEntity* pLocal , CBaseAttributableItem* pWeapon , int nWeaponIndex );
bool ApplyCustomKillIcon( IGameEvent* pEvent );

bool WINAPI FireEventClientSideThink( IGameEvent* pEvent );
void SetViewModelSequence( const CRecvProxyData *pDataConst , void *pStruct , void *pOut );

void InitalizeSkins();