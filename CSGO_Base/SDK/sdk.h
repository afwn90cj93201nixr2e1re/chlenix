#pragma once

#include "types.h"
#include "basetypes.h"
#include "button.h"
#include "color.h"
#include "const.h"
#include "bspflags.h"
#include "string.h"
#include "vector.h"
#include "mathlib.h"
#include "dt_recv.h"
#include "crc.h"
#include "cinput.h"

#include "../main.h"
#include "../client.h"

#pragma region OFFSET

#define CSGO_VERSION XorStr("1.35.5.4")
#define CSGO_CLIENT_VERSION 381

#define m_vecOrigin 0x134
#define m_hMyWeapons 0x2DE8
#define m_hViewModel 0x32FC
#define m_fEffects 0xEC
#define m_iTeamNum 0xF0
#define m_angEyeAngles 0xA9FC
#define m_iHealth 0xFC
#define m_ArmorValue 0xA9F8
#define m_iShotsFired 0xA2C0
#define m_iCrossHairID 0xAA64
#define m_lifeState 0x25B
#define m_fFlags 0x100
#define m_vecViewOffset 0x104
#define m_aimPunchAngle 0x301C
#define m_hActiveWeapon 0x2EE8
#define m_iFOVStart 0x31D8
#define m_MoveType 0x258
#define m_iClip1 0x3204
#define m_iItemDefinitionIndex 0x2F88
#define m_nFallbackPaintKit 0x3170
#define m_flFallbackWear 0x3178
#define m_iItemIDHigh 0x2FA0
#define m_OriginalOwnerXuidHigh 0x316C
#define m_OriginalOwnerXuidLow 0x3168
#define m_iAccountID 0x2FA8
#define m_iEntityQuality 0x2F8C
#define m_nModelIndex 0x254
#define m_hOwner 0x29BC
#define m_hWeapon 0x29B8
#define m_hOwnerEntity 0x148

#define m_nTickBase 0x3424
#define m_flNextPrimaryAttack 0x31D8

#define m_dwGlowObject 0x4FC5054
#define m_iGlowIndex 0xA320

#define CSPlayerResource 0x2EEBE94
#define m_iCompetitiveRanking 0x1A44

#pragma endregion

#pragma region SDK

class IVEngineClient;
class IBaseClientDLL;
class IEngineSound;
class ISurface;
class IPanel;
class IPlayerInfoManager;
class CGlobalVarsBase;
class IClientMode;
class IClientEntity;
class IClientEntityList;
class IVModelInfoClient;
class IGameEventManager2;
class IModelRender;
class IRenderView;
class IMaterialSystem;

extern IVEngineClient*		g_pEngine;
extern IBaseClientDLL*		g_pClient;
extern IEngineSound*		g_pSound;
extern ISurface*			g_pSurface;
extern IPanel*				g_pPanel;
extern IPlayerInfoManager*	g_pPlayerInfoManager;
extern CGlobalVarsBase*		g_pGlobalVarsBase;
extern IClientMode*			g_pClientMode;
extern IClientEntityList*	g_pClientEntList;
extern IVModelInfoClient*	g_pModelInfo;
extern IGameEventManager2*	g_pGameEventMgr;
extern IModelRender*		g_pModelRender;
extern IRenderView*			g_pRenderView;
extern IMaterialSystem*		g_pMaterialSystem;
extern CInput*              g_pInput;

#define VirtualFn( cast ) typedef cast( __thiscall* OriginalFn )

#pragma endregion

#pragma region Defines

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

struct GlowObjectDefinition_t
{
	IClientEntity* pEntity;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	uint8_t unk2[14];
};

#pragma endregion

#pragma region Interface

#define VENGINE_CLIENT_INTERFACE_VERSION		"VEngineClient014"
#define CLIENT_DLL_INTERFACE_VERSION			"VClient017"
#define VCLIENTENTITYLIST_INTERFACE_VERSION		"VClientEntityList003"
#define VGUI_SURFACE_INTERFACE_VERSION			"VGUI_Surface031"
#define VGUI_PANEL_INTERFACE_VERSION			"VGUI_Panel009"
#define INTERFACEVERSION_PLAYERINFOMANAGER		"PlayerInfoManager002"
#define IENGINESOUND_CLIENT_INTERFACE_VERSION	"IEngineSoundClient003"
#define VMODELINFO_CLIENT_INTERACE_VERSION		"VModelInfoClient004"
#define GAMEEVENTMANAGER_INTERFACE_VERSION		"GAMEEVENTSMANAGER002"
#define VENGINE_HUDMODEL_INTERFACE_VERSION		"VEngineModel016"
#define VENGINE_RENDERVIEW_INTERFACE_VERSION	"VEngineRenderView014"
#define MATERIAL_SYSTEM_INTERFACE_VERSION		"VMaterialSystem080"
#define CREATEINTERFACE_PROCNAME				"CreateInterface"

class IBaseInterface
{
public:
	virtual	~IBaseInterface() { }
};

typedef void* ( *CreateInterfaceFn )( const char *pName , int *pReturnCode );

#pragma endregion

#pragma region WorldSize

#define MAX_COORD_INTEGER			(16384)
#define MIN_COORD_INTEGER			(-MAX_COORD_INTEGER)
#define MAX_COORD_FRACTION			(1.0-(1.0/16.0))
#define MIN_COORD_FRACTION			(-1.0+(1.0/16.0))

#define MAX_COORD_FLOAT				(16384.0f)
#define MIN_COORD_FLOAT				(-MAX_COORD_FLOAT)

// Width of the coord system, which is TOO BIG to send as a client/server coordinate value
#define COORD_EXTENT				(2*MAX_COORD_INTEGER)

// Maximum traceable distance ( assumes cubic world and trace from one corner to opposite )
// COORD_EXTENT * sqrt(3)
#define MAX_TRACE_LENGTH			( 1.732050807569 * COORD_EXTENT )		

// This value is the LONGEST possible range (limited by max valid coordinate number, not 2x)
#define MAX_COORD_RANGE				(MAX_COORD_INTEGER)

#pragma endregion

#pragma region Studio

#define MAXSTUDIOTRIANGLES	25000
#define MAXSTUDIOVERTS		10000
#define	MAXSTUDIOFLEXVERTS	1000

#define MAXSTUDIOSKINS		32		// total textures
#define MAXSTUDIOBONES		128		// total bones actually used
#define MAXSTUDIOFLEXDESC	1024	// maximum number of low level flexes (actual morph targets)
#define MAXSTUDIOFLEXCTRL	96		// maximum number of flexcontrollers (input sliders)
#define MAXSTUDIOPOSEPARAM	24
#define MAXSTUDIOBONECTRLS	4
#define MAXSTUDIOANIMBLOCKS 256

#define MAXSTUDIOBONEBITS	7		// NOTE: MUST MATCH MAXSTUDIOBONES

// NOTE!!! : Changing this number also changes the vtx file format!!!!!
#define MAX_NUM_BONES_PER_VERT 3

//Adrian - Remove this when we completely phase out the old event system.
#define NEW_EVENT_STYLE ( 1 << 10 )

#define BONE_CALCULATE_MASK			0x1F
#define BONE_PHYSICALLY_SIMULATED	0x01	// bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL		0x02	// procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL		0x04	// bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE	0x08	// bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER	0x10	// bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800	
#define BONE_USED_BY_VERTEX_LOD2	0x00001000  
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000	// bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8

#define BONE_TYPE_MASK				0x00F00000
#define BONE_FIXED_ALIGNMENT		0x00100000	// bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS		0x00200000	// Vector48
#define BONE_HAS_SAVEFRAME_ROT		0x00400000	// Quaternion64

#pragma endregion

#pragma region IVEngineClient

typedef struct player_info_s {
private:
	DWORD __pad0[2];
public:
	int m_nXuidLow;
	int m_nXuidHigh;
	char m_szPlayerName[128];
	int m_nUserID;
	char m_szSteamID[33];
	UINT m_nSteam3ID;
	char m_szFriendsName[128];
	bool m_bIsFakePlayer;
	bool m_bIsHLTV;
	DWORD m_dwCustomFiles[4];
	BYTE m_FilesDownloaded;
private:
	int __pad1;
} player_info_t;

struct client_textmessage_t
{
	int		effect;
	byte	r1 , g1 , b1 , a1;		// 2 colors for effects
	byte	r2 , g2 , b2 , a2;
	float	x;
	float	y;
	float	fadein;
	float	fadeout;
	float	holdtime;
	float	fxtime;
	const char *pVGuiSchemeFontName; // If null, use default font for messages
	const char *pName;
	const char *pMessage;
	bool    bRoundedRectBackdropBox;
	float	flBoxSize; // as a function of font height
	byte	boxcolor[4];
	char const *pClearMessage; // message to clear
};

struct OcclusionParams_t
{
	float	m_flMaxOccludeeArea;
	float	m_flMinOccluderArea;
};

enum SkyboxVisibility_t
{
	SKYBOX_NOT_VISIBLE = 0 ,
	SKYBOX_3DSKYBOX_VISIBLE ,
	SKYBOX_2DSKYBOX_VISIBLE ,
};

enum EngineInputContextId_t
{
	ENGINE_INPUT_CONTEXT_GAME = 0 ,
	ENGINE_INPUT_CONTEXT_GAMEUI ,
};

typedef struct con_nprint_s
{
	int		index;			// Row #
	float	time_to_live;	// # of seconds before it disappears. -1 means to display for 1 frame then go away.
	float	color[3];		// RGB colors ( 0.0 -> 1.0 scale )
	bool	fixed_width_font;
} con_nprint_t;

struct model_t;
class SurfInfo;
class IMaterial;
class CSentence;
class CAudioSource;
class ISpatialQuery;
class IMaterialSystem;
class Frustum_t;
struct AudioState_t;
class INetChannelInfo;
class CPhysCollide;
class IAchievementMgr;
class ISPSharedMemory;
class CGamestatsData;
class CSteamAPIContext;
class KeyValues;

#define FORWARD_DECLARE_HANDLE(name) typedef struct name##__ *name
typedef void( *pfnDemoCustomDataCallback )( uint8 *pData , size_t iSize );
FORWARD_DECLARE_HANDLE( InputContextHandle_t );

template< class T , class A > class CUtlVector;
template< class T , class I > class CUtlMemory;

template< class T , class I = int >
class CUtlMemory { };

template< class T , class A = CUtlMemory<T> >
class CUtlVector { };

class IVEngineClient
{
public:
	// Find the model's surfaces that intersect the given sphere.
	// Returns the number of surfaces filled in.
	virtual int					GetIntersectingSurfaces(
		const model_t *model ,
		const Vector &vCenter ,
		const float radius ,
		const bool bOnlyVisibleSurfaces ,	// Only return surfaces visible to vCenter.
		SurfInfo *pInfos ,
		const int nMaxInfos ) = 0;

	// Get the lighting intensivty for a specified point
	// If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
	virtual Vector				GetLightForPoint( const Vector &pos , bool bClamp ) = 0;

	// Traces the line and reports the material impacted as well as the lighting information for the impact point
	virtual IMaterial			*TraceLineMaterialAndLighting( const Vector &start , const Vector &end ,
															   Vector &diffuseLightColor , Vector& baseColor ) = 0;

	// Given an input text buffer data pointer, parses a single token into the variable token and returns the new
	//  reading position
	virtual const char			*ParseFile( const char *data , char *token , int maxlen ) = 0;
	virtual bool				CopyFile( const char *source , const char *destination ) = 0;

