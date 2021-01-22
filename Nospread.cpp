#include "Nospread.h"
#include "main.h"

cNospread gNospread;

bool cNospread::GetWeaponInfo2(C_BaseCombatWeapon*pWeapon,int iWeaponID, int &iBulletType, int &iPenetration, int &iDamage, float &flDistance, float &flRangeModifier)
				 {
					 bool bPistolBit = false;//*(PBOOL)((DWORD)pWeapon + 0x1824 );
					 bool bRifleBit = false;//*(PBOOL)((DWORD)pWeapon + 0x1828 );
					 
					 switch(iWeaponID)
					 {
					 case WEAPON_NULL:
						 iBulletType = 0;
						 iPenetration = 0;
						 iDamage = 0;
						 flDistance = 0.0f;
						 flRangeModifier = 0.0f;
						 break;
					 case WEAPON_P228:
						 iBulletType = 9;
						 iPenetration = 1;
						 iDamage = 40;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.8f;
						 break;
					 case WEAPON_GLOCK18:
						 iBulletType = 8;
						 iPenetration = 1;
						 iDamage = 25;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.75f;
						 break;
					 case WEAPON_SCOUT:
						 iBulletType = 2;
						 iPenetration = 1;
						 iDamage = 75;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.98f;
						 break;
					 case WEAPON_MAC10:
						 iBulletType = 8;
						 iPenetration = 1;
						 iDamage = 29;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.82f;
						 break;
					 case WEAPON_AUG:
						 iBulletType = 2;
						 iPenetration = 2;
						 iDamage = 32;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.96f;
						 break;
					 case WEAPON_ELITES:
						 iBulletType = 6;
						 iPenetration = 1;
						 iDamage = 45;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.75f;
						 break;
					 case WEAPON_FIVESEVEN:
						 iBulletType = 10;
						 iPenetration = 1;
						 iDamage = 25;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.885f;
						 break;
					 case WEAPON_UMP45:
						 iBulletType = 8;
						 iPenetration = 1;
						 iDamage = 30;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.82f;
						 break;
					 case WEAPON_SG550:
						 iBulletType = 3;
						 iPenetration = 2;
						 iDamage = 70;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.98f;
						 break;
					 case WEAPON_GALIL:
						 iBulletType = 3;
						 iPenetration = 2;
						 iDamage = 30;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.98f;
						 break;
					 case WEAPON_FAMAS:
						 iBulletType = 3;
						 iPenetration = 2;
						 iDamage = 30;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.96f;
						 break;
					 case WEAPON_USP45:
						 iBulletType = 8;
						 iPenetration = 1;
						 iDamage = bPistolBit ? 30.0f : 34.0f;;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.79f;
						 break;
					 case WEAPON_AWP:
						 iBulletType = 5;
						 iPenetration = 3;
						 iDamage = 115;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.99f;
						 break;
					 case WEAPON_MP5:
						 iBulletType = 6;
						 iPenetration = 1;
						 iDamage = 26;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.84f;
						 break;
					 case WEAPON_M249:
						 iBulletType = 4;
						 iPenetration = 2;
						 iDamage = 32;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.97f;
						 break;
					 case WEAPON_M4A1:
						 iBulletType = 3;
						 iPenetration = 2;
						 iDamage = 33;
						 flDistance = 8192.0f;
						 flRangeModifier = bRifleBit ? 0.95f : 0.97f;
						 break;
					 case WEAPON_TMP:
						 iBulletType = 6;
						 iPenetration = 1;
						 iDamage = 26;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.84f;
						 break;
					 case WEAPON_G3SG1:
						 iBulletType = 2;
						 iPenetration = 3;
						 iDamage = 80;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.98f;
						 break;
					 case WEAPON_DEAGLE:
						 iBulletType = 1;
						 iPenetration = 2;
						 iDamage = 54;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.81f;
						 break;
					 case WEAPON_SG552:
						 iBulletType = 3;
						 iPenetration = 2;
						 iDamage = 33;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.955f;
						 break;
					 case WEAPON_AK47:
						 iBulletType = 2;
						 iPenetration = 2;
						 iDamage = 36;
						 flDistance = 8192.0f;
						 flRangeModifier = 0.98f;
						 break;
					 case WEAPON_P90:
						 iBulletType = 10;
						 iPenetration = 1;
						 iDamage = 26;
						 flDistance = 4096.0f;
						 flRangeModifier = 0.84f;
						 break;
					 default:
						 iBulletType = 0;
						 iPenetration = 0;
						 iDamage = 0;
						 flDistance = 0.0f;
						 flRangeModifier = 0.0f;
						 break;
					 }

					 if(iBulletType != 0)
						 return true;
					 else
						 return false;
				 }

