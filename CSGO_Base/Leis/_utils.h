#pragma once

#include "../main.h"

/* FUNCTION UTILS */

struct weapon_data;

void UTIL_TraceLine( const Vector& vecAbsStart , const Vector& vecAbsEnd , unsigned int mask , const IClientEntity* ignore , int collisionGroup , trace_t* ptr );

void ForceMaterial( Color color , IMaterial* material , bool useColor = true , bool forceMaterial = true );
IMaterial* CreateMaterial( bool bFlat , bool bShouldIgnoreZ , bool bIsWireframe );

bool GetBonePosition( IClientEntity* pPlayer , Vector& vBone , int Bone );
bool ScreenTransform( const Vector& vPoint , Vector& vScreen );
bool WorldToScreen( const Vector& vOrigin , Vector& vScreen );
bool GetVisible( Vector vEyeOrigin , Vector vOrigin );

weapon_data GetWeaponData( int iItemDefinitionIndex );

void AngleVectors( const QAngle& angles , Vector& vForward , Vector& vRight , Vector& vUp );
void VectorAnglesNew( const float *forward , float *angles );
void VectorAngles( const Vector vVorward , QAngle& qAngles );
float CalcDistPlayerScreen( Vector2D vSceenPos , Vector2D vPlayerPosSceen );

/* ÑÀÌ ×ÈÒ */

#define CFG_VERDANA XorStr("Verdana")

#define CFG_LEIS_MESSAGE XorStr("=> VAGINIX V 2.2.8 <=")

#define CFG_TRIGGER_ENABLED XorStr("triggerbot: enabled") //0x89,20,0x9CEAEFCE>("\xFD\xF8\xE2\xEB\xEA\xEB\xFD\xF2\xFE\xE6\xA9\xB4\xF0\xF8\xF6\xFA\xF5\xFF\xFF"+0x9CEAEFCE).s
#define CFG_TRIGGER_DISABLED XorStr("triggerbot: disabled") //0x8D,21,0x8D23B19C>("\xF9\xFC\xE6\xF7\xF6\xF7\xE1\xF6\xFA\xE2\xAD\xB8\xFD\xF3\xE8\xFD\xFF\xF2\xFA\xC4"+0x8D23B19C).s

#define CFG_LEIS_SAVED XorStr("Settings Saved OK") //0x7C,18,0xB2E6DDAC>("\x2F\x18\x0A\x0B\xE9\xEF\xE5\xF0\xA4\xD6\xE7\xF1\xED\xED\xAA\xC4\xC7"+0xB2E6DDAC).s
#define CFG_LEIS_LOADED XorStr("Settings Loaded OK") //0xF5,19,0x4DEA5A0F>("\xA6\x93\x83\x8C\x90\x94\x9C\x8F\xDD\xB2\x90\x61\x65\x67\x67\x24\x4A\x4D"+0x4DEA5A0F).s

/* ÄËß ÊÎÍÔÈÃÀ */

#define CFG_LEIS_CONFIG XorStr("settings.ini") //0xD3,13,0xC8F50DA4>("\xA0\xB1\xA1\xA2\xBE\xB6\xBE\xA9\xF5\xB5\xB3\xB7"+0xC8F50DA4).s

#define CFG_RADAR XorStr("radar") //0x87,6,0x64198C4B>("\xF5\xE9\xED\xEB\xF9"+0x64198C4B).s
#define CFG_ESP XorStr("esp") //0x0D,4,0xCB6693FB>("\x68\x7D\x7F"+0xCB6693FB).s
#define CFG_MISC XorStr("misc") //0x9A,5,0x2A6B8F72>("\xF7\xF2\xEF\xFE"+0x2A6B8F72).s
#define CFG_SKIN XorStr("skin") //0x46,5,0x45B6D58B>("\x35\x2C\x21\x27"+0x45B6D58B).s

/* ÄËß ÅÑÏ */

#define ESP_HP XorStr("HP:") //0x15,4,0xD5608FB9>("\x5D\x46\x2D"+0xD5608FB9).s
#define ESP_AR XorStr("AR:") //0xAC,4,0x1565771F>("\xED\xFF\x94"+0x1565771F).s

/* ÌÅÍÞ È ÊÂÀÐÛ */