	// Gets the dimensions of the game window
	virtual void				GetScreenSize( int& width , int& height ) = 0;

	// Forwards szCmdString to the server, sent reliably if bReliable is set
	virtual void				ServerCmd( const char *szCmdString , bool bReliable = true ) = 0;
	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
	//       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void				ClientCmd( const char *szCmdString ) = 0;

	// Fill in the player info structure for the specified player index (name, model, etc.)
	virtual bool				GetPlayerInfo( int ent_num , player_info_t *pinfo ) = 0;

	// Retrieve the player entity number for a specified userID
	virtual int					GetPlayerForUserID( int userID ) = 0;

	// Retrieves text message system information for the specified message by name
	virtual client_textmessage_t *TextMessageGet( const char *pName ) = 0; // 10

																		   // Returns true if the console is visible
	virtual bool				Con_IsVisible( void ) = 0;

	// Get the entity index of the local player
	virtual int					GetLocalPlayer( void ) = 0;

	// Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
	virtual const model_t		*LoadModel( const char *pName , bool bProp = false ) = 0;

	// Get the exact server timesstamp ( server time ) from the last message received from the server
	virtual float				GetLastTimeStamp( void ) = 0;

	// Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
	//  captioning data )
	virtual CSentence			*GetSentence( CAudioSource *pAudioSource ) = 0; // 15
																				// Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
	virtual float				GetSentenceLength( CAudioSource *pAudioSource ) = 0;
	// Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
	virtual bool				IsStreaming( CAudioSource *pAudioSource ) const = 0;

	// Copy current view orientation into va
	virtual void				GetViewAngles( QAngle& va ) = 0;
	// Set current view orientation from va
	virtual void				SetViewAngles( QAngle& va ) = 0;

	// Retrieve the current game's maxclients setting
	virtual int					GetMaxClients( void ) = 0; // 20

														   // Given the string pBinding which may be bound to a key, 
														   //  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
	virtual	const char			*Key_LookupBinding( const char *pBinding ) = 0;

	// Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
	virtual const char			*Key_BindingForKey( ButtonCode_t &code ) = 0;
	virtual void				Key_SetBinding( ButtonCode_t , char const* ) = 0;

	// key trapping (for binding keys)
	virtual void				StartKeyTrapMode( void ) = 0;
	virtual bool				CheckDoneKeyTrapping( ButtonCode_t &code ) = 0;

	// Returns true if the player is fully connected and active in game (i.e, not still loading)
	virtual bool				IsInGame( void ) = 0;
	// Returns true if the player is connected, but not necessarily active in game (could still be loading)
	virtual bool				IsConnected( void ) = 0;
	// Returns true if the loading plaque should be drawn
	virtual bool				IsDrawingLoadingImage( void ) = 0;
	virtual void				HideLoadingPlaque( void ) = 0;

	// Prints the formatted string to the notification area of the screen ( down the right hand edge
	//  numbered lines starting at position 0
	virtual void				Con_NPrintf( int pos , const char *fmt , ... ) = 0; // 30
																					// Similar to Con_NPrintf, but allows specifying custom text color and duration information
	virtual void				Con_NXPrintf( const struct con_nprint_s *info , const char *fmt , ... ) = 0;

	// Is the specified world-space bounding box inside the view frustum?
	virtual int					IsBoxVisible( const Vector& mins , const Vector& maxs ) = 0;

	// Is the specified world-space boudning box in the same PVS cluster as the view origin?
	virtual int					IsBoxInViewCluster( const Vector& mins , const Vector& maxs ) = 0;

	// Returns true if the specified box is outside of the view frustum and should be culled
	virtual bool				CullBox( const Vector& mins , const Vector& maxs ) = 0;

	// Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
	virtual void				Sound_ExtraUpdate( void ) = 0;

	// Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
	virtual const char			*GetGameDirectory( void ) = 0;

	// Get access to the world to screen transformation matrix
	virtual const D3DMATRIX& 		WorldToScreenMatrix() = 0;

	// Get the matrix to move a point from world space into view space
	// (translate and rotate so the camera is at the origin looking down X).
	virtual const D3DMATRIX& 		WorldToViewMatrix() = 0;

	// The .bsp file can have mod-specified data lumps. These APIs are for working with such game lumps.

	// Get mod-specified lump version id for the specified game data lump
	virtual int					GameLumpVersion( int lumpId ) const = 0;
	// Get the raw size of the specified game data lump.
	virtual int					GameLumpSize( int lumpId ) const = 0; // 40
																	  // Loads a game lump off disk, writing the data into the buffer pointed to by pBuffer
																	  // Returns false if the data can't be read or the destination buffer is too small
	virtual bool				LoadGameLump( int lumpId , void* pBuffer , int size ) = 0;

	// Returns the number of leaves in the level
	virtual int					LevelLeafCount() const = 0;

	// Gets a way to perform spatial queries on the BSP tree
	virtual ISpatialQuery*		GetBSPTreeQuery() = 0;

	// Convert texlight to gamma...
	virtual void		LinearToGamma( float* linear , float* gamma ) = 0;

	// Get the lightstyle value
	virtual float		LightStyleValue( int style ) = 0; // 45

														  // Computes light due to dynamic lighting at a point
														  // If the normal isn't specified, then it'll return the maximum lighting
	virtual void		ComputeDynamicLighting( const Vector& pt , const Vector* pNormal , Vector& color ) = 0;

	// Returns the color of the ambient light
	virtual void		GetAmbientLightColor( Vector& color ) = 0;

	// Returns the dx support level
	virtual int			GetDXSupportLevel() = 0;

	// GR - returns the HDR support status
	virtual bool        SupportsHDR() = 0;

	// Replace the engine's material system pointer.
	virtual void		Mat_Stub( IMaterialSystem *pMatSys ) = 0; // 50

																  // Get the name of the current map
	virtual void GetChapterName( char *pchBuff , int iMaxLength ) = 0;
	virtual char const	*GetLevelName( void ) = 0;
	virtual char const	*GetLevelNameShort( void ) = 0;
	virtual char const	*GetMapGroupName( void ) = 0;

	// Obtain access to the voice tweaking API
	virtual struct IVoiceTweak_s *GetVoiceTweakAPI( void ) = 0;

	///// new virtual added on 14\08\2014 /////
	virtual void SetVoiceCasterID( unsigned int someint ) = 0; // 56

															   // Tell engine stats gathering system that the rendering frame is beginning/ending
	virtual void		EngineStats_BeginFrame( void ) = 0;
	virtual void		EngineStats_EndFrame( void ) = 0;

	// This tells the engine to fire any events (temp entity messages) that it has queued up this frame. 
	// It should only be called once per frame.
	virtual void		FireEvents() = 0;

	// Returns an area index if all the leaves are in the same area. If they span multple areas, then it returns -1.
	virtual int			GetLeavesArea( unsigned short *pLeaves , int nLeaves ) = 0;

	// Returns true if the box touches the specified area's frustum.
	virtual bool		DoesBoxTouchAreaFrustum( const Vector &mins , const Vector &maxs , int iArea ) = 0; // 60
	virtual int			GetFrustumList( Frustum_t **pList , int listMax ) = 0;
	virtual bool		ShouldUseAreaFrustum( int i ) = 0;

	// Sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize 
	//  sound appropriately ).
	virtual void		SetAudioState( const AudioState_t& state ) = 0;

	// Sentences / sentence groups
	virtual int			SentenceGroupPick( int groupIndex , char *name , int nameBufLen ) = 0;
	virtual int			SentenceGroupPickSequential( int groupIndex , char *name , int nameBufLen , int sentenceIndex , int reset ) = 0;
	virtual int			SentenceIndexFromName( const char *pSentenceName ) = 0;
	virtual const char *SentenceNameFromIndex( int sentenceIndex ) = 0;
	virtual int			SentenceGroupIndexFromName( const char *pGroupName ) = 0;
	virtual const char *SentenceGroupNameFromIndex( int groupIndex ) = 0;
	virtual float		SentenceLength( int sentenceIndex ) = 0;

	// Computes light due to dynamic lighting at a point
	// If the normal isn't specified, then it'll return the maximum lighting
	// If pBoxColors is specified (it's an array of 6), then it'll copy the light contribution at each box side.
	virtual void		ComputeLighting( const Vector& pt , const Vector* pNormal , bool bClamp , Vector& color , Vector *pBoxColors = NULL ) = 0;

	// Activates/deactivates an occluder...
	virtual void		ActivateOccluder( int nOccluderIndex , bool bActive ) = 0;
	virtual bool		IsOccluded( const Vector &vecAbsMins , const Vector &vecAbsMaxs ) = 0; // 74
	virtual int			GetOcclusionViewId( void ) = 0;

	// The save restore system allocates memory from a shared memory pool, use this allocator to allocate/free saverestore 
	//  memory.
	virtual void		*SaveAllocMemory( size_t num , size_t size ) = 0;
	virtual void		SaveFreeMemory( void *pSaveMem ) = 0;

	// returns info interface for client netchannel
	virtual INetChannelInfo	*GetNetChannelInfo( void ) = 0;

	// Debugging functionality:
	// Very slow routine to draw a physics model
	virtual void		DebugDrawPhysCollide( const CPhysCollide *pCollide , IMaterial *pMaterial , const matrix3x4_t& transform , const color32 &color ) = 0; //79
																																							   // This can be used to notify test scripts that we're at a particular spot in the code.
	virtual void		CheckPoint( const char *pName ) = 0; // 80
															 // Draw portals if r_DrawPortals is set (Debugging only)
	virtual void		DrawPortals() = 0;
	// Determine whether the client is playing back or recording a demo
	virtual bool		IsPlayingDemo( void ) = 0;
	virtual bool		IsRecordingDemo( void ) = 0;
	virtual bool		IsPlayingTimeDemo( void ) = 0;
	virtual int			GetDemoRecordingTick( void ) = 0;
	virtual int			GetDemoPlaybackTick( void ) = 0;
	virtual int			GetDemoPlaybackStartTick( void ) = 0;
	virtual float		GetDemoPlaybackTimeScale( void ) = 0;
	virtual int			GetDemoPlaybackTotalTicks( void ) = 0;
	// Is the game paused?
	virtual bool		IsPaused( void ) = 0; // 90

											  // What is the game timescale multiplied with the host_timescale?
	virtual float GetTimescale( void ) const = 0;

	// Is the game currently taking a screenshot?
	virtual bool		IsTakingScreenshot( void ) = 0;
	// Is this a HLTV broadcast ?
	virtual bool		IsHLTV( void ) = 0;
	// Is this a Replay demo?
	//virtual bool		IsReplay( void ) = 0;
	// is this level loaded as just the background to the main menu? (active, but unplayable)
	virtual bool		IsLevelMainMenuBackground( void ) = 0;
	// returns the name of the background level
	virtual void		GetMainMenuBackgroundName( char *dest , int destlen ) = 0;

	// Occlusion system control
	virtual void		SetOcclusionParameters( const OcclusionParams_t &params ) = 0; // 96

																					   // What language is the user expecting to hear .wavs in, "english" or another...
	virtual void		GetUILanguage( char *dest , int destlen ) = 0;

	// Can skybox be seen from a particular point?
	virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint( const Vector &vecPoint ) = 0;

	// Get the pristine map entity lump string.  (e.g., used by CS to reload the map entities when restarting a round.)
	virtual const char*	GetMapEntitiesString() = 0;

	// Is the engine in map edit mode ?
	virtual bool		IsInEditMode( void ) = 0; // 100