static CBaseEntity* GetEntityByIndex( int Index )
{
	if( g_pEntList == NULL )
		return NULL;

	IClientEntity *pClient = g_pEntList->GetClientEntity( Index );

	return pClient->GetBaseEntity();
}

static CBaseEntity* pLocalEntity()
{
	if( g_pEngine == NULL )
		return NULL;

	return GetEntityByIndex( g_pEngine->GetLocalPlayer() );
}

C_BaseCombatWeapon* cNospread::GetBaseCombatActiveWeapon( C_BaseEntity* pBaseEntity )
{
	EHANDLE pActiveWeapon = *reinterpret_cast< EHANDLE* >((DWORD)pBaseEntity + 0xD80);//m_hActiveWeapon
	return (C_BaseCombatWeapon*)g_pEntList->GetClientEntityFromHandle(pActiveWeapon);
}

const char* cNospread::GetWeaponAlias( int weaponID )
{
	static void* weaponIDToAlias = 0;

	if ( !weaponIDToAlias )
	{
		weaponIDToAlias = (void*)((DWORD)GetModuleHandleA("client.dll") + 0x213C00);
	}

	char* weaponAlias = 0;

	_asm
	{
		PUSH weaponID
			CALL weaponIDToAlias
			ADD ESP, 4
			MOV weaponAlias, EAX
	}

	return weaponAlias;
}

typedef int ( __thiscall *GetWeaponID_t )( void *thisptr );

int cNospread::GetWeaponID( C_BaseCombatWeapon *pWeapon )
{
	//todo: sigs?
	//client Base 58fb0000 Size 6a2000 \x8B\x82\x00\x00\x00\x00\x51\x8B\x8E\x00\x00\x00\x00\xD9\x1C\x24 xx????xxx????xxx
	return reinterpret_cast<GetWeaponID_t>( *reinterpret_cast<PDWORD>( *reinterpret_cast<PDWORD>( pWeapon ) + 0x5B4 ) )( pWeapon );
}

void* cNospread::GetSDKWeaponInfo( C_BaseCombatWeapon* weapon )
{
	static void* lookupWeaponInfoSlot = 0;
	static void* getFileWeaponInfoFromHandle = 0;

	if ( !lookupWeaponInfoSlot )
	{
		lookupWeaponInfoSlot = (void*)((DWORD)GetModuleHandleA("client.dll") + 0x1CB3C0 );
	}

	if ( !getFileWeaponInfoFromHandle )
	{
		getFileWeaponInfoFromHandle = (void*)((DWORD)GetModuleHandleA("client.dll") + 0x1CB2B0);
	}

	char weaponName[128];

	sprintf_s( weaponName, sizeof( weaponName ), "weapon_%s", GetWeaponAlias( GetWeaponID( weapon ) ) );

	void* weaponInfo = 0;
	_asm
	{
		LEA EDX, weaponName
			PUSH EDX
			CALL lookupWeaponInfoSlot
			ADD ESP, 4
			MOVZX EDI, AX
			PUSH EDI
			CALL getFileWeaponInfoFromHandle
			ADD ESP, 4
			MOV weaponInfo, EAX
	}

	return weaponInfo;
}