#define CFG_WEAPON_GLOBAL XorStr("Weapon") //0xCB,7,0xBA12511B>("\x9C\xA9\xAC\xBE\xA0\xBE"+0xBA12511B).s
#define CFG_ESP_SETTINGS XorStr("Esp") //0xD0,4,0x4FF5F65D>("\x95\xA2\xA2"+0x4FF5F65D).s
#define CFG_RADAR_SETTINGS XorStr("Radar") //0xD8,6,0x4AC651CF>("\x8A\xB8\xBE\xBA\xAE"+0x4AC651CF).s
#define CFG_MISC_SETTINGS XorStr("Misc") //0x3F,5,0x442FDD22>("\x72\x29\x32\x21"+0x442FDD22).s

#define CFG_ESP_TYPE XorStr("esp.type") //0xE9,9,0x6D4AE0C0>("\x8C\x99\x9B\xC2\x99\x97\x9F\x95"+0x6D4AE0C0).s
#define CFG_ESP_SIZE XorStr("esp.size") //0xB3,9,0x4B23263E>("\xD6\xC7\xC5\x98\xC4\xD1\xC3\xDF"+0x4B23263E).s
#define CFG_ESP_NAME XorStr("esp.name") //0x52,9,0x97486F96>("\x37\x20\x24\x7B\x38\x36\x35\x3C"+0x97486F96).s

#define CFG_ESP_W_WEAPON XorStr("esp.w_weapon")
#define CFG_ESP_W_GRENADE XorStr("esp.w_grenade")

#define CFG_ESP_RANK XorStr("esp.rank") //0xCB,9,0x5CD89C9A>("\xAE\xBF\xBD\xE0\xBD\xB1\xBF\xB9"+0x5CD89C9A).s
#define CFG_ESP_BOMB XorStr("esp.bomb") //0xDB,9,0xAD5C8510>("\xBE\xAF\xAD\xF0\xBD\x8F\x8C\x80"+0xAD5C8510).s
#define CFG_ESP_BOMBTIMER XorStr("esp.bomb.timer") //0x81,15,0x43836571>("\xE4\xF1\xF3\xAA\xE7\xE9\xEA\xEA\xA7\xFE\xE2\xE1\xE8\xFC"+0x43836571).s

#define CFG_ESP_HEALTH XorStr("esp.health") //0x96,11,0x5F4D7E3A>("\xF3\xE4\xE8\xB7\xF2\xFE\xFD\xF1\xEA\xF7"+0x5F4D7E3A).s
#define CFP_ESP_ARMOR XorStr("esp.armor") //0xFC,10,0xB0399507>("\x99\x8E\x8E\xD1\x61\x73\x6F\x6C\x76"+0xB0399507).s
#define CFG_ESP_WEAPON XorStr("esp.weapon") //0x57,11,0xA11A7575>("\x32\x2B\x29\x74\x2C\x39\x3C\x2E\x30\x0E"+0xA11A7575).s
#define CFG_ESP_TEAM XorStr("esp.team") //0xA8,9,0x9B95DEE9>("\xCD\xDA\xDA\x85\xD8\xC8\xCF\xC2"+0x9B95DEE9).s
#define CFG_ESP_VISIBLE XorStr("esp.visible") //0x98,12,0x438126F5>("\xFD\xEA\xEA\xB5\xEA\xF4\xED\xF6\xC2\xCD\xC7"+0x438126F5).s
#define CFG_ESP_SOUND XorStr("esp.sound") //0x54,10,0xFED4FF4D>("\x31\x26\x26\x79\x2B\x36\x2F\x35\x38"+0xFED4FF4D).s
#define CFG_ESP_AIMBONE XorStr("esp.aimbone") //0xCD,12,0xBD26B870>("\xA8\xBD\xBF\xFE\xB0\xBB\xBE\xB6\xBA\xB8\xB2"+0xBD26B870).s
#define CFG_ESP_GLOW XorStr("esp.glow") //0x9B,9,0x50444379>("\xFE\xEF\xED\xB0\xF8\xCC\xCE\xD5"+0x50444379).s
#define CFG_ESP_DRAWFOV XorStr("esp.draw.fov")
#define CFG_ESP_VIS_CHAMS XorStr("esp.vis.chams") //0x32,14,0x6B8796BB>("\x57\x40\x44\x1B\x40\x5E\x4B\x17\x59\x53\x5D\x50\x4D"+0x6B8796BB).s
#define CFG_ESP_VIS_HANDS XorStr("esp.vis.hands") //0x88,14,0xA800FE40>("\xED\xFA\xFA\xA5\xFA\xE4\xFD\xA1\xF8\xF0\xFC\xF7\xE7"+0xA800FE40).s

