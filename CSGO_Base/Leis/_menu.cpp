#include "_menu.h"

cMenu g_Menu;

cMenu::cMenu()
{
	pValue = AllocChar( INT_DIGITS );

	Visible = false;
	SubMenu = false;

	M_EntryPos = 0;
	M_EntrySize = 0;

	S_EntryPos = 0;
	S_EntrySize = 0;

	ClearMenu();

	dwLastSaveTime = 0;
	dwLastLoadTime = 0;

	DisableReload = false;
}

void cMenu::InitializeMenu()
{
	ClearMenu();

	AddMenu( CFG_WEAPON_GLOBAL );
	AddMenu( CFG_ESP_SETTINGS );
	AddMenu( CFG_RADAR_SETTINGS );
	AddMenu( CFG_MISC_SETTINGS );

	if( M_EntryPos == 0 )
	{
		AddSubMenu( CFG_AIM_ENABLE , &cvar.weapon_settings[cvar.wpn].aim_enable , 0 , 1 , 1 );
		AddSubMenu( CFG_AIM_SILENT , &cvar.weapon_settings[cvar.wpn].aim_silent , 0 , 1 , 1 );
		AddSubMenu( CFG_AIM_SILENTFOV , &cvar.weapon_settings[cvar.wpn].aim_silent_fov , 0 , 30 , 1 );
		AddSubMenu( CFG_AIM_BONE , &cvar.weapon_settings[cvar.wpn].aim_bone , 1 , 6 , 1 );
		AddSubMenu( CFG_AIM_SMOOTH , &cvar.weapon_settings[cvar.wpn].aim_smooth , 0 , 100 , 1 );
		AddSubMenu( CFG_AIM_RCSX , &cvar.weapon_settings[cvar.wpn].aim_rcsx , 0 , 10 , 1 );
		AddSubMenu( CFG_AIM_RCSY , &cvar.weapon_settings[cvar.wpn].aim_rcsy , 0 , 10 , 1 );
		AddSubMenu( CFG_AIM_FOV , &cvar.weapon_settings[cvar.wpn].aim_fov , 1 , 360 , 1 );
		AddSubMenu( CFG_AIM_DELAY , &cvar.weapon_settings[cvar.wpn].aim_delay , 0 , 1000 , 5 );
		AddSubMenu( CFG_AIM_SMART , &cvar.weapon_settings[cvar.wpn].aim_smart , 0 , 1 , 1 );
		AddSubMenu( CFG_TRIGGER_MODE , &cvar.weapon_settings[cvar.wpn].trigger_mode , 0 , 2 , 1 );
		AddSubMenu( CFG_TRIGGER_TIME , &cvar.weapon_settings[cvar.wpn].trigger_time , 0 , 5000 , 10 );
		AddSubMenu( CFG_SKIN_ID , &g_SkinChangerCfg[g_Local.iItemDefinitionIndex].nFallbackPaintKit , 0 , 600 , 1 );
	}
	if ( M_EntryPos == 1 )
	{
		AddSubMenu( CFG_ESP_TYPE , &cvar.esp_type , 1 , 2 , 1 );
		AddSubMenu( CFG_ESP_SIZE , &cvar.esp_size , 0 , 10 , 1 );
		AddSubMenu( CFG_ESP_NAME , &cvar.esp_name , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_RANK , &cvar.esp_rank , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_W_WEAPON , &cvar.esp_w_weapon , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_W_GRENADE , &cvar.esp_w_grenade , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_BOMB , &cvar.esp_bomb , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_BOMBTIMER , &cvar.esp_bombtimer , 0 , 60 , 1 );
		AddSubMenu( CFG_ESP_HEALTH , &cvar.esp_health , 0 , 3 , 1 );
		AddSubMenu( CFP_ESP_ARMOR , &cvar.esp_armor , 0 , 3 , 1 );
		AddSubMenu( CFG_ESP_WEAPON , &cvar.esp_weapon , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_TEAM , &cvar.esp_team , 1 , 3 , 1 );
		AddSubMenu( CFG_ESP_VISIBLE , &cvar.esp_visible , 1 , 4 , 1 );
		AddSubMenu( CFG_ESP_SOUND , &cvar.esp_sound , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_AIMBONE , &cvar.esp_aimbone , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_GLOW , &cvar.esp_glow , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_DRAWFOV , &cvar.esp_drawfov , 0 , 1 , 1 );
		AddSubMenu( CFG_ESP_VIS_CHAMS , &cvar.esp_vis_chams , 0 , 2 , 1 );
		AddSubMenu( CFG_ESP_VIS_HANDS , &cvar.esp_vis_hands , 0 , 2 , 1 );

		AddSubMenu( CFG_CHAMS_COLOR_CT_R , &cvar.chams_color_ct_r , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_CT_G , &cvar.chams_color_ct_g , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_CT_B , &cvar.chams_color_ct_b , 0 , 255 , 1 );

		AddSubMenu( CFG_CHAMS_COLOR_CT_VIS_R , &cvar.chams_color_ct_vis_r , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_CT_VIS_G , &cvar.chams_color_ct_vis_g , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_CT_VIS_B , &cvar.chams_color_ct_vis_b , 0 , 255 , 1 );

		AddSubMenu( CFG_CHAMS_COLOR_TT_R , &cvar.chams_color_tt_r , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_TT_G , &cvar.chams_color_tt_g , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_TT_B , &cvar.chams_color_tt_b , 0 , 255 , 1 );

		AddSubMenu( CFG_CHAMS_COLOR_TT_VIS_R , &cvar.chams_color_tt_vis_r , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_TT_VIS_G , &cvar.chams_color_tt_vis_g , 0 , 255 , 1 );
		AddSubMenu( CFG_CHAMS_COLOR_TT_VIS_B , &cvar.chams_color_tt_vis_b , 0 , 255 , 1 );
	}
	if ( M_EntryPos == 2 )
	{
		AddSubMenu( CFG_RADAR_ENABLE , &cvar.radar_enable , 0 , 1 , 1 );
		AddSubMenu( CFG_RADAR_SIZE , &cvar.radar_size , 0 , 500 , 1 );
		AddSubMenu( CFG_RADAR_ZOOM , &cvar.radar_zoom , 100 , 5000 , 100 );
		AddSubMenu( CFG_RADAR_X , &cvar.rad_x , 0 , g_Screen.iWidth - cvar.radar_size , 1 );
		AddSubMenu( CFG_RADAR_Y , &cvar.rad_y , 0 , g_Screen.iHeight - cvar.radar_size , 1 );
		AddSubMenu( CFG_RADAR_VISIBLE , &cvar.rad_visible , 0 , 2 , 1 );
	}
	if ( M_EntryPos == 3 )
	{
		AddSubMenu( CFG_MISC_BHOP , &cvar.misc_Bhop , 0 , 1 , 1 );
		AddSubMenu( CFG_MISC_LOADSETTINGS , &cvar.misc_LoadSettings , 0 , 1 , 1 );
		AddSubMenu( CFG_MISC_SAVESETTINGS , &cvar.misc_SaveSettings , 0 , 1 , 1 );
	}
}