												  // current screen aspect ratio (eg. 4.0f/3.0f, 16.0f/9.0f)
	virtual float		GetScreenAspectRatio( int viewportWidth , int viewportHeight ) = 0;

	// allow the game UI to login a user
	virtual bool		REMOVED_SteamRefreshLogin( const char *password , bool isSecure ) = 0; // 100
	virtual bool		REMOVED_SteamProcessCall( bool & finished ) = 0;

	// allow other modules to know about engine versioning (one use is a proxy for network compatability)
	virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
	virtual const char *	GetProductVersionString() = 0; // mods version number (steam.inf)

														   // Communicates to the color correction editor that it's time to grab the pre-color corrected frame
														   // Passes in the actual size of the viewport
	virtual void			GrabPreColorCorrectedFrame( int x , int y , int width , int height ) = 0;

	virtual bool			IsHammerRunning() const = 0;

	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// And then executes the command string immediately (vs ClientCmd() which executes in the next frame)
	//
	// Note: this is NOT checked against the FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void			ExecuteClientCmd( const char *szCmdString ) = 0; //108

																			 // returns if the loaded map was processed with HDR info. This will be set regardless
																			 // of what HDR mode the player is in.
	virtual bool MapHasHDRLighting( void ) = 0;
	virtual bool MapHasLightMapAlphaData( void ) = 0;

	virtual int	GetAppID() = 0;

	// Just get the leaf ambient light - no caching, no samples
	virtual Vector			GetLightForPointFast( const Vector &pos , bool bClamp ) = 0;

	// This version does NOT check against FCVAR_CLIENTCMD_CAN_EXECUTE.
	virtual void			ClientCmd_Unrestricted( char  const* , int , bool ) = 0;
	virtual void			ClientCmd_Unrestricted( const char *szCmdString ) = 0; // 114

																				   // This used to be accessible through the cl_restrict_server_commands cvar.
																				   // By default, Valve games restrict the server to only being able to execute commands marked with FCVAR_SERVER_CAN_EXECUTE.
																				   // By default, mods are allowed to execute any server commands, and they can restrict the server's ability to execute client
																				   // commands with this function.
	virtual void			SetRestrictServerCommands( bool bRestrict ) = 0;

	// If set to true (defaults to true for Valve games and false for others), then IVEngineClient::ClientCmd
	// can only execute things marked with FCVAR_CLIENTCMD_CAN_EXECUTE.
	virtual void			SetRestrictClientCommands( bool bRestrict ) = 0;

	// Sets the client renderable for an overlay's material proxy to bind to
	virtual void			SetOverlayBindProxy( int iOverlayID , void *pBindProxy ) = 0;

	virtual bool			CopyFrameBufferToMaterial( const char *pMaterialName ) = 0;

	// Causes the engine to read in the user's configuration on disk
	virtual void			ReadConfiguration( const int iController , const bool readDefault ) = 0;

	virtual void			SetAchievementMgr( IAchievementMgr *pAchievementMgr ) = 0;
	virtual IAchievementMgr*GetAchievementMgr() = 0;
	virtual bool			MapLoadFailed( void ) = 0;
	virtual void			SetMapLoadFailed( bool bState ) = 0;
	virtual bool			IsLowViolence() = 0;
	virtual const char		*GetMostRecentSaveGame( void ) = 0;
	virtual void			SetMostRecentSaveGame( const char *lpszFilename ) = 0;
	virtual void			StartXboxExitingProcess() = 0;
	virtual bool			IsSaveInProgress() = 0;
	virtual bool			IsAutoSaveDangerousInProgress( void ) = 0;
	virtual uint			OnStorageDeviceAttached( int iController ) = 0;
	virtual void			OnStorageDeviceDetached( int iController ) = 0;
	virtual char* const		GetSaveDirName( void ) = 0;
	// generic screenshot writing
	virtual void			WriteScreenshot( const char *pFilename ) = 0;
	virtual void			ResetDemoInterpolation( void ) = 0;
	// For non-split screen games this will always be zero
	virtual int				GetActiveSplitScreenPlayerSlot() = 0;
	virtual int				SetActiveSplitScreenPlayerSlot( int slot ) = 0;
	// This is the current # of players on the local host
	virtual bool			SetLocalPlayerIsResolvable( char const *pchContext , int nLine , bool bResolvable ) = 0;
	virtual bool			IsLocalPlayerResolvable() = 0;
	virtual int				GetSplitScreenPlayer( int nSlot ) = 0;
	virtual bool			IsSplitScreenActive() = 0;
	virtual bool			IsValidSplitScreenSlot( int nSlot ) = 0;
	virtual int				FirstValidSplitScreenSlot() = 0; // -1 == invalid
	virtual int				NextValidSplitScreenSlot( int nPreviousSlot ) = 0; // -1 == invalid
																			   //Finds or Creates a shared memory space, the returned pointer will automatically be AddRef()ed
	virtual ISPSharedMemory *GetSinglePlayerSharedMemorySpace( const char *szName , int ent_num = MAX_EDICTS ) = 0;
	// Computes an ambient cube that includes ALL dynamic lights
	virtual void ComputeLightingCube( const Vector& pt , bool bClamp , Vector *pBoxColors ) = 0;
	//All callbacks have to be registered before demo recording begins. TODO: Macro'ize a way to do it at startup
	virtual void RegisterDemoCustomDataCallback( string_t szCallbackSaveID , pfnDemoCustomDataCallback pCallback ) = 0;
	virtual void RecordDemoCustomData( pfnDemoCustomDataCallback pCallback , const void *pData , size_t iDataLength ) = 0;
	// global sound pitch scaling
	virtual void SetPitchScale( float flPitchScale ) = 0;
	virtual float GetPitchScale( void ) = 0;
	// Load/unload the SFM - used by Replay
	virtual bool		LoadFilmmaker() = 0;
	virtual void		UnloadFilmmaker() = 0;
	// leaf flag management. Allows fast leaf enumeration of leaves that have a flag set
	// set a bit in a leaf flag
	virtual void SetLeafFlag( int nLeafIndex , int nFlagBits ) = 0;
	// you must call this once done modifying flags. Not super fast.
	virtual void RecalculateBSPLeafFlags( void ) = 0;
	virtual bool DSPGetCurrentDASRoomNew( void ) = 0;
	virtual bool DSPGetCurrentDASRoomChanged( void ) = 0;
	virtual bool DSPGetCurrentDASRoomSkyAbove( void ) = 0;
	virtual float DSPGetCurrentDASRoomSkyPercent( void ) = 0;
	virtual void SetMixGroupOfCurrentMixer( const char *szgroupname , const char *szparam , float val , int setMixerType ) = 0;
	virtual int GetMixLayerIndex( const char *szmixlayername ) = 0;
	virtual void SetMixLayerLevel( int index , float level ) = 0;
	virtual int	 GetMixGroupIndex( char  const* groupname ) = 0;
	virtual void SetMixLayerTriggerFactor( int i1 , int i2 , float fl ) = 0;
	virtual void SetMixLayerTriggerFactor( char  const* char1 , char  const* char2 , float fl ) = 0;
	virtual bool IsCreatingReslist() = 0;
	virtual bool IsCreatingXboxReslist() = 0;
	virtual void SetTimescale( float flTimescale ) = 0;
	// Methods to set/get a gamestats data container so client & server running in same process can send combined data
	virtual void SetGamestatsData( CGamestatsData *pGamestatsData ) = 0;
	virtual CGamestatsData *GetGamestatsData() = 0;
	virtual void GetMouseDelta( int &dx , int &dy , bool b ) = 0; // unknown
																  // Given the string pBinding which may be bound to a key, 
																  //  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
																  // Increment start count to iterate through multiple keys bound to the same binding
																  // iAllowJoystick defaults to -1 witch returns joystick and non-joystick binds, 0 returns only non-joystick, 1 returns only joystick
	virtual	const char *Key_LookupBindingEx( const char *pBinding , int iUserId = -1 , int iStartCount = 0 , int iAllowJoystick = -1 ) = 0;
	virtual int			Key_CodeForBinding( char  const* , int , int , int ) = 0;
	// Updates dynamic light state. Necessary for light cache to work properly for d- and elights
	virtual void UpdateDAndELights( void ) = 0;
	// Methods to get bug count for internal dev work stat tracking.
	// Will get the bug count and clear it every map transition
	virtual int			GetBugSubmissionCount() const = 0;
	virtual void		ClearBugSubmissionCount() = 0;
	// Is there water anywhere in the level?
	virtual bool	DoesLevelContainWater() const = 0;
	// How much time was spent in server simulation?
	virtual float	GetServerSimulationFrameTime() const = 0;
	virtual void SolidMoved( class IClientEntity *pSolidEnt , class ICollideable *pSolidCollide , const Vector* pPrevAbsOrigin , bool accurateBboxTriggerChecks ) = 0;
	virtual void TriggerMoved( class IClientEntity *pTriggerEnt , bool accurateBboxTriggerChecks ) = 0;
	// Using area bits, check whether the area of the specified point flows into the other areas
	virtual void ComputeLeavesConnected( const Vector &vecOrigin , int nCount , const int *pLeafIndices , bool *pIsConnected ) = 0;
	// Is the engine in Commentary mode?
	virtual bool IsInCommentaryMode( void ) = 0;
	virtual void SetBlurFade( float amount ) = 0;
	virtual bool IsTransitioningToLoad() = 0;
	virtual void SearchPathsChangedAfterInstall() = 0;
	virtual void ConfigureSystemLevel( int nCPULevel , int nGPULevel ) = 0;
	virtual void SetConnectionPassword( char const *pchCurrentPW ) = 0;
	virtual CSteamAPIContext* GetSteamAPIContext() = 0;
	virtual void SubmitStatRecord( char const *szMapName , uint uiBlobVersion , uint uiBlobSize , const void *pvBlob ) = 0;
	// Sends a key values server command, not allowed from scripts execution
	// Params:
	//	pKeyValues	- key values to be serialized and sent to server
	//				  the pointer is deleted inside the function: pKeyValues->deleteThis()
	virtual void ServerCmdKeyValues( KeyValues *pKeyValues ) = 0; // 203
																  // Tells the engine what and where to paint
	virtual void SpherePaintSurface( const model_t* model , const Vector& location , unsigned char chr , float fl1 , float fl2 ) = 0;
	virtual bool HasPaintmap( void ) = 0;
	// Enable paint in the engine for project Paint
	virtual void EnablePaintmapRender() = 0;
	//virtual void TracePaintSurface( const model_t *model, const Vector& position, float radius, CUtlVector<Color>& surfColors ) = 0;
	virtual void SphereTracePaintSurface( const model_t* model , const Vector& position , const Vector &vec2 , float radius , CUtlVector<unsigned char , CUtlMemory<unsigned char , int>> & utilVecShit ) = 0;
	virtual void RemoveAllPaint() = 0;
	virtual void PaintAllSurfaces( unsigned char uchr ) = 0;
	virtual void RemovePaint( const model_t* model ) = 0;

	virtual bool IsActiveApp() = 0;

	// is this client running inside the same process as an active server?
	virtual bool IsClientLocalToActiveServer() = 0;

	// Callback for LevelInit to tick the progress bar during time consuming operations
	virtual void TickProgressBar() = 0;

