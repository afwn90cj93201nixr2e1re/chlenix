#include "_skins.h"

std::unordered_map<int , EconomyItemCfg> g_SkinChangerCfg;
std::unordered_map<int , const char*> g_ViewModelCfg;
std::unordered_map<const char* , const char*> g_KillIconCfg;

RecvVarProxyFn fnSequenceProxyFn = NULL;

/*
Bayonet - models/weapons/v_knife_bayonet.mdl						1
Flip Knife - models/weapons/v_knife_flip.mdl						2
Gut Knife - models/weapons/v_knife_gut.mdl							3
Karambit - models/weapons/v_knife_karam.mdl							4
M9 Bayonet - models/weapons/v_knife_m9_bay.mdl						5
Huntsman Knife - models/weapons/v_knife_tactical.mdl				6
Falchion Knife - models/weapons/v_knife_falchion_advanced­.mdl		7
Bowie Knife - models/weapons/v_knife_survival_bowie.md­l				8
Butterfly Knife - models/weapons/v_knife_butterfly.mdl				9
Shadow Daggers - models/weapons/v_knife_push.mdl					10
*/

void SetSkinConfig()
{
	// Ïèñòîëåòû
	g_SkinChangerCfg[WEAPON_DEAGLE].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_DEAGLE_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_ELITE].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_ELITE_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_FIVESEVEN].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_FIVESEVEN_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_GLOCK].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_GLOCK_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_HKP2000].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_HKP2000_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_P250].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_P250_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_USP_SILENCER].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_USP_S_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_CZ75A].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_CZ75A_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_REVOLVER].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_REVOLVER_STR , 0 , cvar.IniPatch );

	// Àâòîìàòû
	g_SkinChangerCfg[WEAPON_AK47].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_AK47_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_AUG].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_AUG_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_FAMAS].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_FAMAS_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_GALILAR].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_GALILAR_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_M249].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_M249_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_M4A1].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_M4A1_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_M4A1_SILENCER].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_M4A1_S_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_MAC10].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_MAC10_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_P90].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_P90_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_UMP45].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_UMP45_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_XM1014].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_XM1014_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_BIZON].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_BIZON_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_MAG7].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_MAG7_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_NEGEV].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_NEGEV_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_SAWEDOFF].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_SAWEDOFF_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_TEC9].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_TEC9_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_MP7].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_MP7_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_MP9].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_MP9_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_NOVA].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_NOVA_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_SG553].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_SG553_STR , 0 , cvar.IniPatch );

	// Ñíàéïåðêè
	g_SkinChangerCfg[WEAPON_AWP].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_AWP_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_G3SG1].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_G3SG1_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_SCAR20].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_SCAR20_STR , 0 , cvar.IniPatch );
	g_SkinChangerCfg[WEAPON_SSG08].nFallbackPaintKit = cvar.ReadInt( CFG_SKIN , WEAPON_SSG08_STR , 0 , cvar.IniPatch );
	
	int KnifeModelsType[10] =
	{
		WEAPON_KNIFE_BAYONET,WEAPON_KNIFE_FLIP,WEAPON_KNIFE_GUT,WEAPON_KNIFE_KARAMBIT,
		WEAPON_KNIFE_M9_BAYONET,WEAPON_KNIFE_TACTICAL,WEAPON_KNIFE_FALCHION,
		WEAPON_KNIFE_SURVIVAL_BOWIE,WEAPON_KNIFE_BUTTERFLY,WEAPON_KNIFE_PUSH
	};

	if ( cvar.knife_ct_model >= 1 && cvar.knife_ct_model <= 10 )
	{
		g_SkinChangerCfg[WEAPON_KNIFE].iItemDefinitionIndex = KnifeModelsType[cvar.knife_ct_model - 1];
	}
	if ( cvar.knife_ct_skin )
	{
		g_SkinChangerCfg[WEAPON_KNIFE].nFallbackPaintKit = cvar.knife_ct_skin;
	}

	if ( cvar.knife_tt_model )
	{
		g_SkinChangerCfg[WEAPON_KNIFE_T].iItemDefinitionIndex = KnifeModelsType[cvar.knife_tt_model - 1];
	}
	if ( cvar.knife_tt_model >= 1 && cvar.knife_tt_model <= 10 )
	{
		g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackPaintKit = cvar.knife_tt_skin;
	}
}

