#include "_cvar.h"

cCvar cvar;

// Данные для считывания настроек для оружия в ini файле

char* pWeaponData[33] =
{
	// ПИСТОЛЕТЫ - 0 - 8
	WEAPON_DEAGLE_STR,WEAPON_ELITE_STR,WEAPON_FIVESEVEN_STR,
	WEAPON_GLOCK_STR,WEAPON_HKP2000_STR,WEAPON_P250_STR,
	WEAPON_USP_S_STR,WEAPON_CZ75A_STR,WEAPON_REVOLVER_STR,
	// АВТОМАТЫ - 9 - 28
	WEAPON_AK47_STR,WEAPON_AUG_STR,WEAPON_FAMAS_STR,WEAPON_GALILAR_STR,
	WEAPON_M249_STR,WEAPON_M4A1_STR,WEAPON_M4A1_S_STR,WEAPON_MAC10_STR,
	WEAPON_P90_STR,WEAPON_UMP45_STR,WEAPON_XM1014_STR,WEAPON_BIZON_STR,
	WEAPON_MAG7_STR,WEAPON_NEGEV_STR,WEAPON_SAWEDOFF_STR,WEAPON_TEC9_STR,
	WEAPON_MP7_STR,WEAPON_MP9_STR,WEAPON_NOVA_STR,WEAPON_SG553_STR,
	// СНАЙПЕРКИ  - 29 - 32
	WEAPON_AWP_STR,WEAPON_G3SG1_STR,WEAPON_SCAR20_STR,WEAPON_SSG08_STR
};

void cCvar::InitPatch()
{
	IniPatch = AllocChar( MAX_PATH );
	IniValue = AllocChar( INT_DIGITS );
	IniSection = AllocChar( INT_DIGITS );

	nt_strcpy( IniPatch , BaseDir );
	nt_strcat( IniPatch , CFG_LEIS_CONFIG );

	//MessageBoxA( 0 , IniPatch , 0 , 0 );

	misc_LoadSettings = 0;
	misc_SaveSettings = 0;

	bInitPatch = true;
}

void cCvar::LoadCvarWeapon()
{
	for( DWORD i = 0; i < WEAPON_DATA_SIZE; i++ )
	{
		GetWeaponSection( i );

		weapon_settings[i].aim_enable = ReadInt( IniSection , CFG_AIM_ENABLE , 0 , IniPatch );
		weapon_settings[i].aim_silent = ReadInt( IniSection , CFG_AIM_SILENT , 0 , IniPatch );
		weapon_settings[i].aim_silent_fov = ReadInt( IniSection , CFG_AIM_SILENTFOV , 5 , IniPatch );
		weapon_settings[i].aim_bone = ReadInt( IniSection , CFG_AIM_BONE , 6 , IniPatch );
		weapon_settings[i].aim_smooth = ReadInt( IniSection , CFG_AIM_SMOOTH , 50 , IniPatch );
		weapon_settings[i].aim_rcsx = ReadInt( IniSection , CFG_AIM_RCSX , 10 , IniPatch );
		weapon_settings[i].aim_rcsy = ReadInt( IniSection , CFG_AIM_RCSY , 10 , IniPatch );
		weapon_settings[i].aim_fov = ReadInt( IniSection , CFG_AIM_FOV , 10 , IniPatch );
		weapon_settings[i].aim_delay = ReadInt( IniSection , CFG_AIM_DELAY , 100 , IniPatch );
		weapon_settings[i].aim_smart = ReadInt( IniSection , CFG_AIM_SMART , 0 , IniPatch );
		weapon_settings[i].trigger_mode = ReadInt( IniSection , CFG_TRIGGER_MODE , 0 , IniPatch );
		weapon_settings[i].trigger_time = ReadInt( IniSection , CFG_TRIGGER_TIME , 3000 , IniPatch );
		weapon_settings[i].trigger_key = ReadTriggerKeyString( IniSection , CFG_TRIGGER_KEY , CFG_KEY_MOUSE3 , IniPatch );
	}
}