	// Returns the requested input context
	virtual InputContextHandle_t GetInputContext( EngineInputContextId_t id ) = 0;
	virtual void				GetStartupImage( char* filename , int size ) = 0;
	virtual bool				IsUsingLocalNetworkBackdoor( void ) = 0;
	virtual void				SaveGame( const char* , bool , char* , int , char* , int ) = 0;
	virtual void				GetGenericMemoryStats(/* GenericMemoryStat_t */ void ** ) = 0;
	virtual bool				GameHasShutdownAndFlushedMemory( void ) = 0;
	virtual int					GetLastAcknowledgedCommand( void ) = 0;
	virtual void				FinishContainerWrites( int i ) = 0;
	virtual void				FinishAsyncSave( void ) = 0;
	virtual int					GetServerTick( void ) = 0;
	virtual const char*			GetModDirectory( void ) = 0;
	virtual bool				AudioLanguageChanged( void ) = 0;
	virtual bool				IsAutoSaveInProgress( void ) = 0;
	virtual void				StartLoadingScreenForCommand( const char* command ) = 0;
	virtual void				StartLoadingScreenForKeyValues( KeyValues* values ) = 0;
	virtual void				SOSSetOpvarFloat( const char* , float ) = 0;
	virtual void				SOSGetOpvarFloat( const char* , float & ) = 0;
	virtual bool				IsSubscribedMap( const char* , bool ) = 0;
	virtual bool				IsFeaturedMap( const char* , bool ) = 0;
	virtual void				GetDemoPlaybackParameters( void ) = 0;
	virtual int					GetClientVersion( void ) = 0;
	virtual bool				IsDemoSkipping( void ) = 0;
	virtual void				SetDemoImportantEventData( const KeyValues* values ) = 0;
	virtual void				ClearEvents( void ) = 0;
	virtual int					GetSafeZoneXMin( void ) = 0;
	virtual bool				IsVoiceRecording( void ) = 0;
	virtual void				ForceVoiceRecordOn( void ) = 0;
	virtual bool				IsReplay( void ) = 0;
};

#pragma endregion

#pragma region IBaseClientDLL

class CGlobalVarsBase;
class IClientNetworkable;

typedef IClientNetworkable*	( *CreateClientClassFn )( int entnum , int serialNum );
typedef IClientNetworkable*	( *CreateEventFn )( );

class ClientClass
{
public:
	const char* GetName() { return m_pNetworkName; }

public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;	// Only called for event objects.
	char					*m_pNetworkName;
	RecvTable				*m_pRecvTable;
	ClientClass				*m_pNext;
	int						m_ClassID;	// Managed by the engine.
};

class CViewSetup;
class CEngineSprite;

#define FFADE_IN			0x0001		// Just here so we don't pass 0 into the function
#define FFADE_OUT			0x0002		// Fade out (not in)
#define FFADE_MODULATE		0x0004		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0008		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE			0x0010		// Purges all other fades, replacing them with this one

#define SCREENFADE_FRACBITS		9		// which leaves 16-this for the integer part
// This structure is sent over the net to describe a screen fade event
struct ScreenFade_t
{
	unsigned short 	duration;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration
	unsigned short 	holdTime;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration until reset (fade & hold)
	short			fadeFlags;		// flags
	byte			r , g , b , a;		// fade to color ( max alpha )
};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1 ,			// (haven't run any frames yet)
	FRAME_START ,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START ,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START ,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END ,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END ,

	// We're about to start rendering the scene
	FRAME_RENDER_START ,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

struct bf_write;
struct bf_read;

class IBaseClientDLL
{
public:
	virtual int				Connect( CreateInterfaceFn appSystemFactory , CGlobalVarsBase *pGlobals ) = 0;
	virtual int				Disconnect( void ) = 0;
	virtual int				Init( CreateInterfaceFn appSystemFactory , CGlobalVarsBase *pGlobals ) = 0;
	virtual void			PostInit() = 0;
	virtual void			Shutdown( void ) = 0;
	virtual void			LevelInitPreEntity( char const* pMapName ) = 0;
	virtual void			LevelInitPostEntity() = 0;
	virtual void			LevelShutdown( void ) = 0;
	virtual ClientClass		*GetAllClasses( void ) = 0;
	virtual int				HudVidInit( void ) = 0;
	virtual void			HudProcessInput( bool bActive ) = 0;
	virtual void			HudUpdate( bool bActive ) = 0;
	virtual void			HudReset( void ) = 0;
	virtual void			HudText( const char * message ) = 0;
	virtual void			ShouldDrawDropdownConsole( void ) = 0;
	virtual void			IN_ActivateMouse( void ) = 0;
	virtual void			IN_DeactivateMouse( void ) = 0;
	virtual void			IN_Accumulate( void ) = 0;
	virtual void			IN_ClearStates( void ) = 0;
	virtual bool			IN_IsKeyDown( const char *name , bool& isdown ) = 0;
	virtual int				IN_KeyEvent( int eventcode , ButtonCode_t keynum , const char *pszCurrentBinding ) = 0;
	virtual void			CreateMove( int sequence_number , float input_sample_frametime , bool active ) = 0;
	virtual void			ExtraMouseSample( float frametime , bool active ) = 0;
	virtual bool			WriteUsercmdDeltaToBuffer( int nSlot , bf_write *buf , int from , int to , bool isnewcommand ) = 0;
	virtual void			EncodeUserCmdToBuffer( int nSlot , bf_write& buf , int slot ) = 0;
	virtual void			DecodeUserCmdFromBuffer( int nSlot , bf_read& buf , int slot ) = 0;
	virtual void			View_Render( vrect_t *rect ) = 0;
	virtual void			RenderView( const CViewSetup &view , int nClearFlags , int whatToDraw ) = 0;
	virtual void			View_Fade( ScreenFade_t *pSF ) = 0;
	virtual void			SetCrosshairAngle( const QAngle& angle ) = 0;
	virtual void			InitSprite( CEngineSprite *pSprite , const char *loadname ) = 0;
	virtual void			ShutdownSprite( CEngineSprite *pSprite ) = 0;
	virtual int				GetSpriteSize( void ) const = 0;
	virtual void			VoiceStatus( int entindex , int iSsSlot , qboolean bTalking ) = 0;
	virtual int				PlayerAudible( int audible ) = 0;
	virtual void			InstallStringTableCallback( char const *tableName ) = 0;
	virtual void			FrameStageNotify( ClientFrameStage_t curStage ) = 0;
	virtual bool			DispatchUserMessage( int msg_type , int unk1 , int unk2 , bf_read &msg_data ) = 0;
};

#pragma endregion

#pragma region IClientEntity

class CBaseHandle;
class ICollideable;
class IClientUnknown;
class IClientRenderable;
class IClientNetworkable;
class IClientThinkable;
class IClientEntity;
class IClientEntityList;
class CBaseViewModel;

class IClientUnknown
{
public:
	virtual ICollideable*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual IClientEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};

struct model_t;

typedef unsigned short ClientShadowHandle_t;

enum
{
	CLIENTSHADOW_INVALID_HANDLE = (ClientShadowHandle_t)~0
};

typedef unsigned short ClientRenderHandle_t;

enum
{
	INVALID_CLIENT_RENDER_HANDLE = (ClientRenderHandle_t)0xffff ,
};

struct RenderableInstance_t
{
	uint8 m_nAlpha;
};

class IClientRenderable
{
public:
	virtual IClientUnknown*			GetIClientUnknown() = 0;
	virtual Vector const&			GetRenderOrigin() = 0;
	virtual QAngle const&			GetRenderAngles() = 0;
	virtual bool					ShouldDraw() = 0;
	virtual bool					IsTransparent() = 0;
	virtual void					Unused();
	virtual ClientShadowHandle_t	GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&	RenderHandle() = 0;
	virtual const model_t*			GetModel() const = 0;
	virtual int						DrawModel( int flags , const RenderableInstance_t &instance ) = 0;
	virtual int						GetBody() = 0;
	virtual void					GetColorModulation( float* color ) = 0;
	virtual bool					LODTest() = 0;
	virtual bool					SetupBones( matrix3x4_t *pBoneToWorldOut , int nMaxBones , int boneMask , float currentTime ) = 0;
};

enum ShouldTransmitState_t
{
	SHOULDTRANSMIT_START = 0 ,
	SHOULDTRANSMIT_END
};

enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0 ,
	DATA_UPDATE_DATATABLE_CHANGED ,
};

class IClientNetworkable
{
public:
	virtual IClientUnknown*	GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass*	GetClientClass() = 0;
	virtual void			NotifyShouldTransmit( ShouldTransmitState_t state ) = 0;
	virtual void			OnPreDataChanged( DataUpdateType_t updateType ) = 0;
	virtual void			OnDataChanged( DataUpdateType_t updateType ) = 0;
	virtual void			PreDataUpdate( DataUpdateType_t updateType ) = 0;
	virtual void			PostDataUpdate( DataUpdateType_t updateType ) = 0;
	virtual void			unknown() = 0;
	virtual bool			IsDormant() = 0;
	virtual int				Index() const = 0;
	virtual void			ReceiveMessage( int classID , bf_read &msg ) = 0;
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities() = 0;
};

class CClientThinkHandlePtr;
typedef CClientThinkHandlePtr* ClientThinkHandle_t;

class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual ClientThinkHandle_t	GetThinkHandle() = 0;
	virtual void				SetThinkHandle( ClientThinkHandle_t* hThink ) = 0;
	virtual void				Release() = 0;
};

class IClientEntityList
{
public:
	virtual IClientNetworkable*	GetClientNetworkable( int entnum ) = 0;
	virtual IClientNetworkable*	GetClientNetworkableFromHandle( CBaseHandle hEnt ) = 0;
	virtual IClientUnknown*		GetClientUnknownFromHandle( CBaseHandle hEnt ) = 0;
	virtual IClientEntity*		GetClientEntity( int entnum ) = 0;
	virtual IClientEntity*		GetClientEntityFromHandle( DWORD hEnt ) = 0;
	virtual int					NumberOfEntities( bool bIncludeNonNetworkable ) = 0;
	virtual int					GetHighestEntityIndex( void ) = 0;
	virtual void				SetMaxEntities( int maxents ) = 0;
	virtual int					GetMaxEntities() = 0;
};

class __declspec ( novtable ) IClientEntity : public IClientUnknown , public IClientRenderable , public IClientNetworkable , public IClientThinkable
{
public:

	const Vector& GetAbsOrigin()
	{
		typedef const Vector&( __thiscall* oGetAbsOrigin )( PVOID );
		return call_func< oGetAbsOrigin >( this , 10 )( this );
	}

	const QAngle& GetAbsAngles()
	{
		typedef const QAngle&( __thiscall* oGetAbsAngles )( PVOID );
		return call_func< oGetAbsAngles >( this , 11 )( this );
	}

	char* GetWeaponName( DWORD pWeapon )
	{
		typedef char*( __thiscall* GetWeaponNameFn )( PVOID );
		GetWeaponNameFn WeaponName = (GetWeaponNameFn)( ( *( PDWORD* )this )[378] );
		return WeaponName( (PVOID)pWeapon );
	}

	Vector GetOrigin()
	{
		return *reinterpret_cast<Vector*>( ( DWORD )this + (DWORD)m_vecOrigin );
	}