void SetModelConfig()
{
	char* pszDefaultCtModel = "models/weapons/v_knife_default_ct.mdl";
	char* pszDefaultTtModel = "models/weapons/v_knife_default_t.mdl";

	char* pszKnifeBayonet = "models/weapons/v_knife_bayonet.mdl";
	char* pszKnifeFlip = "models/weapons/v_knife_flip.mdl";
	char* pszKnifeGut = "models/weapons/v_knife_gut.mdl";
	char* pszKnifeKarambit = "models/weapons/v_knife_karam.mdl";
	char* pszKnifeM9Bay = "models/weapons/v_knife_m9_bay.mdl";
	char* pszKnifeHuntsman = "models/weapons/v_knife_tactical.mdl";
	char* pszKnifeFalchion = "models/weapons/v_knife_falchion_advanced.mdl";
	char* pszKnifeBowie = "models/weapons/v_knife_survival_bowie.mdl";
	char* pszKnifeButterfly = "models/weapons/v_knife_butterfly.mdl";
	char* pszKnifeShadow = "models/weapons/v_knife_push.mdl";

	char* pszKnifeModels[10] =
	{
		pszKnifeBayonet,pszKnifeFlip,pszKnifeGut,pszKnifeKarambit,
		pszKnifeM9Bay,pszKnifeHuntsman,pszKnifeFalchion,pszKnifeBowie,
		pszKnifeButterfly,pszKnifeShadow
	};

	int nOriginalKnifeCT = g_pModelInfo->GetModelIndex( pszDefaultCtModel );
	int nOriginalKnifeT = g_pModelInfo->GetModelIndex( pszDefaultTtModel );

	if ( cvar.knife_ct_model >= 1 && cvar.knife_ct_model <= 10 )
		g_ViewModelCfg[nOriginalKnifeCT] = pszKnifeModels[cvar.knife_ct_model - 1];

	if ( cvar.knife_tt_model >= 1 && cvar.knife_tt_model <= 10 )
		g_ViewModelCfg[nOriginalKnifeT] = pszKnifeModels[cvar.knife_tt_model - 1];
}

void SetKillIconCfg()
{
	char* pszKnifeModelsIcon[10] =
	{
		"bayonet","knife_flip","knife_gut","knife_karambit",
		"knife_m9_bayonet","knife_tactical","knife_falchion",
		"knife_survival_bowie","knife_butterfly","knife_push"
	};

	if ( cvar.knife_ct_model >= 1 && cvar.knife_ct_model <= 10 )
	{
		g_KillIconCfg["knife_default_ct"] = pszKnifeModelsIcon[cvar.knife_ct_model - 1];
	}
	if ( cvar.knife_tt_model >= 1 && cvar.knife_tt_model <= 10 )
	{
		g_KillIconCfg["knife_t"] = pszKnifeModelsIcon[cvar.knife_tt_model - 1];
	}
}

bool ApplyCustomSkin( CBaseAttributableItem* pWeapon , int nWeaponIndex )
{
	if ( g_SkinChangerCfg.find( nWeaponIndex ) == g_SkinChangerCfg.end() )
		return false;

	*pWeapon->GetFallbackPaintKit() = g_SkinChangerCfg[nWeaponIndex].nFallbackPaintKit;
	*pWeapon->GetEntityQuality() = g_SkinChangerCfg[nWeaponIndex].iEntityQuality;
	*pWeapon->GetFallbackWear() = g_SkinChangerCfg[nWeaponIndex].flFallbackWear;

	if ( g_SkinChangerCfg[nWeaponIndex].iItemDefinitionIndex )
		*pWeapon->GetItemDefinitionIndex() = g_SkinChangerCfg[nWeaponIndex].iItemDefinitionIndex;

	*pWeapon->GetItemIDHigh() = -1;

	return true;
}

bool ApplyCustomModel( IClientEntity* pLocal , CBaseAttributableItem* pWeapon , int nWeaponIndex )
{
	CBaseViewModel* pViewModel = pLocal->GetViewModel();
	
	if ( !pViewModel )
		return false;
	
	DWORD hViewModelWeapon = pViewModel->GetWeapon();
	CBaseAttributableItem* pViewModelWeapon = (CBaseAttributableItem*)g_pClientEntList->GetClientEntityFromHandle( hViewModelWeapon );

	if ( pViewModelWeapon != pWeapon )
		return false;

	int nViewModelIndex = pViewModel->GetModelIndex();

	if ( g_ViewModelCfg.find( nViewModelIndex ) == g_ViewModelCfg.end() )
		return false;

	pViewModel->SetWeaponModel( g_ViewModelCfg[nViewModelIndex] , pWeapon );
	
	return true;
}

bool ApplyCustomKillIcon( IGameEvent* pEvent )
{
	int nUserID = pEvent->GetInt( XorStr( "attacker" ) );

	if ( !nUserID )
		return false;

	if ( g_pEngine->GetPlayerForUserID( nUserID ) != g_pEngine->GetLocalPlayer() )
		return false;

	const char* szWeapon = pEvent->GetString( XorStr( "weapon" ) );

	for ( auto ReplacementIcon : g_KillIconCfg )
	{
		if ( !strcmp( szWeapon , ReplacementIcon.first ) )
		{

			pEvent->SetString( XorStr( "weapon" ) , ReplacementIcon.second );

			break;
		}

	}

	return true;
}

