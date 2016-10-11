#include "_utils.h"

void UTIL_TraceLine( const Vector& vecAbsStart , const Vector& vecAbsEnd , unsigned int mask , const IClientEntity* ignore , int collisionGroup , trace_t* ptr )
{
	typedef void( __fastcall* _UTIL_TraceLine )( const Vector& , const Vector& , unsigned int , const IClientEntity* , int , trace_t* );
	
	static _UTIL_TraceLine UTIL_TraceLineFn = 0;
	static bool SearchFunction = false;

	if ( !SearchFunction )
	{
		DWORD dwClient = (DWORD)GetModuleHandleA( CLIENT_DLL );

		if ( dwClient )
		{
			DWORD dwFunctionTrace = FindPattern( "\x55\x8B\xEC\x83\xE4\xF0\x83\xEC\x7C\x56\x52\x51" , 11 , dwClient , dwClient + 0x1FFFFF , 0 );

			if ( *(PBYTE)dwFunctionTrace == 0x55 )
			{
				UTIL_TraceLineFn = (_UTIL_TraceLine)dwFunctionTrace;
				SearchFunction = true;
			}
		}
	}

	if ( UTIL_TraceLineFn )
	{
		UTIL_TraceLineFn( vecAbsStart , vecAbsEnd , mask , ignore , collisionGroup , ptr );
		_asm add esp , 0x10
	}
}

void ForceMaterial( Color color , IMaterial* material , bool useColor , bool forceMaterial )
{
	if ( useColor )
	{
		float blend[3] = { (float)color.r() / 255.f, (float)color.g() / 255.f, (float)color.b() / 255.f };
		float alpha = (float)color.a() / 255.f;

		g_pRenderView->SetBlend( alpha );
		g_pRenderView->SetColorModulation( blend );
	}

	if ( forceMaterial )
		g_pModelRender->ForcedMaterialOverride( material );
}

bool KeyValues::LoadFromBuffer( KeyValues *pThis , const char *pszFirst , const char *pszSecond , PVOID pSomething , PVOID pAnother , PVOID pLast )
{
	typedef bool( __thiscall *_LoadFromBuffer )( KeyValues* , const char* , const char* , PVOID , PVOID , PVOID );

	static _LoadFromBuffer LoadFromBufferFn = 0;
	static bool SearchFunction = false;

	if ( !SearchFunction )
	{
		DWORD dwFunctionAddress = FindPattern( "\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x34\x53\x8B\x5D\x0C\x89" , XorStr( "xxxxxxxxxxxxxx" ) , offset.dwClientModule , offset.dwClientModuleEnd , 0 );

		if ( *(PBYTE)dwFunctionAddress == 0x55 )
		{
			LoadFromBufferFn = (_LoadFromBuffer)dwFunctionAddress;
			SearchFunction = true;
		}
	}

	if ( LoadFromBufferFn && SearchFunction )
	{
		return LoadFromBufferFn( pThis , pszFirst , pszSecond , pSomething , pAnother , pLast );
	}

	return false;
}

IMaterial* CreateMaterial( bool bFlat , bool bShouldIgnoreZ , bool bIsWireframe )
{
	static int iCreated = 0;

	static const char szTmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"VGUI/white_additive\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$nocull\" \"1\"\
		\n\t\"$nofog\" \"1\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"1\"\
		\n\t\"halflambert\" \"1\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
	};

	char szMaterial[512];
	char szBaseType[64];

	if ( bFlat )
	{
		static const char pszBaseType[] = "UnlitGeneric";
		sprintf_s( szMaterial , sizeof( szMaterial ) , szTmp , pszBaseType , ( bShouldIgnoreZ ) ? 1 : 0 , ( bIsWireframe ) ? 1 : 0 );
		strcpy_s( szBaseType , pszBaseType );
	}
	else
	{
		static const char pszBaseType[] = "VertexLitGeneric";
		sprintf_s( szMaterial , sizeof( szMaterial ) , szTmp , pszBaseType , ( bShouldIgnoreZ ) ? 1 : 0 , ( bIsWireframe ) ? 1 : 0 );
		strcpy_s( szBaseType , pszBaseType );
	}

	char szName[512];
	sprintf_s( szName , sizeof( szName ) , "custom_material_%i.vmt" , iCreated );

	++iCreated;

	auto pKeyValues = new KeyValues( szBaseType );
	pKeyValues->LoadFromBuffer( pKeyValues , szName , szMaterial );
	auto pCreatedMaterial = g_pMaterialSystem->CreateMaterial( szName , pKeyValues );
	pCreatedMaterial->IncrementReferenceCount();
	return pCreatedMaterial;
}