WeaponInfo_s cNospread::GetWeaponInfo( void* localPlayer, C_BaseCombatWeapon* weapon )
{
	static void* getBulletTypeParameters = 0;

	if ( !getBulletTypeParameters )
	{
		getBulletTypeParameters = (void*)((DWORD)GetModuleHandleA("client.dll") + 0x1E2C90);
	}

	void* sdkWeaponInfo = GetSDKWeaponInfo( weapon );

	WeaponInfo_s weaponInfo;

	weaponInfo.penetration = *reinterpret_cast<int*>( (size_t)sdkWeaponInfo + 0x884 );
	weaponInfo.damage = *reinterpret_cast<int*>( (size_t)sdkWeaponInfo + 0x888 );
	weaponInfo.maxRange = *reinterpret_cast<float*>( (size_t)sdkWeaponInfo + 0x88C );
	weaponInfo.rangeModifier = *reinterpret_cast<float*>( (size_t)sdkWeaponInfo + 0x890 );
	weaponInfo.bulletsPerShot = *reinterpret_cast<int*>( (size_t)sdkWeaponInfo + 0x894 );
	weaponInfo.ammoType = *reinterpret_cast<int*>( (size_t)sdkWeaponInfo + 0x6c0 );

	weaponInfo.weaponID = GetWeaponID( weapon );


	if ( weaponInfo.weaponID == WEAPON_M4A1 )
	{
		bool specialWeaponMode = *reinterpret_cast<bool*>( (size_t)weapon + 0x9d8 );

		if ( specialWeaponMode == 1 )
		{
			weaponInfo.rangeModifier = .95f;
		}
	}

	if ( weaponInfo.weaponID == WEAPON_GLOCK18 )
	{
		bool specialWeaponMode = *reinterpret_cast<bool*>( (size_t)weapon + 0x9d0 );

		if( specialWeaponMode )
		{
			int burstShotsRemaining = *reinterpret_cast<int*>( (size_t)weapon + 0x9dc );

			if ( burstShotsRemaining > 0 )
			{
				weaponInfo.damage = 18;
				weaponInfo.rangeModifier = .9f;
			}
		}
	}

	if ( weaponInfo.weaponID == WEAPON_USP45 )
	{
		bool specialWeaponMode = *reinterpret_cast<bool*>( (size_t)weapon + 0x9d0 );

		if ( specialWeaponMode )
		{
			weaponInfo.damage = 30;
		}
	}

	_asm
	{
		LEA ECX, weaponInfo.penetrationRange
			PUSH ECX
			LEA EDX, weaponInfo.penetrationPower
			PUSH EDX
			PUSH weaponInfo.ammoType
			MOV ECX, localPlayer
			MOV ECX, DWORD PTR DS:[ECX]
		CALL getBulletTypeParameters
	}

	return weaponInfo;
}