bool WINAPI FireEventClientSideThink( IGameEvent* pEvent )
{
	bool RET = false;

	if ( !pEvent )
	{
		GameEventTable.UnHook();
		RET = g_pGameEventMgr->FireEventClientSide( pEvent );
		GameEventTable.ReHook();
		return RET;
	}

	if ( cvar.esp_bombtimer )
	{
		if ( !strcmp( pEvent->GetName() , XorStr( "bomb_defused" ) ) || !strcmp( pEvent->GetName() , XorStr( "bomb_exploded" ) ) )
		{
			g_Local.bC4Planted = false;
		}
		else if ( !strcmp( pEvent->GetName() , XorStr( "bomb_planted" ) ) )
		{
			g_Local.bC4Planted = true;
			g_Local.m_c4timer = cvar.esp_bombtimer;
		}
	}
	else
	{
		g_Local.bC4Planted = false;
	}

	if ( !strcmp( pEvent->GetName() , XorStr( "round_start" ) ) || !strcmp( pEvent->GetName() , XorStr( "player_connect_full" ) ) )
	{
		g_Cheat.ClearPlayers();
		g_Sound.sound.clear();
		g_Local.bC4Planted = false;
		g_Local.m_c4timer = cvar.esp_bombtimer;
	}

	if ( !strcmp( pEvent->GetName() , XorStr( "player_death" ) ) )
		ApplyCustomKillIcon( pEvent );

	if ( !strcmp( pEvent->GetName() , XorStr( "game_newmap" ) ) )
	{
		if ( g_ViewModelCfg.size() >= 1 )
			g_ViewModelCfg.clear();

		SetModelConfig();
	}

	GameEventTable.UnHook();
	RET = g_pGameEventMgr->FireEventClientSide( pEvent );
	GameEventTable.ReHook();

	return RET;
}

void SetViewModelSequence( const CRecvProxyData *pDataConst , void *pStruct , void *pOut )
{
	CRecvProxyData* pData = const_cast<CRecvProxyData*>( pDataConst );
	CBaseViewModel* pViewModel = (CBaseViewModel*)pStruct;

	if ( pViewModel )
	{
		IClientEntity* pOwner = g_pClientEntList->GetClientEntityFromHandle( pViewModel->GetOwner() );

		if ( pOwner && pOwner->Index() == g_pEngine->GetLocalPlayer() )
		{
			void* pModel = g_pModelInfo->GetModel( pViewModel->GetModelIndex() );
			string szModel = g_pModelInfo->GetModelName( pModel );

			int m_nSequence = pData->m_Value.m_Int;

			if ( !strcmp( szModel.c_str() , XorStr( "models/weapons/v_knife_butterfly.mdl" ) ) )
			{
				switch ( m_nSequence )
				{
					case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = RandomInt( SEQUENCE_BUTTERFLY_DRAW , SEQUENCE_BUTTERFLY_DRAW2 ); break;
					case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt( SEQUENCE_BUTTERFLY_LOOKAT01 , SEQUENCE_BUTTERFLY_LOOKAT03 ); break;
					default:
					m_nSequence++;
				}
			}
			else if ( !strcmp( szModel.c_str() , XorStr( "models/weapons/v_knife_falchion_advanced.mdl" ) ) )
			{
				switch ( m_nSequence )
				{
					case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt( SEQUENCE_FALCHION_HEAVY_MISS1 , SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP ); break;
					case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt( SEQUENCE_FALCHION_LOOKAT01 , SEQUENCE_FALCHION_LOOKAT02 ); break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
					break;
					default:
					m_nSequence--;
				}
			}
			else if ( !strcmp( szModel.c_str() , XorStr( "models/weapons/v_knife_push.mdl" ) ) )
			{
				switch ( m_nSequence )
				{
					case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
					case SEQUENCE_DEFAULT_LIGHT_MISS1:
					case SEQUENCE_DEFAULT_LIGHT_MISS2:
					m_nSequence = RandomInt( SEQUENCE_DAGGERS_LIGHT_MISS1 , SEQUENCE_DAGGERS_LIGHT_MISS5 ); break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt( SEQUENCE_DAGGERS_HEAVY_MISS2 , SEQUENCE_DAGGERS_HEAVY_MISS1 ); break;
					case SEQUENCE_DEFAULT_HEAVY_HIT1:
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
					case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence += 3; break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
					break;
					default:
					m_nSequence += 2;
				}
			}
			else if ( !strcmp( szModel.c_str() , XorStr( "models/weapons/v_knife_survival_bowie.mdl" ) ) )
			{
				switch ( m_nSequence )
				{
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
					break;
					case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_BOWIE_IDLE1; break;
					default:
					m_nSequence--;
				}
			}

			pData->m_Value.m_Int = m_nSequence;
		}
	}
	
	fnSequenceProxyFn( pData , pStruct , pOut );
}

void InitalizeSkins()
{
	SetSkinConfig();

	SetKillIconCfg();

	for ( ClientClass* pClass = g_pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext )
	{
		if ( !strcmp( pClass->m_pNetworkName , XorStr( "CBaseViewModel" ) ) )
		{
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for ( int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++ )
			{
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if ( !pProp || strcmp( pProp->m_pVarName , XorStr( "m_nSequence" ) ) )
					continue;

				fnSequenceProxyFn = pProp->m_ProxyFn;

				pProp->m_ProxyFn = (RecvVarProxyFn)SetViewModelSequence;

				break;
			}

			break;
		}
	}
}