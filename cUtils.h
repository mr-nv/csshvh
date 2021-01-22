#pragma once;
#include "main.h"

enum
{
	TEAM_COUNTER_TERRORIST	= 3,
	TEAM_TERRORIST			= 2
};

#define TRACE_FLAGS_ISVISIBLE 0x4600400B
#define vecView_offset   0xE4

class cUtils
{
public:



	void DrawString(int x, int y, bool bCenter,int r, int g, int b, int a, const char* text, ...);
	void DrawString1(HFont Font, bool Centered, int x, int y, DWORD Colour, const char *fmt, ... );
	void DrawString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void FPS();
	void DrawSmiley(int x, int y, float scale1, float scale2 );
	void InitRessources();
	bool WorldToScreen( const Vector &vOrigin, Vector &vScreen );
	void para1(CUserCmd*pCmd,C_BaseEntity*pBaseEntity,bool *bSendPackets,int m_TeamNum);
	void DrawExtraString2( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void DrawStringnew( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	DWORD dwFindPattern(DWORD , DWORD , BYTE* , char* );
	bool IsKeyPressed1(int iKey);
	void blackBorder(int x,int y,int w, int h);
	void DrawString2( int x, int y, int r, int g,int b,int a, bool bCenter, const char *pszText, ... );
	void DrawExtraString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter );
	void DrawCustomString( int x, int y, int r, int g,int b, bool bCenter, HFont fonttype, const char *pszText, ... );
	void FillRGBAA( int x, int y, int w, int h, DWORD dwColor );
	void Border(int x,int y,int w, int h, DWORD dwBorderColor);
	bool bKeyPressed[256];
	DWORD GetPunchAngle();
	DWORD dw_m_fFlags();
	void fillRGBA( int x, int y, int w, int h, DWORD colour );
	void outline(int x,int y,int w,int h,DWORD dwColor);
    QAngle GetRecoil(C_BaseEntity *pMe);
	void GetSpreadVector(unsigned int uiSeed, QAngle& qaAngles, Vector& vSpreadDir);
	bool bDataCompare(const BYTE* , const BYTE* , const char* );
	void pTraceLine( const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter *pFilter, trace_t *ptr );
	void TextW( vgui::HFont font, int x, int y, int r, int g, int b, int a, wchar_t *pszString );
	void CenterText( vgui::HFont font, int x, int y, int r, int g, int b, int a, char *text, ... );
	Vector &GetEyePositionNormal(C_BaseEntity* pEntity);
	void TextA( vgui::HFont font, int x, int y, int r, int g, int b, int a, char *pszString );
	void DrawSprite( int x, int y, int r, int g,int b, int a, const char *pszText, ... );
	bool TransformVector( Vector v, Vector &s );
	Vector GetBasePlayerFlags( C_BaseEntity* pEntity );
	void DrawWindow(int x,int y,int w,int h,char* title);
	void PrintText( int x, int y, DWORD dwColor, const char *pszText, ... );
	void FontInit( void );
	void Normalize(Vector &vIn, Vector &vOut);
	bool CanFire( C_BaseEntity* localPlayer );
	int dwTraceFilter;
	int dwGetTextureInformation;
	int dwGetBulletTypeParameters;
	bool GetVisible(Vector vEnd);
	void FillRGBA( int x, int y, int w, int h, int r, int g,int b, int a );
	bool ScreenTransform( const Vector &point, Vector &screen );
	void FillRGBA1( int x, int y, int w, int h, DWORD dwColor );
	void lel();
	Color GetTeamColor( CBaseEntity *pEntity, bool Visible );
	void Unlock();
	Vector GetEyePosition( C_BaseEntity* pEntity );
	//Vector GetEyePosition( C_BaseEntity* pEntity );
	bool IsVisible( C_BaseEntity* pEntity );
	CBaseEntity* GetLocalEntity();
	CBaseEntity* GetEntityByIndex( int idx );
	int GetBaseEntityTeamNum( C_BaseEntity* pEntity );

	Vector GetVelocity( CBaseEntity* pBaseEntity );
	Vector GetBaseVelocity( CBaseEntity* pBaseEntity );

	int GetMaxEntities();
private:
	int m_iHealth;
	int m_iTeamNum;
	int m_LifeState;
	int m_fFlags;
	int m_vecViewOffset;
	int m_hActiveWeapon;
	int m_bDucked;
	int m_ArmorValue;
	int m_vecPunchAngle;
	int m_nTickBase;
	int m_flNextPrimaryAttack;
	int m_flFlashDuration;
	int m_flFlashMaxAlpha;
	int m_iFOV;
	int m_vecVelocity;
	int m_angEyeAngles;
	int moveparent;
	int m_vecBaseVelocity;
	int m_Smiley;
	vgui::HFont font;
	vgui::HFont m_Font;
	vgui::HFont m_hcsd;
	vgui::HFont kik;

};

extern cUtils gUtils;