void cMenu::DrawMenu( int x , int y , bool center )
{
	if ( g_pEngine->IsActiveApp() )
		KeyEvent();

	if ( !Visible )
	{
		nt_memset( subm_entry , sizeof( subm_entry ) , 0 );
		nt_memset( menu_entry , sizeof( menu_entry ) , 0 );

		dwLastSaveTime = 0;
		dwLastLoadTime = 0;

		cvar.misc_LoadSettings = 0;
		cvar.misc_SaveSettings = 0;

		return;
	}

	InitializeMenu();

	int menu_all_width = MENU_ALL_WIDTH;

	if ( center )
		x -= menu_all_width / 2;

	int menu_head_width = menu_all_width;

	// меню с надписью чита
	g_Draw.DrawBox( x , y , menu_head_width , ENTRY_HEIGHT  , Color( 0 , 0 , 0 , 255 ) );
	g_Draw.FillArea( x + 1 , y + 1 , menu_head_width - 2 , ENTRY_HEIGHT - 2 , Color( 255 , 135 , 0 , 255 ) );

	if( cvar.misc_LoadSettings && !dwLastLoadTime )
	{
		dwLastLoadTime = GetTickCount() + 1500;
		cvar.LoadCvarFromIni();
	}
	else if( dwLastLoadTime > GetTickCount() && !dwLastSaveTime )
	{
		g_FontMenu.DrawString( x + ( menu_head_width / 2 ) , y , Color( 255 , 255 , 255 , 255 ) , true , CFG_LEIS_LOADED );
	}
	else
	{
		dwLastLoadTime = 0;
		cvar.misc_LoadSettings = 0;
	}

	if( cvar.misc_SaveSettings && !dwLastSaveTime )
	{
		dwLastSaveTime = GetTickCount() + 1500;
		cvar.SaveCvarFromSet();
	}
	else if( dwLastSaveTime > GetTickCount() && !dwLastLoadTime )
	{
		g_FontMenu.DrawString( x + ( menu_head_width / 2 ) , y , Color( 255 , 255 , 255 , 255 ) , true , CFG_LEIS_SAVED );
	}
	else
	{
		dwLastSaveTime = 0;
		cvar.misc_SaveSettings = 0;
	}

	if( !dwLastSaveTime && !dwLastLoadTime )
	{
		g_FontMenu.DrawString( x + ( menu_head_width / 2 ) , y , Color( 255 , 255 , 255 , 255 ) , true , CFG_LEIS_MESSAGE );
	}

	y += ENTRY_HEIGHT + MENU_PADDING_TOP;

	// меню с функциями чита
	g_Draw.DrawBox( x , y , MENU_ENTRY_WIDTH , ENTRY_HEIGHT * M_EntrySize + 2 , Color( 0 , 0 , 0 , 255 ) );
	g_Draw.FillArea( x + 1 , y + 1 , MENU_ENTRY_WIDTH - 2 , ENTRY_HEIGHT * M_EntrySize , Color( 255 , 255 , 255 , 255 ) );

	for ( int i = 0; i < M_EntrySize; i++ )
	{
		if ( i == M_EntryPos && !SubMenu )
		{
			g_Draw.FillArea( x + 1 , y + 1 + ENTRY_HEIGHT * i , MENU_ENTRY_WIDTH - 2 , ENTRY_HEIGHT , Color( 125 , 190 , 70 , 255 ) );
		}

		for ( byte a = 0; a < sizeof( m_entry::name ); a++ )
			menu_entry[i].name[a] ^= MENU_ENTRY_KEY;

		if ( i == M_EntryPos && !SubMenu )
			g_FontMenu.DrawString( x + TEXT_PADDING_LEFT , y + ENTRY_HEIGHT * i , Color( 255 , 255 , 255 , 255 ) , false , menu_entry[i].name );
		else
			g_FontMenu.DrawString( x + TEXT_PADDING_LEFT , y + ENTRY_HEIGHT * i , Color( 0 , 0 , 0 , 255 ) , false , menu_entry[i].name );

		for ( byte a = 0; a < sizeof( m_entry::name ); a++ )
			menu_entry[i].name[a] ^= MENU_ENTRY_KEY;
	}

	int subm_x = x + MENU_ENTRY_WIDTH + SUBM_PADDING_LEFT;

	// меню с кварами чита
	g_Draw.DrawBox( subm_x , y , SUBM_ENTRY_WIDTH , ENTRY_HEIGHT * S_EntrySize + 2 , Color( 0 , 0 , 0 , 255 ) );
	g_Draw.FillArea( subm_x + 1 , y + 1 , SUBM_ENTRY_WIDTH - 2 , ENTRY_HEIGHT * S_EntrySize , Color( 255 , 255 , 255 , 255 ) );

	if ( S_EntryPos >( S_EntrySize - 1 ) )
		S_EntryPos = ( S_EntrySize - 1 );

	for ( int i = 0; i < S_EntrySize; i++ )
	{
		char* on = "on";
		char* off = "off";

		BYTE r1 , g1 , b1; // on
		BYTE r2 , g2 , b2; // off
		BYTE r3 , g3 , b3; // value

		r1 = 70; g1 = 120; b1 = 250; // on
		r2 = 70; g2 = 120; b2 = 250; // off
		r3 = 70; g3 = 120; b3 = 250; // value

		if ( i == S_EntryPos && SubMenu )
		{
			r1 = 255; g1 = 255; b1 = 255; // on
			r2 = 255; g2 = 255; b2 = 255; // off
			r3 = 255; g3 = 255; b3 = 255; // value

			g_Draw.FillArea( subm_x + 1 , y + 1 + ENTRY_HEIGHT * i , SUBM_ENTRY_WIDTH - 2 , ENTRY_HEIGHT , Color( 125 , 190 , 70 , 255 ) );
		}

		for ( byte a = 0; a < 32; a++ )
			subm_entry[i].name[a] ^= SUBM_ENTRY_KEY;

		if ( subm_entry[i].min == 0 && subm_entry[i].max == 1 )
		{
			if ( i == S_EntryPos && SubMenu )
				g_FontMenu.DrawString( subm_x + TEXT_PADDING_LEFT , y + ENTRY_HEIGHT * i , Color( 255 , 255 , 255 , 255 ) , false , subm_entry[i].name );
			else
				g_FontMenu.DrawString( subm_x + TEXT_PADDING_LEFT , y + ENTRY_HEIGHT * i , Color( 0 , 0 , 0 , 255 ) , false , subm_entry[i].name );
							
			if ( *subm_entry[i].value == 0 )
				g_FontMenu.DrawString( subm_x + SUBM_ENTRY_WIDTH - SUBM_VALUE_PADDING , y + ENTRY_HEIGHT * i , Color( r2 , g2 , b2 , 255 ) , false , off );
			else
				g_FontMenu.DrawString( subm_x + SUBM_ENTRY_WIDTH - SUBM_VALUE_PADDING , y + ENTRY_HEIGHT * i , Color( r1 , g1 , b1 , 255 ) , false , on );
		}
		else
		{
			if ( i == S_EntryPos && SubMenu )
				g_FontMenu.DrawString( subm_x + TEXT_PADDING_LEFT , y + ENTRY_HEIGHT * i , Color( 255 , 255 , 255 , 255 ) , false , subm_entry[i].name );
			else
				g_FontMenu.DrawString( subm_x + TEXT_PADDING_LEFT , y + ENTRY_HEIGHT * i , Color( 0 , 0 , 0 , 255 ) , false , subm_entry[i].name );
			
			if ( *subm_entry[i].value == 0 )
				g_FontMenu.DrawString( subm_x + SUBM_ENTRY_WIDTH - SUBM_VALUE_PADDING , y + ENTRY_HEIGHT * i , Color( r2 , g2 , b2 , 255 ) , false , off );
			else
			{
				pValue = nt_itoa( *subm_entry[i].value );
				g_FontMenu.DrawString( subm_x + SUBM_ENTRY_WIDTH - SUBM_VALUE_PADDING , y + ENTRY_HEIGHT * i , Color( r3 , g3 , b3 , 255 ) , false , pValue );
			}
		}

		for ( byte a = 0; a < 32; a++ )
			subm_entry[i].name[a] ^= SUBM_ENTRY_KEY;
	}
}

