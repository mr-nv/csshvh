#pragma once

#include <windows.h>

struct offsets
{
	unsigned long offs_simulationtime;
};
extern offsets g_pOffsets;

#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
#pragma warning( disable:4244 )
#pragma warning( disable:4541 )
#pragma warning( disable:4267 )
#pragma warning( disable:4183 )
#pragma warning( disable:4018 )
#pragma warning( default:4355 )//
#pragma warning( default:4098 )
#pragma warning( disable:4409 )
#pragma warning( disable:4390 )
#pragma warning( disable:4172 )
#pragma warning( disable:4700 )
#pragma warning( disable:4101 )

#define DO_ONCE( arg )				\
	static bool UnIqUe_ONC3 = false;\
	if( UnIqUe_ONC3 == false )\
{									\
	UnIqUe_ONC3 = true;				\
	arg								\
}

#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

#define M_RADPI 57.295779513082f

#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK						(1 << 2)
#define IN_FORWARD					(1 << 3)
#define IN_BACK						(1 << 4)
#define IN_USE						(1 << 5)
#define IN_CANCEL					(1 << 6)
#define IN_LEFT						(1 << 7)
#define IN_RIGHT					(1 << 8)
#define IN_MOVELEFT					(1 << 9)
#define IN_MOVERIGHT				(1 << 10)
#define IN_ATTACK2					(1 << 11)
#define IN_RUN						(1 << 12)
#define IN_RELOAD					(1 << 13)
#define IN_ALT1						(1 << 14)
#define IN_ALT2						(1 << 15)
#define IN_SCORE					(1 << 16)
#define IN_SPEED					(1 << 17)
#define IN_WALK						(1 << 18)
#define IN_ZOOM						(1 << 19)
#define IN_WEAPON1					(1 << 20)
#define IN_WEAPON2					(1 << 21)
#define IN_BULLRUSH					(1 << 22)
#define OUTLINE COLORCODE(3, 6, 26, 215)

// First
#include "SDK\\public\\tier0\\wchartypes.h"

// Public
#include "SDK\\public\\cdll_int.h"
#include "SDK\\public\\mathlib\halton.h"
#include "SDK\\public\\mathlib\ssemath.h"
#include "SDK\\public\\iprediction.h"
#include "SDK\\public\\bone_setup.h"
#include "SDK\\public\\icliententitylist.h"
#include "SDK\\public\\ienginevgui.h"
#include "SDK\\public\\IGameUIFuncs.h"
#include "SDK\\public\\dlight.h"
#include "SDK\\public\\iefx.h" 
#include "SDK\\public\\igameevents.h"
#include "SDK\\public\\view_shared.h"
#include "SDK\\public\\inetchannel.h"
#include "SDK\\public\\iachievementmgr.h"
#include "SDK\\public\\steam\\steam_api.h"
#include "SDK\\public\\steam\\isteamuserstats.h"
#include "SDK\\public\\eiface.h"

// Client
#include "SDK\\game\\client\\imessagechars.h"
#include "SDK\\game\\client\\iclientmode.h"
#include "SDK\\game\\client\\cliententitylist.h"
#include "SDK\\game\\client\\cdll_client_int.h"
#include "SDK\\game\\client\\cbase.h"
#include "SDK\\game\\client\\c_baseanimating.h"
#include "SDK\\game\\client\\c_basecombatweapon.h"
#include "SDK\\game\\client\\c_baseplayer.h"
#include "SDK\\game\\client\\enginesprite.h"
#include "SDK\\game\\client\\input.h"
#include "SDK\\game\\client\\c_playerresource.h"
#include "SDK\\game\\client\\iviewrender.h"
#include "SDK\\game\\client\\viewrender.h"
#include "SDK\\game\\client\\game_controls\\commandmenu.h"
#include "SDK\\game\\client\\hudelement.h"

// Server
//#include "SDK\\game\\server\\bg2\\weapon_bg2base.h"

// Engine
#include "SDK\\public\\engine\\ivmodelrender.h"
#include "SDK\\public\\engine\\ivdebugoverlay.h"
#include "SDK\\public\\engine\\ivmodelinfo.h"
#include "SDK\\public\\engine\\IEngineTrace.h"
#include "SDK\\public\\engine\\IEngineSound.h"

// Material System
#include "SDK\\public\\materialsystem\\imaterialsystemstub.h"
#include "SDK\\public\\materialsystem\\itexture.h"
#include "SDK\\public\\materialsystem\\IMaterialVar.h"

