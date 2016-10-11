#pragma once

#include "main.h"

char* AllocChar( DWORD dwSize );
void FreeChar( char* AllocChar );

class cTimer
{
private:

	DWORD dwTime;
	bool bEnable;
public:

	cTimer()
	{
		dwTime = 0;
		bEnable = true;
	}

	bool delay( DWORD dwMsec );
	void reset();
	void stop();
};