void cMenu::KeyEvent()
{
	if ( KEY_DOWN( cvar.key_ToggleMenu ) )
		Visible = !Visible;
		
	if ( KEY_DOWN( cvar.key_NavEnter ) )
	{
		if ( Visible )
		{
			if ( !SubMenu )
			{
				S_EntryPos = 0;
				SubMenu = true;
			}
		}
	}
	else if ( KEY_DOWN( cvar.key_NavLeave ) )
	{
		if ( Visible )
		{
			if ( SubMenu )
			{
				SubMenu = false;
			}
			else
			{
				Visible = false;
			}
		}
	}
	else if ( KEY_DOWN( cvar.key_NavUp ) )
	{
		if ( Visible )
		{
			if ( SubMenu )
			{
				if ( S_EntryPos > 0 )
					S_EntryPos--;
				else
					S_EntryPos = S_EntrySize - 1;
			}
			else
			{
				if ( M_EntryPos > 0 )
					M_EntryPos--;
				else
					M_EntryPos = M_EntrySize - 1;
			}
		}
	}
	else if ( KEY_DOWN( cvar.key_NavDown ) )
	{
		if ( Visible )
		{
			if ( SubMenu )
			{
				if ( S_EntryPos < ( S_EntrySize - 1 ) )
					S_EntryPos++;
				else
					S_EntryPos = 0;
			}
			else
			{
				if ( M_EntryPos < ( M_EntrySize - 1 ) )
					M_EntryPos++;
				else
					M_EntryPos = 0;
			}
		}
	}
	else if ( KEY_DOWN( cvar.key_NavLeft ) )
	{
		if ( SubMenu && Visible )
		{
			*subm_entry[S_EntryPos].value -= subm_entry[S_EntryPos].step;

			if ( *subm_entry[S_EntryPos].value < subm_entry[S_EntryPos].min )
				*subm_entry[S_EntryPos].value = subm_entry[S_EntryPos].min;
		}
	}
	else if ( KEY_DOWN( cvar.key_NavRight ) )
	{
		if ( SubMenu && Visible )
		{
			*subm_entry[S_EntryPos].value += subm_entry[S_EntryPos].step;

			if ( *subm_entry[S_EntryPos].value > subm_entry[S_EntryPos].max )
				*subm_entry[S_EntryPos].value = subm_entry[S_EntryPos].max;
		}
	}
}