#define CFG_CHAMS_COLOR_CT_R XorStr("chams.color.ct.r") //0x90,17,0xFB762D02>("\xF3\xF9\xF3\xFE\xE7\xBB\xF5\xF8\xF4\xF6\xE8\xB5\xFF\xE9\xB0\xED"+0xFB762D02).s
#define CFG_CHAMS_COLOR_CT_G XorStr("chams.color.ct.g") //0xEF,17,0x95BEA88D>("\x8C\x98\x90\x9F\x80\xDA\x96\x99\x9B\x97\x8B\xD4\x98\x88\xD3\x99"+0x95BEA88D).s
#define CFG_CHAMS_COLOR_CT_B XorStr("chams.color.ct.b") //0xA4,17,0xAAEB87F4>("\xC7\xCD\xC7\xCA\xDB\x87\xC9\xC4\xC0\xC2\xDC\x81\xD3\xC5\x9C\xD1"+0xAAEB87F4).s
#define CFG_CHAMS_COLOR_CT_VIS_R XorStr("chams.color.ct.vis.r") //0x02,21,0x2A0D3100>("\x61\x6B\x65\x68\x75\x29\x6B\x66\x66\x64\x7E\x23\x6D\x7B\x3E\x67\x7B\x60\x3A\x67"+0x2A0D3100).s
#define CFG_CHAMS_COLOR_CT_VIS_G XorStr("chams.color.ct.vis.g") //0x15,21,0xBF986A33>("\x76\x7E\x76\x75\x6A\x34\x78\x73\x71\x71\x6D\x0E\x42\x56\x0D\x52\x4C\x55\x09\x4F"+0xBF986A33).s
#define CFG_CHAMS_COLOR_CT_VIS_B XorStr("chams.color.ct.vis.b") //0x8B,21,0x97D55F7D>("\xE8\xE4\xEC\xE3\xFC\xBE\xF2\xFD\xFF\xFB\xE7\xB8\xF4\xEC\xB7\xEC\xF2\xEF\xB3\xFC"+0x97D55F7D).s

#define CFG_CHAMS_COLOR_TT_R XorStr("chams.color.tt.r") //0x9B,17,0x85251A0A>("\xF8\xF4\xFC\xF3\xEC\x8E\xC2\xCD\xCF\xCB\xD7\x88\xD3\xDC\x87\xD8"+0x85251A0A).s
#define CFG_CHAMS_COLOR_TT_G XorStr("chams.color.tt.g") //0x7F,17,0xDA1C1EFF>("\x1C\xE8\xE0\xEF\xF0\xAA\xE6\xE9\xEB\xE7\xFB\xA4\xFF\xF8\xA3\xE9"+0xDA1C1EFF).s
#define CFG_CHAMS_COLOR_TT_B XorStr("chams.color.tt.b") //0x09,17,0x49ADD995>("\x6A\x62\x6A\x61\x7E\x20\x6C\x7F\x7D\x7D\x61\x3A\x61\x62\x39\x7A"+0x49ADD995).s
#define CFG_CHAMS_COLOR_TT_VIS_R XorStr("chams.color.tt.vis.r") //0xD3,21,0x08E5674B>("\xB0\xBC\xB4\xBB\xA4\xF6\xBA\xB5\xB7\xB3\xAF\xF0\xAB\x94\xCF\x94\x8A\x97\xCB\x94"+0x08E5674B).s
#define CFG_CHAMS_COLOR_TT_VIS_G XorStr("chams.color.tt.vis.g") //0x88,21,0xDB7E7C19>("\xEB\xE1\xEB\xE6\xFF\xA3\xED\xE0\xFC\xFE\xE0\xBD\xE0\xE1\xB8\xE1\xF1\xEA\xB4\xFC"+0xDB7E7C19).s
#define CFG_CHAMS_COLOR_TT_VIS_B XorStr("chams.color.tt.vis.b") //0x52,21,0xD925EA21>("\x31\x3B\x35\x38\x25\x79\x3B\x36\x36\x34\x2E\x73\x2A\x2B\x4E\x17\x0B\x10\x4A\x07"+0xD925EA21).s