bool GetBonePosition( IClientEntity* pPlayer , Vector& vBone , int Bone )
{
	matrix3x4_t MatrixArray[MAXSTUDIOBONES];

	if ( !pPlayer->SetupBones( MatrixArray , MAXSTUDIOBONES , BONE_USED_BY_HITBOX , g_pEngine->GetLastTimeStamp() ) )
		return FALSE;

	matrix3x4_t HitboxMatrix = MatrixArray[Bone];

	vBone = Vector( HitboxMatrix[0][3] , HitboxMatrix[1][3] , HitboxMatrix[2][3] );

	return true;
}

bool ScreenTransform( const Vector& vPoint , Vector& vScreen )
{
	float w = 0.f;
	bool bRet = false;
	const D3DMATRIX& worldToScreen = g_pEngine->WorldToScreenMatrix();

	vScreen.x = worldToScreen.m[0][0] * vPoint.x + worldToScreen.m[0][1] * vPoint.y + worldToScreen.m[0][2] * vPoint.z + worldToScreen.m[0][3];
	vScreen.y = worldToScreen.m[1][0] * vPoint.x + worldToScreen.m[1][1] * vPoint.y + worldToScreen.m[1][2] * vPoint.z + worldToScreen.m[1][3];
	vScreen.z = 0.0f;

	w = worldToScreen.m[3][0] * vPoint.x + worldToScreen.m[3][1] * vPoint.y + worldToScreen.m[3][2] * vPoint.z + worldToScreen.m[3][3];

	if ( w < 0.001f )
	{
		bRet = true;

		vScreen.x *= 100000;
		vScreen.y *= 100000;
	}
	else
	{
		float invw = 1.0f / w;

		vScreen.x *= invw;
		vScreen.y *= invw;
	}

	return bRet;
}

bool WorldToScreen( const Vector& vOrigin , Vector& vScreen )
{
	int width = 0 , height = 0;
	float fScreenX = 0.f , fScreenY = 0.f;
	bool bRet = false;

	if ( !ScreenTransform( vOrigin , vScreen ) )
	{
		g_pEngine->GetScreenSize( width , height );

		fScreenX = float( width / 2 );
		fScreenY = float( height / 2 );

		fScreenX += 0.5f * vScreen.x * width + 0.5f;
		fScreenY -= 0.5f * vScreen.y * height + 0.5f;

		vScreen.x = fScreenX;
		vScreen.y = fScreenY;

		bRet = true;
	}

	return bRet;
}

bool GetVisible( Vector vEyeOrigin , Vector vOrigin )
{
	trace_t tr;
	UTIL_TraceLine( vEyeOrigin , vOrigin , PlayerVisibleMask , 0 , 0 , &tr );
	return tr.IsVisible();
}

float CalcDistPlayerScreen( Vector2D vSceenPos , Vector2D vPlayerPosSceen )
{
	return ( nt_sqrt( nt_powx( vPlayerPosSceen.x - vSceenPos.x , 2 ) + nt_powx( vPlayerPosSceen.y - vSceenPos.y , 2 ) ) );
}