void cMenu::AddMenu( char* name )
{
	nt_memset( menu_entry[M_EntrySize].name , sizeof( m_entry::name ) , 0 );
	nt_strcpy( menu_entry[M_EntrySize].name , name );

	for ( byte i = 0; i < 32; i++ )
		menu_entry[M_EntrySize].name[i] ^= MENU_ENTRY_KEY;

	M_EntrySize++;
}

void cMenu::AddSubMenu( char* name , int* value , int min , int max , int step )
{
	nt_memset( subm_entry[S_EntrySize].name , sizeof( s_entry::name ) , 0 );
	nt_strcpy( subm_entry[S_EntrySize].name , name );

	for ( byte i = 0; i < 32; i++ )
		subm_entry[S_EntrySize].name[i] ^= SUBM_ENTRY_KEY;

	subm_entry[S_EntrySize].value = value;
	subm_entry[S_EntrySize].min = min;
	subm_entry[S_EntrySize].max = max;
	subm_entry[S_EntrySize].step = step;

	S_EntrySize++;
}

void cMenu::ClearMenu()
{
	for ( byte i = 0; i < M_EntrySize; i++ )
	{
		nt_memset( &menu_entry[i].name , sizeof( m_entry::name ) , 0 );
	}

	for ( byte i = 0; i < S_EntrySize; i++ )
	{
		nt_memset( &subm_entry[i].name , sizeof( s_entry::name ) , 0 );

		subm_entry[i].value = 0;
		subm_entry[i].min = 0;
		subm_entry[i].max = 0;
		subm_entry[i].step = 0;
	}

	M_EntrySize = 0;
	S_EntrySize = 0;
}

int cMenu::CharToKey( char* Key )
{
	if( !nt_strcmp( Key , CFG_KEY_INS ) ) return VK_INSERT;
	if ( !nt_strcmp( Key , CFG_KEY_ENTER ) ) return VK_RETURN;
	if ( !nt_strcmp( Key , CFG_KEY_BACKSPACE ) ) return VK_BACK;
	if ( !nt_strcmp( Key , CFG_KEY_UPARROW ) ) return VK_UP;
	if ( !nt_strcmp( Key , CFG_KEY_DOWNARROW ) ) return VK_DOWN;
	if ( !nt_strcmp( Key , CFG_KEY_LEFTARROW ) ) return VK_LEFT;
	if ( !nt_strcmp( Key , CFG_KEY_RIGHTARROW ) ) return VK_RIGHT;

	return 0;
}