#define CFG_RADAR_ENABLE XorStr("radar.enable") //0xAD,13,0xA27FBE3A>("\xDF\xCF\xCB\xD1\xC3\x9C\xD6\xDA\xD4\xD4\xDB\xDD"+0xA27FBE3A).s
#define CFG_RADAR_SIZE XorStr("radar.size") //0x50,11,0xB873B928>("\x22\x30\x36\x32\x26\x7B\x25\x3E\x22\x3C"+0xB873B928).s
#define CFG_RADAR_ZOOM XorStr("radar.zoom") //0x16,11,0x4A8A2A5E>("\x64\x76\x7C\x78\x68\x35\x66\x72\x71\x72"+0x4A8A2A5E).s
#define CFG_RADAR_X XorStr("radar.x") //0xA0,8,0x75256015>("\xD2\xC0\xC6\xC2\xD6\x8B\xDE"+0x75256015).s
#define CFG_RADAR_Y XorStr("radar.y") //0x77,8,0x50424BB9>("\x05\x19\x1D\x1B\x09\x52\x04"+0x50424BB9).s
#define CFG_RADAR_VISIBLE XorStr("radar.visible") //0x16,14,0x7EE57E34>("\x64\x76\x7C\x78\x68\x35\x6A\x74\x6D\x76\x42\x4D\x47"+0x7EE57E34).s

#define CFG_MISC_BHOP XorStr("misc.bhop") //0xA4,10,0x752DF087>("\xC9\xCC\xD5\xC4\x86\xCB\xC2\xC4\xDC"+0x752DF087).s

#define CFG_SKIN_CT_MODEL XorStr("knife.ct.model") //0x4A,15,0x68B8F1AE>("\x21\x25\x25\x2B\x2B\x61\x33\x25\x7C\x3E\x3B\x31\x33\x3B"+0x68B8F1AE).s
#define CFG_SKIN_CT_SKIN XorStr("knife.ct.skin") //0x56,14,0xB7F3B4C0>("\x3D\x39\x31\x3F\x3F\x75\x3F\x29\x70\x2C\x0B\x08\x0C"+0xB7F3B4C0).s
#define CFG_SKIN_TT_MODEL XorStr("knife.tt.model") //0x69,15,0x71201F48>("\x02\x04\x02\x0A\x08\x40\x1B\x04\x5F\x1F\x1C\x10\x10\x1A"+0x71201F48).s
#define CFG_SKIN_TT_SKIN XorStr("knife.tt.skin") //0xEE,14,0x77EA1E06>("\x85\x81\x99\x97\x97\xDD\x80\x81\xD8\x84\x93\x90\x94"+0x77EA1E06).s

