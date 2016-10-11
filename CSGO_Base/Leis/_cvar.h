#pragma once

#include "../main.h"

extern char* pWeaponData[33];

#define WEAPON_DATA_SIZE ( sizeof( pWeaponData ) / sizeof( *pWeaponData ) )

class cCvar
{
public:

	PCHAR IniPatch;
	PCHAR IniValue;
	PCHAR IniSection;

	bool bInitPatch;

	int wpn;

	cCvar()
	{
		IniPatch = nullptr;
		IniValue = nullptr;
		IniSection = nullptr;
		bInitPatch = false;
		wpn = -1;
	}

	int esp_type;
	int esp_size;
	int esp_name;
	int esp_rank;
	int esp_w_weapon;
	int esp_w_grenade;
	int esp_bomb;
	int esp_bombtimer;
	int esp_health;
	int esp_armor;
	int esp_weapon;
	int esp_team;
	int esp_sound;
	int esp_visible;
	int esp_aimbone;
	int esp_drawfov;
	int esp_glow;
	int esp_vis_chams;
	int esp_vis_hands;

	int chams_color_ct_r;
	int chams_color_ct_g;
	int chams_color_ct_b;
	int chams_color_ct_vis_r;
	int chams_color_ct_vis_g;
	int chams_color_ct_vis_b;

	int chams_color_tt_r;
	int chams_color_tt_g;
	int chams_color_tt_b;
	int chams_color_tt_vis_r;
	int chams_color_tt_vis_g;
	int chams_color_tt_vis_b;

	int radar_enable;
	int radar_size;
	int radar_zoom;
	int rad_x;
	int rad_y;
	int rad_visible;

	int misc_Bhop;

	int knife_ct_model;
	int knife_ct_skin;
	int knife_tt_model;
	int knife_tt_skin;

	struct weapon_settings_s
	{
		int aim_enable;
		int aim_silent;
		int aim_silent_fov;
		int aim_bone;
		int aim_smooth;
		int aim_rcsx;
		int aim_rcsy;
		int aim_fov;
		int aim_delay;
		int aim_smart;
		int trigger_mode;
		int trigger_time;
		int trigger_key;
	}	weapon_settings[33];

	int misc_LoadSettings;
	int misc_SaveSettings;

	int key_ToggleMenu;
	int key_NavEnter;
	int key_NavLeave;
	int key_NavUp;
	int key_NavDown;
	int key_NavLeft;
	int key_NavRight;

	void InitPatch();

	void LoadCvarWeapon();
	void SaveCvarWeapon();

	void GetWeaponSection( int iIndex );

	byte GetIndexSettingsFromWeapon();

	void LoadCvarFromIni();
	void SaveCvarFromSet();

	int ReadInt( char* szSection , char* szKey , int iDefaultValue , char* Patch );
	void SaveInt( char* szSection , char* szKey , int iValue , char* Patch );

	int ReadTriggerKeyString( char* szSection , char* szKey , char* cDefaultValue , char* Patch );
};

extern cCvar cvar;