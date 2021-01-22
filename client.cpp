#include "main.h"
#include "time.h"

bool m_bFirstAttack;
float m_flAttackTtime;

std::vector<IMaterial*> g_vecMapTextures;
std::vector<IMaterial*> g_vecPlayerTextures;

DWORD g_dwOrgGetUserCmd;

CUserCmd* __stdcall new_GetUserCmd( int seq )
{
	DWORD GetUserCmd = *( DWORD* )( ( DWORD ) g_pInput + 0xC4 ) + ( seq % 90 << 6 );
	CUserCmd *pCmd = ( CUserCmd* ) GetUserCmd;


	/*if(g_vars.nospread){*/
	pCmd->random_seed = 165;
	pCmd->command_number = 2087;
	//}

	return pCmd;
}

IMaterial* ICreateMaterial( bool shouldIgnoreZ, bool isWireframe = false )
{
	static int created = 0;

	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"VGUI/white\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$nocull\" \"1\"\
		\n\t\"$nofog\" \"1\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"1\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
	};

	static const char baseType[] = "VertexLitGeneric";


	// this holds the material
	char material[512];

	sprintf_s( material, sizeof( material ), tmp, baseType, ( shouldIgnoreZ ) ? 1 : 0, ( isWireframe ) ? 1 : 0 );


	// make a unique name for our material
	char name[512];

	sprintf_s( name, sizeof( name ), "custom_material_%i.vmt", created );


	++created;


	// construct keyvalues based on the basetype
	KeyValues *keyValues = new KeyValues( baseType );


	// load material into our instance of keyvalues
	keyValues->LoadFromBuffer( name, material, 0, 0 );


	// create the actual material
	IMaterial *createdMaterial = g_pMatSystem->CreateMaterial(baseType,keyValues);


	createdMaterial->IncrementReferenceCount();


	return createdMaterial;
}

class MyColor
{
public: 
	float r,g,b,a;
	MyColor(float R,float G,float B,float A);

};
MyColor::MyColor(float R,float G,float B,float A)
{
	r = R;
	g = G;
	b = B;
	a = A;
}

void ForceMaterial(MyColor Color,IMaterial *Material,bool bColor = true,bool bForceMat = true)
{
	if ( bColor )
	{
		float Temp[3] = { Color.r , Color.g, Color.b };
		float Alpha = Color.a;
		g_pRenderView->SetBlend(Alpha);
		g_pRenderView->SetColorModulation(Temp);
	}

	if(bForceMat)
		g_pModelRender->ForcedMaterialOverride(Material);
}
int chams = 1;
typedef void(__thiscall*DrawModelExecute_t)(void*thisptr, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld );
DWORD g_dwOrgDrawelExecute;
void __stdcall DrawelExecute( const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld )
{
	//Interfaces->ModelRender->Function<DrawModelExecute_t>(E_Indexes::DrawModelExecute)(thisptr,state,pInfo,pCustomBoneToWorld);
	static MyColor Color(0.0f,0.0f,0.0f,0.0f);

	static IMaterial *In = ICreateMaterial(true),*Out = ICreateMaterial(false),*Wire = ICreateMaterial(true,true);

	std::string ModelName = g_pModelinfo->GetModelName( pInfo.pModel );

	bool Active = false;

	if ( ModelName.find( "models/player" ) != std::string::npos )
	{

		Color = MyColor(0.0f,0.0f,0.0f,0.0f);
		ForceMaterial(Color,Wire);


		//Interfaces->ModelRender->Function<DrawModelExecute_t>(E_Indexes::DrawModelExecute)(thisptr,state,pInfo,pCustomBoneToWorld);

		C_BaseEntity *OthersPlayers = (C_BaseEntity*)g_pEntList->GetClientEntity(pInfo.entity_index);

		if(OthersPlayers && ((*(int*)((DWORD)OthersPlayers + 0x94)) > 0 ))//remplace gethealth by theoffset yo u know and getrender shit by the offset m_clrRender i think and getteamnumbert shouldnt be a problem then it should works after
		{
			if( ((*(int*)((DWORD)OthersPlayers + 0x94)) < 500) || ((*(color32*)((DWORD)OthersPlayers + 0x58)).a < 255.f) )
			{
				if(chams)
				{
					if((*(int*)((DWORD)OthersPlayers + 0x9c)) == 2)
					{
						Color = MyColor(1.0f,0.0f,0.0f,1.0f);
					}
					else if((*(int*)((DWORD)OthersPlayers + 0x9c)) == 3) 
					{
						Color = MyColor(0.0f,0.0f,0.8f,1.0f);
					}
					else
					{
						Color = MyColor(0.0f,0.0f,0.0f,1.0f);
					}

					ForceMaterial(Color,In);
				}
				else if(chams == 1)
				{
					Color = MyColor(0.0f,0.0f,0.0f,1.0f);
					ForceMaterial(Color,In);
				}
			}

			((DrawModelExecute_t)g_dwOrgDrawelExecute)(g_pModelRender,state,pInfo,pCustomBoneToWorld);
			//get offsets instead of gethealth ect
			if( ((*(int*)((DWORD)OthersPlayers + 0x94)) < 500) || ((*(color32*)((DWORD)OthersPlayers + 0x58)).a < 255.f) )
			{
				if(chams)
				{
					if( (*(int*)((DWORD)OthersPlayers + 0x9c)) == 2)
					{
						Color = MyColor(1.0f,0.0f,0.0f,1.0f);
					}
					else if((*(int*)((DWORD)OthersPlayers + 0x9c)) == 3) 
					{
						Color = MyColor(0.0f,0.0f,0.8f,1.0f);
					}
					else
					{
						Color = MyColor(1.0f,1.0f,1.0f,1.0f);
					}

					ForceMaterial(Color,Out);
				}
				else if(chams == 1)
				{
					Color = MyColor(1.0f,1.0f,1.0f,1.0f);
					ForceMaterial(Color,Out);
				}

				Active = true;
			}
		}
		else if(chams == 1)
		{
			Color = MyColor(1.0f,1.0f,1.0f,1.0f);
			ForceMaterial(Color,Wire);

			((DrawModelExecute_t)g_dwOrgDrawelExecute)(g_pModelRender,state,pInfo,pCustomBoneToWorld);

			Color = MyColor(1.0f,1.0f,1.0f,1.0f);
			ForceMaterial(Color,In);

			((DrawModelExecute_t)g_dwOrgDrawelExecute)(g_pModelRender,state,pInfo,pCustomBoneToWorld);

			Color = MyColor(1.0f,1.0f,1.0f,1.0f);
			ForceMaterial(Color,Out);

			Active = true;
		}
	}

	((DrawModelExecute_t)g_dwOrgDrawelExecute)(g_pModelRender,state,pInfo,pCustomBoneToWorld);

	if(Active)
	{
		ForceMaterial(MyColor(0,0,0,0),0,0);
	}
}