#define CFG_AIM_ENABLE XorStr("aim.enable") //0xFE,11,0xE6AD6C9A>("\x9F\x96\x6D\x2F\x67\x6D\x65\x67\x6A\x62"+0xE6AD6C9A).s
#define CFG_AIM_SILENT XorStr("aim.silent")
#define CFG_AIM_SILENTFOV XorStr("aim.silent.fov")
#define CFG_AIM_BONE XorStr("aim.bone") //0x42,9,0x1CCBA70A>("\x23\x2A\x29\x6B\x24\x28\x26\x2C"+0x1CCBA70A).s
#define CFG_AIM_SMOOTH XorStr("aim.smooth") //0x38,11,0xC258B16C>("\x59\x50\x57\x15\x4F\x50\x51\x50\x34\x29"+0xC258B16C).s
#define CFG_AIM_RCSX XorStr("aim.rcsx") //0x7B,9,0xE370CBBD>("\x1A\x15\x10\x50\x0D\xE3\xF2\xFA"+0xE370CBBD).s
#define CFG_AIM_RCSY XorStr("aim.rcsy") //0xE5,9,0x3D60E9EB>("\x84\x8F\x8A\xC6\x9B\x89\x98\x95"+0x3D60E9EB).s
#define CFG_AIM_FOV XorStr("aim.fov") //0x1A,8,0x8837FE2A>("\x7B\x72\x71\x33\x78\x70\x56"+0x8837FE2A).s
#define CFG_AIM_DELAY XorStr("aim.delay") //0xA1,10,0xD25CE7B2>("\xC0\xCB\xCE\x8A\xC1\xC3\xCB\xC9\xD0"+0xD25CE7B2).s
#define CFG_AIM_SMART XorStr("aim.smart") //0x1D,10,0xC4413523>("\x7C\x77\x72\x0E\x52\x4F\x42\x56\x51"+0xC4413523).s
#define CFG_TRIGGER_MODE XorStr("trigger.mode") //0xF8,13,0x390781D9>("\x8C\x8B\x93\x9C\x9B\x98\x8C\xD1\x6D\x6E\x66\x66"+0x390781D9).s
#define CFG_TRIGGER_TIME XorStr("trigger.time") //0xD9,13,0x27AC3FEF>("\xAD\xA8\xB2\xBB\xBA\xBB\xAD\xCE\x95\x8B\x8E\x81"+0x27AC3FEF).s
#define CFG_TRIGGER_KEY XorStr("trigger.key") //0x8C,12,0x452E8CD0>("\xF8\xFF\xE7\xE8\xF7\xF4\xE0\xBD\xFF\xF0\xEF"+0x452E8CD0).s
#define CFG_SKIN_ID XorStr("skin.id") //0x87,8,0x4C5BCE6F>("\xF4\xE3\xE0\xE4\xA5\xE5\xE9"+0x4C5BCE6F).s

#define CFG_MISC_LOADSETTINGS XorStr("misc_LoadSettings") //0x04,18,0x2C97C10C>("\x69\x6C\x75\x64\x57\x45\x65\x6A\x68\x5E\x6B\x7B\x64\x78\x7C\x74\x67"+0x2C97C10C).s
#define CFG_MISC_SAVESETTINGS XorStr("misc_SaveSettings") //0x43,18,0x7E20CFCC>("\x2E\x2D\x36\x25\x18\x1B\x28\x3C\x2E\x1F\x28\x3A\x3B\x39\x3F\x35\x20"+0x7E20CFCC).s

// ÊÍÎÏÊÈ ÌÅÍÞ

#define CFG_KEY_INS XorStr("INS") //0x66,4,0xDF444B99>("\x2F\x29\x3B"+0xDF444B99).s
#define CFG_KEY_ENTER XorStr("ENTER") //0x50,6,0xF49F2483>("\x15\x1F\x06\x16\x06"+0xF49F2483).s
#define CFG_KEY_BACKSPACE XorStr("BACKSPACE") //0x90,10,0x79A48D72>("\xD2\xD0\xD1\xD8\xC7\xC5\xD7\xD4\xDD"+0x79A48D72).s
#define CFG_KEY_UPARROW XorStr("UPARROW") //0x71,8,0xAACB1F33>("\x24\x22\x32\x26\x27\x39\x20"+0xAACB1F33).s
#define CFG_KEY_DOWNARROW XorStr("DOWNARROW") //0x90,10,0x85435E63>("\xD4\xDE\xC5\xDD\xD5\xC7\xC4\xD8\xCF"+0x85435E63).s
#define CFG_KEY_LEFTARROW XorStr("LEFTARROW") //0x6E,10,0x8F8FBC65>("\x22\x2A\x36\x25\x33\x21\x26\x3A\x21"+0x8F8FBC65).s
#define CFG_KEY_RIGHTARROW XorStr("RIGHTARROW") //0x97,11,0x5D93FB20>("\xC5\xD1\xDE\xD2\xCF\xDD\xCF\xCC\xD0\xF7"+0x5D93FB20).s

// ÊÍÎÏÊÈ ÒÐÈÃÃÅÐÀ

