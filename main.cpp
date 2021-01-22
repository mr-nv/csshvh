#include "main.h"

offsets g_pOffsets;
IBaseClientDLL*	          g_pClient           = NULL;
CInput*			          g_pInput            = NULL;
CGameMovement*			  g_pGameMovement     = NULL;
IVEngineClient*	          g_pEngine           = NULL;
IClientEntityList*        g_pEntList          = NULL;
IEngineTrace*	          g_pEnginetrace      = NULL;
C_BaseEntity*             g_pBaseEntity       = NULL;
IVModelInfoClient*        g_pModelinfo        = NULL;
IVPhysicsDebugOverlay*    g_pDebugOverlay     = NULL;
IPhysicsSurfaceProps*     g_pPhysicAPI        = NULL;
ICvar*                    g_pCvar             = NULL;
IPanel*					  g_pPanel			  = NULL;
IMaterialSystem*		  g_pMatSystem		  = NULL;
IVRenderView*			  g_pRenderView		  = NULL;
IMatSystemSurface*        g_pMatSytemSurface  = NULL;    
ISurface*				  g_pSurface		  = NULL;
IGameEventManager2*       g_pEventManager2	  = NULL;
ILocalize*			      g_pVGUILocalize	  = NULL;
CGlobalVarsBase*          g_pGlobals          = NULL;
IVEfx*                    g_pEffects          = NULL;
IVModelRender*            g_pModelRender      = NULL; 
IPrediction*			  g_pPrediction		  = NULL;
//LocalPlayer*			  m_pMyPlayer         = NULL;
CBaseEntityList*          g_pEntityList       = NULL;
//LocalPlayer*			  g_pMyPlayer         = NULL;
INetChannelInfo*		  g_pNet			  = NULL;
HFont                    font = NULL;
HFont                     font2 = NULL;
//cMenu                     gMenu;
CNetworkedVars GNetworkedVariables;

DETOUR_TRAMPOLINE(BOOL WINAPI PeekMessageA_t(LPMSG,HWND,UINT,UINT,UINT),PeekMessageA);
DETOUR_TRAMPOLINE(BOOL WINAPI SetCursorPos_t(int,int),SetCursorPos);
DETOUR_TRAMPOLINE(BOOL WINAPI GetCursorPos_t(LPPOINT),GetCursorPos);

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(; *szMask; ++szMask, ++pData, ++bMask)
	{
		if(*szMask == 'x' && *pData != *bMask)
		{
			return false;
		}
	}
	return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, char* szMask)
{
	for(DWORD i = NULL; i < dwSize; i++)
	{
		if(bDataCompare((BYTE*)(dwAddress + i), pbMask, szMask))
		{
			return (DWORD)(dwAddress + i);
		}
	}
	return 0;
}
//DETOUR_TRAMPOLINE(BOOL WINAPI PeekMessageA_t(LPMSG, HWND, UINT, UINT, UINT), PeekMessageA);
//DETOUR_TRAMPOLINE(BOOL WINAPI SetCursorPos_t(int, int), SetCursorPos);
//DETOUR_TRAMPOLINE(BOOL WINAPI GetCursorPos_t(LPPOINT), GetCursorPos);