int cNospread::getWeaponID(const char *weaponName){
	C_BaseCombatWeapon *m_pWeapon = GetBaseCombatActiveWeapon(pLocalEntity());
	if(!m_pWeapon)
		return WEAPON_NULL;
	if(strstr(weaponName,"_knife_t.mdl"))
		return WEAPON_KNIFE;
	if(strstr(weaponName,"_knife_ct.mdl"))
		return WEAPON_KNIFE;
	if(strstr(weaponName,"_pist_deagle.mdl"))
		return WEAPON_DEAGLE;
	if(strstr(weaponName,"_pist_elite.mdl"))
		return WEAPON_ELITES;
	if(strstr(weaponName,"_pist_fiveseven.mdl"))
		return WEAPON_FIVESEVEN;
	if(strstr(weaponName,"_pist_glock18.mdl"))
		return WEAPON_GLOCK18;
	if(strstr(weaponName,"_pist_p228.mdl"))
		return WEAPON_P228;
	if(strstr(weaponName,"_pist_usp.mdl"))
		return WEAPON_USP45;
	if(strstr(weaponName,"_rif_ak47.mdl"))
		return WEAPON_AK47;
	if(strstr(weaponName,"_rif_aug.mdl"))
		return WEAPON_AUG;
	if(strstr(weaponName,"_rif_m4a1.mdl"))
		return WEAPON_M4A1;
	if(strstr(weaponName,"_rif_famas.mdl"))
		return WEAPON_FAMAS;
	if(strstr(weaponName,"_rif_galil.mdl"))
		return WEAPON_GALIL;
	if(strstr(weaponName,"_rif_sg552.mdl"))
		return WEAPON_SG552;
	if(strstr(weaponName,"_mach_m249para.mdl"))
		return WEAPON_M249;
	if(strstr(weaponName,"_smg_tmp.mdl"))
		return WEAPON_TMP;
	if(strstr(weaponName,"_smg_mac10.mdl"))
		return WEAPON_MAC10;
	if(strstr(weaponName,"_smg_p90.mdl"))
		return WEAPON_P90;
	if(strstr(weaponName,"_smg_ump45.mdl"))
		return WEAPON_UMP45;
	if(strstr(weaponName,"_smg_mp5.mdl"))
		return WEAPON_MP5;
	if(strstr(weaponName,"_snip_g3sg1.mdl"))
		return WEAPON_G3SG1;
	if(strstr(weaponName,"_snip_scout.mdl"))
		return WEAPON_SCOUT;
	if(strstr(weaponName,"_snip_sg550.mdl"))
		return WEAPON_SG550;
	if(strstr(weaponName,"_snip_awp.mdl"))
		return WEAPON_AWP;
	if(strstr(weaponName,"_shot_xm1014.mdl"))
		return WEAPON_XM1014;
	if(strstr(weaponName,"_shot_m3super90.mdl"))
		return WEAPON_M3;
	if(strstr(weaponName,"_eq_flashbang.mdl"))
		return WEAPON_FLASHBANG;
	if(strstr(weaponName,"_eq_fraggrenade.mdl"))
		return WEAPON_HE_GRENADE;
	if(strstr(weaponName,"_eq_smokegrenade.mdl"))
		return WEAPON_SMOKE_GRENADE;
	if(strstr(weaponName,"_c4.mdl"))
		return WEAPON_C4;
	return WEAPON_NULL;
}

	static float GetWeaponSpread( C_BaseCombatWeapon* pWeapon )
		{
			float flResult = 0.0f;

			__asm
			{
				MOV EAX, 0x5E0;
				MOV ESI, pWeapon;
				MOV EDX, DWORD PTR DS:[ESI];
				MOV EAX, DWORD PTR DS:[EDX + EAX];
				MOV ECX, ESI;
				CALL EAX;
				FSTP flResult;
			}

			return flResult;
		}

		static float GetWeaponCone( C_BaseCombatWeapon* pWeapon )
		{
			float flResult = 0.0f;

			__asm
			{
				MOV EAX, 0x5E4;
				MOV ESI, pWeapon;
				MOV EDX, DWORD PTR DS:[ESI];
				MOV EAX, DWORD PTR DS:[EDX + EAX];
				MOV ECX, ESI;
				CALL EAX;
				FSTP flResult;
			}

			return flResult;
		}

		static VOID UpdateAccuracyPenalty( C_BaseCombatWeapon* pWeapon )
		{
			__asm
			{
				MOV EAX, 0x5A0
				MOV ESI, pWeapon
				MOV EDX, DWORD PTR DS:[ ESI ]
				MOV EAX, DWORD PTR DS:[ EDX + EAX ]
				MOV ECX, ESI
				CALL EAX
			}
		}

		static VOID GetSpreadXY( UINT seed, Vector& vec )
		{
			int iSeed = seed & 255;
			iSeed++;
			RandomSeed(iSeed);

			Vector vSpread;

			C_BaseCombatWeapon* m_pWeapon = gNospread.GetBaseCombatActiveWeapon( pLocalEntity() );

			if ( !m_pWeapon )
				return;

			UpdateAccuracyPenalty( m_pWeapon );

			vSpread.x = GetWeaponSpread(m_pWeapon);
			vSpread.y = GetWeaponCone(m_pWeapon);

			UpdateAccuracyPenalty( m_pWeapon );

			float flA = RandomFloat( 0.0f, 2.f * M_PI );
			float flB = RandomFloat( 0.0f, vSpread.x );
			float flC = RandomFloat( 0.0f, 2.f * M_PI );
			float flD = RandomFloat( 0.0f, vSpread.y );

			UpdateAccuracyPenalty( m_pWeapon );

			vec.x = ( cos ( flA ) * flB ) + ( cos ( flC ) * flD );
			vec.y = ( sin ( flA ) * flB ) + ( sin ( flC) * flD );
	
			return;
		}

		 VOID cNospread::GetSpreadFix( UINT seed, QAngle& vIn, QAngle& vOut )
		{
			Vector forward, right, up, vecDir;
			Vector view, spread;
			QAngle dest;
			AngleVectors( vIn, &forward, &right, &up );
			GetSpreadXY( seed, spread );

			view.x = forward.x + spread.x * right.x + spread.y * up.x;
			//view.x = 8192.0f * vecDir.x;

			view.y = forward.y + spread.x * right.y + spread.y * up.y;
			//view.y = 8192.0f * vecDir.y;

			view.z = forward.z + spread.x * right.z + spread.y * up.z;
			//view.z = 8192.0f * vecDir.z;

			VectorAngles( view, dest );
			vOut.x = vIn.x - dest.x;
			vOut.y = vIn.y - dest.y;
	
			return;
		}