#define CFG_KEY_F1 XorStr("F1") //0x8C,3,0x7CE1BA79>("\xCA\xBC"+0x7CE1BA79).s
#define CFG_KEY_F2 XorStr("F2") //0x86,3,0x3E2A8BEC>("\xC0\xB5"+0x3E2A8BEC).s
#define CFG_KEY_F3 XorStr("F3") //0xCB,3,0x293FBD53>("\x8D\xFF"+0x293FBD53).s
#define CFG_KEY_F4 XorStr("F4") //0xD8,3,0xA508D39F>("\x9E\xED"+0xA508D39F).s
#define CFG_KEY_F5 XorStr("F5") //0x03,3,0x57A272D2>("\x45\x31"+0x57A272D2).s
#define CFG_KEY_F6 XorStr("F6") //0x31,3,0x21E09157>("\x77\x04"+0x21E09157).s
#define CFG_KEY_F7 XorStr("F7") //0x78,3,0x5854E2EF>("\x3E\x4E"+0x5854E2EF).s
#define CFG_KEY_F8 XorStr("F8") //0xB9,3,0xFEE2041B>("\xFF\x82"+0xFEE2041B).s
#define CFG_KEY_F9 XorStr("F9") //0x9A,3,0x2841FA61>("\xDC\xA2"+0x2841FA61).s
#define CFG_KEY_F10 XorStr("F10") //0x7A,4,0x7C35E7E0>("\x3C\x4A\x4C"+0x7C35E7E0).s
#define CFG_KEY_F11 XorStr("F11") //0x21,4,0xCB3EA338>("\x67\x13\x12"+0xCB3EA338).s
#define CFG_KEY_F12 XorStr("F12") //0x28,4,0x350B0A26>("\x6E\x18\x18"+0x350B0A26).s
#define CFG_KEY_MOUSE3 XorStr("MOUSE3") //0x9B,7,0x0606F5AB>("\xD6\xD3\xC8\xCD\xDA\x93"+0x0606F5AB).s
#define CFG_KEY_MOUSE4 XorStr("MOUSE4") //0x13,7,0xCA9D6CFF>("\x5E\x5B\x40\x45\x52\x2C"+0xCA9D6CFF).s
#define CFG_KEY_MOUSE5 XorStr("MOUSE5") //0xE1,7,0xEE5933E4>("\xAC\xAD\xB6\xB7\xA0\xD3"+0xEE5933E4).s

// ÎÐÓÆÈß

// ÏÈÑÒÎËÅÒÛ

#define WEAPON_DEAGLE_STR		"deagle"		// 0
#define WEAPON_ELITE_STR		"elite"			// 1
#define WEAPON_FIVESEVEN_STR	"fiveseven"		// 2
#define WEAPON_GLOCK_STR		"glock"			// 3
#define WEAPON_TASER_STR		"taser"
#define WEAPON_HKP2000_STR		"hkp2000"		// 4
#define WEAPON_P250_STR			"p250"			// 5
#define WEAPON_USP_S_STR		"usp_silencer"	// 6
#define WEAPON_CZ75A_STR		"cz75a"			// 7
#define WEAPON_REVOLVER_STR		"revolver"		// 8

// ÄÐÎÁÎÂÈÊÈ , ÀÂÒÎÌÀÒÛ

#define WEAPON_AK47_STR		"ak47"				// 9
#define WEAPON_AUG_STR		"aug"				// 10
#define WEAPON_FAMAS_STR	"famas"				// 11
#define WEAPON_GALILAR_STR	"galilar"			// 12
#define WEAPON_M249_STR		"m249"				// 13
#define WEAPON_M4A1_STR		"m4a1"				// 14
#define WEAPON_M4A1_S_STR	"m4a1_silencer"		// 15
#define WEAPON_MAC10_STR	"mac10"				// 16
#define WEAPON_P90_STR		"p90"				// 17
#define WEAPON_UMP45_STR	"ump45"				// 18
#define WEAPON_XM1014_STR	"xm1014"			// 19
#define WEAPON_BIZON_STR	"bizon"				// 20
#define WEAPON_MAG7_STR		"mag7"				// 21
#define WEAPON_NEGEV_STR	"negev"				// 22
#define WEAPON_SAWEDOFF_STR	"sawedoff"			// 23
#define WEAPON_TEC9_STR		"tec9"				// 24
#define WEAPON_MP7_STR		"mp7"				// 25
#define WEAPON_MP9_STR		"mp9"				// 26
#define WEAPON_NOVA_STR		"nova"				// 27
#define WEAPON_SG553_STR	"sg553"				// 28