void cCvar::SaveCvarWeapon()
{
	for( DWORD i = 0; i < WEAPON_DATA_SIZE; i++ )
	{
		GetWeaponSection( i );

		SaveInt( IniSection , CFG_AIM_ENABLE , weapon_settings[i].aim_enable , IniPatch );
		SaveInt( IniSection , CFG_AIM_SILENT , weapon_settings[i].aim_silent , IniPatch );
		SaveInt( IniSection , CFG_AIM_SILENTFOV , weapon_settings[i].aim_silent_fov , IniPatch );
		SaveInt( IniSection , CFG_AIM_BONE , weapon_settings[i].aim_bone , IniPatch );
		SaveInt( IniSection , CFG_AIM_SMOOTH , weapon_settings[i].aim_smooth , IniPatch );
		SaveInt( IniSection , CFG_AIM_RCSX , weapon_settings[i].aim_rcsx , IniPatch );
		SaveInt( IniSection , CFG_AIM_RCSY , weapon_settings[i].aim_rcsy , IniPatch );
		SaveInt( IniSection , CFG_AIM_FOV , weapon_settings[i].aim_fov , IniPatch );
		SaveInt( IniSection , CFG_AIM_DELAY , weapon_settings[i].aim_delay , IniPatch );
		SaveInt( IniSection , CFG_AIM_SMART , weapon_settings[i].aim_smart , IniPatch );
		SaveInt( IniSection , CFG_TRIGGER_MODE , weapon_settings[i].trigger_mode , IniPatch );
		SaveInt( IniSection , CFG_TRIGGER_TIME , weapon_settings[i].trigger_time , IniPatch );
	}
}

void cCvar::GetWeaponSection( int iIndex )
{
	nt_strcpy( IniSection , pWeaponData[iIndex] );
}

byte cCvar::GetIndexSettingsFromWeapon()
{
	for( byte i = 0; i < WEAPON_DATA_SIZE; i++ )
	{
		if( nt_strcmp( g_Local.weapon.name , pWeaponData[i] ) == 0 )
			return i;
	}

	return 0;
}

void cCvar::LoadCvarFromIni()
{
	if ( !bInitPatch )
		InitPatch();

	esp_type = ReadInt( CFG_ESP , CFG_ESP_TYPE , 1 , IniPatch );
	esp_size = ReadInt( CFG_ESP , CFG_ESP_SIZE , 5 , IniPatch );
	esp_name = ReadInt( CFG_ESP , CFG_ESP_NAME , 0 , IniPatch );
	esp_rank = ReadInt( CFG_ESP , CFG_ESP_RANK , 0 , IniPatch );

	esp_w_weapon = ReadInt( CFG_ESP , CFG_ESP_W_WEAPON , 0 , IniPatch );
	esp_w_grenade = ReadInt( CFG_ESP , CFG_ESP_W_GRENADE , 0 , IniPatch );

	esp_bomb = ReadInt( CFG_ESP , CFG_ESP_BOMB , 0 , IniPatch );
	esp_bombtimer = ReadInt( CFG_ESP , CFG_ESP_BOMBTIMER , 40 , IniPatch );
	esp_health = ReadInt( CFG_ESP , CFG_ESP_HEALTH , 0 , IniPatch );
	esp_armor = ReadInt( CFG_ESP , CFP_ESP_ARMOR , 0 , IniPatch );
	esp_weapon = ReadInt( CFG_ESP , CFG_ESP_WEAPON , 0 , IniPatch );
	esp_team = ReadInt( CFG_ESP , CFG_ESP_TEAM , 3 , IniPatch );
	esp_visible = ReadInt( CFG_ESP , CFG_ESP_VISIBLE , 1 , IniPatch );
	esp_sound = ReadInt( CFG_ESP , CFG_ESP_SOUND , 0 , IniPatch );
	esp_aimbone = ReadInt( CFG_ESP , CFG_ESP_AIMBONE , 0 , IniPatch );
	esp_glow = ReadInt( CFG_ESP , CFG_ESP_GLOW , 0 , IniPatch );
	esp_drawfov = ReadInt( CFG_ESP , CFG_ESP_DRAWFOV , 0 , IniPatch );
	esp_vis_chams = ReadInt( CFG_ESP , CFG_ESP_VIS_CHAMS , 0 , IniPatch );
	esp_vis_hands = ReadInt( CFG_ESP , CFG_ESP_VIS_HANDS , 0 , IniPatch );

	chams_color_ct_r = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_CT_R , 0 , IniPatch );
	chams_color_ct_g = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_CT_G , 0 , IniPatch );
	chams_color_ct_b = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_CT_B , 255 , IniPatch );
	chams_color_ct_vis_r = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_CT_VIS_R , 0 , IniPatch );
	chams_color_ct_vis_g = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_CT_VIS_G , 255 , IniPatch );
	chams_color_ct_vis_b = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_CT_VIS_B , 0 , IniPatch );

	chams_color_tt_r = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_TT_R , 255 , IniPatch );
	chams_color_tt_g = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_TT_G , 0 , IniPatch );
	chams_color_tt_b = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_TT_B , 0 , IniPatch );
	chams_color_tt_vis_r = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_TT_VIS_R , 0 , IniPatch );
	chams_color_tt_vis_g = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_TT_VIS_G , 255 , IniPatch );
	chams_color_tt_vis_b = ReadInt( CFG_ESP , CFG_CHAMS_COLOR_TT_VIS_B , 0 , IniPatch );
	
	radar_enable = ReadInt( CFG_RADAR , CFG_RADAR_ENABLE , 1 , IniPatch );
	radar_size = ReadInt( CFG_RADAR , CFG_RADAR_SIZE , 150 , IniPatch );
	radar_zoom = ReadInt( CFG_RADAR , CFG_RADAR_ZOOM , 3500 , IniPatch );
	rad_x = ReadInt( CFG_RADAR , CFG_RADAR_X , 10 , IniPatch );
	rad_y = ReadInt( CFG_RADAR , CFG_RADAR_Y , 310 , IniPatch );
	rad_visible = ReadInt( CFG_RADAR , CFG_RADAR_VISIBLE , 1 , IniPatch );

	misc_Bhop = ReadInt( CFG_MISC , CFG_MISC_BHOP , 1 , IniPatch );

	knife_ct_model = ReadInt( CFG_SKIN , CFG_SKIN_CT_MODEL , 0 , IniPatch );
	knife_ct_skin = ReadInt( CFG_SKIN , CFG_SKIN_CT_SKIN , 0 , IniPatch );
	knife_tt_model = ReadInt( CFG_SKIN , CFG_SKIN_TT_MODEL , 0 , IniPatch );
	knife_tt_skin = ReadInt( CFG_SKIN , CFG_SKIN_TT_SKIN , 0 , IniPatch );

	LoadCvarWeapon();
	
	key_ToggleMenu = g_Menu.CharToKey( CFG_KEY_INS );
	key_NavEnter = g_Menu.CharToKey( CFG_KEY_ENTER );
	key_NavLeave = g_Menu.CharToKey( CFG_KEY_BACKSPACE );
	key_NavUp = g_Menu.CharToKey( CFG_KEY_UPARROW );
	key_NavDown = g_Menu.CharToKey( CFG_KEY_DOWNARROW );
	key_NavLeft = g_Menu.CharToKey( CFG_KEY_LEFTARROW );
	key_NavRight = g_Menu.CharToKey( CFG_KEY_RIGHTARROW  );
}

