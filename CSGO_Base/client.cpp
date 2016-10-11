#include "main.h"

bool InitalizeHack = false;

IMaterial* visible_flat = nullptr;
IMaterial* visible_tex = nullptr;
IMaterial* hidden_flat = nullptr;
IMaterial* hidden_tex = nullptr;

void InitHack()
{
	if (!InitalizeHack)
	{
			g_Leis.InitHack();

			visible_flat = CreateMaterial(true, false, false);
			visible_tex = CreateMaterial(false, false, false);
			hidden_flat = CreateMaterial(true, true, false);
			hidden_tex = CreateMaterial(false, true, false);

			InitalizeHack = true;
		}
	}

void WINAPI LevelShutdown()
{
	g_Cheat.ClearPlayers();
	g_Sound.ClearSound();

	ClientTable.UnHook();
	g_pClient->LevelShutdown();
	ClientTable.ReHook();
}

void WINAPI HudUpdate(bool bActive)
{
	if (bActive)
	{
		InitHack();
	}

	ClientTable.UnHook();
	g_pClient->HudUpdate(bActive);
	ClientTable.ReHook();
}

void HUD_Redraw(const char* pszName, unsigned int vguiPanel)
{
	int iWidth = 0;
	int iHeight = 0;

	g_pEngine->GetScreenSize(iWidth, iHeight);

	if (InitalizeHack && iWidth != g_Screen.iWidth && iHeight != g_Screen.iHeight)
	{
		InitalizeHack = false;
	}

	g_Screen.iWidth = iWidth;
	g_Screen.iHeight = iHeight;

	if (nt_strcmp((char*)pszName, MAT_SYSTEM_TOP_PANEL) == 0)
	{
		if (!g_pEngine->IsTakingScreenshot() && !g_pEngine->IsInGame() && !g_pEngine->IsConnected())
		{
			g_FontEsp.DrawString(3, 3, Color(255, 255, 255), false, CFG_LEIS_MESSAGE);
		}

		if (!g_pEngine->IsTakingScreenshot() && g_pEngine->IsInGame() && g_pEngine->IsConnected())
		{
			g_Leis.HUD_Redraw();
		}
	}
}

void WINAPI PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	PanelTable.UnHook();
	g_pPanel->PaintTraverse(vguiPanel, forceRepaint, allowForce);
	PanelTable.ReHook();

	if (InitalizeHack)
	{
		const char* szName = g_pPanel->GetName(vguiPanel);
		HUD_Redraw(szName, vguiPanel);
	}
}

void CL_CreateMove_ClientTable(int sequence_number, float input_sample_frametime, bool active)
{
	CUserCmd* pCmd = g_pInput->GetUserCmd(sequence_number);

	if (!pCmd)
		return;

	CVerifiedUserCmd* pVerified = g_pInput->GetVerifiedUserCmd(sequence_number);

	if (!pVerified)
		return;

	static int tick_send = 0;

	Vector vView = pCmd->viewangles;
	float fSide = pCmd->sidemove;
	float fForw = pCmd->forwardmove;

	if (pCmd->buttons & IN_ATTACK)
	{
		if (tick_send < 1)
		{
			g_Leis.CL_AimbotMove(pCmd);
		}
		else
		{
			pCmd->viewangles = vView;
			pCmd->sidemove = fSide;
			pCmd->forwardmove = fForw;

			g_Aimbot.Update(pCmd);
		}

		tick_send++;
	}
	else
	{
		pCmd->viewangles = vView;
		pCmd->sidemove = fSide;
		pCmd->forwardmove = fForw;

		g_Aimbot.Update(pCmd);
		tick_send = 0;
	}

	pVerified->m_cmd = *pCmd;
	pVerified->m_crc = pCmd->GetChecksum();
}

void WINAPI CreateMove_ClientTable(int sequence_number, float input_sample_frametime, bool active)
{
	ClientTable.UnHook();
	g_pClient->CreateMove(sequence_number, input_sample_frametime, active);
	ClientTable.ReHook();

	if (g_pEngine->IsActiveApp())
	{
		if (cvar.weapon_settings[cvar.wpn].aim_silent && g_Local.iShotsFired < 1)
		{
			CL_CreateMove_ClientTable(sequence_number, input_sample_frametime, active);
		}
	}
}