weapon_data GetWeaponData( int iItemDefinitionIndex )
{
	weapon_data data;

	switch ( iItemDefinitionIndex )
	{
		case WEAPON_DEAGLE:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_DEAGLE_STR );
			break;
		case WEAPON_ELITE:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_ELITE_STR );
			break;
		case WEAPON_FIVESEVEN:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_FIVESEVEN_STR );
			break;
		case WEAPON_GLOCK:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_GLOCK_STR );
			break;
		case WEAPON_AK47:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_AK47_STR );
			break;
		case WEAPON_AUG:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_AUG_STR );
			break;
		case WEAPON_AWP:
			data.type = WEAPON_TYPE_SNIPER;
			nt_strcpy( data.name , WEAPON_AWP_STR );
			break;
		case WEAPON_FAMAS:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_FAMAS_STR );
			break;
		case WEAPON_G3SG1:
			data.type = WEAPON_TYPE_SNIPER;
			nt_strcpy( data.name , WEAPON_G3SG1_STR );
			break;
		case WEAPON_GALILAR:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_GALILAR_STR );
			break;
		case WEAPON_M249:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_M249_STR );
			break;
		case WEAPON_M4A1:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_M4A1_STR );
			break;
		case WEAPON_MAC10:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_MAC10_STR );
			break;
		case WEAPON_P90:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_P90_STR );
			break;
		case WEAPON_UMP45:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_UMP45_STR );
			break;
		case WEAPON_XM1014:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_XM1014_STR );
			break;
		case WEAPON_BIZON:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_BIZON_STR );
			break;
		case WEAPON_MAG7:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_MAG7_STR );
			break;
		case WEAPON_NEGEV:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_NEGEV_STR );
			break;
		case WEAPON_SAWEDOFF:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_SAWEDOFF_STR );
			break;
		case WEAPON_TEC9:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_TEC9_STR );
			break;
		case WEAPON_TASER:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_TASER_STR );
			break;
		case WEAPON_HKP2000:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_HKP2000_STR );
			break;
		case WEAPON_MP7:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_MP7_STR );
			break;
		case WEAPON_MP9:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_MP9_STR );
			break;
		case WEAPON_NOVA:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_NOVA_STR );
			break;
		case WEAPON_P250:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_P250_STR );
			break;
		case WEAPON_SCAR20:
			data.type = WEAPON_TYPE_SNIPER;
			nt_strcpy( data.name , WEAPON_SCAR20_STR );
			break;
		case WEAPON_SG553:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_SG553_STR );
			break;
		case WEAPON_SSG08:
			data.type = WEAPON_TYPE_SNIPER;
			nt_strcpy( data.name , WEAPON_SSG08_STR );
			break;
		case WEAPON_KNIFE:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_STR );
			break;
		case WEAPON_FLASHBANG:
			data.type = WEAPON_TYPE_GRENADE;
			nt_strcpy( data.name , WEAPON_GRENADE_FL_STR );
			break;
		case WEAPON_HEGRENADE:
			data.type = WEAPON_TYPE_GRENADE;
			nt_strcpy( data.name , WEAPON_GRENADE_HE_STR );
			break;
		case WEAPON_SMOKEGRENADE:
			data.type = WEAPON_TYPE_GRENADE;
			nt_strcpy( data.name , WEAPON_GRENADE_SM_STR );
			break;
		case WEAPON_MOLOTOV:
			data.type = WEAPON_TYPE_GRENADE;
			nt_strcpy( data.name , WEAPON_GRENADE_MO_STR );
			break;
		case WEAPON_DECOY:
			data.type = WEAPON_TYPE_GRENADE;
			nt_strcpy( data.name , WEAPON_GRENADE_DE_STR );
			break;
		case WEAPON_INCGRENADE:
			data.type = WEAPON_TYPE_GRENADE;
			nt_strcpy( data.name , WEAPON_GRENADE_IN_STR );
			break;
		case WEAPON_C4:
			data.type = WEAPON_TYPE_C4;
			nt_strcpy( data.name , WEAPON_C4_STR );
			break;
		case WEAPON_KNIFE_T:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_T_STR );
			break;
		case WEAPON_M4A1_SILENCER:
			data.type = WEAPON_TYPE_SHOTGUN;
			nt_strcpy( data.name , WEAPON_M4A1_S_STR );
			break;
		case WEAPON_USP_SILENCER:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_USP_S_STR );
			break;
		case WEAPON_CZ75A:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_CZ75A_STR );
			break;
		case WEAPON_REVOLVER:
			data.type = WEAPON_TYPE_PISTOL;
			nt_strcpy( data.name , WEAPON_REVOLVER_STR );
			break;
		case WEAPON_KNIFE_BAYONET:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_BA_STR );
			break;
		case WEAPON_KNIFE_FLIP:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_FL_STR );
			break;
		case WEAPON_KNIFE_GUT:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_GU_STR );
			break;
		case WEAPON_KNIFE_KARAMBIT:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_KA_STR );
			break;
		case WEAPON_KNIFE_M9_BAYONET:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_M9_STR );
			break;
		case WEAPON_KNIFE_TACTICAL:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_TA_STR );
			break;
		case WEAPON_KNIFE_FALCHION:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_FA_STR );
			break;
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_SB_STR );
			break;
		case WEAPON_KNIFE_BUTTERFLY:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_BU_STR );
			break;
		case WEAPON_KNIFE_PUSH:
			data.type = WEAPON_TYPE_KNIFE;
			nt_strcpy( data.name , WEAPON_KNIFE_PU_STR );
			break;
		default:
			data.type = WEAPON_TYPE_UNKNOWN;
			nt_strcpy( data.name , WEAPON_UNKNOWN_STR );
			break;
	}

	return data;
}