void PrintText( int x, int y, DWORD dwColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );

	wsprintfW( szString, L"%S", szBuffer );

	g_pMatSystemSurface->DrawSetTextPos( x, y );
	g_pMatSystemSurface->DrawSetTextFont( font );
	g_pMatSystemSurface->DrawSetTextColor( Color(RED(dwColor),GREEN(dwColor),BLUE(dwColor),ALPHA(dwColor)) );
	g_pMatSystemSurface->DrawPrintText( szString, wcslen( szString ) );
}

//Private AAA by Raklatif
void AAAX(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	float flPitch = pData->m_Value.m_Float;
	flPitch -= 0.087929; //Fix Headup Reb0rn by Everyone Pasta

	if(flPitch > 180)
		flPitch -= 360;

	flPitch = clamp(flPitch, -90, 90);

	static bool JitterTick[MAX_PLAYERS];
	bool switchedTemp = JitterTick[((C_BaseEntity*)(pStruct))->index];

	JitterTick[((C_BaseEntity*)(pStruct))->index] = (flPitch == 90);

	if (flPitch == -90)
	{
		if (switchedTemp)
			flPitch = 90;
	}

	*(float*)pOut = flPitch;

}

void AAAY(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	float flYaw = pData->m_Value.m_Float;

	flYaw -= 0.087929;//them pitchs man

	static bool JitterFix[MAX_PLAYERS];
	bool jitTemporary = JitterFix[((C_BaseEntity*)(pStruct))->index];

	JitterFix[((C_BaseEntity*)(pStruct))->index] = (flYaw >= 180 && flYaw <= 360);

	if (jitTemporary && (flYaw >= 0 && flYaw <= 180))
	{
		flYaw += 359;
	}
	flYaw = flYaw - (int)(flYaw / 360) * 360;
	if (flYaw < -180)
	{
		flYaw = flYaw + 360;
	}
	else if (flYaw > 180)
	{
		flYaw = flYaw - 360;
	}

	*(float*)pOut = flYaw;


}

void ClearMapTextures()
{
	g_vecMapTextures.clear();
	g_vecPlayerTextures.clear();
}
void SetTexturesSolid()
{
	for (int i = 0;i < g_vecMapTextures.size();i++)
		g_vecMapTextures[i]->ColorModulate( 0.3f, 0.3f, 0.2f);
	//g_vecMapTextures[i]->AlphaModulate( 1.0f );
}
void SetTexturesTransparent()
{
	try
	{
		for (int i = 0;i < g_vecMapTextures.size();i++)
		{
			g_vecMapTextures[i]->AlphaModulate( 0.5f );
			g_vecMapTextures[i]->ColorModulate( 0.5f, 0.5f, 0.5f);
		}
	}catch(...){ return; }
}

