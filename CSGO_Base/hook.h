#pragma once

#include "main.h"

class cHookTable
{
private:

	DWORD dwPtrPtrTable;
	DWORD dwPtrNewTable;
	DWORD dwPtrOldTable;
	DWORD dwSizeTable;

public:

	bool HookTable( DWORD dwTablePtrPtr );
	void HookIndex( DWORD dwIndex , DWORD dwNewAddress );

	DWORD RetHookIndex( DWORD dwIndex , DWORD dwNewAddress );

	void UnHook();
	void ReHook();
};