void cCvar::SaveCvarFromSet()
{
	SaveInt( CFG_ESP , CFG_ESP_TYPE , cvar.esp_type , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_SIZE , cvar.esp_size , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_NAME , cvar.esp_name , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_RANK , cvar.esp_rank , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_W_WEAPON , cvar.esp_w_weapon , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_W_GRENADE , cvar.esp_w_grenade , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_BOMB , cvar.esp_bomb , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_BOMBTIMER , cvar.esp_bombtimer , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_HEALTH , cvar.esp_health , IniPatch );
	SaveInt( CFG_ESP , CFP_ESP_ARMOR , cvar.esp_armor , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_WEAPON , cvar.esp_weapon , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_TEAM , cvar.esp_team , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_VISIBLE , cvar.esp_visible , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_SOUND , cvar.esp_sound , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_AIMBONE , cvar.esp_aimbone , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_DRAWFOV , cvar.esp_drawfov , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_GLOW , cvar.esp_glow , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_VIS_CHAMS , cvar.esp_vis_chams , IniPatch );
	SaveInt( CFG_ESP , CFG_ESP_VIS_HANDS , cvar.esp_vis_hands , IniPatch );
	
	SaveInt( CFG_RADAR , CFG_RADAR_ENABLE , cvar.radar_enable , IniPatch );
	SaveInt( CFG_RADAR , CFG_RADAR_SIZE , cvar.radar_size , IniPatch );
	SaveInt( CFG_RADAR , CFG_RADAR_ZOOM , cvar.radar_zoom , IniPatch );
	SaveInt( CFG_RADAR , CFG_RADAR_X , cvar.rad_x , IniPatch );
	SaveInt( CFG_RADAR , CFG_RADAR_Y , cvar.rad_y , IniPatch );
	SaveInt( CFG_RADAR , CFG_RADAR_VISIBLE , cvar.rad_visible , IniPatch );

	SaveInt( CFG_MISC , CFG_MISC_BHOP , cvar.misc_Bhop , IniPatch );

	SaveCvarWeapon();
}

int cCvar::ReadInt( char* szSection , char* szKey , int iDefaultValue , char* Patch )
{
	return GetPrivateProfileIntA( szSection , szKey , iDefaultValue , Patch );
}

void cCvar::SaveInt( char* szSection , char* szKey , int iValue , char* Patch )
{
	IniValue = nt_itoa( iValue );
	WritePrivateProfileStringA( szSection , szKey , IniValue , Patch );
}

int cCvar::ReadTriggerKeyString( char* szSection , char* szKey , char* cDefaultValue , char* Patch )
{
	char cTempString[INT_DIGITS];
	GetPrivateProfileStringA( szSection , szKey , cDefaultValue , cTempString , 16 , Patch );
	return g_Trigger.TriggerCharToKey( cTempString );
}