	int GetLocalFovStart()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_iFOVStart );
	}

	int GetEffects()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_fEffects );
	}

	int GetTeamNum()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_iTeamNum );
	}

	QAngle GetEyeAngles()
	{
		return *reinterpret_cast<QAngle*>( ( DWORD )this + (DWORD)m_angEyeAngles );
	}

	int GetHealth()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_iHealth );
	}

	int GetArmorValue()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_ArmorValue );
	}

	int GetShotsFired()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_iShotsFired );
	}

	BYTE GetMoveType()
	{
		return *reinterpret_cast<BYTE*>( ( DWORD )this + (DWORD)m_MoveType );
	}

	BYTE GetlifeState()
	{
		return *reinterpret_cast<BYTE*>( ( DWORD )this + (DWORD)m_lifeState );
	}

	int GetFlags()
	{
		return *reinterpret_cast<int*>( ( DWORD )this + (DWORD)m_fFlags );
	}

	Vector GetViewOffset()
	{
		return *reinterpret_cast<Vector*>( ( DWORD )this + (DWORD)m_vecViewOffset );
	}

	Vector GetAimPunch()
	{
		return *reinterpret_cast<Vector*>( ( DWORD )this + (DWORD)m_aimPunchAngle );
	}

	DWORD GetAcitveWeapon()
	{
		return *reinterpret_cast<DWORD*>( ( DWORD )this + (DWORD)m_hActiveWeapon );
	}

	int GetIndex() {
		return *(int*)( ( DWORD )this + 0x64 );
	}

	int GetGlowIndex() {
		return *(int*)( ( DWORD )this + m_iGlowIndex );
	}

	UINT* GetWeapons() {
		// DT_BasePlayer -> m_hMyWeapons
		return (UINT*)( ( DWORD )this + m_hMyWeapons );
	}

	CBaseViewModel* GetViewModel()
	{
		// DT_BasePlayer -> m_hViewModel
		return (CBaseViewModel*)g_pClientEntList->GetClientEntityFromHandle( *(PDWORD)( (DWORD)this + m_hViewModel ) );
	}
};

#pragma endregion

#pragma region ISurface

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0 ,
	FONT_DRAW_NONADDITIVE ,
	FONT_DRAW_ADDITIVE ,
	FONT_DRAW_TYPE_COUNT = 2 ,
};

enum EFontFlags
{
	FONTFLAG_NONE ,
	FONTFLAG_ITALIC = 0x001 ,
	FONTFLAG_UNDERLINE = 0x002 ,
	FONTFLAG_STRIKEOUT = 0x004 ,
	FONTFLAG_SYMBOL = 0x008 ,
	FONTFLAG_ANTIALIAS = 0x010 ,
	FONTFLAG_GAUSSIANBLUR = 0x020 ,
	FONTFLAG_ROTARY = 0x040 ,
	FONTFLAG_DROPSHADOW = 0x080 ,
	FONTFLAG_ADDITIVE = 0x100 ,
	FONTFLAG_OUTLINE = 0x200 ,
	FONTFLAG_CUSTOM = 0x400 ,
	FONTFLAG_BITMAP = 0x800 ,
};

class ISurface
{
public:
	void DrawSetColor( Color col )
	{
		typedef void( __thiscall* oDrawSetColor )( PVOID , Color );
		call_func< oDrawSetColor >( this , HookIndexSDK::ISurface::DrawSetColor1 )( this , col );
	}
	void DrawSetColor( int r , int g , int b , int a )
	{
		typedef void( __thiscall* oDrawSetColor )( PVOID , int , int , int , int );
		call_func< oDrawSetColor >( this , HookIndexSDK::ISurface::DrawSetColor2 )( this , r , g , b , a );
	}
	void DrawFilledRect( int x0 , int y0 , int x1 , int y1 )
	{
		typedef void( __thiscall* oDrawFilledRect )( PVOID , int , int , int , int );
		call_func< oDrawFilledRect >( this , HookIndexSDK::ISurface::DrawFilledRect )( this , x0 , y0 , x1 , y1 );
	}
	void DrawOutlinedRect( int x0 , int y0 , int x1 , int y1 )
	{
		typedef void( __thiscall* oDrawOutlinedRect )( PVOID , int , int , int , int );
		call_func< oDrawOutlinedRect >( this , HookIndexSDK::ISurface::DrawOutlinedRect )( this , x0 , y0 , x1 , y1 );
	}
	void DrawLine( int x0 , int y0 , int x1 , int y1 )
	{
		typedef void( __thiscall* oDrawLine )( PVOID , int , int , int , int );
		call_func< oDrawLine >( this , HookIndexSDK::ISurface::DrawLine )( this , x0 , y0 , x1 , y1 );
	}
	void DrawSetTextFont( unsigned long hFont )
	{
		typedef void( __thiscall* oDrawSetTextFont )( PVOID , unsigned long );
		call_func< oDrawSetTextFont >( this , HookIndexSDK::ISurface::DrawSetTextFont )( this , hFont );
	}
	void DrawSetTextColor( Color col )
	{
		typedef void( __thiscall* oDrawSetTextColor )( PVOID , Color );
		call_func< oDrawSetTextColor >( this , HookIndexSDK::ISurface::DrawSetTextColor )( this , col );
	}
	void DrawSetTextPos( int x , int y )
	{
		typedef void( __thiscall* oDrawSetTextPos )( PVOID , int , int );
		call_func< oDrawSetTextPos >( this , HookIndexSDK::ISurface::DrawSetTextPos )( this , x , y );
	}
	void DrawPrintText( wchar_t *text , int textLen , FontDrawType_t drawType = FONT_DRAW_DEFAULT )
	{
		typedef void( __thiscall* oDrawPrintText )( PVOID , wchar_t* , int , FontDrawType_t );
		call_func< oDrawPrintText >( this , HookIndexSDK::ISurface::DrawPrintText )( this , text , textLen , drawType );
	}
	DWORD FontCreate()
	{
		typedef DWORD( __thiscall* oCreateFont )( PVOID );
		return call_func< oCreateFont >( this , HookIndexSDK::ISurface::FontCreate )( this );
	}
	void SetFontGlyphSet( unsigned long font , const char *windowsFontName , int tall , int weight , int blur , int scanlines , int flags , int nRangeMin = 0 , int nRangeMax = 0 )
	{
		typedef void( __thiscall* oSetFontGlyphSet )( PVOID , unsigned long , const char * , int , int , int , int , int , int , int );
		call_func< oSetFontGlyphSet >( this , HookIndexSDK::ISurface::SetFontGlyphSet )( this , font , windowsFontName , tall , weight , blur , scanlines , flags , nRangeMin , nRangeMax );
	}
	void GetTextSize( unsigned long font , const wchar_t *text , int &wide , int &tall )
	{
		typedef void( __thiscall* oGetTextSize )( PVOID , unsigned long , const wchar_t* , int& , int& );
		call_func< oGetTextSize >( this , HookIndexSDK::ISurface::GetTextSize )( this , font , text , wide , tall );
	}
};

#pragma endregion

#pragma region IPanel

class IPanel
{
public:
	bool IsVisible( unsigned int vguiPanel )
	{
		typedef bool( __thiscall* oIsVisible )( PVOID , unsigned int );
		return call_func< oIsVisible >( this , HookIndexSDK::IPanel::IsVisible )( this , vguiPanel );
	}
	const char* GetName( unsigned int vguiPanel )
	{
		typedef const char*( __thiscall* oGetName )( PVOID , unsigned int );
		return call_func< oGetName >( this , HookIndexSDK::IPanel::GetName )( this , vguiPanel );
	}
	void PaintTraverse( unsigned int vguiPanel , bool forceRepaint , bool allowForce = true )
	{
		typedef void( __thiscall* oPaintTraverse )( PVOID , unsigned int , bool , bool );
		return call_func< oPaintTraverse >( this , HookIndexSDK::IPanel::PaintTraverse )( this , vguiPanel , forceRepaint , allowForce );
	}
};

#pragma endregion

#pragma region CGameTrace

#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)

#define PlayerVisibleMask (CONTENTS_HITBOX | CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN | CONTENTS_CURRENT_270 | CONTENTS_CURRENT_180 | CONTENTS_MOVEABLE | CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_GRATE)

struct cplane_t
{
	Vector	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];
};

struct csurface_t
{
	const char	*name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

class CBaseTrace
{
public:
	// Displacement flags tests.
	bool IsDispSurface( void ) { return ( ( dispFlags & DISPSURF_FLAG_SURFACE ) != 0 ); }
	bool IsDispSurfaceWalkable( void ) { return ( ( dispFlags & DISPSURF_FLAG_WALKABLE ) != 0 ); }
	bool IsDispSurfaceBuildable( void ) { return ( ( dispFlags & DISPSURF_FLAG_BUILDABLE ) != 0 ); }
	bool IsDispSurfaceProp1( void ) { return ( ( dispFlags & DISPSURF_FLAG_SURFPROP1 ) != 0 ); }
	bool IsDispSurfaceProp2( void ) { return ( ( dispFlags & DISPSURF_FLAG_SURFPROP2 ) != 0 ); }
public:
	// these members are aligned!!
	Vector			startpos;				// start position
	Vector			endpos;					// final position
	cplane_t		plane;					// surface normal at impact
	float			fraction;				// time completed, 1.0 = didn't hit anything
	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data
	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area
	CBaseTrace() { }
};

class CGameTrace : public CBaseTrace
{
public:

	bool IsVisible() const
	{
		return fraction > 0.97f;
	}

public:
	float			fractionleftsolid;	// time we left a solid, only valid if we started in solid
	csurface_t		surface;			// surface hit (impact surface)
	int				hitgroup;			// 0 == generic, non-zero is specific body part
	short			physicsbone;		// physics bone hit by trace in studio
	unsigned short	worldSurfaceIndex;	// Index of the msurface2_t, if applicable
	IClientEntity	*m_pEnt;
	int				hitbox;				// box hit by trace in studio
	CGameTrace() { }
};

typedef CGameTrace trace_t;

#pragma endregion

#pragma region CGlobalVarsBase

class CGlobalVarsBase
{
public:
	float    realtime;
	int    framecount;
	float    absolute_frametime;
	float    absolute_framestarttimestddev;
	float    curtime;
	float    frameTime;
	int    maxClients;
	int    tickcount;
	float    interval_per_tick;
	float    interpolation_amount;
	int    simThicksThisFrame;
	int    network_protocol;
};

#pragma endregion

#pragma region IPlayerInfoManager

class IPlayerInfo;
struct edict_t;

class IPlayerInfoManager
{
public:
	virtual IPlayerInfo* GetPlayerInfo( edict_t *pEdict ) = 0;
	virtual CGlobalVarsBase* GetGlobalVars() = 0;
};

#pragma endregion

#pragma region IClientMode

class IClientMode
{
public:
	bool CL_CreateMove( float flInputSampleTime , CUserCmd* cmd )
	{
		typedef bool( __thiscall* oCreateMove )( PVOID , float , CUserCmd* );
		return call_func< oCreateMove >( this , HookIndexSDK::IClientMode::CL_CreateMove )( this , flInputSampleTime , cmd );
	}
};

#pragma endregion

#pragma region IEngineSound

class IRecipientFilter
{
public:
	virtual			~IRecipientFilter() {}

	virtual bool	IsReliable( void ) const = 0;
	virtual bool	IsInitMessage( void ) const = 0;

