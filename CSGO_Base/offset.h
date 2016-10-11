#pragma once

#include "main.h"

#define ENGINE_DLL		XorStr("engine.dll") //0x62,11,0x0AFBF0E2>("\x07\x0D\x03\x0C\x08\x02\x46\x0D\x06\x07"+0x0AFBF0E2).s
#define CLIENT_DLL		XorStr("client.dll") //0x8F,11,0xF629CECA>("\xEC\xFC\xF8\xF7\xFD\xE0\xBB\xF2\xFB\xF4"+0xF629CECA).s
#define VGUIMT_DLL		XorStr("vguimatsurface.dll") //0x5A,19,0xA183C89C>("\x2C\x3C\x29\x34\x33\x3E\x14\x12\x17\x11\x02\x04\x05\x02\x46\x0D\x06\x07"+0xA183C89C).s
#define VGUI2_DLL		XorStr("vgui2.dll") //0x41,10,0x5424F8AA>("\x37\x25\x36\x2D\x77\x68\x23\x24\x25"+0x5424F8AA).s
#define SERVER_DLL		XorStr("server.dll") //0x18,11,0x35A388A4>("\x6B\x7C\x68\x6D\x79\x6F\x30\x7B\x4C\x4D"+0x35A388A4).s
#define MATERIAL_DLL	XorStr("materialsystem.dll") //0x38,19,0x7A7D02F1>("\x55\x58\x4E\x5E\x4E\x54\x5F\x53\x33\x38\x31\x37\x21\x28\x68\x23\x24\x25"+0x7A7D02F1).s
#define SHADER_DLL		XorStr("shaderapidx9.dll") //0x15,17,0xC4A9F0EB>("\x66\x7E\x76\x7C\x7C\x68\x7A\x6C\x74\x7A\x67\x19\x0F\x46\x4F\x48"+0xC4A9F0EB).s

#define ICLIENT_MODE_PATTERN	"\xB9\x00\x00\x00\x00\x83\x38\x02\x75\x0D\xFF\xB0\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5D\xC3"
#define ICLIENT_MODE_MASK		XorStr("x????xxxxxxx????x????xx") 

class cOffset
{
public:

	DWORD dwClientModule;
	DWORD dwClientModuleSize;
	DWORD dwClientModuleEnd;

	DWORD dwEngineModule;
	DWORD dwEngineModuleSize;
	DWORD dwEngineModuleEnd;
	
	bool ModuleLoad();

	CreateInterfaceFn CaptureFactory( char* FactoryModule );
	PDWORD CaptureInterface( CreateInterfaceFn Interface , char* InterfaceName );

	DWORD GetModuleSize( DWORD Address );
};

extern cOffset offset;