void AngleVectors( const QAngle& angles , Vector& vForward , Vector& vRight , Vector& vUp )
{
	float angle;
	float sr , sp , sy , cr , cp , cy;

	angle = angles.y * ( M_PI * 2 / 360 );

	sy = nt_sin( angle );
	cy = nt_cos( angle );

	angle = angles.x * ( M_PI * 2 / 360 );

	sp = nt_sin( angle );
	cp = nt_cos( angle );

	angle = angles.z * ( M_PI * 2 / 360 );

	sr = nt_sin( angle );
	cr = nt_cos( angle );

	vForward.x = cp*cy;
	vForward.y = cp*sy;
	vForward.z = -sp;

	vRight.x = ( -1 * sr*sp*cy + -1 * cr*-sy );
	vRight.y = ( -1 * sr*sp*sy + -1 * cr*cy );
	vRight.z = -1 * sr*cp;

	vUp.x = ( cr*sp*cy + -sr*-sy );
	vUp.y = ( cr*sp*sy + -sr*cy );
	vUp.z = cr*cp;
}

void VectorAnglesNew( const float *forward , float *angles )
{
	float	tmp , yaw , pitch;

	if( forward[1] == 0 && forward[0] == 0 )
	{
		yaw = 0;
		if( forward[2] > 0 )
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = ( atan2( forward[1] , forward[0] ) * 180 / M_PI );
		if( yaw < 0 )
			yaw += 360;

		tmp = sqrt( forward[0] * forward[0] + forward[1] * forward[1] );
		pitch = ( atan2( -forward[2] , tmp ) * 180 / M_PI );
		if( pitch < 0 )
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

void VectorAngles( const Vector vVorward , QAngle& qAngles )
{
	float tmp , yaw , pitch;

	if( vVorward[1] == 0 && vVorward[0] == 0 )
	{
		yaw = 0;
		if( vVorward[2] > 0 )
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = ( nt_atan2( vVorward[1] , vVorward[0] ) * 180 / M_PI );
		if( yaw < 0 )
			yaw += 360;

		tmp = nt_sqrt( vVorward[0] * vVorward[0] + vVorward[1] * vVorward[1] );
		pitch = ( nt_atan2( -vVorward[2] , tmp ) * 180 / M_PI );
		
		if( pitch < 0 )
			pitch += 360;
	}

	qAngles[0] = pitch;
	qAngles[1] = yaw;
	qAngles[2] = 0;
}