// VGUI
#include "SDK\\public\\matsys_controls\\matsyscontrols.h"
#include "SDK\\public\\vgui\\IClientPanel.h"
#include "SDK\\public\\vgui\\IPanel.h"
#include "SDK\\public\\vgui\\ISurface.h"
#include "SDK\\public\\vgui\\ILocalize.h"
#include "SDK\\public\\collisionutils.h"

// VGUI Controls
#include "SDK\\public\\vgui_controls\\Panel.h"

// VGUI Material Surface
#include "SDK\\public\\VGuiMatSurface\\IMatSystemSurface.h"

// Shared
#include "SDK\\game\\shared\\usermessages.h"
#include "SDK\\game\\shared\\basecombatweapon_shared.h"
#include "SDK\\game\\shared\\takedamageinfo.h"
#include "SDK\\game\\shared\\predicted_viewmodel.h"
#include "SDK\\game\\shared\\ipredictionsystem.h"
#include "SDK\\game\\shared\\predictableid.h"
#include "SDK\\game\\shared\\predictioncopy.h"
#include "SDK\\game\\shared\\base_playeranimstate.h"
#include "SDK\\game\\shared\\predictable_entity.h"

#include "SDK\\game\\client\\c_vehicle_jeep.h"


#include "game\client\prediction.h"

#include <Psapi.h>

//#include <d3d9.h>
//#include <d3dx9.h>
#include "detours.h"
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "detours.lib") 

#pragma comment(lib, "SDK/lib/public/tier0.lib")
#pragma comment(lib, "SDK/lib/public/tier1.lib")
#pragma comment(lib, "SDK/lib/public/tier2.lib")
#pragma comment(lib, "SDK/lib/public/tier3.lib")
#pragma comment(lib, "SDK/lib/public/mathlib.lib")
#pragma comment(lib, "SDK/lib/public/vstdlib.lib")
#pragma comment(lib, "SDK/lib/public/vgui_controls.lib")

#include "cAimbot.h"
#include "Nospread.h"
#include "netvars.h"
#include "cUtils.h"
#include "detours.h"
#include "xorstr.h"
#include "mymath.h"
#include "maths.h"
#include "Fakelagfix.h"
#include "cMouse.h"
	 
extern IBaseClientDLL*	          g_pClient;
extern CInput*			          g_pInput;
extern IVEngineClient*	          g_pEngine;
extern IClientEntityList*         g_pEntList;
extern IEngineTrace*	          g_pEnginetrace;
extern IVModelInfoClient*         g_pModelinfo;
extern IVPhysicsDebugOverlay*     g_pDebugOverlay;
extern C_BasePlayer*              g_pBasePlayer;
extern C_BaseEntity*              g_pBaseEntity;
extern ICvar*                     g_pCvar;
extern IPanel*					  g_pPanel;
extern IMaterialSystem*			  g_pMatSystem;
extern IVRenderView*			  g_pRenderView;
extern IGameEventManager2*		  g_pEventManager2;
extern ISurface*				  g_pSurface;
extern IMatSystemSurface*         g_pMatSytemSurface;
extern ILocalize*			      g_pVGUILocalize;
extern HFont                      font;
extern HFont                      font2;
extern IVRenderView*			  GRenderView;
extern CGlobalVarsBase*           g_pGlobals;
extern IPhysicsSurfaceProps*      g_pPhysicAPI;
extern IVEfx*                     g_pEffects;
extern CGameMovement*			  g_pGameMovement;
extern IVModelRender*             g_pModelRender;
extern IPrediction*				  g_pPrediction;
//extern cMenu                      gMenu;
//extern aspimenu                  gaspimenu;
extern CBaseEntityList*           g_pEntityList;
extern INetChannelInfo*		      g_pNet;

#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RED(COLORCODE)((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)((int) COLORCODE & 0xFF )
#define RGBA(COLORCODE) RED( COLORCODE ), GREEN( COLORCODE ), BLUE( COLORCODE ), ALPHA( COLORCODE )

#define CHEAT_ORANGE COLORCODE( 255, 100, 0, 255 )
#define CHEAT_YELLOW COLORCODE( 255, 255, 0, 255 )
#define CHEAT_PURPLE COLORCODE( 55, 25, 128, 255 )
#define CHEAT_RED COLORCODE( 255, 0, 0, 255 )
#define CHEAT_GREEN COLORCODE( 0, 255, 0, 255 )
#define CHEAT_BLUE COLORCODE( 0, 0, 255, 255 )
#define CHEAT_BLACK COLORCODE( 0, 0, 0, 255 )
#define CHEAT_WHITE COLORCODE( 255, 255, 255, 255 )
#define CHEAT_PINK COLORCODE( 255, 0, 255, 255 )
#define CHEAT_LIGHTBLUE COLORCODE( 0, 0, 225, 225 )
#define CHEAT_LIGHTGREEN COLORCODE( 0, 225, 0, 225 )
#define CHEAT_LIGHTRED COLORCODE( 225, 0, 0, 225 )
struct var_s{

