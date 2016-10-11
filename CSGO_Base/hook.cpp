#include "main.h"

bool cHookTable::HookTable( DWORD dwTablePtrPtr )
{
	DWORD dwIndexFunction = 0;

	dwPtrPtrTable = dwTablePtrPtr;
	dwPtrOldTable = *(PDWORD)dwPtrPtrTable;
	
	for ( dwIndexFunction = 0; ( (PDWORD)*(PDWORD)dwTablePtrPtr )[dwIndexFunction]; dwIndexFunction++ )
		if ( IsBadCodePtr( (FARPROC)( (PDWORD)*(PDWORD)dwTablePtrPtr )[dwIndexFunction] ) )
			break;

	dwSizeTable = sizeof( DWORD ) * dwIndexFunction;

	if ( dwIndexFunction && dwSizeTable )
	{
		dwPtrNewTable = (DWORD)HeapAlloc( GetProcessHeap() , HEAP_ZERO_MEMORY , dwSizeTable );
		nt_memcpy( (PVOID)dwPtrNewTable , (PVOID)*(PDWORD)dwTablePtrPtr , dwSizeTable );

		*(PDWORD)dwTablePtrPtr = dwPtrNewTable;

		return true;
	}

	return false;
}

void cHookTable::HookIndex( DWORD dwIndex , DWORD dwNewAddress )
{
	( (PDWORD)dwPtrNewTable )[dwIndex] = dwNewAddress;
}

DWORD cHookTable::RetHookIndex( DWORD dwIndex , DWORD dwNewAddress )
{
	DWORD old = ( (PDWORD)dwPtrNewTable )[dwIndex];
	( (PDWORD)dwPtrNewTable )[dwIndex] = dwNewAddress;
	return old;
}

void cHookTable::UnHook()
{
	if( dwPtrPtrTable )
		*(PDWORD)dwPtrPtrTable = dwPtrOldTable;
}

void cHookTable::ReHook()
{
	if ( dwPtrPtrTable )
		*(PDWORD)dwPtrPtrTable = dwPtrNewTable;
}