bool bIngame = false;
DWORD g_dwOrgFindMaterial;
IMaterial* __stdcall new_FindMaterial( char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix )
{
	IMaterial* pTemp = NULL;

	try{
		_asm
		{
			PUSH pComplainPrefix
				PUSH complain
				PUSH pTextureGroupName
				PUSH pMaterialName
				CALL g_dwOrgFindMaterial
				MOV pTemp, EAX
		}
	}catch (...) {
		return NULL;
	}
	_asm pushad;
	if (pMaterialName && pTextureGroupName )
	{
		if(g_pEngine->IsInGame())
		{
			ConVar *r_skybox=g_pCvar->FindVar("r_skybox");
			ConVar *r_3dsky=g_pCvar->FindVar("r_3dsky");
			ConVar *gl_clear=g_pCvar->FindVar("gl_clear");
			r_skybox->SetValue(0); r_3dsky->SetValue(0); gl_clear->SetValue(1);
			bIngame = true;
		}
		else
		{
			if (bIngame)
			{
				bIngame = false;
			}
			if(strstr(pMaterialName,"models\\players"))
				g_vecPlayerTextures.push_back(pTemp);
			if(strstr(pTextureGroupName,"World"))
				g_vecMapTextures.push_back(pTemp);

			if (	strstr(pMaterialName,"wood")
				||	strstr(pMaterialName,"WOOD")
				||	strstr(pMaterialName,"door")
				||	strstr(pMaterialName,"DOOR")
				||	strstr(pMaterialName,"gate")
				||	strstr(pMaterialName,"GATE")
				||	strstr(pMaterialName,"box")
				||	strstr(pMaterialName,"BOX") )
				g_vecMapTextures.push_back( pTemp );

		}
	}
	_asm popad;
	return pTemp;
}

DWORD g_dwOrgPush3DView;
void __stdcall new_Push3DView( const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes )
{
	_asm
	{
		PUSH frustumPlanes
			PUSH pRenderTarget
			PUSH nFlags
			PUSH view
			CALL g_dwOrgPush3DView
	}	
}

DWORD g_dwOrgInKeyEvent;
int __stdcall new_IN_KeyEvent ( int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding )
{
	int RetValue;
	__asm
	{
		PUSH pszCurrentBinding
			PUSH keynum
			PUSH eventcode
			CALL g_dwOrgInKeyEvent
			MOV RetValue, EAX;

	}
	return RetValue;
}

void FakeDuck(CUserCmd*Cmd, C_BasePlayer*LocalPlayer, bool**SendPacket)
{
	if ((Cmd->buttons & IN_DUCK) && (LocalPlayer->m_vecAbsVelocity.Length() < 300.f))
	{

		static int Ticks = 2;
		if (Ticks <= 0)
		{
			Cmd->viewangles.y -= 230;  //wie hoch oder niedrig ich gucken soll
			Cmd->buttons &= ~IN_DUCK;
			**SendPacket = false;
			Ticks = 2;
		}
		else
		{
			**SendPacket = true;
			Cmd->viewangles.y -= 92;  // in welche richting ich gucken soll
			Ticks--;
		}
	}
}
void fakesideways( C_BaseEntity *localPlayer, CUserCmd *cmd , bool *bSendPacket, int force, int FakelagType, bool isstatic)
{
	int Force = force;
	cmd->viewangles.x = 180.0f;
	if(FakelagType == 0 || FakelagType == 1 )
	{
		if(g_vars.AntiAimtype > 0)
		{
			static int Ticks = Force;
			if (Ticks <= 0)
			{
				cmd->viewangles.y -= 180.0f;
				*bSendPacket = true;
				Ticks = Force;
			}
			else 
			{
				cmd->viewangles.y -= 270.0f;
				*bSendPacket = false;
				Ticks--;
			}
		}
		else
		{
			static int Ticks = Force;
			if (Ticks <= 0)
			{
				cmd->viewangles.y -= 180.0f;
				*bSendPacket = true;
				Ticks = Force;
			}
			else 
			{
				cmd->viewangles.y -= 270.0f;
				*bSendPacket = false;
				Ticks--;
			}
		}

	}

	if(FakelagType == 2 || FakelagType == 3 )
	{
		static bool first;

		if(!(g_vars.AntiAimtype > 0))
		{
			if(first)
			{
				first = false; 		
				cmd->viewangles.y -= 180.0f;		
				*bSendPacket  = true;
			}
			else
			{		
				cmd->viewangles.y -= 270.0f;
				first = true;
				*bSendPacket = false;
			}
		}
		else 
		{
			if(first)
			{
				first = false; 		
				cmd->viewangles.y -= 180.0f;	
				*bSendPacket  = true;
			}
			else
			{		
				cmd->viewangles.y -= 270.0f;
				first = true;
				*bSendPacket = false;
			}
		}

		static int Ticks = 0;
		static bool Packet_Drop = false;
		bool Reset_Counter = false;
		if(Packet_Drop)
			*bSendPacket = false;
		if(Packet_Drop&&Ticks>4) // 5 or 7 //4 !
		{
			Reset_Counter = true;
			Packet_Drop = false;
		}
		else if(!Packet_Drop&&Ticks>2) //2 or 4 //2 !
		{
			Reset_Counter = true;
			Packet_Drop = true;
		}

		Ticks++;
		if(Reset_Counter)
			Ticks = 0;

	}
}



int GetTeam(C_BaseEntity* pEntity)
{
	int m_iTeamNum = *(int*)((DWORD)pEntity + 0x9C);
	return m_iTeamNum;
}

bool IsAlivePlayer(C_BaseEntity* pEntity)
{
	char szLifeState = *(char*)((DWORD)pEntity + 0x93);

	return (szLifeState == LIFE_ALIVE);
}

