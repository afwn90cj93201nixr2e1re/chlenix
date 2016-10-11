#include "main.h"

IVEngineClient*		g_pEngine = nullptr;
IBaseClientDLL*		g_pClient = nullptr;
IEngineSound*		g_pSound = nullptr;
ISurface*			g_pSurface = nullptr;
IPanel*				g_pPanel = nullptr;
IPlayerInfoManager* g_pPlayerInfoManager = nullptr;
CGlobalVarsBase*	g_pGlobalVarsBase = nullptr;
IClientMode*		g_pClientMode = nullptr;
IClientEntityList*	g_pClientEntList = nullptr;
IVModelInfoClient*	g_pModelInfo = nullptr;
IGameEventManager2* g_pGameEventMgr = nullptr;
IModelRender*		g_pModelRender = nullptr;
IRenderView*		g_pRenderView = nullptr;
IMaterialSystem*	g_pMaterialSystem = nullptr;
CInput*             g_pInput = nullptr;

cHookTable EngineTable;
cHookTable ClientTable;
cHookTable SoundTable;
cHookTable SurfaceTable;
cHookTable PanelTable;
cHookTable ClientModeTable;
cHookTable GameEventTable;
cHookTable ModelRenderTable;

PCHAR BaseDir;

DWORD WINAPI CheatThread( PVOID ThreadParameter )
{
	BYTE bCounterFind = 0;
	
	while ( !offset.ModuleLoad() )
	{
		if ( bCounterFind == 100 )
		{
			MessageBoxA( 0 , ERROR_TITLE , ERROR_TEXT , MB_OK | MB_ICONERROR );
			return 0;
		}

		Sleep( 150 );
		bCounterFind++;
	}

	CreateInterfaceFn EngineFactory		= offset.CaptureFactory( ENGINE_DLL );
	CreateInterfaceFn ClientFactory		= offset.CaptureFactory( CLIENT_DLL );

	CreateInterfaceFn VguiMatFactory	= offset.CaptureFactory( VGUIMT_DLL );
	CreateInterfaceFn Vgui2Factory		= offset.CaptureFactory( VGUI2_DLL );
	CreateInterfaceFn ServerFactory		= offset.CaptureFactory( SERVER_DLL );
	CreateInterfaceFn MaterialFactory	= offset.CaptureFactory( MATERIAL_DLL );

	g_pEngine				= (IVEngineClient*)( offset.CaptureInterface( EngineFactory , VENGINE_CLIENT_INTERFACE_VERSION ) );
	g_pClient				= (IBaseClientDLL*)( offset.CaptureInterface( ClientFactory , CLIENT_DLL_INTERFACE_VERSION ) );
	g_pSound				= (IEngineSound*)offset.CaptureInterface( EngineFactory , IENGINESOUND_CLIENT_INTERFACE_VERSION );
	g_pSurface				= (ISurface*)( offset.CaptureInterface( VguiMatFactory , VGUI_SURFACE_INTERFACE_VERSION ) );
	g_pPanel				= (IPanel*)( offset.CaptureInterface( Vgui2Factory , VGUI_PANEL_INTERFACE_VERSION ) );
	g_pPlayerInfoManager	= (IPlayerInfoManager*)( offset.CaptureInterface( ServerFactory , INTERFACEVERSION_PLAYERINFOMANAGER ) );
	
	if ( g_pPlayerInfoManager )
		g_pGlobalVarsBase	= g_pPlayerInfoManager->GetGlobalVars();
	else
		return 0;

	g_pClientMode			= (IClientMode*)( *(PDWORD)FindPattern( ICLIENT_MODE_PATTERN , ICLIENT_MODE_MASK ,
									(DWORD)offset.dwClientModule ,
									(DWORD)offset.dwClientModule + offset.dwClientModuleSize , 1 ) );

	g_pClientEntList		= (IClientEntityList*)( offset.CaptureInterface( ClientFactory , VCLIENTENTITYLIST_INTERFACE_VERSION ) );
	g_pModelInfo			= (IVModelInfoClient*)( offset.CaptureInterface( EngineFactory , VMODELINFO_CLIENT_INTERACE_VERSION ) );
	g_pGameEventMgr			= (IGameEventManager2*)( offset.CaptureInterface( EngineFactory , GAMEEVENTMANAGER_INTERFACE_VERSION ) );
	g_pModelRender			= (IModelRender*)( offset.CaptureInterface( EngineFactory , VENGINE_HUDMODEL_INTERFACE_VERSION ) );
	g_pRenderView			= (IRenderView*)( offset.CaptureInterface( EngineFactory , VENGINE_RENDERVIEW_INTERFACE_VERSION ) );
	g_pMaterialSystem		= (IMaterialSystem*)( offset.CaptureInterface( MaterialFactory , MATERIAL_SYSTEM_INTERFACE_VERSION ) );
	
	if ( !EngineTable.HookTable( (DWORD)g_pEngine ) )
		return 0;

	if ( !ClientTable.HookTable( (DWORD)g_pClient ) )
		return 0;

	if( !SoundTable.HookTable( (DWORD)g_pSound ) )
		return 0;

	if ( !SurfaceTable.HookTable( (DWORD)g_pSurface ) )
		return 0;

	if ( !PanelTable.HookTable( (DWORD)g_pPanel ) )
		return 0;

	if ( !ClientModeTable.HookTable( (DWORD)g_pClientMode ) )
		return 0;

	if ( !GameEventTable.HookTable( (DWORD)g_pGameEventMgr ) )
		return 0;

	if ( !ModelRenderTable.HookTable( (DWORD)g_pModelRender ) )
		return 0;

	auto g_pClientVFTable = *(PDWORD*)g_pClient;
	g_pInput = *(CInput**)( g_pClientVFTable[15] + 0x01 );
	
	HookFunction();
	
	return 1;
}

#include <Shlobj.h>

BOOL WINAPI DllMain( HINSTANCE hinstDLL , DWORD fdwReason , LPVOID lpReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hinstDLL );
		BaseDir = AllocChar( MAX_PATH );
		
		SHGetFolderPathA( NULL , CSIDL_PROFILE , NULL , 0 , BaseDir );
		strcat( BaseDir , XorStr( "\\AppData\\Roaming\\" ) );
				
		CreateThread( NULL , 0 , CheatThread , 0 , 0 , NULL );

		return TRUE;
	}

	return TRUE;
}