#pragma once

#pragma once

#include "../main.h"

#define MAX_MENU_COUNT		5
#define MAX_SUB_MENU_COUNT	31

#define TEXT_PADDING_LEFT	3

#define MENU_ENTRY_WIDTH	110
#define MENU_PADDING_TOP	2

#define SUBM_ENTRY_WIDTH	185
#define SUBM_PADDING_LEFT	2
#define SUBM_VALUE_PADDING	35

#define ENTRY_HEIGHT		13

#define MENU_ENTRY_KEY		0x5B15E
#define SUBM_ENTRY_KEY		0x1DC42

#define MENU_ALL_WIDTH		SUBM_ENTRY_WIDTH + MENU_ENTRY_WIDTH + SUBM_PADDING_LEFT

#define KEY_DOWN( KeyNum ) ( GetAsyncKeyState(KeyNum) & 0x1 )

struct m_entry
{
	char name[32];
};

struct s_entry
{
	char name[32];
	int* value;
	int min;
	int max;
	int step;
};

class cMenu
{
public:

	cMenu();

	void InitializeMenu();

	void DrawMenu( int x , int y , bool center );
	int CharToKey( char* Key );

	bool Visible;
	bool SubMenu;
	bool DisableReload;

private:

	PCHAR pValue;

	int M_EntryPos;
	int M_EntrySize;

	int S_EntryPos;
	int S_EntrySize;

	m_entry menu_entry[MAX_MENU_COUNT];
	s_entry subm_entry[MAX_SUB_MENU_COUNT];

	DWORD dwLastSaveTime;
	DWORD dwLastLoadTime;

	void KeyEvent();

	void AddMenu( char* name );
	void AddSubMenu( char* name , int* value , int min , int max , int step );

	void ClearMenu();
};

extern cMenu g_Menu;