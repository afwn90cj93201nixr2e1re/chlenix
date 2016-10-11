#include "offset.h"

cOffset offset;

bool cOffset::ModuleLoad()
{
	dwEngineModule = (DWORD)GetModuleHandleA( ENGINE_DLL );
	dwClientModule = (DWORD)GetModuleHandleA( CLIENT_DLL );

	if ( dwEngineModule )
	{
		dwEngineModuleSize = GetModuleSize( dwEngineModule );
		dwEngineModuleEnd = dwEngineModule + dwEngineModuleSize;
	}

	if ( dwClientModule )
	{
		dwClientModuleSize = GetModuleSize( dwClientModule );
		dwClientModuleEnd = dwClientModule + dwClientModuleSize;
	}

	HMODULE hVguiMatSurface = GetModuleHandleA( VGUIMT_DLL );
	HMODULE hVgui2Interface = GetModuleHandleA( VGUI2_DLL );

	return ( dwEngineModule && dwEngineModuleEnd && dwClientModule && dwClientModuleEnd && hVguiMatSurface && hVgui2Interface );
}

CreateInterfaceFn cOffset::CaptureFactory( char* FactoryModule )
{
	CreateInterfaceFn Interface = 0;

	while ( !Interface )
	{
		HMODULE hFactoryModule = GetModuleHandleA( FactoryModule );

		if ( hFactoryModule )
		{
			Interface = (CreateInterfaceFn)( GetProcAddress( hFactoryModule , CREATEINTERFACE_PROCNAME ) );
		}

		Sleep( 100 );
	}

	return Interface;
}

PDWORD cOffset::CaptureInterface( CreateInterfaceFn Interface , char* InterfaceName )
{
	PDWORD dwPointer = nullptr;

	while ( !dwPointer )
	{
		dwPointer = (PDWORD)( Interface( InterfaceName , 0 ) );

		Sleep( 100 );
	}

	return dwPointer;
}

DWORD cOffset::GetModuleSize( DWORD Address )
{
	return PIMAGE_NT_HEADERS( Address + (DWORD)PIMAGE_DOS_HEADER( Address )->e_lfanew )->OptionalHeader.SizeOfImage;
}