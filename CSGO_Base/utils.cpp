#include "utils.h"

char* AllocChar( DWORD dwSize )
{
	return (char*)HeapAlloc( GetProcessHeap() , HEAP_ZERO_MEMORY , dwSize );
}

void FreeChar( char* AllocChar )
{
	nt_memset( AllocChar , lstrlenA( AllocChar ) , 0 );
	HeapFree( GetProcessHeap() , HEAP_ZERO_MEMORY , AllocChar );
}

bool cTimer::delay( DWORD dwMsec )
{
	if ( !bEnable )
		return true;

	if ( !dwTime )
		dwTime = GetTickCount();

	if ( dwTime + dwMsec < GetTickCount() )
	{
		dwTime = 0;
		bEnable = false;
		return true;
	}
	else
	{
		return false;
	}
}

void cTimer::reset()
{
	if ( !bEnable )
		bEnable = true;
}

void cTimer::stop()
{
	bEnable = false;
}