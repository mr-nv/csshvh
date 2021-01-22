#pragma once;
#include "main.h"

#define WEAPON_NULL					0
#define WEAPON_AK47					1
#define WEAPON_AUG					2
#define WEAPON_AWP					3
#define WEAPON_DEAGLE				4
#define WEAPON_ELITES				5
#define WEAPON_FAMAS				6
#define WEAPON_FIVESEVEN			7
#define WEAPON_G3SG1				8
#define WEAPON_GALIL				9
#define WEAPON_GLOCK18				10
#define WEAPON_M249					11
#define WEAPON_M3					12
#define WEAPON_M4A1					13
#define WEAPON_MAC10				14
#define WEAPON_MP5					15
#define WEAPON_P228					16
#define WEAPON_P90					17
#define WEAPON_SCOUT				18
#define WEAPON_SG550				19  
#define WEAPON_SG552				20 
#define WEAPON_TMP					21
#define WEAPON_UMP45				22
#define WEAPON_USP45				23
#define WEAPON_XM1014				24
#define WEAPON_KNIFE				25
#define WEAPON_FLASHBANG			26 
#define WEAPON_HE_GRENADE			27
#define WEAPON_SMOKE_GRENADE		28 
#define WEAPON_C4					29

struct WeaponInfo_s
{
int weaponID;
int penetration;
int damage;
float maxRange;
float rangeModifier;
int bulletsPerShot;
int ammoType;
float penetrationRange;
float penetrationPower;
};

class cNospread
{
public:
   static VOID GetSpreadFix(UINT seed,QAngle& vIn,QAngle& vOut );
   static C_BaseCombatWeapon* GetBaseCombatActiveWeapon( C_BaseEntity* pBaseEntity );
   static int getWeaponID(const char *weaponName);
   void GetSpreadVector(unsigned int uiSeed, QAngle& qaAngles, Vector& vSpreadDir);
   void* GetSDKWeaponInfo( C_BaseCombatWeapon* weapon );
   WeaponInfo_s GetWeaponInfo( void* localPlayer, C_BaseCombatWeapon* weapon );
   const char* GetWeaponAlias( int weaponID );
   int GetWeaponID( C_BaseCombatWeapon *pWeapon );
   QAngle GetRecoil(C_BaseEntity *pMe);
   	void SmoothRecoil(CUserCmd*,C_BaseEntity*);
	int RCS(CUserCmd*cmd,C_BaseEntity* pBaseEntity);
	bool GetWeaponInfo2(C_BaseCombatWeapon*pWeapon,int iWeaponID, int &iBulletType, int &iPenetration, int &iDamage, float &flDistance, float &flRangeModifier);
	//void GetSpreadXY( UINT seed, Vector& vec, CUserCmd * pCmd );
	//void GetSpreadXY( UINT seed, Vector& vec );
	int getWeaponIDD( C_BaseCombatWeapon *pWeapon );
	//VOID GetSpreadFix( UINT seed, QAngle& vIn, QAngle& vOut );
   float GetSpreadValue();
	//void GetSpreadFix1( UINT seed, QAngle& vIn, QAngle& vOut);
    void GetNewVecSpread( IClientEntity * pLocalPlayer, Vector & vSpread );
	bool GetWeaponInfo(C_BaseCombatWeapon*pWeapon,int iWeaponID, int &iBulletType, int &iPenetration, float &iCurrentDamage, float &flCurrentDistance, float &flRangeModifier);
};

extern cNospread gNospread;// OMFG 