	virtual int		GetRecipientCount( void ) const = 0;
	virtual int		GetRecipientIndex( int slot ) const = 0;
};

//-----------------------------------------------------------------------------
// channels
//-----------------------------------------------------------------------------
enum
{
	CHAN_REPLACE = -1 ,
	CHAN_AUTO = 0 ,
	CHAN_WEAPON = 1 ,
	CHAN_VOICE = 2 ,
	CHAN_ITEM = 3 ,
	CHAN_BODY = 4 ,
	CHAN_STREAM = 5 ,		// allocate stream channel from the static or dynamic area
	CHAN_STATIC = 6 ,		// allocate channel from the static area 
	CHAN_VOICE2 = 7 ,
	CHAN_VOICE_BASE = 8 ,		// allocate channel for network voice data
	CHAN_USER_BASE = ( CHAN_VOICE_BASE + 128 )		// Anything >= this number is allocated to game code.
};

//-----------------------------------------------------------------------------
// common volume values
//-----------------------------------------------------------------------------
#define VOL_NORM		1.0f


//-----------------------------------------------------------------------------
// common attenuation values
//-----------------------------------------------------------------------------
#define ATTN_NONE		0.0f
#define ATTN_NORM		0.8f
#define ATTN_IDLE		2.0f
#define ATTN_STATIC		1.25f 
#define ATTN_RICOCHET	1.5f

// HL2 world is 8x bigger now! We want to hear gunfire from farther.
// Don't change this without consulting Kelly or Wedge (sjb).
#define ATTN_GUNFIRE	0.27f

enum soundlevel_t
{
	SNDLVL_NONE = 0 ,

	SNDLVL_20dB = 20 ,			// rustling leaves
	SNDLVL_25dB = 25 ,			// whispering
	SNDLVL_30dB = 30 ,			// library
	SNDLVL_35dB = 35 ,
	SNDLVL_40dB = 40 ,
	SNDLVL_45dB = 45 ,			// refrigerator

	SNDLVL_50dB = 50 ,	// 3.9	// average home
	SNDLVL_55dB = 55 ,	// 3.0

	SNDLVL_IDLE = 60 ,	// 2.0	
	SNDLVL_60dB = 60 ,	// 2.0	// normal conversation, clothes dryer

	SNDLVL_65dB = 65 ,	// 1.5	// washing machine, dishwasher
	SNDLVL_STATIC = 66 ,	// 1.25

	SNDLVL_70dB = 70 ,	// 1.0	// car, vacuum cleaner, mixer, electric sewing machine

	SNDLVL_NORM = 75 ,
	SNDLVL_75dB = 75 ,	// 0.8	// busy traffic

	SNDLVL_80dB = 80 ,	// 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
	SNDLVL_TALKING = 80 ,	// 0.7
	SNDLVL_85dB = 85 ,	// 0.6	// average factory, electric shaver
	SNDLVL_90dB = 90 ,	// 0.5	// screaming child, passing motorcycle, convertible ride on frw
	SNDLVL_95dB = 95 ,
	SNDLVL_100dB = 100 ,	// 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
	SNDLVL_105dB = 105 ,			// helicopter, power mower
	SNDLVL_110dB = 110 ,			// snowmobile drvrs seat, inboard motorboat, sandblasting
	SNDLVL_120dB = 120 ,			// auto horn, propeller aircraft
	SNDLVL_130dB = 130 ,			// air raid siren

	SNDLVL_GUNFIRE = 140 ,	// 0.27	// THRESHOLD OF PAIN, gunshot, jet engine
	SNDLVL_140dB = 140 ,	// 0.2

	SNDLVL_150dB = 150 ,	// 0.2

	SNDLVL_180dB = 180 ,			// rocket launching

									// NOTE: Valid soundlevel_t values are 0-255.
									//       256-511 are reserved for sounds using goldsrc compatibility attenuation.
};

#define MAX_SNDLVL_BITS		9	// Used to encode 0-255 for regular soundlevel_t's and 256-511 for goldsrc-compatible ones.
#define MIN_SNDLVL_VALUE	0
#define MAX_SNDLVL_VALUE	((1<<MAX_SNDLVL_BITS)-1)


#define ATTN_TO_SNDLVL( a ) (soundlevel_t)(int)((a) ? (50 + 20 / ((float)a)) : 0 )
#define SNDLVL_TO_ATTN( a ) ((a > 50) ? (20.0f / (float)(a - 50)) : 4.0 )

// This is a limit due to network encoding.
// It encodes attenuation * 64 in 8 bits, so the maximum is (255 / 64)
#define MAX_ATTENUATION		3.98f

//-----------------------------------------------------------------------------
// Flags to be or-ed together for the iFlags field
//-----------------------------------------------------------------------------
enum SoundFlags_t
{
	SND_NOFLAGS = 0 ,			// to keep the compiler happy
	SND_CHANGE_VOL = ( 1 << 0 ) ,		// change sound vol
	SND_CHANGE_PITCH = ( 1 << 1 ) ,		// change sound pitch
	SND_STOP = ( 1 << 2 ) ,		// stop the sound
	SND_SPAWNING = ( 1 << 3 ) ,		// we're spawning, used in some cases for ambients
									// not sent over net, only a param between dll and server.
									SND_DELAY = ( 1 << 4 ) ,		// sound has an initial delay
									SND_STOP_LOOPING = ( 1 << 5 ) ,		// stop all looping sounds on the entity.
									SND_SPEAKER = ( 1 << 6 ) ,		// being played again by a microphone through a speaker

									SND_SHOULDPAUSE = ( 1 << 7 ) ,		// this sound should be paused if the game is paused
									SND_IGNORE_PHONEMES = ( 1 << 8 ) ,
									SND_IGNORE_NAME = ( 1 << 9 ) ,		// used to change all sounds emitted by an entity, regardless of scriptname

									SND_DO_NOT_OVERWRITE_EXISTING_ON_CHANNEL = ( 1 << 10 ) ,
};

#define SND_FLAG_BITS_ENCODE 11

#define MAX_SOUND_INDEX_BITS	14
#define	MAX_SOUNDS				(1<<MAX_SOUND_INDEX_BITS)

#define MAX_SOUND_DELAY_MSEC_ENCODE_BITS	(13)

// Subtract one to leave room for the sign bit
#define MAX_SOUND_DELAY_MSEC				(1<<(MAX_SOUND_DELAY_MSEC_ENCODE_BITS-1))    // 4096 msec or about 4 seconds

//-----------------------------------------------------------------------------
// common pitch values
//-----------------------------------------------------------------------------
#define	PITCH_NORM		100			// non-pitch shifted
#define PITCH_LOW		95			// other values are possible - 0-255, where 255 is very high
#define PITCH_HIGH		120

#define DEFAULT_SOUND_PACKET_VOLUME 1.0f
#define DEFAULT_SOUND_PACKET_PITCH	100
#define DEFAULT_SOUND_PACKET_DELAY	0.0f

// Handy defines for EmitSound
#define SOUND_FROM_UI_PANEL			-2		// Sound being played inside a UI panel on the client
#define SOUND_FROM_LOCAL_PLAYER		-1
#define SOUND_FROM_WORLD			0

// These are used to feed a soundlevel to the sound system and have it use
// goldsrc-type attenuation. We should use this as little as possible and 
// phase it out as soon as possible.

// Take a regular sndlevel and convert it to compatibility mode.
#define SNDLEVEL_TO_COMPATIBILITY_MODE( x )		((soundlevel_t)(int)( (x) + 256 ))

// Take a compatibility-mode sndlevel and get the REAL sndlevel out of it.
#define SNDLEVEL_FROM_COMPATIBILITY_MODE( x )	((soundlevel_t)(int)( (x) - 256 ))

// Tells if the given sndlevel is marked as compatibility mode.
#define SNDLEVEL_IS_COMPATIBILITY_MODE( x )		( (x) >= 256 )

//-----------------------------------------------------------------------------
// Client-server neutral effects interface
//-----------------------------------------------------------------------------

typedef void* FileNameHandle_t;

struct SndInfo_t
{
	// Sound Guid
	int			m_nGuid;
	FileNameHandle_t m_filenameHandle;		// filesystem filename handle - call IFilesystem to conver this to a string
	int			m_nSoundSource;
	int			m_nChannel;
	// If a sound is being played through a speaker entity (e.g., on a monitor,), this is the
	//  entity upon which to show the lips moving, if the sound has sentence data
	int			m_nSpeakerEntity;
	float		m_flVolume;
	float		m_flLastSpatializedVolume;
	// Radius of this sound effect (spatialization is different within the radius)
	float		m_flRadius;
	int			m_nPitch;
	Vector		*m_pOrigin;
	Vector		*m_pDirection;

	// if true, assume sound source can move and update according to entity
	bool		m_bUpdatePositions;
	// true if playing linked sentence
	bool		m_bIsSentence;
	// if true, bypass all dsp processing for this sound (ie: music)	
	bool		m_bDryMix;
	// true if sound is playing through in-game speaker entity.
	bool		m_bSpeaker;
	// for snd_show, networked sounds get colored differently than local sounds
	bool		m_bFromServer;
};

//-----------------------------------------------------------------------------
// Hearing info
//-----------------------------------------------------------------------------
struct AudioState_t
{
	Vector m_Origin;
	QAngle m_Angles;
	bool m_bIsUnderwater;
};

class IEngineSound
{
public:
	// Precache a particular sample
	virtual bool PrecacheSound( const char *pSample , bool bPreload = false , bool bIsUISound = false ) = 0;
	virtual bool IsSoundPrecached( const char *pSample ) = 0;
	virtual void PrefetchSound( const char *pSample ) = 0;
	virtual bool IsLoopingSound( const char *pSample ) = 0;

	// Just loads the file header and checks for duration (not hooked up for .mp3's yet)
	// Is accessible to server and client though
	virtual float GetSoundDuration( const char *pSample ) = 0;

	// Pitch of 100 is no pitch shift.  Pitch > 100 up to 255 is a higher pitch, pitch < 100
	// down to 1 is a lower pitch.   150 to 70 is the realistic range.
	// EmitSound with pitch != 100 should be used sparingly, as it's not quite as
	// fast (the pitchshift mixer is not native coded).

	// NOTE: setting iEntIndex to -1 will cause the sound to be emitted from the local
	// player (client-side only)
	virtual int EmitSound1( IRecipientFilter& filter , int iEntIndex , int iChannel , const char *pSoundEntry , unsigned int nSoundEntryHash , const char *pSample ,
							float flVolume , soundlevel_t iSoundlevel , int nSeed , int iFlags = 0 , int iPitch = PITCH_NORM ,
							const Vector *pOrigin = NULL , const Vector *pDirection = NULL , CUtlVector< Vector >* pUtlVecOrigins = NULL , bool bUpdatePositions = true , float soundtime = 0.0f , int speakerentity = -1 ) = 0;

	virtual int EmitSound2( IRecipientFilter& filter , int iEntIndex , int iChannel , const char *pSoundEntry , unsigned int nSoundEntryHash , const char *pSample ,
							float flVolume , float flAttenuation , int nSeed , int iFlags = 0 , int iPitch = PITCH_NORM ,
							const Vector *pOrigin = NULL , const Vector *pDirection = NULL , CUtlVector< Vector >* pUtlVecOrigins = NULL , bool bUpdatePositions = true , float soundtime = 0.0f , int speakerentity = -1 ) = 0;

	virtual void EmitSentenceByIndex( IRecipientFilter& filter , int iEntIndex , int iChannel , int iSentenceIndex ,
									  float flVolume , soundlevel_t iSoundlevel , int nSeed , int iFlags = 0 , int iPitch = PITCH_NORM ,
									  const Vector *pOrigin = NULL , const Vector *pDirection = NULL , CUtlVector< Vector >* pUtlVecOrigins = NULL , bool bUpdatePositions = true , float soundtime = 0.0f , int speakerentity = -1 ) = 0;

	virtual void StopSound( int iEntIndex , int iChannel , const char *pSample , unsigned int nSoundEntryHash ) = 0;
};

#pragma endregion

#pragma region IGameEventManager2

class IGameEvent {
public:
	const char* GetName() {
		return call_func<const char*( __thiscall * )( void* )>( this , 1 )( this );
	}