BOOL WINAPI hkPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg){
	if (!PeekMessageA_t(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
		return false;
	if (g_pEngine->IsInGame()){
		if (gMouse.MousePeekMessage(lpMsg->message, lpMsg->wParam, lpMsg->lParam))
			return false;
		//if(gConsole.peekMessage(lpMsg->message,lpMsg->wParam,lpMsg->lParam))
		//	return false;
	}

	return true;

}

//===================================================================================
BOOL WINAPI hkSetCursorPos(int x, int y){
	gMouse.OldPos[0] = x;
	gMouse.OldPos[1] = y;
	if (gMouse.ActiveMouse&&!g_pEngine->Con_IsVisible())
		return true;

	return SetCursorPos_t(x, y);
}
//===================================================================================
BOOL WINAPI hkGetCursorPos(LPPOINT lpPoint){
	BOOL ret = GetCursorPos_t(lpPoint);
	if (gMouse.ActiveMouse){
		ScreenToClient(GetForegroundWindow(), lpPoint);
		gMouse.MousePos[0] = lpPoint->x;
		gMouse.MousePos[1] = lpPoint->y;
		if (g_pEngine->IsInGame()){
			lpPoint->x = gMouse.OldPos[0];
			lpPoint->y = gMouse.OldPos[1];
		}
	}

	return ret;
}

bool CheckAddress( PCHAR pCurrent, const string strPattern )
{
	for( string::const_iterator Current = strPattern.begin(); Current != strPattern.end(); ++Current )
	{
		if( *Current == '?' )
		{
			pCurrent++;
			continue;
		}

		if( *pCurrent != *Current )
		{
			return false;
		}

		pCurrent++;
	}

	return true;
}
int GetOffset(char *szClassName, char *szVariable)
{
 ClientClass* pClass = g_pClient->GetAllClasses();

 for (; pClass; pClass = pClass->m_pNext)
 {
  RecvTable* pTable = pClass->m_pRecvTable;

  if (pTable->GetNumProps() <= 1) continue;

  for (int i = 0; i < pTable->GetNumProps(); i++)
  {
   RecvProp* pProp = pTable->GetProp(i);

   if (!pProp) continue;

   if (!V_strcmp(pTable->GetName(), szClassName) && !V_strcmp(pProp->GetName(), szVariable))
   {
    return pProp->GetOffset();
   }
   if (pProp->GetDataTable())
   {
    RecvTable* pTable = pProp->GetDataTable();
    for (int i = 0; i < pTable->GetNumProps(); i++)
    {
     RecvProp* pProp = pTable->GetProp(i);

     if (!pProp) continue;

     if (!V_strcmp(pTable->GetName(), szClassName) && !V_strcmp(pProp->GetName(), szVariable))
     {
      return pProp->GetOffset();
     }
    }
   }
  }
 }
 Msg("Fucked up, no offset for %s\n", szVariable);
 return 0; //fucked up town, shit fly in my mouth. I cant seeeeeeeeeeeeeeeeeeee
}

DWORD WINAPI HookThread(LPVOID lpArgs)
{
	while(!GetModuleHandle("client.dll"))
		Sleep(200);

	//ConColorMsg(Color(0,255,0,255),"\nPower-Productions Private is now Loaded\n");

	CreateInterfaceFn EngineFactory = Sys_GetFactory( "engine.dll" );
	CreateInterfaceFn ClientFactory = Sys_GetFactory( "client.dll" );
	CreateInterfaceFn VGUI2Factory	= Sys_GetFactory( "vgui2.dll" );
	CreateInterfaceFn MatSysFac		= Sys_GetFactory( "materialsystem.dll");
	CreateInterfaceFn VGUIFactory	= Sys_GetFactory( "vguimatsurface.dll");
	CreateInterfaceFn CvarFactory	= Sys_GetFactory( "vstdlib.dll" );
	CreateInterfaceFn PhysicFactory	= Sys_GetFactory( "vphysics.dll" );

	g_pEngine = (IVEngineClient*)EngineFactory(VENGINE_CLIENT_INTERFACE_VERSION, 0);
	DWORD* pdwEngineVMT = (DWORD*)*(DWORD*)g_pEngine;

	g_pClient = (IBaseClientDLL*)ClientFactory("VClient017", NULL);
	PDWORD pdwClientVMT = (PDWORD)*(PDWORD)g_pClient;

	g_pInput = (CInput*)*(DWORD*)*(DWORD*)(pdwClientVMT[21] + 0x20);// 14
	PDWORD pdwInputVMT = ( PDWORD ) * ( PDWORD ) g_pInput;

	g_pModelinfo = (IVModelInfoClient*)EngineFactory(VMODELINFO_CLIENT_INTERFACE_VERSION, 0);
	g_pEnginetrace = (IEngineTrace*)EngineFactory(INTERFACEVERSION_ENGINETRACE_CLIENT, 0);
	g_pEntList = (IClientEntityList*)ClientFactory(VCLIENTENTITYLIST_INTERFACE_VERSION, 0);
	g_pDebugOverlay = (IVPhysicsDebugOverlay*)EngineFactory(VPHYSICS_DEBUG_OVERLAY_INTERFACE_VERSION, 0);
	g_pCvar = (ICvar*)EngineFactory(CVAR_INTERFACE_VERSION, 0);
	g_pPanel = (IPanel*) ( VGUI2Factory( VGUI_PANEL_INTERFACE_VERSION , 0));
	g_pCvar = (ICvar *)CvarFactory(CVAR_INTERFACE_VERSION, 0);
	g_pEffects = (IVEfx*)EngineFactory(VENGINE_EFFECTS_INTERFACE_VERSION,0);
	g_pMatSystem = (IMaterialSystem*)MatSysFac("VMaterialSystem080",0);
	g_pSurface			= (vgui::ISurface*)		VGUIFactory		(VGUI_SURFACE_INTERFACE_VERSION,0);
	g_pPhysicAPI = (IPhysicsSurfaceProps *)PhysicFactory(VPHYSICS_SURFACEPROPS_INTERFACE_VERSION, NULL);
	g_pMatSystemSurface	= (IMatSystemSurface*)	g_pSurface->QueryInterface(MAT_SYSTEM_SURFACE_INTERFACE_VERSION); 
	g_pModelRender = (IVModelRender*)EngineFactory(VENGINE_HUDMODEL_INTERFACE_VERSION,0);
	g_pVGUILocalize	= (ILocalize*)	VGUI2Factory(VGUI_LOCALIZE_INTERFACE_VERSION,0);
	g_pEventManager2 = (IGameEventManager2*) EngineFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2,0 );
	g_pPrediction = (IPrediction*)ClientFactory(VCLIENT_PREDICTION_INTERFACE_VERSION,0);
	/*g_cAimbot.dwTraceFilter = dwFindPattern((DWORD)GetModuleHandle("client.dll"),0x300000,(BYTE*)"\x55\x8B\xEC\x8B\x55\x10\x8B\xC1\x8B\x4D\x08\x89\x48\x04\x8B\x4D\x0C", "xxxxxxxxxxxxxxxxx" );
	g_cAimbot.dwGetBulletTypeParameters= dwFindPattern((DWORD)GetModuleHandle("client.dll"),0x300000,(BYTE*)"\x55\x8B\xEC\x56\x8B\x75\x08\x68\x00\x00\x00\x00\x56\xE8\x00\x00\x00\x00\x83\xC4\x08\x84\xC0", "xxxxxxxx????xx????xxxxx" );*/

		DWORD dwGlobals = dwFindPattern( ( DWORD )GetModuleHandle( "engine.dll" ), 0x653000, ( PBYTE ) "\x68\x00\x00\x00\x00\x50\x50\xFF\x12", "x????xxxx" ) + 0x1;
		g_pGlobals = ( CGlobalVarsBase* )*( PDWORD )dwGlobals;
		//Msg("\nGlobals: [0x%x]\n", g_pGlobals);

	g_pRenderView = (IVRenderView*)( EngineFactory( VENGINE_RENDERVIEW_INTERFACE_VERSION ,0) );
	DWORD* pdwPanelVMT = (PDWORD)*(PDWORD)g_pPanel;

	MEMORY_BASIC_INFORMATION Mbi;

	if(VirtualQuery((LPVOID)&pdwInputVMT[8], &Mbi, sizeof(Mbi)))
	{
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
		g_dwOrgCreateMove = pdwInputVMT[8];
		pdwInputVMT[8] = (DWORD)&new_GetUserCmd;
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwInputVMT[8], sizeof(DWORD));
		SecureZeroMemory(&Mbi, sizeof(Mbi));
	}

	//if(VirtualQuery((LPVOID)&pdwClientVMT[11], &Mbi, sizeof(Mbi)))
	//{
	//	VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
	//	g_dwOrgHudUpdate = pdwClientVMT[11];
	//	pdwClientVMT[11] = (DWORD)&new_HudUpdate;
	//	VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
	//	FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwClientVMT[11], sizeof(DWORD));
	//	SecureZeroMemory(&Mbi, sizeof(Mbi));
	//}

	DWORD dwOldProtect;
	DWORD* pdwMR = (PDWORD)*(PDWORD)g_pModelRender;

	if(VirtualQuery((LPVOID)&pdwPanelVMT[41], &Mbi, sizeof(Mbi)))
	{
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
		g_dwOrgPaintTraverse = pdwPanelVMT[41];
		pdwPanelVMT[41] = (DWORD)&new_PaintTraverse;
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwPanelVMT[41], sizeof(DWORD));
		SecureZeroMemory(&Mbi, sizeof(Mbi));
	}

	//if(VirtualQuery((LPVOID)&pdwPanelVMT[41], &Mbi, sizeof(Mbi)))
	//{
	//	VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
	//	g_dwOrgPaintTraverseNPC = pdwPanelVMT[41];
	//	pdwPanelVMT[41] = (DWORD)&new_PaintTraverseNPC;
	//	VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
	//	FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwPanelVMT[41], sizeof(DWORD));
	//	SecureZeroMemory(&Mbi, sizeof(Mbi));
	//}


	DWORD* pdwMatSysVMT = (PDWORD)*(PDWORD)g_pMatSystem;

	if(VirtualQuery((LPVOID)&pdwMatSysVMT[71], &Mbi, sizeof(Mbi)))
	{
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
		g_dwOrgFindMaterial = pdwMatSysVMT[71];
		pdwMatSysVMT[71] = (DWORD)&new_FindMaterial;
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwMatSysVMT[71], sizeof(DWORD));
		SecureZeroMemory(&Mbi, sizeof(Mbi));
	}

	if(VirtualProtect(&pdwClientVMT[35], 4, PAGE_EXECUTE_READWRITE, &dwOldProtect)) //VTABLE 35
	{
		g_dwOrgFrameStageNotify = pdwClientVMT[35];
		pdwClientVMT[35] = (DWORD)&new_FrameStageNotify;
		VirtualProtect(&pdwClientVMT[35], 4, dwOldProtect, &dwOldProtect);
	}

	if(VirtualQuery((LPVOID)&pdwMR[19], &Mbi, sizeof(Mbi)))
	{
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
		g_dwOrgDrawelExecute = pdwMR[19];
		pdwMR[19] = (DWORD)&DrawelExecute;
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwMR[19], sizeof(DWORD));
		SecureZeroMemory(&Mbi, sizeof(Mbi));
	}

	font = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font, "sketchflow print normal", 11, 500, 0, 0, 0x200);
    //g_pSurface->SetFontGlyphSet( font, "Arial Black", 14, 0 , 0, 0, 0x200 );

	font2 = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font2, "sketchflow print normal", 11, 500, 0, 0, 0x200);

	if(VirtualQuery((LPVOID)&pdwClientVMT[21], &Mbi, sizeof(Mbi)))
	{
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, PAGE_EXECUTE_READWRITE, &Mbi.Protect);
		g_dwOrgCreateMove = pdwClientVMT[21];
		pdwClientVMT[21] = (DWORD)&new_CreateMove;
		VirtualProtect((LPVOID)Mbi.BaseAddress, Mbi.RegionSize, Mbi.Protect, 0);
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)&pdwClientVMT[21], sizeof(DWORD));
		SecureZeroMemory(&Mbi, sizeof(Mbi));
	}

	if(GNetworkedVariables.StoreNetworkedVariableInfo(g_pClient))
	{
		//GNetworkedVariables.HookTableProp("DT_CSPlayer", "m_angEyeAngle[1]", AAAY);
		GNetworkedVariables.HookTableProp("DT_CSPlayer", "m_angEyeAngles[0]", AAAX);

	}

	g_pOffsets.offs_simulationtime = GetOffset("DT_BaseEntity", "m_flSimulationTime");
	//g_pCvar->FindVar("cl_extrapolate")->AddFlags(~FCVAR_CHEAT);


	DetourFunctionWithTrampoline((PBYTE)PeekMessageA_t, (PBYTE)hkPeekMessageA);
	DetourFunctionWithTrampoline((PBYTE)SetCursorPos_t, (PBYTE)hkSetCursorPos);
	DetourFunctionWithTrampoline((PBYTE)GetCursorPos_t, (PBYTE)hkGetCursorPos);

	gUtils.lel();
	gUtils.InitRessources();

	return false;
}//add cvar to console stuff so like playerlist_add STEAMID or NAME from console real css console

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	if(dwReason == DLL_PROCESS_ATTACH)
	{
        CreateThread(0, 0, ( LPTHREAD_START_ROUTINE)HookThread, 0, 0, 0);
		return TRUE;
	}
	return FALSE;
}