void cNospread::GetSpreadVector(unsigned int uiSeed, QAngle& qaAngles, Vector& vSpreadDir)
{
	Vector vForward, vRight, vUp, vSpread;
	QAngle qaDir;

	uiSeed &= 255;
	uiSeed++;

	RandomSeed(uiSeed);

	C_BaseCombatWeapon* m_pWeapon = GetBaseCombatActiveWeapon(pLocalEntity());

	if ( !m_pWeapon )
		return;

	vSpread.x = GetWeaponSpread(m_pWeapon);
	vSpread.y = GetWeaponCone(m_pWeapon);

	float flA = RandomFloat(0.0f, 2.f * M_PI);
	float flB = RandomFloat(0.0f, vSpread.x);
	float flC = RandomFloat(0.0f, 2.f * M_PI);
	float flD = RandomFloat(0.0f, vSpread.y);

	vSpread.x = ( cosf ( flA ) * flB ) + ( cosf ( flC ) * flD );
	vSpread.y = ( sinf ( flA ) * flB ) + ( sinf ( flC) * flD );

	AngleVectors(qaAngles, &vForward, &vRight, &vUp);

	vSpreadDir = vForward + vRight * vSpread.x + vUp * vSpread.y;
}

QAngle cNospread::GetRecoil(C_BaseEntity *pMe)
{

	//cAngle viewangles = *(cAngle*)( (int)userCommand + CMD_VIEWANGLES );
	//viewangles += ( muzzleClimb * 2.f );

	float factor = 2.f;

	QAngle qPunch = *( QAngle* )( (DWORD)pMe + (0xDDC + 0x6C) /*0xD98*/ );

	float flModifier = VectorNormalize(qPunch.Base());
	flModifier -= (flModifier * 0.5f + 10.0f) * g_pGlobals->interval_per_tick;
	qPunch *= flModifier;

	/*float len = fastSqrt(qPunch.x * qPunch.x + qPunch.y * qPunch.y); 
	if ( len > 0.0f ) 
	{
	float p = len - ( 0.5f * len + 10.0f ) * g_pGlobals->interval_per_tick; 
	if ( p < 0.0f ) p = 0.0f;
	qPunch *= p / len;
	}*/

	return qPunch * factor;
}

int cNospread::RCS(CUserCmd*cmd,C_BaseEntity* pBaseEntity)
{
	QAngle *punchs = (QAngle*) ( (DWORD)pBaseEntity + (DWORD)0xDDC + 0x6C); QAngle ppunchs = *punchs;
	float power = ppunchs.Length();
	if( power > 0.125 )
		ppunchs /= power; power -= 0.125; ppunchs *= power;
	cmd->viewangles.x -= (ppunchs.x * 2);
	cmd->viewangles.x += (ppunchs.x * 1.97);
	//cmd->viewangles.y += (ppunchs.x * 3);
	g_pEngine->SetViewAngles(cmd->viewangles);
	return (double)power;
}