	int GetInt( const char* szKeyName , int nDefault = 0 ) {
		return call_func<int( __thiscall * )( void* , const char* , int )>( this , 6 )( this , szKeyName , nDefault );
	}

	const char* GetString( const char* szKeyName ) {
		return call_func<const char*( __thiscall * )( void* , const char* , int )>( this , 9 )( this , szKeyName , 0 );
	}

	void SetString( const char* szKeyName , const char* szValue ) {
		return call_func<void( __thiscall * )( void* , const char* , const char* )>( this , 16 )( this , szKeyName , szValue );
	}
};

class IGameEventManager2 {
public:
	bool FireEventClientSide( IGameEvent* pEvent ) {
		return call_func<bool( __thiscall * )( void* , IGameEvent* )>( this , 9 )( this , pEvent );
	}
};

#pragma endregion

#pragma region CBaseViewModel

class CBaseViewModel : public IClientEntity {
public:
	int GetModelIndex() {
		// DT_BaseViewModel -> m_nModelIndex
		return *(int*)( ( DWORD )this + m_nModelIndex );
	}

	DWORD GetOwner() {
		// DT_BaseViewModel -> m_hOwner
		return *(PDWORD)( ( DWORD )this + m_hOwner );
	}

	DWORD GetWeapon() {
		// DT_BaseViewModel -> m_hWeapon
		return *(PDWORD)( ( DWORD )this + m_hWeapon );
	}

	void SetWeaponModel( const char* Filename , IClientEntity* Weapon ) {
		return call_func<void( __thiscall* )( void* , const char* , IClientEntity* )>( this , 242 )( this , Filename , Weapon );
	}
};

#pragma endregion

#pragma region CBaseAttributableItem

class CBaseAttributableItem : public IClientEntity {
public:
	int* GetItemDefinitionIndex() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex
		return (int*)( ( DWORD )this + m_iItemDefinitionIndex );
	}

	int* GetItemIDHigh() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh
		return (int*)( ( DWORD )this + m_iItemIDHigh );
	}

	int* GetAccountID() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
		return (int*)( ( DWORD )this + m_iAccountID );
	}

	int* GetEntityQuality() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		return (int*)( ( DWORD )this + m_iEntityQuality );
	}

	int* GetOriginalOwnerXuidLow() {
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow
		return (int*)( ( DWORD )this + m_OriginalOwnerXuidLow );
	}

	int* GetOriginalOwnerXuidHigh() {
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh
		return (int*)( ( DWORD )this + m_OriginalOwnerXuidHigh );
	}

	int* GetFallbackPaintKit() {
		// DT_BaseAttributableItem -> m_nFallbackPaintKit
		return (int*)( ( DWORD )this + m_nFallbackPaintKit );
	}

	float* GetFallbackWear() {
		// DT_BaseAttributableItem -> m_flFallbackWear
		return (float*)( ( DWORD )this + m_flFallbackWear );
	}

	int* GetOwnerEntity() {
		// DT_BaseAttributableItem -> m_hOwnerEntity
		return (int*)( ( DWORD )this + m_hOwnerEntity );
	}
};

#pragma endregion

#pragma region IModelRender

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

struct mstudiobbox_t
{
	int				bone;				// 0x0
	int				group;				// 0x4
	Vector	bbmin;				// 0x8
	Vector	bbmax;				// 0x14
	int				szhitboxnameindex;	// 0x18
	PAD( 0x8 );
	float           m_flRadius;// 0x1C	
	char* GetHitboxName( void )
	{
		if ( szhitboxnameindex == 0 )
			return "";

		return ( ( char* )this ) + szhitboxnameindex;
	} // 0x28 
	PAD( 0x18 );
};

struct mstudiohitboxset_t
{
	int						sznameindex;
	inline char* const		GetName( void ) const { return ( ( char* )this ) + sznameindex; }
	int						numhitboxes;
	int						hitboxindex;
	float                   m_flRadius;
	inline mstudiobbox_t*	pHitbox( int i ) const { return (mstudiobbox_t*)( ( ( BYTE* )this ) + hitboxindex ) + i; };
};

struct mstudiobone_t
{
	int					sznameindex;
	inline char * const GetName( void ) const { return ( ( char * )this ) + sznameindex; }
	int		 			parent;
	int					bonecontroller[6];

	Vector				pos;
	float				quat[4];
	Vector				rot;
	Vector				posscale;
	Vector				rotscale;

	matrix3x4_t			poseToBone;
	float				qAlignment[4];
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void *		GetProcedure() const { if ( procindex == 0 ) return NULL; else return  (void *)( ( ( BYTE * )this ) + procindex ); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char * const GetSurfaceProps( void ) const { return ( ( char * )this ) + surfacepropidx; }
	int					contents;		// See BSPFlags.h for the contents flags

	int					unused[8];		// remove as appropriate
};

struct studiohdr_t
{
	int					id;
	int					version;
	int					checksum;
	char				name[64];
	int					length;
	Vector				eyeposition;
	Vector				illumposition;
	Vector				hull_min;
	Vector				hull_max;
	Vector				view_bbmin;
	Vector				view_bbmax;
	int					flags;
	int					numbones;
	int					boneindex;

	inline mstudiobone_t *pBone( int i ) const { return (mstudiobone_t *)( ( ( BYTE * )this ) + boneindex ) + i; };

	int					numbonecontrollers;
	int					bonecontrollerindex;
	int					numhitboxsets;
	int					hitboxsetindex;

	mstudiohitboxset_t* pHitboxSet( int i ) const
	{
		return (mstudiohitboxset_t*)( ( ( BYTE* )this ) + hitboxsetindex ) + i;
	}

	inline mstudiobbox_t* pHitbox( int i , int set ) const
	{
		mstudiohitboxset_t const* s = pHitboxSet( set );

		if ( !s )
			return NULL;

		return s->pHitbox( i );
	}

	inline int GetHitboxCount( int set ) const
	{
		mstudiohitboxset_t const* s = pHitboxSet( set );

		if ( !s )
			return 0;

		return s->numhitboxes;
	}

	int					numlocalanim;
	int					localanimindex;
	int					numlocalseq;
	int					localseqindex;
	mutable int			activitylistversion;
	mutable int			eventsindexed;
	int					numtextures;
	int					textureindex;
	int					numcdtextures;
	int					cdtextureindex;
	int					numskinref;
	int					numskinfamilies;
	int					skinindex;
	int					numbodyparts;
	int					bodypartindex;
	int					numlocalattachments;
	int					localattachmentindex;
	int					numlocalnodes;
	int					localnodeindex;
	int					localnodenameindex;
	int					numflexdesc;
	int					flexdescindex;
	int					numflexcontrollers;
	int					flexcontrollerindex;
	int					numflexrules;
	int					flexruleindex;
	int					numikchains;
	int					ikchainindex;
	int					nummouths;
	int					mouthindex;
	int					numlocalposeparameters;
	int					localposeparamindex;
	int					surfacepropindex;
	int					keyvalueindex;
	int					keyvaluesize;
	int					numlocalikautoplaylocks;
	int					localikautoplaylockindex;
	float				mass;
	int					contents;
	int					numincludemodels;
	int					includemodelindex;
	mutable void		*virtualModel;
	int					szanimblocknameindex;
	int					numanimblocks;
	int					animblockindex;
	mutable void		*animblockModel;
	int					bonetablebynameindex;
	void				*pVertexBase;
	void				*pIndexBase;
	BYTE				constdirectionallightdot;
	BYTE				rootLOD;
	BYTE				numAllowedRootLODs;
	PAD( 0x5 );
	int					numflexcontrollerui;
	int					flexcontrolleruiindex;
	float				flVertAnimFixedPointScale;
	PAD( 0x4 );
	int					studiohdr2index;
	PAD( 0x4 );
};

struct DrawModelState_t
{
	struct studiohdr_t*	m_pStudioHdr;
	unsigned long		m_pStudioHWData;
	IClientEntity*		m_pRenderable;
	const matrix3x4_t*	m_pModelToWorld;
	unsigned long		m_decals;
	int					m_drawFlags;
	int					m_lod;
};

struct ModelRenderInfo_t
{
	Vector				origin;
	QAngle				angles;
	IClientEntity*		pRenderable;
	const model_t*		pModel;
	const matrix3x4_t*	pModelToWorld;
	const matrix3x4_t*	pLightingOffset;
	const Vector*		pLightingOrigin;
	int					flags;
	int					entity_index;
	int					skin;
	int					body;
	int					hitboxset;
	unsigned short		instance;
	ModelRenderInfo_t( void )
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

class IModelRender
{
public:
	void DrawModelExecute( PVOID pContext , const DrawModelState_t& pState , const ModelRenderInfo_t& pInfo , matrix3x4_t* pCustomBoneToWorld )
	{
		VirtualFn( void )( PVOID , PVOID , const DrawModelState_t& , const ModelRenderInfo_t& , matrix3x4_t* );
		call_func< OriginalFn >( this , 21 )( this , pContext , pState , pInfo , pCustomBoneToWorld );
	}
	void ForcedMaterialOverride( IMaterial *newMaterial , int nOverrideType = 0 , int iUnknown = 0 )
	{
		VirtualFn( void )( PVOID , IMaterial* , int , int );
		call_func< OriginalFn >( this , 1 )( this , newMaterial , nOverrideType , iUnknown );
	}
};

#pragma endregion

#pragma region IVModelInfoClient

class IVModelInfoClient {
public:
	void* GetModel( int Index ) {
		return call_func<void*( __thiscall * )( void* , int )>( this , 1 )( this , Index );
	}

	int GetModelIndex( const char* Filename ) {
		return call_func<int( __thiscall * )( void* , const char* )>( this , 2 )( this , Filename );
	}

	std::string GetModelName( const void* Model ) {
		return call_func<const char*( __thiscall * )( void* , const void* )>( this , 3 )( this , Model );
	}