bool WINAPI CreateMove_ClientModeTable(float flInputSampleTime, CUserCmd* cmd)
{
	if (g_pEngine->IsActiveApp())
	{
		g_Leis.CL_CreateMove(flInputSampleTime, cmd);

		if (cvar.weapon_settings[cvar.wpn].aim_silent <= 0)
		{
			g_Leis.CL_AimbotMove(cmd);
		}
		else if (cvar.weapon_settings[cvar.wpn].aim_silent && g_Local.iShotsFired >= 1)
		{
			g_Leis.CL_AimbotMove(cmd);
		}
	}

	ClientModeTable.UnHook();
	bool ret = g_pClientMode->CL_CreateMove(flInputSampleTime, cmd);
	ClientModeTable.ReHook();

	return ret;
}

int WINAPI EmitSound1(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
	float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
	const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1)
{
	if (g_Local.bAlive && pOrigin && g_Local.vEyeOrigin.IsValid())
	{
		IClientEntity* pEnt = g_pClientEntList->GetClientEntity(iEntIndex);

		if (pEnt && g_Player[iEntIndex].iTeam != g_Local.iTeam)
		{

			if (!GetVisible(g_Local.vEyeOrigin, *pOrigin))
				g_Sound.AddSound(*pOrigin);
		}
	}

	SoundTable.UnHook();
	int ret = g_pSound->EmitSound1(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
		flVolume, iSoundlevel, nSeed, iFlags, iPitch,
		pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
	SoundTable.ReHook();
	return ret;
}

int WINAPI EmitSound2(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
	float flVolume, float flAttenuation, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
	const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1)
{
	if (g_Local.bAlive && pOrigin && g_Local.vEyeOrigin.IsValid())
	{
		IClientEntity* pEnt = g_pClientEntList->GetClientEntity(iEntIndex);

		if (pEnt && g_Player[iEntIndex].iTeam != g_Local.iTeam)
		{
			if (!GetVisible(g_Local.vEyeOrigin, *pOrigin))
				g_Sound.AddSound(*pOrigin);
		}
	}

	SoundTable.UnHook();
	int ret = g_pSound->EmitSound2(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
		flVolume, flAttenuation, nSeed, iFlags, iPitch,
		pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
	SoundTable.ReHook();
	return ret;
}

void WINAPI FrameStageNotify(ClientFrameStage_t Stage)
{
	while (Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		int nLocalPlayerID = g_pEngine->GetLocalPlayer();
		IClientEntity* pLocal = (IClientEntity*)g_pClientEntList->GetClientEntity(nLocalPlayerID);

		if (!pLocal || pLocal->GetlifeState() != LIFE_ALIVE)
			break;

		UINT* hWeapons = pLocal->GetWeapons();

		if (!hWeapons)
			break;

		player_info_t LocalPlayerInfo;
		g_pEngine->GetPlayerInfo(nLocalPlayerID, &LocalPlayerInfo);

		for (int nIndex = 0; hWeapons[nIndex]; nIndex++)
		{
			CBaseAttributableItem* pWeapon = (CBaseAttributableItem*)g_pClientEntList->GetClientEntityFromHandle(hWeapons[nIndex]);

			if (!pWeapon)
				continue;

			int nWeaponIndex = *pWeapon->GetItemDefinitionIndex();

			ApplyCustomModel(pLocal, pWeapon, nWeaponIndex);

			if (LocalPlayerInfo.m_nXuidLow != *pWeapon->GetOriginalOwnerXuidLow())
				continue;

			if (LocalPlayerInfo.m_nXuidHigh != *pWeapon->GetOriginalOwnerXuidHigh())
				continue;

			ApplyCustomSkin(pWeapon, nWeaponIndex);

			*pWeapon->GetAccountID() = LocalPlayerInfo.m_nXuidLow;
		}

		break;
	}

	ClientTable.UnHook();
	g_pClient->FrameStageNotify(Stage);
	ClientTable.ReHook();
}

void WINAPI DrawModelExecute(PVOID pContext, const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	ModelRenderTable.UnHook();

	if (!g_pEngine->IsTakingScreenshot() && g_pEngine->IsConnected())
	{
		auto strModelName = g_pModelInfo->GetModelName(pInfo.pModel);

		if (cvar.esp_vis_chams && g_Local.bAlive && strModelName.find(XorStr("models/player")) != std::string::npos)
		{
			IClientEntity* pBaseEntity = g_pClientEntList->GetClientEntity(pInfo.entity_index);

			if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == CC_CCSPlayer)
			{
				if (g_Player[pInfo.entity_index].bAlive)
				{
					bool CheckTeam = g_Esp.GetPlayerCheckTeam(pInfo.entity_index);

					float no_vis_color[3] = { 0 };
					float vis_color[3] = { 0 };

					if (pBaseEntity->GetTeamNum() == TEAM_CT)
					{
						no_vis_color[0] = cvar.chams_color_ct_r;
						no_vis_color[1] = cvar.chams_color_ct_g;
						no_vis_color[2] = cvar.chams_color_ct_b;

						vis_color[0] = cvar.chams_color_ct_vis_r;
						vis_color[1] = cvar.chams_color_ct_vis_g;
						vis_color[2] = cvar.chams_color_ct_vis_b;
					}
					else if (pBaseEntity->GetTeamNum() == TEAM_TT)
					{
						no_vis_color[0] = cvar.chams_color_tt_r;
						no_vis_color[1] = cvar.chams_color_tt_g;
						no_vis_color[2] = cvar.chams_color_tt_b;

						vis_color[0] = cvar.chams_color_tt_vis_r;
						vis_color[1] = cvar.chams_color_tt_vis_g;
						vis_color[2] = cvar.chams_color_tt_vis_b;
					}

					if (CheckTeam)
					{
						Color TeamHideColor(no_vis_color[0], no_vis_color[1], no_vis_color[2]);
						Color TeamVisibleColor(vis_color[0], vis_color[1], vis_color[2]);

						if (cvar.esp_vis_chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						else if (cvar.esp_vis_chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}

						g_pModelRender->DrawModelExecute(pContext, pState, pInfo, pCustomBoneToWorld);

						if (cvar.esp_vis_chams == 1)
						{
							ForceMaterial(TeamVisibleColor, visible_flat);
							visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else if (cvar.esp_vis_chams >= 2)
						{
							ForceMaterial(TeamVisibleColor, visible_tex);
							visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
					}
				}
			}
		}

		if (cvar.esp_vis_hands)
		{
			if (strModelName.find("models/weapons/ct_arms") != std::string::npos || strModelName.find("models/weapons/t_arms") != std::string::npos)
			{
				auto pMaterial = g_pMaterialSystem->FindMaterial(strModelName.c_str(), "Model textures");

				if (cvar.esp_vis_hands == 1)
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				else
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

				if (cvar.esp_vis_hands == 2)
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
				else
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);

				g_pModelRender->ForcedMaterialOverride(pMaterial);
			}
		}
	}

	g_pModelRender->DrawModelExecute(pContext, pState, pInfo, pCustomBoneToWorld);
	g_pModelRender->ForcedMaterialOverride(NULL);
	ModelRenderTable.ReHook();
}

byte StringFindCount(const char *data, size_t len)
{
	HANDLE process = GetCurrentProcess();
	byte count_find = 0;
	if (process)
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		MEMORY_BASIC_INFORMATION info;
		std::vector<char> chunk;
		char* p = 0;
		while (p < si.lpMaximumApplicationAddress)
		{
			if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
			{
				p = (char*)info.BaseAddress;
				chunk.clear();
				chunk.resize(info.RegionSize);
				SIZE_T bytesRead;
				if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
				{
					for (size_t i = 0; i < (bytesRead - len); ++i)
					{
						if (memcmp(data, &chunk[i], len) == 0)
						{
							count_find++;
							//return (char*)p + i;
						}
					}
				}
				p += info.RegionSize;
			}
		}
	}

	return count_find;
}

void HookFunction()
{
		cvar.LoadCvarFromIni();

			ClientTable.HookIndex(HookIndexSDK::IBaseClientDLL::LevelShutdown, (DWORD)LevelShutdown);
			ClientTable.HookIndex(HookIndexSDK::IBaseClientDLL::HudUpdate, (DWORD)HudUpdate);
			ClientTable.HookIndex(HookIndexSDK::IBaseClientDLL::FrameStageNotify, (DWORD)FrameStageNotify);
			ClientTable.HookIndex(HookIndexSDK::IBaseClientDLL::CreateMove, (DWORD)CreateMove_ClientTable);

			PanelTable.HookIndex(HookIndexSDK::IPanel::PaintTraverse, (DWORD)PaintTraverse);

			ClientModeTable.HookIndex(HookIndexSDK::IClientMode::CL_CreateMove, (DWORD)CreateMove_ClientModeTable);

			SoundTable.HookIndex(HookIndexSDK::IEngineSound::EmitSound1, (DWORD)EmitSound1);
			SoundTable.HookIndex(HookIndexSDK::IEngineSound::EmitSound2, (DWORD)EmitSound2);

			GameEventTable.HookIndex(9, (DWORD)FireEventClientSideThink);
			ModelRenderTable.HookIndex(21, (DWORD)DrawModelExecute);

			InitalizeSkins();
}