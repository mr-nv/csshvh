#pragma once;

#include "main.h"

typedef void ( __thiscall *CTraceFilterSkipTwoEntities_t )( void *thisPtr, const IHandleEntity *pPassEntity, const IHandleEntity *pPassEntity2, int collisionGroup );

class cAimbot
{
public:
	cAimbot();
	void DropTarget();
	void CalcAngle(Vector &, Vector &, QAngle &);
	bool GetVisible(Vector &vAbsStart, C_BaseEntity *pMe);
	bool GetHitboxPosition(int nIndex, int rofl);
	void GAntiAim(CUserCmd* pUserCmd, bool **sendpacket);
	bool weaponsawp();
	bool weaponsawp2();
	void PredictTarget(C_BaseEntity* pBaseEntity, Vector &vEyePos, C_BaseEntity *pMe);
	bool weaponsawp3();
	void AtTarget(CUserCmd* pUserCmd, QAngle &ang, bool& bAim, QAngle &aimalways);
	bool getvis(C_BaseEntity *TargetEntity, C_BaseEntity *LocalPlayer, const Vector &TargetPosition, const Vector &EyePos);
	void MainP100AWP(CUserCmd* pUserCmd, QAngle &ang, bool& bAim, QAngle &aimalways);
	bool GetHitboxPositiondays(int nIndex, /*int SPOT, Vector lol[12],*/ C_BaseEntity * pEnemy);
	Vector &GetPredictedEyePosition(C_BaseEntity*);
	bool IsAlive(C_BaseEntity*);
	int GetTeamNumber(C_BaseEntity*);
	void Main(CUserCmd*);
	bool KnifeBot ( Vector& vecAbsOrigin, Vector& vecEndPos, CBaseEntity *pBaseEntity );
	void EDGE( C_BaseEntity *localPlayer, CUserCmd *cmd ,float angleyaw);
	float GetRadius( Vector MyEyePosition, C_BaseEntity* pEntity );
	void MakeVector(QAngle angle, QAngle& vector);
	bool autowall( Vector nigg, Vector vPos, C_BaseEntity* pMe );
	bool CanFire( C_BaseEntity* localPlayer );
	bool __fastcall TriggerBot2(CUserCmd* pCmd, C_BaseEntity* pMe, C_BaseEntity* test );
	bool bCheckVisible( Vector &vecAbs ,Vector &vecDest, C_BaseEntity *pEnt );
	void Normalize(Vector &vIn, Vector &vOut);
	void SilentAim ( CUserCmd* cmd, QAngle angAim );
    bool AutoWall( Vector &vAbsStart,C_BaseEntity* pMe,C_BaseEntity* pPlayer, const  Vector &targetorigin);
	bool __fastcall TriggerBotT( CUserCmd* cmd, C_BaseEntity* local, C_BaseEntity* test ) ;
	bool TriggerBot(CUserCmd* pCmd,C_BaseEntity* pLocal);
	void __fastcall TriggerBot12( CUserCmd* pCmd, int *sequence_number);
	DWORD GetPunchAngle();
	void PrintText( int x, int y, DWORD dwColor, const char *pszText, ... );
//	void PredictTarget(C_BaseEntity* pBaseEntity, Vector &vEyePos, C_BaseEntity *pMe);

	float GetFov(QAngle angle, Vector src, Vector dst);
	int GetAimTarget() { return m_nTarget; }
	//int GetTotalDamage2(C_BasePlayer *LocalPlayer, WeaponInfo_s* Weapon);
	int dwTraceFilter;
	int dwGetBulletTypeParameters;

public:
	int m_nTarget;
	float m_flBestDist;
	Vector m_vPosition;
	Vector m_vecMyEyePos;
	Vector m_vLastPosition[64];
	Vector m_vFinalPosition;
	Vector m_vMyLastEyePosition;
	vgui::HFont m_Font;
};

extern cAimbot g_cAimbot;