	void GetModelMaterials( const model_t *model , int count , IMaterial** ppMaterial )
	{
		call_func<void*( __thiscall * )( void* , const model_t* , int , IMaterial** )>( this , 17 )( this , model , count , ppMaterial );
	}
	studiohdr_t* GetStudioModel( const model_t *mod )
	{
		return call_func<studiohdr_t*( __thiscall * )( void* , const model_t* )>( this , 30 )( this , mod );
	}
};

#pragma endregion

#pragma region IMaterial

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = ( 1 << 0 ) ,
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = ( 1 << 1 ) ,
	MATERIAL_VAR_NO_DRAW = ( 1 << 2 ) ,
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = ( 1 << 3 ) ,
	MATERIAL_VAR_VERTEXCOLOR = ( 1 << 4 ) ,
	MATERIAL_VAR_VERTEXALPHA = ( 1 << 5 ) ,
	MATERIAL_VAR_SELFILLUM = ( 1 << 6 ) ,
	MATERIAL_VAR_ADDITIVE = ( 1 << 7 ) ,
	MATERIAL_VAR_ALPHATEST = ( 1 << 8 ) ,
	MATERIAL_VAR_ZNEARER = ( 1 << 10 ) ,
	MATERIAL_VAR_MODEL = ( 1 << 11 ) ,
	MATERIAL_VAR_FLAT = ( 1 << 12 ) ,
	MATERIAL_VAR_NOCULL = ( 1 << 13 ) ,
	MATERIAL_VAR_NOFOG = ( 1 << 14 ) ,
	MATERIAL_VAR_IGNOREZ = ( 1 << 15 ) ,
	MATERIAL_VAR_DECAL = ( 1 << 16 ) ,
	MATERIAL_VAR_ENVMAPSPHERE = ( 1 << 17 ) , // OBSOLETE
	MATERIAL_VAR_ENVMAPCAMERASPACE = ( 1 << 19 ) , // OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK = ( 1 << 20 ) ,
	MATERIAL_VAR_TRANSLUCENT = ( 1 << 21 ) ,
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = ( 1 << 22 ) ,
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = ( 1 << 23 ) , // OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE = ( 1 << 24 ) ,
	MATERIAL_VAR_ENVMAPMODE = ( 1 << 25 ) , // OBSOLETE
	MATERIAL_VAR_SUPPRESS_DECALS = ( 1 << 26 ) ,
	MATERIAL_VAR_HALFLAMBERT = ( 1 << 27 ) ,
	MATERIAL_VAR_WIREFRAME = ( 1 << 28 ) ,
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = ( 1 << 29 ) ,
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = ( 1 << 30 ) ,
	MATERIAL_VAR_VERTEXFOG = ( 1 << 31 ) ,
};

class IMaterial
{
public:
	std::string GetName( void )
	{
		VirtualFn( const char* )( PVOID );
		return std::string( call_func< OriginalFn >( this , 0 )( this ) );
	}
	std::string GetTextureGroupName( void )
	{
		VirtualFn( const char* )( PVOID );
		return std::string( call_func< OriginalFn >( this , 1 )( this ) );
	}
	void IncrementReferenceCount( void )
	{
		VirtualFn( void )( PVOID );
		call_func< OriginalFn >( this , 12 )( this );
	}
	void AlphaModulate( float alpha )
	{
		VirtualFn( void )( PVOID , float );
		call_func< OriginalFn >( this , 27 )( this , alpha );
	}
	void ColorModulate( float r , float g , float b )
	{
		VirtualFn( void )( PVOID , float , float , float );
		call_func< OriginalFn >( this , 28 )( this , r , g , b );
	}
	void SetMaterialVarFlag( MaterialVarFlags_t flag , bool on )
	{
		VirtualFn( void )( PVOID , MaterialVarFlags_t , bool );
		call_func< OriginalFn >( this , 29 )( this , flag , on );
	}
};

#pragma endregion

#pragma region IRenderView

class IRenderView
{
public:
	void SetBlend( float blend )
	{
		VirtualFn( void )( PVOID , float );
		call_func< OriginalFn >( this , 4 )( this , blend );
	}
	void SetColorModulation( float const* blend )
	{
		VirtualFn( void )( PVOID , float const* );
		call_func< OriginalFn >( this , 6 )( this , blend );
	}
};

#pragma endregion

#pragma region IMaterialSystem

class IMaterialSystem
{
public:
	IMaterial* CreateMaterial( const char* pMaterialName , KeyValues* pVMTKeyValues )
	{
		VirtualFn( IMaterial* )( PVOID , const char* , KeyValues* );
		return call_func< OriginalFn >( this , 83 )( this , pMaterialName , pVMTKeyValues );
	}
	IMaterial* FindMaterial( const char* pMaterialName , const char* pTextureGroupName , bool complain = true , const char* pComplainPrefix = 0 )
	{
		VirtualFn( IMaterial* )( PVOID , const char* , const char* , bool , const char* );
		return call_func< OriginalFn >( this , 84 )( this , pMaterialName , pTextureGroupName , complain , pComplainPrefix );
	}
};

#pragma endregion

#pragma region KeyValues

class KeyValues
{
public:
	static void SetUseGrowableStringTable( bool bUseGrowableTable );

	KeyValues( const char *setName )
	{
		Init();
		SetName( setName );
	}

	class AutoDelete
	{
	public:
		explicit inline AutoDelete( KeyValues *pKeyValues ) : m_pKeyValues( pKeyValues ) {}
		explicit inline AutoDelete( const char *pchKVName ) : m_pKeyValues( new KeyValues( pchKVName ) ) {}
		inline ~AutoDelete( void ) { if ( m_pKeyValues ) m_pKeyValues->deleteThis(); }
		inline void Assign( KeyValues *pKeyValues ) { m_pKeyValues = pKeyValues; }
		KeyValues *operator->() { return m_pKeyValues; }
		operator KeyValues *( ) { return m_pKeyValues; }
	private:
		AutoDelete( AutoDelete const &x ); // forbid
		AutoDelete & operator= ( AutoDelete const &x ); // forbid
		KeyValues *m_pKeyValues;
	};

	const char *GetName() const;
	void SetName( const char *setName )
	{
		m_iKeyName = 2;
	}

	int GetNameSymbol() const { return m_iKeyName; }

	void UsesEscapeSequences( bool state ); // default false
	void UsesConditionals( bool state ); // default true

	KeyValues *FindKey( const char *keyName , bool bCreate = false );
	KeyValues *FindKey( int keySymbol ) const;
	KeyValues *CreateNewKey();		// creates a new key, with an autogenerated name.  name is guaranteed to be an integer, of value 1 higher than the highest other integer key name
	void AddSubKey( KeyValues *pSubkey );	// Adds a subkey. Make sure the subkey isn't a child of some other keyvalues
	void RemoveSubKey( KeyValues *subKey );	// removes a subkey from the list, DOES NOT DELETE IT

	KeyValues *GetFirstSubKey() { return m_pSub; }	// returns the first subkey in the list
	KeyValues *GetNextKey() { return m_pPeer; }		// returns the next subkey
	void SetNextKey( KeyValues * pDat );
	KeyValues *FindLastSubKey();	// returns the LAST subkey in the list.  This requires a linked list iteration to find the key.  Returns NULL if we don't have any children

	KeyValues* GetFirstTrueSubKey();
	KeyValues* GetNextTrueSubKey();

	KeyValues* GetFirstValue();	// When you get a value back, you can use GetX and pass in NULL to get the value.
	KeyValues* GetNextValue();

	// Data access
	int   GetInt( const char *keyName = NULL , int defaultValue = 0 );
	float GetFloat( const char *keyName = NULL , float defaultValue = 0.0f );
	const char *GetString( const char *keyName = NULL , const char *defaultValue = "" );
	const wchar_t *GetWString( const char *keyName = NULL , const wchar_t *defaultValue = L"" );
	void *GetPtr( const char *keyName = NULL , void *defaultValue = (void*)0 );
	bool GetBool( const char *keyName = NULL , bool defaultValue = false );
	bool  IsEmpty( const char *keyName = NULL );

	// Data access
	int   GetInt( int keySymbol , int defaultValue = 0 );
	float GetFloat( int keySymbol , float defaultValue = 0.0f );
	const char *GetString( int keySymbol , const char *defaultValue = "" );
	const wchar_t *GetWString( int keySymbol , const wchar_t *defaultValue = L"" );
	void *GetPtr( int keySymbol , void *defaultValue = (void*)0 );
	bool  IsEmpty( int keySymbol );

	// Key writing
	void SetWString( const char *keyName , const wchar_t *value );
	void SetString( const char *keyName , const char *value );
	void SetInt( const char *keyName , int value );
	void SetUint64( const char *keyName , UINT value );
	void SetFloat( const char *keyName , float value );
	void SetPtr( const char *keyName , void *value );
	void SetBool( const char *keyName , bool value ) { SetInt( keyName , value ? 1 : 0 ); }

	KeyValues& operator=( KeyValues& src );

	// Adds a chain... if we don't find stuff in this keyvalue, we'll look
	// in the one we're chained to.
	void ChainKeyValue( KeyValues* pChain );

	// Allocate & create a new copy of the keys
	KeyValues *MakeCopy( void ) const;

	// Make a new copy of all subkeys, add them all to the passed-in keyvalues
	void CopySubkeys( KeyValues *pParent ) const;

	// Clear out all subkeys, and the current value
	void Clear( void );

	// Data type
	enum types_t
	{
		TYPE_NONE = 0 ,
		TYPE_STRING ,
		TYPE_INT ,
		TYPE_FLOAT ,
		TYPE_PTR ,
		TYPE_WSTRING ,
		TYPE_COLOR ,
		TYPE_UINT64 ,
		TYPE_NUMTYPES ,
	};
	types_t GetDataType( const char *keyName = NULL );

	// Virtual deletion function - ensures that KeyValues object is deleted from correct heap
	void deleteThis();

	void SetStringValue( char const *strValue );

	// unpack a key values list into a structure
	void UnpackIntoStructure( struct KeyValuesUnpackStructure const *pUnpackTable , void *pDest , size_t DestSizeInBytes );

	// Process conditional keys for widescreen support.
	bool ProcessResolutionKeys( const char *pResString );

	// Dump keyvalues recursively into a dump context
	bool Dump( class IKeyValuesDumpContext *pDump , int nIndentLevel = 0 );

	// Merge in another KeyValues, keeping "our" settings
	void RecursiveMergeKeyValues( KeyValues *baseKV );

public:
	KeyValues( KeyValues& );	// prevent copy constructor being used

								// prevent delete being called except through deleteThis()
	~KeyValues();

	KeyValues* CreateKey( const char *keyName );

	KeyValues* CreateKeyUsingKnownLastChild( const char *keyName , KeyValues *pLastChild );
	void AddSubkeyUsingKnownLastChild( KeyValues *pSubKey , KeyValues *pLastChild );

	void RecursiveCopyKeyValues( KeyValues& src );
	void RemoveEverything();

	void Init()
	{
		m_iKeyName = -1;
		m_iDataType = TYPE_NONE;

		m_pSub = NULL;
		m_pPeer = NULL;
		m_pChain = NULL;

		m_sValue = NULL;
		m_wsValue = NULL;
		m_pValue = NULL;

		m_bHasEscapeSequences = false;

		// for future proof
		memset( unused , 0 , sizeof( unused ) );
	}

	void FreeAllocatedValue();
	void AllocateValueBlock( int size );

	int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

					// These are needed out of the union because the API returns string pointers
	char *m_sValue;
	wchar_t *m_wsValue;

	// we don't delete these
	union
	{
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char	   m_iDataType;
	char	   m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
	char	   m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
	char	   unused[1];

	KeyValues *m_pPeer;	// pointer to next key in list
	KeyValues *m_pSub;	// pointer to Start of a new sub key list
	KeyValues *m_pChain;// Search here if it's not in our list

private:
	// Statics to implement the optional growable string table
	// Function pointers that will determine which mode we are in
	static int( *s_pfGetSymbolForString )( const char *name , bool bCreate );
	static const char *( *s_pfGetStringForSymbol )( int symbol );

public:
	// Functions that invoke the default behavior
	static int GetSymbolForStringClassic( const char *name , bool bCreate = true );
	static const char *GetStringForSymbolClassic( int symbol );

	// Functions that use the growable string table
	static int GetSymbolForStringGrowable( const char *name , bool bCreate = true );
	static const char *GetStringForSymbolGrowable( int symbol );

	// Functions to get external access to whichever of the above functions we're going to call.
	static int CallGetSymbolForString( const char *name , bool bCreate = true ) { return s_pfGetSymbolForString( name , bCreate ); }
	static const char *CallGetStringForSymbol( int symbol ) { return s_pfGetStringForSymbol( symbol ); }

	bool LoadFromBuffer( KeyValues *pThis , const char *pszFirst , const char *pszSecond , PVOID pSomething = 0 , PVOID pAnother = 0 , PVOID pLast = 0 );
};

#pragma endregion