static void AimAtTarget(CUserCmd* Cmd, C_BaseEntity* LocalPlayer)
{
	if (!LocalPlayer)
		return;

	Vector EyePos = Fakelagfix.PredictTheEyePosition(LocalPlayer);

	player_info_t m_pInfo;
	float flBestDis = 8192.0f;

	for (int i = 64; i >= 1; --i)
	{
		if (i == g_pEngine->GetLocalPlayer())
			continue;

		C_BaseEntity* TargetPlayer = (C_BaseEntity*)g_pEntList->GetClientEntity(i);

		if (TargetPlayer == NULL)
			continue;
		int GetHealth = *(int*)((DWORD)TargetPlayer + 0x94);
		if ((GetTeam(TargetPlayer) == GetTeam(LocalPlayer))
			|| (TargetPlayer->IsDormant())
			|| !IsAlivePlayer(TargetPlayer)
			|| !g_pEngine->GetPlayerInfo(i, &m_pInfo)
			|| GetHealth <= 0)
		{
			continue;
		}

		Vector FinalTargetPosition = Fakelagfix.PredictTheEyePosition(TargetPlayer);

		if (flBestDis > g_cAimbot.GetRadius(EyePos, TargetPlayer))
		{
			flBestDis = g_cAimbot.GetRadius(EyePos, TargetPlayer);
			g_cAimbot.CalcAngle(EyePos, FinalTargetPosition, Cmd->viewangles);
		}
	}
}

BYTE m_MoveType( C_BaseEntity *pLocal )
{ 
	return *( BYTE* )( ( DWORD )pLocal + 0x178 );
}

bool weaponsknife()
{
	C_BaseEntity*pLocalPlayer = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocalPlayer);
	if(!pWeapon)
		return false;
	int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
	bool MiscWpn = ((iWeaponID == 0 || iWeaponID == 25 || iWeaponID == 26 || iWeaponID == 27 || iWeaponID == 28 || iWeaponID == 29) ? true : false);
	if(MiscWpn)
		return true;
	return false;
}