	//AIMBOT
	float aimbot;
	float autoshoot;
	float aimspot;
	float hitscan;
	float psilent;
	float aimwall;
	float aimsilent;

	//VISUALS
	float chams;
	float asuswall;
	float boxesp;
	float healthbar;

	//REMOVALS
	float novisrecoil;
	float norecoil;
	float nospread;
	int nospread2;
	float nosky;

	//MISC
	float attargets;
	float antiaim;
	float fakelag;
	float newstrafer;
	float fakelagvalue;
	float fakelaginattack;
	float fakelagvalue1;
	float autopistol;
	float packets;
	float fakelagfix;
	float bhop;
	float antiaimtype;
	float bcachingMethod; //bool because only two caching methods
	float bdisableinterpolation;
	float bdisableextrapolation;
	float bshowlagcorrection;
	float AA_Sent;
	float AA_Blocked;
	float AntiAimtype;
	float FakelagType;
	float In_Attack_Value;
	float Constant_Lag_Value;
	float fastawp;
	float bypass;
	float fakeduck;
	float edge;
	float spincrosshair;
	float emotionx;
	float fakedownx;
	float normalx;
	float spinjitter;
	float fakesideways;
	float fakeforwards;
	float staticforward;
	float clock;

	//WHITELIST
	float whitevane;
	float whitezylx;
	float whiteneo;
	float whitepara;
	float whitecrownt;
	float whiteville;
	float whitegene;

	//MENU STUFF
	int menu_active;
	int menu_page;
	int pos_bx;
	int pos_by;
	int pos_bw;
	int pos_bh;
	int pos_bs;
	bool canmodify;


};

extern var_s g_vars;
#include "Menu.h"


#define MENU_BG COLORCODE( 0, 0, 0, 120 )//background color behind menu items
#define MENU_TEXT COLORCODE( 0, 150, 255, 250 )//menu text color
#define MENU_SELECTION COLORCODE( 0, 0, 0, 255 )//top half of selection bar color
#define MENU_SELECTIONB COLORCODE( 0, 0, 0, 255 )//bottom half of slection bar color
#define MENU_TITLE COLORCODE( 171, 242, 4, 255 )//color of text in title
#define MENU_TITLEBG COLORCODE( 253, 77, 2, 120 )//top half of title bar background color
#define MENU_TITLEBGB COLORCODE( 254, 124, 69, 120 )//bottom  half of title bar background color

extern DWORD g_dwUserWirtCmd;
extern DWORD dwFindPattern(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, char* szMask);
extern DWORD g_dwOrgCreateMove;
extern DWORD g_CreateMove;
extern DWORD g_dwOrgHudUpdate;
extern DWORD g_dwOrgGetUserCmd;
extern DWORD g_dwOrgPaintTraverse;
extern DWORD g_dwOrgEngineSBegin;
extern DWORD g_dwOrgFindMaterial;
extern DWORD g_dwOrgEngineStats_BeginFrame;
extern DWORD g_dwOrgFrameStageNotify;
extern DWORD g_dwOrgPaintTraverseNPC;
void __stdcall new_PaintTraverseNPC(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce);//drawing
void STDMETHODCALLTYPE new_EngineStats_BeginFrame( void );
void __stdcall new_HudUpdate( bool bActive );
void __stdcall DrawelExecute( const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld );
extern DWORD g_dwOrgDrawelExecute;
IMaterial* __stdcall new_FindMaterial( char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix );
CUserCmd* __stdcall new_GetUserCmd( int seq );
void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce);
bool _stdcall gg( bf_write *buf, int from, int to, bool isnewcommand );
void __stdcall new_CreateMove(int sequence_number, float input_sample_frametime, bool active);
void __stdcall new_FrameStageNotify( ClientFrameStage_t curStage );
void new_CSPlayer_FlashVariables( const CRecvProxyData *pData, void *pStruct, void *pOut );
void HookPropRecvX( const CRecvProxyData *pData, void *pStruct, void *pOut );
void AAAX(const CRecvProxyData *pData, void *pStruct, void *pOut);
void AAAY(const CRecvProxyData *pData, void *pStruct, void *pOut);
void HookPropRecvX2( const CRecvProxyData *pData, void *pStruct, void *pOut );
extern DWORD g_dwOrgFindMaterial;
IMaterial* __stdcall new_FindMaterial( char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix );


//#define CT ( (NumVertices == 3417 && primCount == 5030) || (NumVertices == 2245 && primCount == 2998) || (NumVertices == 1609 && primCount == 1794) || (NumVertices == 929 && primCount == 1007) || (NumVertices == 499 && primCount == 533) || (NumVertices == 409 && primCount == 433) || (NumVertices == 3887 && primCount == 4974) || (NumVertices == 2487 && primCount == 3006) || (NumVertices == 2130 && primCount == 3004) || (NumVertices == 899 && primCount == 910) || (NumVertices == 513 && primCount == 451) || (NumVertices == 369 && primCount == 297) ||  (NumVertices == 3206 && primCount == 4872) || (NumVertices == 1498 && primCount == 1822) || (NumVertices == 1424 && primCount == 1858) || (NumVertices == 814 && primCount == 945)||(NumVertices == 475 && primCount == 510) || (NumVertices == 343 && primCount == 344) || (NumVertices == 3304 && primCount == 5003) || (NumVertices == 2196 && primCount == 3061)|| (NumVertices == 1404 && primCount == 1919) || (NumVertices == 811 && primCount == 989) || (NumVertices == 466 && primCount == 550) || (NumVertices == 324 && primCount == 372) )
//#define T ( (NumVertices == 3561 && primCount == 5066) || (NumVertices == 2261 && primCount == 3003) || (NumVertices == 1588 && primCount == 2013) || (NumVertices == 911 && primCount == 996) || (NumVertices == 526 && primCount == 594) || (NumVertices == 389 && primCount == 386) || (NumVertices == 3265 && primCount == 5015) || (NumVertices == 2274 && primCount == 3070) || (NumVertices == 1510 && primCount == 1871) || (NumVertices == 873 && primCount == 986) || (NumVertices == 563 && primCount == 590) || (NumVertices == 368 && primCount == 377) || (NumVertices == 3087 && primCount == 4911) || (NumVertices == 1992 && primCount == 2996) || (NumVertices == 1311 && primCount == 1812) || (NumVertices == 735 && primCount == 899) || (NumVertices == 454 && primCount == 519) || (NumVertices == 323 && primCount == 338) || (NumVertices == 3210 && primCount == 4503) || (NumVertices == 2292 && primCount == 3015) || (NumVertices == 1488 && primCount == 1819) || (NumVertices == 835 && primCount == 899) || (NumVertices == 554 && primCount == 509) || (NumVertices == 408 && primCount == 344) )
#define HANDS (NumVertices == 1286 && primCount == 1778)
//#define SKY	(g_cBase.m_nStride == 32 && NumVertices == 4 && primCount == 2 && ((startIndex == 0 || startIndex == 6 || startIndex == 12 || startIndex == 18 || startIndex == 24 /*|| startIndex == 54 || startIndex == 60 || startIndex == 66 || startIndex == 72*/ ) && (MinVertexIndex == 0 || MinVertexIndex == 4 || MinVertexIndex == 8 || MinVertexIndex == 12)))
#define WEAPON ( (NumVertices == 403 && primCount == 269) || (NumVertices == 499 && primCount == 326) || (NumVertices == 336 && primCount == 220) || (NumVertices == 394 && primCount == 263) || (NumVertices == 399 && primCount == 271) || (NumVertices == 724 && primCount == 496) || (NumVertices == 469 && primCount == 329) || (NumVertices == 456 && primCount == 382) || (NumVertices == 450 && primCount == 323) || (NumVertices == 394 && primCount == 280) || (NumVertices == 502 && primCount == 410) || (NumVertices == 560 && primCount == 391) || (NumVertices == 465 && primCount == 329) || (NumVertices == 431 && primCount == 285) || (NumVertices == 758 && primCount == 462) || (NumVertices == 462 && primCount == 364) || (NumVertices == 606 && primCount == 477) ||(NumVertices == 616 && primCount == 494) ||(NumVertices == 620 && primCount == 464) || (NumVertices == 628 && primCount == 402) || (NumVertices == 681 && primCount == 523) || (NumVertices == 376 && primCount == 300) ||(NumVertices == 581 && primCount == 433) || (NumVertices == 671 && primCount == 489) || (NumVertices == 753 && primCount == 541) || (NumVertices == 650 && primCount == 522) || (NumVertices == 573 && primCount == 417) || (NumVertices == 671 && primCount == 493) )
int GetOffset(char *szClassName, char *szVariable);