// ÑÍÀÉÏÅÐÊÈ

#define WEAPON_AWP_STR		"awp"				// 29
#define WEAPON_G3SG1_STR	"g3sg1"				// 30
#define WEAPON_SCAR20_STR	"scar20"			// 31
#define WEAPON_SSG08_STR	"ssg08"				// 32

// ÃÐÀÍÀÒÛ

#define WEAPON_GRENADE_FL_STR	"flashbang"
#define WEAPON_GRENADE_HE_STR	"hegrenade"
#define WEAPON_GRENADE_SM_STR	"smokegrenade"
#define WEAPON_GRENADE_MO_STR	"molotov"
#define WEAPON_GRENADE_DE_STR	"decoy"
#define WEAPON_GRENADE_IN_STR	"incgrenade"

// ÎÒÑÒÀËÜÍÎÅ È ÍÎÆÈ

#define WEAPON_C4_STR		"c4"

#define WEAPON_KNIFE_STR XorStr("knife") //0x95,6,0x5F10F92B>("\xFE\xF8\xFE\xFE\xFC"+0x5F10F92B).s
#define WEAPON_KNIFE_T_STR XorStr("knife_t") //0xBC,8,0x8D899EBB>("\xD7\xD3\xD7\xD9\xA5\x9E\xB6"+0x8D899EBB).s
#define WEAPON_KNIFE_BA_STR XorStr("knife_bayonet") //0x06,14,0xCF613E61>("\x6D\x69\x61\x6F\x6F\x54\x6E\x6C\x77\x60\x7E\x74\x66"+0xCF613E61).s
#define WEAPON_KNIFE_FL_STR XorStr("knife_flip") //0xFF,11,0x8FDFFA0B>("\x94\x6E\x68\x64\x66\x5B\x63\x6A\x6E\x78"+0x8FDFFA0B).s
#define WEAPON_KNIFE_GU_STR XorStr("knife_gut") //0x63,10,0x4756DF17>("\x08\x0A\x0C\x00\x02\x37\x0E\x1F\x1F"+0x4756DF17).s
#define WEAPON_KNIFE_KA_STR XorStr("knife_karambit") //0x63,15,0x76B1C0FB>("\x08\x0A\x0C\x00\x02\x37\x02\x0B\x19\x0D\x00\x0C\x06\x04"+0x76B1C0FB).s
#define WEAPON_KNIFE_M9_STR XorStr("knife_m9_bayonet") //0x1B,17,0x052C7832>("\x70\x72\x74\x78\x7A\x7F\x4C\x1B\x7C\x46\x44\x5F\x48\x46\x4C\x5E"+0x052C7832).s
#define WEAPON_KNIFE_TA_STR XorStr("knife_tactical") //0x1C,15,0x45B2D60C>("\x77\x73\x77\x79\x45\x7E\x56\x42\x47\x51\x4F\x44\x49\x45"+0x45B2D60C).s
#define WEAPON_KNIFE_FA_STR XorStr("knife_falchion") //0x43,15,0x7014491D>("\x28\x2A\x2C\x20\x22\x17\x2F\x2B\x27\x2F\x25\x27\x20\x3E"+0x7014491D).s
#define WEAPON_KNIFE_SB_STR XorStr("knife_survival_bowie") //0xFC,21,0x216A0B3B>("\x97\x93\x97\x99\x65\x5E\x71\x76\x76\x73\x6F\x71\x69\x65\x55\x69\x63\x7A\x67\x6A"+0x216A0B3B).s
#define WEAPON_KNIFE_BU_STR XorStr("knife_butterfly") //0xC3,16,0x3CE61BF5>("\xA8\xAA\xAC\xA0\xA2\x97\xAB\xBF\xBF\xB8\xA8\xBC\xA9\xBC\xA8"+0x3CE61BF5).s
#define WEAPON_KNIFE_PU_STR XorStr("knife_push") //0x9E,11,0x13441EAB>("\xF5\xF1\xC9\xC7\xC7\xFC\xD4\xD0\xD5\xCF"+0x13441EAB).s

#define WEAPON_UNKNOWN_STR	"unknown"