DWORD g_dwOrgCreateMove;
void __stdcall new_CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	SetTexturesTransparent();

	_asm
	{
		PUSH active
			PUSH input_sample_frametime
			PUSH sequence_number
			CALL g_dwOrgCreateMove
	}

	DWORD_PTR EBPT;

	_asm mov EBPT, ebp;

	bool *bSendPackets = (bool*)(*(DWORD*)EBPT - 0x1);

	*bSendPackets = true;

	if ( !g_pEngine->IsInGame() || !g_pInput )
		return;

	CInput::CVerifiedUserCmd *g_pVerifiedCommands = *(CInput::CVerifiedUserCmd**)( (DWORD)g_pInput + 0xC8 );

	if ( !g_pVerifiedCommands )
		return;

	CInput::CVerifiedUserCmd *pVerified = &g_pVerifiedCommands[ sequence_number % MULTIPLAYER_BACKUP ];

	CUserCmd* pCmd = g_pInput->GetUserCmd( sequence_number );

	//pCmd == CUserCmd
	if ( !pCmd || !pVerified )
		return;  

	C_BaseEntity*pBaseEntity = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	C_BaseCombatWeapon * pWeapon = gNospread.GetBaseCombatActiveWeapon(pBaseEntity);

	Vector penis = *(Vector*)((DWORD)pBaseEntity + 0xF4);
	QAngle OldAngle = pCmd->viewangles,OldAngleFORS = pCmd->viewangles;

	int iFlags = *(PINT)((DWORD)pBaseEntity + 0x350);

	float Speed = sqrt((penis[0] * penis[0])
		+ (penis[1] * penis[1]));

	float Tickrate;

	if (g_pGlobals->interval_per_tick * 100 > 1) Tickrate = 1.1;
	else Tickrate = 1;

	float Value = (8.15 - Tickrate) - (Speed / 340);

	if (Speed > 160 && Speed < 420)
	{
		Value = (4.6 - Tickrate) - (Speed / 340);
	}
	if (Speed > 420)
	{
		Value = (3 - Tickrate) - (Speed / 1000);
	}
	if (Value <= 0.275)
	{
		Value = 0.275;
	}

	if(!(iFlags & FL_ONGROUND))
	{
		static float OldY;
		float Difference = AngleNormalize(OldAngleFORS.y - OldY);
		if (abs(Difference) < Value)
		{
			static bool Flip = false;
			if (Flip)
			{
				OldAngle.y -= Value;
				pCmd->sidemove = -400;
				Flip = false;
			}
			else
			{
				OldAngle.y += Value;
				pCmd->sidemove = 400;
				Flip = true;
			}
		}
		else
		{
			if (Difference > 0.0f)
			{
				pCmd->sidemove = -400;
			}
			if (Difference < 0.0f)
			{
				pCmd->sidemove = 400;
			}
		}

		OldY = OldAngleFORS.y;
	}


	Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	QAngle qMove, qRealView(pCmd->viewangles);
	VectorAngles(vMove, qMove);
	static bool bShoot = true;
	//----------------------------------//
	QAngle aimout;
	bool bAim;
	QAngle aimalways(0, 0, 0);

	if(g_cAimbot.weaponsawp())
	{
		g_cAimbot.MainP100AWP(pCmd, aimout, bAim, aimalways);
	}
	else
	{
		g_cAimbot.Main(pCmd);
	}

	//if(g_vars.bcachingMethod == 1) //caching playertime in createmove.
	//Fakelagfix.Cache();

	Fakelagfix.GetConstantViewlag();

	if(g_cAimbot.GetAimTarget() != -1) //Should allso chek 4 bullettime
	{
		int nOldTC = pCmd->tick_count;
		pCmd->tick_count = Fakelagfix.GetTickCorrection(g_cAimbot.GetAimTarget());
	}
	bool inAir = (pCmd->buttons &IN_JUMP && !(iFlags&FL_ONGROUND) && !(iFlags&FL_PARTIALGROUND));

	if(inAir)
		pCmd->buttons &= ~IN_JUMP; 


	g_pCvar->FindVar("sv_client_min_interp_ratio")->SetValue("0");
	g_pCvar->FindVar("cl_interp_ratio")->SetValue("0");
	g_pCvar->FindVar("cl_interp")->SetValue("0.0152"); //0.0152

	g_vars.fakelagfix ? g_pCvar->FindVar("cl_interpolate")->SetValue(0) : g_pCvar->FindVar("cl_interpolate")->SetValue(1);
	//Fakelagfix.FastAwp(pBaseEntity);

	static QAngle engel;
	float lez = (engel.y - qRealView.y);
	lez = AngleNormalize(lez);
	engel = qRealView;

	static bool bOldBullet;

	if(pCmd->buttons & IN_ATTACK)
	{
		if(gUtils.CanFire(pBaseEntity))
			bOldBullet = true;
		else
		{
			pCmd->buttons &= ~IN_ATTACK;
		}
	}


	/*if ((pCmd->buttons & IN_ATTACK ))
	{
		QAngle PunchAngle = *(QAngle*)((DWORD)pBaseEntity + 0xE48);
		pCmd->viewangles -= PunchAngle * 1.97f;
		QAngle QSpreadAngles;
		gNospread.GetSpreadFix(pCmd->random_seed,pCmd->viewangles,QSpreadAngles);
		pCmd->viewangles += QSpreadAngles;
	}*/

	bool bAntiAim = false;
	static int iAntiAimStart = 0;
	static int iAintiAim = 1;
	int   g_iAntiAimType = 1, g_iFakeLaggEnd = 4;
	static bool bFlip = true;
	static int iFlip = 0;

	C_BasePlayer*pBasePlayer = (C_BasePlayer*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	int m_iTeamNum = *(int*)((DWORD)pBaseEntity + 0x9C);

	if(pWeapon)
	{
		int m_iShots = 0;
		int m_iShotsFired = *(int*)((DWORD)pBasePlayer + 0x1430);
		int m_iClip1 = *(int*)((DWORD)pWeapon + 0x8BC);
		float m_flNextPrimaryAttack = *(float*)((DWORD)pWeapon + 0x878);
		int m_iTeamNum = *(int*)((DWORD)pBaseEntity + 0x9C);
		int m_nTickBase = *(int*) + ((DWORD)pBasePlayer + 0x10EC);
		static bool flick,flipflick,flipflickfix,flippé;
		float curtime = m_nTickBase * g_pGlobals->interval_per_tick;
		if ((pCmd->buttons & IN_ATTACK ))
		{
			QAngle qRecoil = gNospread.GetRecoil(pBaseEntity);
			QAngle QSpreadAngles;
			gNospread.GetSpreadFix(pCmd->random_seed,pCmd->viewangles,QSpreadAngles);
			QAngle QAntiAimAngleShootStatic( (180 - pCmd->viewangles.x) - qRecoil.x + QSpreadAngles.x,-((180 - pCmd->viewangles.y) - (-qRecoil.y) + QSpreadAngles.y), pCmd->upmove);
			QAngle QAntiAimAngleShootMoveAble( pCmd->viewangles.x - qRecoil.x + QSpreadAngles.x,pCmd->viewangles.y - qRecoil.y + QSpreadAngles.y, pCmd->upmove);



			/*pCmd->viewangles.x = 180.087936f;
			AimAtTarget(pCmd,pBaseEntity);
			fakesideways(pBasePlayer,pCmd,bSendPackets,7,2,g_vars.AntiAimtype);*/
			//pCmd->viewangles.x = 180.087936f;
			if(m_MoveType(pBaseEntity) != MOVETYPE_LADDER)
			{
			AimAtTarget(pCmd,pBaseEntity);
			fakesideways(pBasePlayer,pCmd,bSendPackets,5,3,g_vars.AntiAimtype);
			}

			if(g_cAimbot.weaponsawp())
			{
				*bSendPackets = true;
			}
			else
			{
				*bSendPackets = false;
			}


			pCmd->viewangles = QAntiAimAngleShootStatic;

			Vector Direction( pCmd->forwardmove, pCmd->sidemove, pCmd->upmove );

			float Velocity = Direction.Length2D();

			VectorNormalize( Direction );

			QAngle Angles;
			VectorAngles( Direction, Angles );

			float delta = ( pCmd->viewangles.y - OldAngle.y );
			float yaw = DEG2RAD( delta + Angles.y );

			if((pCmd->viewangles.x > 89.0f) || ( pCmd->viewangles.x < -89.0f))
				pCmd->forwardmove = ( -cos( yaw ) * Velocity );
			else
				pCmd->forwardmove = ( cos( yaw ) * Velocity );

			pCmd->sidemove = ( sin( yaw ) * Velocity );
		}
		else
		{
			//make thirdperson view

			//pCmd->viewangles.x = 180.087936f;
			if(m_MoveType(pBaseEntity) != MOVETYPE_LADDER)
			{
			AimAtTarget(pCmd,pBaseEntity);
			fakesideways(pBasePlayer,pCmd,bSendPackets,5,3,g_vars.AntiAimtype);
			}

			//fakecrouch	
			if (m_MoveType(pBaseEntity) != MOVETYPE_LADDER && !weaponsknife() && !inAir)
				gUtils.para1(pCmd,pBasePlayer,bSendPackets,m_iTeamNum);

			//EDGE
			if (m_MoveType(pBaseEntity) != MOVETYPE_LADDER && pBaseEntity->m_vecAbsVelocity.Length() < 300.f && !weaponsknife() && !inAir)
				g_cAimbot.EDGE(pBaseEntity, pCmd, 0);


			Vector Direction( pCmd->forwardmove, pCmd->sidemove, pCmd->upmove );

			float Velocity = Direction.Length2D();

			VectorNormalize( Direction );

			QAngle Angles;
			VectorAngles( Direction, Angles );

			float delta = ( pCmd->viewangles.y - OldAngle.y );
			float yaw = DEG2RAD( delta + Angles.y );

			if((pCmd->viewangles.x > 89.0f) || ( pCmd->viewangles.x < -89.0f))
				pCmd->forwardmove = ( -cos( yaw ) * Velocity );
			else
				pCmd->forwardmove = ( cos( yaw ) * Velocity );

			pCmd->sidemove = ( sin( yaw ) * Velocity );
		}
	}

	pVerified->m_cmd = *pCmd;
	pVerified->m_crc =  pCmd->GetChecksum();
}

DWORD g_dwOrgFrameStageNotify;
void __stdcall new_FrameStageNotify( ClientFrameStage_t curStage )
{

	C_BaseEntity *pMe;
	QAngle *PunchAngle, OldPunch;
	bool bShouldRestore = false;

	if( g_pEngine->IsInGame() )
	{
		pMe = dynamic_cast<C_BaseEntity*>( g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() ) );
	}


	if( curStage == FRAME_RENDER_START )
	{
		if( g_pEngine->IsInGame() )
		{
			if( pMe && !pMe->IsDormant() )
			{
				if( g_cAimbot.IsAlive( pMe ) )
				{
					PunchAngle = reinterpret_cast<QAngle*>( (size_t)pMe + (0xDDC + 0x6C) );
					if( *PunchAngle != QAngle( 0, 0, 0 ) )
					{
						OldPunch = *PunchAngle;
						*PunchAngle = QAngle( 0, 0, 0 );
						bShouldRestore = true;
					}
				}
			}
		}
	}


	_asm
	{
		PUSH curStage
			MOV ECX, g_pClient
			CALL g_dwOrgFrameStageNotify
	}

	if( curStage == FRAME_RENDER_START )
	{
		if( bShouldRestore )
		{
			*PunchAngle = OldPunch;
		}
	}

	if( curStage == FRAME_NET_UPDATE_END && g_pEngine->IsInGame() ) //FRAME_NET_UPDATE_END
	{
		//Fakelagfix.Cache(); 
		//Caching aimbot positions (hitboxes) here would give you much better accuracy.
		//if(g_vars.bcachingMethod == 0)
		//{
		Fakelagfix.Cache(); // Chaching player time.
		//}
	}



}


void FillRGBA( int x, int y, int w, int h, DWORD colour )
{
	g_pMatSystemSurface->DrawSetColor( 255, 0, 0, 255 );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}

void FillRGBA2( int x, int y, int w, int h, DWORD colour )
{
	g_pMatSystemSurface->DrawSetColor( 0, 0, 255, 255 );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}

void FillRGBA1( int x, int y, int w, int h, DWORD colour )
{
	g_pMatSystemSurface->DrawSetColor( RED(colour), GREEN(colour), BLUE(colour), ALPHA(colour) );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}

void Healthbar(int x, int y, int w, int h, DWORD colour)
{
	DWORD BG_BLACK = COLORCODE(0,0,0,255);
	FillRGBA(x,y,w,4,BG_BLACK); //Background
	FillRGBA(x+0.5,y+0.5,w,3,colour); //Health
	gUtils.Border(x,y,w,4,BG_BLACK); //Border
}

Vector GetVecOrigin(C_BaseEntity* pEntity)
{
	return *(Vector*)((DWORD)pEntity + 0x2CC);
}

bool ScreenTransforme( const Vector &point, Vector &screen )
{
	float w;
	const VMatrix &worldToScreen = g_pEngine->WorldToScreenMatrix();
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w		 = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;
	bool behind = false;
	if( w < 0.001f ){
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}
	return behind;
}

void GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter )
{
	if ( pBaseEnt ){
		Vector vMin, vMax;
		pBaseEnt->GetRenderBounds( vMin, vMax );
		vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
		vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
	}
}

bool WorldToScreen( const Vector &vOrigin, Vector &vScreen )
{
	if( ScreenTransforme(vOrigin , vScreen) == false ){
		int iScreenWidth, iScreenHeight;
		g_pEngine->GetScreenSize( iScreenWidth, iScreenHeight );
		float x = iScreenWidth / 2;
		float y = iScreenHeight / 2;
		x += 0.5 * vScreen.x * iScreenWidth + 0.5;
		y -= 0.5 * vScreen.y * iScreenHeight + 0.5;
		vScreen.x = x;
		vScreen.y = y;
		return true;
	}
	return false;
} 

bool TransformVector( Vector v, Vector &s )
{
	if( ScreenTransforme( v, s ) == false )
	{
		int sw, sh;
		g_pEngine->GetScreenSize( sw, sh );
		float x = sw / 2;
		float y = sh / 2;
		x += 0.5 * s.x * sw + 0.5;
		y -= 0.5 * s.y * sh + 0.5;
		s.x = x;
		s.y = y;
		return true;
	}
	return false;
}

CBaseEntity* GetEntityByIndexes( int idx )
{
	if( g_pEntList == NULL ) return NULL;
	IClientEntity *pClient = g_pEntList->GetClientEntity( idx );
	if( pClient == NULL ) return NULL;
	return pClient->GetBaseEntity();
}

void DrawString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... )
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );
	wsprintfW( wbuf, L"%S", szBuffer );
	int iWidth, iHeight;
	g_pMatSystemSurface->GetTextSize( font, wbuf, iWidth, iHeight );
	g_pMatSystemSurface->DrawSetTextFont( font );
	g_pMatSystemSurface->DrawSetTextColor( r, g, b, 255);
	g_pMatSystemSurface->DrawSetTextPos( x - ( bCenter ? iWidth / 2 : 0 ), y );
	g_pMatSystemSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

QAngle &GetEyeAngles(C_BaseEntity* pEntity)
{
	Vector m_VecOrigin = *(Vector*)((DWORD)pEntity + 0x2CC);
	Vector m_vecViewOffset = *(Vector*)((DWORD)pEntity + 0x0E4);
	Vector vEyePosition = (m_VecOrigin + m_vecViewOffset);
	QAngle qEyePostion = QAngle(0,0,0);
	VectorAngles(vEyePosition, qEyePostion);
	return qEyePostion;
}

matrix3x4_t &GetBoneMatrix(int iBone, C_BaseEntity* pBaseEnt)
{
	matrix3x4_t pMatrix[MAXSTUDIOBONES];
	pBaseEnt->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0);
	return pMatrix[iBone];
}	

Vector GetBonePosition(int bone_index, C_BaseEntity *pLocal, C_BaseEntity *pBaseEnt)
{
	Vector pos;
	QAngle EyeAngles = GetEyeAngles( pLocal );
	matrix3x4_t& BoneMatrix = GetBoneMatrix(bone_index, pBaseEnt);
	MatrixAngles(BoneMatrix,EyeAngles,pos);
	return pos;
}	

template<typename T> T MakePtr(void* ent, DWORD addr)
{
	return (T)((DWORD)ent + addr);
}

bool WorldToOurScreen(const Vector &Origin,Vector &Screen)
{
	bool Result = false;
	const VMatrix& WorldToScreen = g_pEngine->WorldToScreenMatrix(); 

	float w = WorldToScreen[3][0] * Origin[0] + WorldToScreen[3][1] * Origin[1] + WorldToScreen[3][2] * Origin[2] + WorldToScreen[3][3]; 
	Screen[2] = 0.0f; 

	if( w > 0.001f ) 
	{ 
		float invw = 1.0f / w; 

		int ScreenSize[2];
		g_pEngine->GetScreenSize( ScreenSize[0], ScreenSize[1] );

		Screen[0] = (ScreenSize[0] / 2.0f) + ((((WorldToScreen[0][0] * Origin[0] + WorldToScreen[0][1] * Origin[1] + WorldToScreen[0][2] * Origin[2] + WorldToScreen[0][3]) * invw) / 2.0f) * ScreenSize[0] + 0.5f); 
		Screen[1] = (ScreenSize[1] / 2.0f) - ((((WorldToScreen[1][0] * Origin[0] + WorldToScreen[1][1] * Origin[1] + WorldToScreen[1][2] * Origin[2] + WorldToScreen[1][3]) * invw) / 2.0f) * ScreenSize[1] + 0.5f); 
		Result = true;
	} 

	return Result; 
}

const wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}
DWORD g_dwOrgPaintTraverse;
void DrawPlayerBox(C_BaseEntity* pEntity, Color clr, player_info_t& chriswillfuckingrage)
{
	const matrix3x4_t& trans = *MakePtr<matrix3x4_t*>(pEntity, 0x338 - 0x30); //m_vecOrigin - 0x30

	Vector min = *MakePtr<Vector*>(pEntity, 0x19c + 0x20); //m_Collision + m_vecMins
	Vector max = *MakePtr<Vector*>(pEntity, 0x19c + 0x2c); //m_Collision + m_vecMaxs
	int flags = *(int*)((DWORD)pEntity + 0x350); //m_fFlags
	max.z = (flags&FL_DUCKING) ? 50 : 70;
	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++)
		VectorTransform(points[i], trans, pointsTransformed[i]);

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	if (!WorldToOurScreen(pointsTransformed[3], flb) || !WorldToOurScreen(pointsTransformed[5], brt)
		|| !WorldToOurScreen(pointsTransformed[0], blb) || !WorldToOurScreen(pointsTransformed[4], frt)
		|| !WorldToOurScreen(pointsTransformed[2], frb) || !WorldToOurScreen(pointsTransformed[1], brb)
		|| !WorldToOurScreen(pointsTransformed[6], blt) || !WorldToOurScreen(pointsTransformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}
	float x = left;
	float y = bottom;
	float w = right - left;
	float h = top - bottom;

	g_pSurface->DrawSetColor(0,0,0,255);
	//g_pSurface->DrawOutlinedRect(x + 1, y + 1, x + w - 1, y + h - 1);
	g_pSurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
	g_pSurface->DrawOutlinedRect(x + 1, y + 1, x + w - 1, y + h - 1);


	g_pSurface->DrawSetColor(clr);
	g_pSurface->DrawOutlinedRect(x, y, x + w, y + h);

	int health = *(int*)((DWORD)pEntity + 0x94); //m_iHealth
	int ohp = health;
	if (health > 100)
		health = 100;

	float iMathens = h / 100;

	int armor = *(int*)((DWORD)pEntity + 0x1498); //m_ArmorValue

	g_pSurface->DrawSetColor(0, 0, 0, 255);
	g_pSurface->DrawOutlinedRect(x - 6, y - 1, x - 2, y + h + 1);

	iMathens = h / 100;
	g_pSurface->DrawSetColor(0, 0, 0, 255);
	g_pSurface->DrawFilledRect(x - 5, y, x - 3, y + h);

	g_pSurface->DrawSetColor(ohp > health ? Color(255, 255, 255, 255) : Color((100 - health)*2.55, health*2.55, 0, 255));
	g_pSurface->DrawFilledRect(x - 5, y + h - (iMathens*health), x - 3, y + h);



}

void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce){//drawing
#define RED_COLOR COLORCODE(255,0,0,255)
#define WHITE_COLOR COLORCODE(255,255,255,255)

	_asm
	{
		PUSH allowForce
			PUSH forceRepaint
			PUSH vguiPanel
			MOV ECX, g_pPanel
			CALL g_dwOrgPaintTraverse
	}
	//	gEvent.RegisterSelf();
	int iScreenSize[2];
	g_pEngine->GetScreenSize(iScreenSize[0], iScreenSize[1]);
	int iScreenCenter[2] = { iScreenSize[0] * 0.5, iScreenSize[1] * 0.5 };
	const char* pszPanelName = g_pPanel->GetName(vguiPanel);
	if(pszPanelName[0] == 'M' 
		&& pszPanelName[3] == 'S' 
		&& pszPanelName[9] == 'T'
		&& pszPanelName[12] == 'P')
	{
		//PrintText(5,5, WHITE_COLOR, /*PowerProductions VIP - July 06 2016*/XorStr<0x93,36,0xA9419AF1>("\xC3\xFB\xE2\xF3\xE5\xC8\xEB\xF5\xFF\xE9\xFE\xEA\xF6\xCF\xCF\xD1\x83\xF2\xEC\xF6\x87\x85\x89\xE0\xDE\xC0\xD4\x8E\x9F\x86\x91\x80\x83\x85\x83"+0xA9419AF1).s);

		new_Menu.DrawMenu2(g_vars.pos_bx, g_vars.pos_by, g_vars.pos_bw, g_vars.pos_bh, "GUI TEST"); //not working, so what!

		//draw menuenz
		gMouse.DrawMouse();
		gMouse.ClickHandler();

		C_BaseEntity*pLocal = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
		player_info_t pinfo;
		for(int index = 1; index <= g_pEntList->GetMaxEntities(); index++)
		{
			if (g_pEngine->IsInGame())
			{
				if (index != g_pEngine->GetLocalPlayer())
				{
					C_BaseEntity* BaseEnt = GetEntityByIndexes(index);
					if (BaseEnt == NULL)
						continue;
					if (BaseEnt->entindex() == pLocal->entindex())
						continue;
					if (stricmp(BaseEnt->GetClientClass()->GetName(), "CCSPlayer") == 0){
						player_info_t pinfo;
						int health = *(int*)((DWORD)BaseEnt + 0x94);
						if (health <= 0)
							continue;
						if (!g_cAimbot.IsAlive(BaseEnt))
							continue;
						if (!g_pEngine->GetPlayerInfo(BaseEnt->entindex(), &pinfo))
							continue;
						if (BaseEnt->IsDormant())
							continue;
						DrawPlayerBox(BaseEnt, Color(255,0,0,255), pinfo);
					}
				}
			}
		}
	}
}