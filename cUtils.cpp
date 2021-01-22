#include "cUtils.h"
#include "main.h"

cUtils gUtils;

CBaseEntity* cUtils::GetEntityByIndex( int idx )
{
	if( g_pEntList == NULL ) return NULL;
	IClientEntity *pClient = g_pEntList->GetClientEntity( idx );
	if( pClient == NULL ) return NULL;
	return pClient->GetBaseEntity();
}

Vector cUtils::GetEyePosition( C_BaseEntity* pEntity )
{
	Vector m_VecOrigin = *(Vector*)((DWORD)pEntity + 0x338);
	Vector m_vecViewOffset = *(Vector*)((DWORD)pEntity + 0xE8);
	Vector vEyePosition = (m_VecOrigin + m_vecViewOffset);
	return vEyePosition;
}

void cUtils::lel()
{
	//Fonts
	kik = g_pSurface->CreateFont();
	g_pMatSystemSurface->SetFontGlyphSet(kik, "Arial", 11,450,0,0,0x200);

	//m_Smiley = g_pMatSystemSurface->CreateNewTextureID();
	//g_pMatSystemSurface->DrawSetTextureFile( m_Smiley, "vgui/regegwr" , true, true);
}

void cUtils::DrawExtraString2( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... )
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

void cUtils::DrawStringnew( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... )
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

Vector cUtils::GetBasePlayerFlags( C_BaseEntity* pEntity )
{
	return pEntity->GetAbsOrigin() + *(Vector*)((DWORD)pEntity + 0x314);
}

Vector cUtils::GetVelocity( CBaseEntity* pBaseEntity )
{
	//float *pVec = (float*)( (DWORD)this + 0xEC );
	static DWORD dwOffs = m_vecVelocity;
	float *pVec = (float*)( (DWORD)pBaseEntity + dwOffs );
	return Vector( pVec[ 0 ], pVec[ 1 ], pVec[ 2 ] );
}

void cUtils::GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter )
{
	if ( pBaseEnt )
	{
		Vector vMin, vMax;
		pBaseEnt->GetRenderBounds( vMin, vMax );
		vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
	}
}

void cUtils::fillRGBA( int x, int y, int w, int h, DWORD colour )
{
	g_pMatSystemSurface->DrawSetColor( RED(colour), GREEN(colour), BLUE(colour), ALPHA(colour) );
	g_pMatSystemSurface->DrawTexturedRect( x, y, x + w, y + h );
}

void cUtils::outline(int x,int y,int w,int h,DWORD dwColor)
{
	g_pMatSystemSurface->DrawSetColor(RED(dwColor),GREEN(dwColor),BLUE(dwColor),ALPHA(dwColor));
	g_pMatSystemSurface->DrawOutlinedRect(x,y,(x + w) + 1,(y + h) + 1);
}

Vector cUtils::GetBaseVelocity( CBaseEntity* pBaseEntity )
{
	//float *pVec = (float*)( (DWORD)this + 0xEC );
	static DWORD dwOffs = m_vecBaseVelocity;
	float *pVec = (float*)( (DWORD)pBaseEntity + dwOffs );
	return Vector( pVec[ 0 ], pVec[ 1 ], pVec[ 2 ] );
}

Vector &cUtils::GetEyePositionNormal(C_BaseEntity* pEntity)
{
    Vector m_vecOrigin = *(Vector*)((DWORD)pEntity + 0x2FC);
    Vector m_vecViewOffset;
	m_vecViewOffset.x = *(float*)((DWORD)pEntity + 0x0E4);
	m_vecViewOffset.y = *(float*)((DWORD)pEntity + 0x0E8);
	m_vecViewOffset.z = *(float*)((DWORD)pEntity + 0x0EC);
	Vector vEyePosition = (m_vecOrigin + m_vecViewOffset);
	return vEyePosition;
}

DWORD cUtils::GetPunchAngle()
 {
	DWORD m_Local = 0x0D7C;
	BYTE m_vecPunchAngle = 0x6C;
	return m_Local + m_vecPunchAngle;
 }

CBaseEntity* cUtils::GetLocalEntity()
{
	if( g_pEngine == NULL ) return NULL;

	return GetEntityByIndex( g_pEngine->GetLocalPlayer() );
}

void cUtils::FontInit( void )
{
	m_Font = g_pMatSystemSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font, "Tahoma", 9,500,0,0,0x200);

	m_Smiley = g_pSurface->CreateNewTextureID();
	g_pMatSystemSurface->DrawSetTextureFile( m_Smiley, "vgui/regegwr" , true, true);
}

int cUtils::GetMaxEntities()
{
	if( g_pEntList )
	{
		return g_pEntList->GetHighestEntityIndex();
	}

	return 0;
}

void cUtils::DrawExtraString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... )
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

void cUtils::FillRGBAA( int x, int y, int w, int h, DWORD dwColor )
{
	g_pMatSystemSurface->DrawSetColor( RGBA( dwColor ) );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}

void cUtils::Border(int x,int y,int w, int h, DWORD dwBorderColor)
{
	FillRGBAA( x-1, y-1, w+2, 1 ,dwBorderColor); 
	FillRGBAA( x-1, y, 1, h-1 ,dwBorderColor );
	FillRGBAA( x+w, y, 1, h-1 ,dwBorderColor);
	FillRGBAA( x-1, y+h-1, w+2, 1 ,dwBorderColor);
}

void cUtils::InitRessources()
{
	//Fonts
	font = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font, "sketchflow print normal", 11, 500, 0, 0, 0x200);

	//m_Smiley = g_pMatSystemSurface->CreateNewTextureID();
	//g_pMatSystemSurface->DrawSetTextureFile( m_Smiley, "vgui/regegwr" , true, true);
}


bool cUtils::TransformVector( Vector v, Vector &s )
{
	if( ScreenTransform( v, s ) == false )
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






//int cUtils::GetBaseEntityTeamNum( C_BaseEntity* pEntity )
//{
//	return *reinterpret_cast< int* >( reinterpret_cast< int >( pEntity ) + NNetworkedVariables::DT_BaseEntity::m_iTeamNum->offset );
//}

//void cUtils::DrawSprite( int x, int y, int r, int g,int b, int a, const char *pszText, ... )
//{
//	if( pszText == NULL )
//		return;
//
//	va_list va_alist;
//
//	char szBuffer[1024] = { '\0' };
//	wchar_t szString[1024] = { '\0' };
//
//	va_start( va_alist, pszText );
//	vsprintf( szBuffer, pszText, va_alist );
//	va_end( va_alist );
//
//	vgui::localize()->ConvertANSIToUnicode( szBuffer, szString, sizeof( szString ) );
//
//	int wide, tall;
//	vgui::surface()->GetTextSize( m_hcsd, szString, wide, tall );
//	x -= ( wide / 2 );
//
//	g_pMatSystemSurface->DrawColoredText( m_hcsd, x, y, r, g, b, a, "%s", szBuffer );
//	
//}

bool cUtils::ScreenTransform( const Vector &point, Vector &screen )
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

bool cUtils::WorldToScreen( const Vector &vOrigin, Vector &vScreen )
{
	if( ScreenTransform(vOrigin , vScreen) == false ){
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

void cUtils::DrawString1(HFont Font, bool Centered, int x, int y, DWORD Colour, const char *fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start( va_alist, fmt );
	_vsnprintf( buf, sizeof( buf ), fmt, va_alist );
	va_end( va_alist );
	wchar_t wbuf[256];
	g_pVGUILocalize->ConvertANSIToUnicode( buf, wbuf, 256 );
	int iWidth, iHeight;
	g_pMatSystemSurface->GetTextSize( Font, wbuf, iWidth, iHeight );
	g_pMatSystemSurface->DrawSetTextFont( Font );
	g_pMatSystemSurface->DrawSetTextColor( RED(Colour),GREEN(Colour),BLUE(Colour),ALPHA(Colour) );
	g_pMatSystemSurface->DrawSetTextPos( x - ( Centered ? iWidth / 2 : 0 ), y );
	g_pMatSystemSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}



void cUtils::DrawCustomString( int x, int y, int r, int g,int b, bool bCenter, HFont fonttype, const char *pszText, ... )
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );
	wsprintfW( wbuf, L"%S", szBuffer );
	int iWidth, iHeight;
	g_pMatSystemSurface->GetTextSize( fonttype, wbuf, iWidth, iHeight );
	g_pMatSystemSurface->DrawSetTextFont( fonttype );
	g_pMatSystemSurface->DrawSetTextColor( r, g, b, 255);
	g_pMatSystemSurface->DrawSetTextPos( x - ( bCenter ? iWidth / 2 : 0 ), y );
	g_pMatSystemSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void cUtils::DrawString2( int x, int y, int r, int g,int b,int a, bool bCenter, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );
	DWORD color = COLORCODE(r,g,b,a);

	wsprintfW( szString, L"%S", szBuffer );
	int iWidth, iHeight;
	g_pMatSystemSurface->GetTextSize( font, szString , iWidth, iHeight );
	g_pSurface->DrawSetTextFont(font);
	g_pMatSystemSurface->DrawSetTextPos( x - ( bCenter ? iWidth / 2 : 0 ), y );
	g_pSurface->DrawSetTextColor( Color(RED(color),GREEN(color),BLUE(color),ALPHA(color)) );
	g_pSurface->DrawPrintText( szString, wcslen( szString ) );
}

void cUtils::blackBorder(int x,int y,int w, int h)
{
	FillRGBA( x - 1, y-1, w+2, 1 ,0,255,0,254 ); //Oppe hvor tyk den skal være
	FillRGBA( x - 1, y, 1, h-1 ,0,255,0,254 );	//<
	FillRGBA( x + w, y, 1, h-1 ,0,255,0,254 );	//>
	FillRGBA( x - 1, y+h-1, w+2, 1 ,0,255,0,254 ); //Nede
}

void cUtils::DrawString(int x, int y, bool bCenter,int r, int g, int b, int a, const char* text, ...)
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start( va_alist, text );
	vsprintf( szBuffer, text, va_alist );
	va_end( va_alist );
	wsprintfW( wbuf, L"%S", szBuffer );
	int iWidth, iHeight;
	g_pMatSystemSurface->GetTextSize( font, wbuf, iWidth, iHeight );
	g_pMatSystemSurface->DrawSetTextFont( font );
	g_pMatSystemSurface->DrawSetTextColor( r, g, b, a);
	g_pMatSystemSurface->DrawSetTextPos( x - ( bCenter ? iWidth / 2 : 0 ), y );
	g_pMatSystemSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void cUtils::Unlock()//HAHAH
{
	ConVar *consistency = g_pCvar->FindVar( "sv_consistency" );
	ConVar *cheets = g_pCvar->FindVar( "sv_cheats" );
	//if(consistency || cheets)
	//{
		//unflag
/*		if(consistency->IsFlagSet(FCVAR_CHEAT))
			consistency->m_nValue &= ~FCVAR_CHEAT;
		if(consistency->IsFlagSet(FCVAR_REPLICATED))
			consistency->m_nValue &= ~FCVAR_REPLICATED;
		if(consistency->IsFlagSet(FCVAR_PROTECTED))
			consistency->m_nValue &= ~FCVAR_PROTECTED;
		if(consistency->IsFlagSet(FCVAR_SPONLY))
			consistency->m_nValue &= ~FCVAR_SPONLY;

		if(cheets->IsFlagSet(FCVAR_CHEAT))
			cheets->m_nValue &= ~FCVAR_CHEAT;
		if(cheets->IsFlagSet(FCVAR_REPLICATED))
			cheets->m_nValue &= ~FCVAR_REPLICATED;
		if(cheets->IsFlagSet(FCVAR_PROTECTED))
			cheets->m_nValue &= ~FCVAR_PROTECTED;
		if(cheets->IsFlagSet(FCVAR_SPONLY))
			cheets->m_nValue &= ~FCVAR_SPONLY*/;

		//set
		consistency->SetValue(0);
		cheets->SetValue(1);
	//
}

void cUtils::FPS()
{
	g_pCvar->FindVar("fps_max")->SetValue("999");
	g_pCvar->FindVar("cl_ragdoll_physics_enable")->SetValue("0");
	g_pCvar->FindVar("cl_crosshairalpha")->SetValue(			"9999");	// _adjusts opacity of crosshair_//
	g_pCvar->FindVar("cl_crosshaircolor")->SetValue( 			"4");	// _adjusts scale of crosshair_//
	g_pCvar->FindVar("cl_crosshairusealpha")->SetValue( 			"1");	// _turns on opacity (0 - 1)_//
	g_pCvar->FindVar("cl_crosshairscale")->SetValue( 			"0");	// _adjusts crosshairscale_//
	g_pCvar->FindVar("cl_dynamiccrosshair")->SetValue(			"1");	// _adjusts how the crosshair opperates_//
	g_pCvar->FindVar("cl_ragdoll_physics_enable")->SetValue( 		"0");	// _determines ragdoll effect_//
	g_pCvar->FindVar("fps_max")->SetValue( 				"999");	// _caps FPS_//
	g_pCvar->FindVar("mat_picmip")->SetValue( 				"2");	// _determines game quality (0 - 2)_//
	g_pCvar->FindVar("net_graph")->SetValue( 				"1");	// _enables net_graph (mandatory)_//	
	g_pCvar->FindVar("net_graphpos")->SetValue( 				"2");	// _determines which side to display net_graph (0-3)_//	
	g_pCvar->FindVar("r_lod")->SetValue( 					"2");	// _determines level of detail of models (-1 - 2)_// 
	g_pCvar->FindVar("r_rootlod")->SetValue( 				"2");	// _base LOD in memory (0 - 3)_//
	g_pCvar->FindVar("r_3dsky")->SetValue( 				"0");	// _disables 3D Sky (trees, mini map, etc) (0 - 1)_//
	g_pCvar->FindVar("hud_centerid")->SetValue( 				"1");	// _determines where enemy name shows on screen_//
	g_pCvar->FindVar("hud_fastswitch")->SetValue( 				"1");	// _faster weapon switching (0 - 1)_//
	g_pCvar->FindVar("mat_monitorgamma")->SetValue( 			"1.6");	// _adjust in-game brightness_//
	g_pCvar->FindVar("cl_righthand")->SetValue(				"0");
	g_pCvar->FindVar("cl_allowdownload")->SetValue( 			"0");
	g_pCvar->FindVar("cl_allowupload")->SetValue(				"0");
	g_pCvar->FindVar("cl_wpn_sway_interp")->SetValue( 			"0");

	g_pCvar->FindVar("cl_scoreboard_dead_color_blue")->SetValue(			"255"); 
	g_pCvar->FindVar("cl_scoreboard_dead_color_green")->SetValue(			"255");
	g_pCvar->FindVar("cl_scoreboard_dead_color_red")->SetValue( 			"255");
	g_pCvar->FindVar("con_enable")->SetValue( 					"1");
	g_pCvar->FindVar("jpeg_quality")->SetValue( 					"100");
	g_pCvar->FindVar("overview_health")->SetValue( 				"1");
	g_pCvar->FindVar("overview_names")->SetValue( 					"1");
	g_pCvar->FindVar("overview_preferred_mode")->SetValue( 			"1");
	g_pCvar->FindVar("overview_tracks")->SetValue( 				"0");

	g_pCvar->FindVar("cl_cmdrate")->SetValue(					"67");
	g_pCvar->FindVar("cl_downloadfilter")->SetValue( 				"nosounds");
	g_pCvar->FindVar("cl_interp")->SetValue(					"0");	// _keep at 0 to always get lowest interp_//
	g_pCvar->FindVar("cl_interp_all")->SetValue( 					"0");
	g_pCvar->FindVar("cl_interp_npcs")->SetValue( 					"0");
	g_pCvar->FindVar("cl_interp_ratio")->SetValue( 				"1");
	g_pCvar->FindVar("cl_lagcompensation")->SetValue( 				"1");
	g_pCvar->FindVar("cl_pred_optimize")->SetValue( 				"1");
	g_pCvar->FindVar("cl_predictweapons")->SetValue( 				"1");
	g_pCvar->FindVar("cl_resend")->SetValue(					"6");
	//g_pCvar->FindVar("cl_smooth")->SetValue( 					"1"
	g_pCvar->FindVar("cl_smoothtime")->SetValue( 					"0.01");
	g_pCvar->FindVar("cl_timeout")->SetValue("1337");
	g_pCvar->FindVar("cl_updaterate")->SetValue(					"67");
	g_pCvar->FindVar("rate")->SetValue(						"35000");

	g_pCvar->FindVar("cl_observercrosshair")->SetValue( 				"1");
	g_pCvar->FindVar("cl_scalecrosshair")->SetValue( 				"1");
	g_pCvar->FindVar("cl_c4progressbar")->SetValue( 				"1");
	g_pCvar->FindVar("cl_autohelp")->SetValue( 					"0");
	g_pCvar->FindVar("cl_autowepswitch")->SetValue(				"0");
	g_pCvar->FindVar("cl_radar_locked")->SetValue( 				"0");
	g_pCvar->FindVar("cl_radaralpha")->SetValue( 					"250");
	g_pCvar->FindVar("cl_radartype")->SetValue( 					"1");
	g_pCvar->FindVar("cl_c4dynamiclight")->SetValue( 				"1");
	g_pCvar->FindVar("cl_detail_avoid_force")->SetValue(				"0");
	g_pCvar->FindVar("cl_detail_avoid_radius")->SetValue(				"0");
	g_pCvar->FindVar("cl_detail_avoid_recover_speed")->SetValue(			"0");
	g_pCvar->FindVar("cl_detail_max_sway")->SetValue(				"0");
	g_pCvar->FindVar("cl_drawmonitors")->SetValue( 				"0");
	g_pCvar->FindVar("cl_ejectbrass")->SetValue( 					"0");
	g_pCvar->FindVar("cl_forcepreload")->SetValue( 				"1");
	g_pCvar->FindVar("cl_logofile")->SetValue( 					"0");
	g_pCvar->FindVar("cl_rumblescale")->SetValue(					"0");
	g_pCvar->FindVar("cl_interp_threadmodeticks")->SetValue( 			"0");
	g_pCvar->FindVar("cl_disablefreezecam")->SetValue( 				"1");
	g_pCvar->FindVar("cl_nowinpanel")->SetValue( 					"1");
	g_pCvar->FindVar("cl_show_achievement_popups")->SetValue( 			"0");
	g_pCvar->FindVar("cl_clearhinthistory")->SetValue( 				"1");
	g_pCvar->FindVar("cl_detaildist")->SetValue( 					"0");
	g_pCvar->FindVar("cl_detailfade")->SetValue( 					"0");
	g_pCvar->FindVar("cl_debugrumble")->SetValue( 					"0");
	g_pCvar->FindVar("cl_playerspraydisable")->SetValue( 				"1");
	g_pCvar->FindVar("cl_showhelp")->SetValue( 					"0");
	g_pCvar->FindVar("cl_threaded_bone_setup")->SetValue( 				"0");
	g_pCvar->FindVar("cl_threaded_client_leaf_system")->SetValue( 			"0");

	g_pCvar->FindVar("mat_autoexposure_max")->SetValue(				"0");
	g_pCvar->FindVar("mat_autoexposure_min")->SetValue( 				"0");
	g_pCvar->FindVar("mat_bloomscale")->SetValue( 					"0");
	g_pCvar->FindVar("mat_bufferprimitives")->SetValue(				"1");
	g_pCvar->FindVar("mat_bumpmap")->SetValue( 					"0");
	g_pCvar->FindVar("mat_clipz")->SetValue( 					"1");
	g_pCvar->FindVar("mat_colorcorrection")->SetValue(				"0");
	g_pCvar->FindVar("mat_compressedtextures")->SetValue( 				"1");
	g_pCvar->FindVar("mat_debug_postprocessing_effects")->SetValue( 		"0");
	g_pCvar->FindVar("mat_debugdepthmode")->SetValue( 				"0");
	g_pCvar->FindVar("mat_debugdepthval")->SetValue(				"128");
	g_pCvar->FindVar("mat_debugdepthvalmax")->SetValue( 				"256");
	g_pCvar->FindVar("mat_disable_bloom")->SetValue(				"1");
	g_pCvar->FindVar("mat_disable_fancy_blending")->SetValue(			"1");
	g_pCvar->FindVar("mat_disable_lightwarp")->SetValue(				"1");
	g_pCvar->FindVar("mat_disable_ps_patch")->SetValue(				"1");
	g_pCvar->FindVar("mat_envmapsize")->SetValue( 					"0");
	g_pCvar->FindVar("mat_envmaptgasize")->SetValue( 				"0");
	g_pCvar->FindVar("mat_fastspecular")->SetValue( 				"1");
	g_pCvar->FindVar("mat_filterlightmaps")->SetValue( 				"1");
	g_pCvar->FindVar("mat_forceaniso")->SetValue( 					"0");
	g_pCvar->FindVar("mat_forcehardwaresync")->SetValue( 				"0");
	g_pCvar->FindVar("mat_forcemanagedtextureintohardware")->SetValue( 		"0");
	g_pCvar->FindVar("mat_framebuffercopyoverlaysize")->SetValue( 			"0");
	g_pCvar->FindVar("mat_hdr_enabled")->SetValue( 				"0");
	g_pCvar->FindVar("mat_hdr_level")->SetValue(					"0");
	g_pCvar->FindVar("mat_parallaxmap")->SetValue( 				"0");
	g_pCvar->FindVar("mat_reducefillrate")->SetValue(				"1");
	g_pCvar->FindVar("mat_specular")->SetValue( 					"0");
	g_pCvar->FindVar("mat_trilinear")->SetValue( 					"0");
	g_pCvar->FindVar("mat_shadowstate")->SetValue(					"0");
	g_pCvar->FindVar("mat_vsync")->SetValue( 					"0");
	g_pCvar->FindVar("mat_alphacoverage")->SetValue( 				"0");
	g_pCvar->FindVar("mat_bloom_scalefactor_scalar")->SetValue( 			"0");
	g_pCvar->FindVar("mat_maxframelatency")->SetValue( 				"0");
	g_pCvar->FindVar("mat_max_worldmesh_vertices")->SetValue( 			"0");
	g_pCvar->FindVar("mat_software_aa_blur_one_pixel_lines")->SetValue( 		"0");
	g_pCvar->FindVar("mat_software_aa_strength")->SetValue( 			"0");
	g_pCvar->FindVar("mat_software_aa_strength_vgui")->SetValue( 			"0");
	g_pCvar->FindVar("mat_software_aa_tap_offset")->SetValue( 			"0");
	g_pCvar->FindVar("mat_queue_mode")->SetValue( 					"2");
     g_pCvar->FindVar("mat_dxlevel")->SetValue(                                     "80");

	g_pCvar->FindVar("r_ambientboost")->SetValue(					"0");
	g_pCvar->FindVar("r_ambientfactor")->SetValue(					"1");
	g_pCvar->FindVar("r_decal_cullsize")->SetValue( 				"9999");
	g_pCvar->FindVar("r_decals")->SetValue( 					"2048");
	g_pCvar->FindVar("r_dopixelvisibility")->SetValue( 				"0");
	g_pCvar->FindVar("r_drawbatchdecals")->SetValue( 				"0");
	g_pCvar->FindVar("r_drawflecks")->SetValue( 					"0");
	g_pCvar->FindVar("r_drawmodeldecals")->SetValue( 				"0");
	g_pCvar->FindVar("r_dynamic")->SetValue( 					"0");
	g_pCvar->FindVar("r_eyegloss")->SetValue(					"0");
	g_pCvar->FindVar("r_eyemove")->SetValue( 					"0");
	g_pCvar->FindVar("r_eyes")->SetValue( 						"0");
	g_pCvar->FindVar("r_eyeshift_x")->SetValue( 					"0");
	g_pCvar->FindVar("r_eyeshift_y")->SetValue( 					"0");
	g_pCvar->FindVar("r_eyeshift_z")->SetValue( 					"0");
	g_pCvar->FindVar("r_eyesize")->SetValue( 					"0");
	g_pCvar->FindVar("r_flex")->SetValue( 						"0");
	g_pCvar->FindVar("r_lightaverage")->SetValue( 					"1");
	g_pCvar->FindVar("r_maxdlights")->SetValue(					"32");
	g_pCvar->FindVar("r_maxmodeldecal")->SetValue( 				"0");
	g_pCvar->FindVar("r_maxnewsamples")->SetValue(					"0");
	g_pCvar->FindVar("r_maxsampledist")->SetValue(					"0");
	g_pCvar->FindVar("r_minnewsamples")->SetValue( 				"0");
	g_pCvar->FindVar("r_norefresh")->SetValue( 					"0");
	g_pCvar->FindVar("r_occlusion")->SetValue( 					"1");
	g_pCvar->FindVar("r_PhysPropStaticLighting")->SetValue( 			"0");
	g_pCvar->FindVar("r_renderoverlayfragment")->SetValue( 			"0");
	g_pCvar->FindVar("r_ropetranslucent")->SetValue( 				"0");
	g_pCvar->FindVar("r_spray_lifetime")->SetValue(				"0");
	g_pCvar->FindVar("r_teeth")->SetValue( 					"0");
	g_pCvar->FindVar("r_worldlightmin")->SetValue( 				"0.0002");
	g_pCvar->FindVar("r_worldlights")->SetValue( 					"1");
	g_pCvar->FindVar("r_bloomtintg")->SetValue( 					"0");
	g_pCvar->FindVar("r_bloomtintb")->SetValue( 					"0");
	g_pCvar->FindVar("r_bloomtintexponent")->SetValue( 				"0");
	g_pCvar->FindVar("r_bloomtintr")->SetValue( 					"0");
	g_pCvar->FindVar("r_drawdetailprops")->SetValue( 				"0");
	g_pCvar->FindVar("r_DrawSpecificStaticProp")->SetValue( 			"0");
	g_pCvar->FindVar("r_flashlightrendermodels")->SetValue( 			"0");
	g_pCvar->FindVar("r_hunkalloclightmaps")->SetValue( 				"0");
	g_pCvar->FindVar("r_lightcache_zbuffercache")->SetValue( 			"0");
	g_pCvar->FindVar("r_pixelfog")->SetValue( 					"0");
	g_pCvar->FindVar("r_propsmaxdist")->SetValue( 					"0");
	g_pCvar->FindVar("r_staticprop_lod")->SetValue( 				"3");
	g_pCvar->FindVar("r_sse_s")->SetValue( 					"1");
	g_pCvar->FindVar("r_threaded_client_shadow_manager")->SetValue( 		"1");
	g_pCvar->FindVar("r_threaded_particles")->SetValue( 				"1");
	g_pCvar->FindVar("r_threaded_renderables")->SetValue( 				"1");
	g_pCvar->FindVar("r_queued_decals")->SetValue( 				"0");
	g_pCvar->FindVar("r_queued_post_processing")->SetValue( 			"1");
	g_pCvar->FindVar("r_queued_ropes")->SetValue( 					"1");
	//r_3dnow 					"1"
	g_pCvar->FindVar("r_sse2")->SetValue( 						"1");

	g_pCvar->FindVar("rope_averagelight")->SetValue( 				"0");
	g_pCvar->FindVar("rope_collide")->SetValue( 					"0");
	g_pCvar->FindVar("rope_rendersolid")->SetValue( 				"0");
	g_pCvar->FindVar("rope_shake")->SetValue( 					"0");
	g_pCvar->FindVar("rope_smooth")->SetValue( 					"0");
	g_pCvar->FindVar("rope_smooth_enlarge")->SetValue( 				"0");
	g_pCvar->FindVar("rope_smooth_maxalpha")->SetValue( 				"0");
	g_pCvar->FindVar("rope_smooth_maxalphawidth")->SetValue( 			"0");
	g_pCvar->FindVar("rope_smooth_minalpha")->SetValue( 				"0");
	g_pCvar->FindVar("rope_smooth_minwidth")->SetValue( 				"0");
	g_pCvar->FindVar("rope_subdiv")->SetValue( 					"0");
	g_pCvar->FindVar("rope_wind_dist")->SetValue( 					"0.01");

	g_pCvar->FindVar("r_waterforceexpensive")->SetValue( 				"0");			
	g_pCvar->FindVar("r_WaterDrawReflection")->SetValue( 				"0");		
	g_pCvar->FindVar("r_WaterDrawRefraction")->SetValue( 				"0");	// Change to 1 if you want clear water_//
	g_pCvar->FindVar("r_waterforcereflectentities")->SetValue(			"0");			
	//g_pCvar->FindVar("r_cheapwaterend")->SetValue( 				"1");
	//g_pCvar->FindVar("r_cheapwaterstart")->SetValue(				"1");			
	g_pCvar->FindVar("r_forcewaterleaf")->SetValue( 				"0");
	g_pCvar->FindVar("r_waterforcereflectentities")->SetValue( 			"0");
	g_pCvar->FindVar("mat_wateroverlaysize")->SetValue( 				"8");			
	g_pCvar->FindVar("cl_show_splashes")->SetValue( 				"0");		

	g_pCvar->FindVar("mat_shadowstate")->SetValue(					"0");
	g_pCvar->FindVar("r_shadows")->SetValue( 					"1");					
	g_pCvar->FindVar("r_shadowmaxrendered")->SetValue( 				"9");		
	g_pCvar->FindVar("r_shadowrendertotexture")->SetValue( 			"1");


	g_pCvar->FindVar("cl_phys_props_max")->SetValue( 				"0");				
	g_pCvar->FindVar("cl_ragdoll_collide")->SetValue( 				"0"); 					
	g_pCvar->FindVar("g_ragdoll_fadespeed")->SetValue( 				"0");
	g_pCvar->FindVar("g_ragdoll_lvfadespeed")->SetValue(				"0");
	g_pCvar->FindVar("violence_ablood")->SetValue( 				"1");
	g_pCvar->FindVar("violence_agibs")->SetValue( 					"1");
	g_pCvar->FindVar("violence_hblood")->SetValue( 				"1");
	g_pCvar->FindVar("violence_hgibs")->SetValue( 					"1");

	g_pCvar->FindVar("dsp_enhance_stereo")->SetValue( 				"0");
	g_pCvar->FindVar("dsp_mix_max")->SetValue( 					"0.9");
	g_pCvar->FindVar("dsp_room")->SetValue( 					"0");
	g_pCvar->FindVar("dsp_slow_cpu")->SetValue( 					"0");
	g_pCvar->FindVar("dsp_spatial")->SetValue( 					"40");
	g_pCvar->FindVar("dsp_speaker")->SetValue( 					"50");
	g_pCvar->FindVar("dsp_volume")->SetValue( 					"2.0");
	g_pCvar->FindVar("dsp_water")->SetValue(					"14");
	g_pCvar->FindVar("room_type")->SetValue( 					"0");
	g_pCvar->FindVar("snd_async_fullyasync")->SetValue( 				"0");
	g_pCvar->FindVar("snd_duckerattacktime")->SetValue( 				"0.5");
	g_pCvar->FindVar("snd_duckerreleasetime")->SetValue( 				"2.5");
	g_pCvar->FindVar("snd_duckerthreshold")->SetValue( 				"0.15");
	g_pCvar->FindVar("snd_ducktovolume")->SetValue( 				"0.55");
	g_pCvar->FindVar("snd_mixahead")->SetValue( 					"0.1");
	g_pCvar->FindVar("snd_musicvolume")->SetValue( 				"0");
	g_pCvar->FindVar("snd_noextraupdate")->SetValue( 				"1");
	g_pCvar->FindVar("snd_pitchquality")->SetValue( 				"1");
	g_pCvar->FindVar("snd_profile")->SetValue( 					"0");
	g_pCvar->FindVar("snd_surround_speakers")->SetValue( 				"0");
	g_pCvar->FindVar("soundscape_flush")->SetValue( 				"9999");
	g_pCvar->FindVar("suitvolume")->SetValue(					"0");
	g_pCvar->FindVar("voice_enable")->SetValue( 					"1");
	g_pCvar->FindVar("voice_forcemicrecord")->SetValue( 				"1");
	g_pCvar->FindVar("voice_modenable")->SetValue( 				"1"); 

	g_pCvar->FindVar("blink_duration")->SetValue( 					"0");
	g_pCvar->FindVar("budget_averages_window")->SetValue( 				"0");
	g_pCvar->FindVar("budget_background_alpha")->SetValue( 			"0");
	g_pCvar->FindVar("budget_history_numsamplesvisible")->SetValue( 		"0");
	g_pCvar->FindVar("budget_history_range_ms")->SetValue( 			"5");
	g_pCvar->FindVar("budget_peaks_window")->SetValue(				"0");
	g_pCvar->FindVar("budget_show_averages")->SetValue( 				"0");
	g_pCvar->FindVar("budget_show_history")->SetValue( 				"0");
	g_pCvar->FindVar("budget_show_peaks")->SetValue( 				"0");
	g_pCvar->FindVar("closecaption")->SetValue(					"0");
	g_pCvar->FindVar("datacachesize")->SetValue( 					"128");
	g_pCvar->FindVar("flex_smooth")->SetValue(					"0");
	g_pCvar->FindVar("gl_clear")->SetValue( 					"1");
	g_pCvar->FindVar("lod_TransitionDist")->SetValue(			        "0");
	g_pCvar->FindVar("mp_decals")->SetValue( 					"0");
	g_pCvar->FindVar("muzzleflash_light")->SetValue( 				"0");
	g_pCvar->FindVar("props_break_max_pieces")->SetValue( 				"0");
	g_pCvar->FindVar("showhitlocation")->SetValue( 				"1");
	g_pCvar->FindVar("sv_forcepreload")->SetValue( 				"1");
	g_pCvar->FindVar("texture_budget_background_alpha")->SetValue( 		"9999999");
	g_pCvar->FindVar("texture_budget_panel_height")->SetValue( 			"0");
	g_pCvar->FindVar("texture_budget_panel_width")->SetValue( 			"0");
	g_pCvar->FindVar("weapon_showproficiency")->SetValue( 				"1");
	g_pCvar->FindVar("prop_active_gib_limit")->SetValue( 				"0");
	g_pCvar->FindVar("adsp_debug")->SetValue( 					"0");
	g_pCvar->FindVar("mp_usehwmmodels")->SetValue( 				"-1");
	g_pCvar->FindVar("mp_usehwmvcds")->SetValue( 					"-1");
	g_pCvar->FindVar("soundscape_flush");
	g_pCvar->FindVar("mat_savechanges");
	g_pCvar->FindVar("clear");


	g_pCvar->FindVar("CL_MINMODELS")->SetValue("1");
	g_pCvar->FindVar("Cl_MIN_T")->SetValue("1");
}

void cUtils::TextW( vgui::HFont font, int x, int y, int r, int g, int b, int a, wchar_t *pszString )
{
	g_pMatSystemSurface->DrawSetTextColor( r, g, b, a );
	g_pMatSystemSurface->DrawSetTextFont( font );
	g_pMatSystemSurface->DrawSetTextPos( x, y );
	g_pMatSystemSurface->DrawPrintText( pszString, ( int )wcslen( pszString ), FONT_DRAW_DEFAULT );
}

//void cUtils::DrawSprite( int x, int y, int r, int g,int b, int a, const char *pszText, ... )
//{
//	if( pszText == NULL )
//		return;
//
//	va_list va_alist;
//
//	char szBuffer[1024] = { '\0' };
//	wchar_t szString[1024] = { '\0' };
//
//	va_start( va_alist, pszText );
//	vsprintf( szBuffer, pszText, va_alist );
//	va_end( va_alist );
//
//	int wide, tall;
//	vgui::surface()->GetTextSize( m_hcsd, szString, wide, tall );
//	x -= ( wide / 2 );
//
//	g_pMatSytemSurface->DrawColoredText( m_hcsd, x, y, r, g, b, a, "%s", szBuffer );
//	
//}


void cUtils::TextA( vgui::HFont font, int x, int y, int r, int g, int b, int a, char *pszString )
{
	wchar_t *pszStringWide = reinterpret_cast< wchar_t* >( malloc( ( strlen( pszString ) + 1 ) * sizeof( wchar_t ) ) );

	mbstowcs( pszStringWide, pszString, ( strlen( pszString ) + 1 ) * sizeof( wchar_t ) );

	TextW( font, x, y, r, g, b, a, pszStringWide );

	free( pszStringWide );
}

void cUtils::para1(CUserCmd*pCmd,C_BaseEntity*pBaseEntity,bool *bSendPackets,int m_TeamNum)
{
		bool bCrouchAA = false;

	if( GetAsyncKeyState( VK_CONTROL ) )
	{
		static bool bDuck = false;
		if( bDuck )
		{
			bDuck = false;
			pCmd->buttons &= ~IN_DUCK;
			*bSendPackets = false;
				pCmd->viewangles.x = 180;
				pCmd->viewangles.y -= 271.0f;


			
		}
		else
		{
			if( pCmd->buttons & IN_DUCK )
			{
				*bSendPackets = true;
				bDuck = true;
				static bool bFakeCrouch = true;
				bFakeCrouch = !bFakeCrouch;
					pCmd->viewangles.x = 180.087936f;
					pCmd->viewangles.y -= 90;
				
			}
		}
		bCrouchAA = true;
	}


	//static bool first;
	//if ((pCmd->buttons & IN_DUCK) && (pBaseEntity->m_vecAbsVelocity.Length() < 300.f))
	//{
	//	pCmd->viewangles.x = 180.087936f;
	//	static bool first;
	//	static int Ticks = 2;
	//	if (Ticks <= 0)
	//	{
	//		pCmd->viewangles.y -= 180.0f;  //wie hoch oder niedrig ich gucken soll
	//		pCmd->buttons &= ~IN_DUCK;
	//		*bSendPackets = false;
	//		first = true;
	//		Ticks = 2;
	//	}
	//	else
	//	{
	//		*bSendPackets = true;
	//		pCmd->viewangles.y -= 269.0f;  // in welche richting ich gucken soll
	//		first = false;
	//		Ticks--;
	//	}
	//	

	//}
}


void cUtils::CenterText( vgui::HFont font, int x, int y, int r, int g, int b, int a, char *text, ... )
{
	if( text == NULL ) return;

	va_list va_alist;

	char TotalBufferMaxLength[ 1024 ] = { 0 };

	memset( TotalBufferMaxLength, 0, sizeof( char ) * 1024 );

	va_start( va_alist, text );
	
	_vsnprintf( TotalBufferMaxLength + strlen( TotalBufferMaxLength ), 
		sizeof( TotalBufferMaxLength ) - strlen( TotalBufferMaxLength ), 
		text, va_alist );

	va_end( va_alist );

//	int CharLength = GMatSurface->DrawTextLen( font, TotalBufferMaxLength );

	int CharLength = strlen( TotalBufferMaxLength ) * 5;

	int xx = x - ( CharLength / 2 );

	TextA( font, xx, y, r, g, b, a, TotalBufferMaxLength );
}

bool cUtils::CanFire( C_BaseEntity* localPlayer )
{
	C_BaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(localPlayer);

	if ( !pWeapon )
	{
		return false;
	}

	float time = ( ( *(int*)((DWORD)localPlayer + 0x10EC) + 1 ) * g_pGlobals->interval_per_tick );
	bool canFire = ( time >= ( *(float*)((DWORD)pWeapon + 0x878 ) ) );

	return canFire;
}

void cUtils::GetSpreadVector(unsigned int uiSeed, QAngle& qaAngles, Vector& vSpreadDir)
{
	Vector vForward, vRight, vUp, vSpread;
	QAngle qaDir;

	uiSeed &= 255;
	uiSeed++;

	RandomSeed(uiSeed);

	vSpread.x = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	vSpread.y = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	vSpread.z = vSpread.x * vSpread.x + vSpread.y * vSpread.y;

	AngleVectors(qaAngles, &vForward, &vRight, &vUp);

	vSpreadDir = vForward + vRight * vSpread.x + vUp * vSpread.y;

	return;
}

QAngle cUtils::GetRecoil(C_BaseEntity *pMe)
{
	float factor = 2.0;

	QAngle pAngle = *( QAngle* )( (DWORD)pMe + gUtils.GetPunchAngle());

	QAngle qPunch = pAngle; float Length = VectorNormalize(qPunch.Base()); 
	Length-= (10.0 + Length * 0.5) * g_pGlobals->interval_per_tick; qPunch *= Length; 

	return pAngle * factor;
}

bool bKeyPressed1[256];
bool cUtils::IsKeyPressed1(int iKey){
	//used for menu toggle
	if (GetAsyncKeyState(iKey)){
		if (!bKeyPressed1[iKey]){
			bKeyPressed1[iKey] = true;
			return true;
		}
	}
	else
		bKeyPressed[iKey] = false;

	return false;
}

void cUtils::DrawString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... )
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

bool cUtils::GetVisible(Vector vEnd)
{
	trace_t Trace;
	Ray_t Ray;

	C_BaseEntity *pMe = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();

	Ray.Init(g_cAimbot.GetPredictedEyePosition(pMe), vEnd);
	g_pEnginetrace->TraceRay(Ray, CONTENTS_SOLID|CONTENTS_GRATE|CONTENTS_HITBOX, NULL, &Trace);

	if(Trace.fraction >= 0.97f)
		return true;

	if(Trace.fraction <= 0.70f)
		return false;

	if(Trace.startsolid || Trace.allsolid)
		return false;

	return false;
}

void cUtils::DrawSmiley( int x, int y, float scale1, float scale2 )
{
	g_pMatSystemSurface->DrawSetColor( 255, 255, 255, 255 );
	g_pMatSystemSurface->DrawSetTexture( m_Smiley );
	g_pMatSystemSurface->DrawTexturedRect( x - 512*scale1/2, y - 512*scale2/2, x + 512*scale1/2 , y + 512*scale2/2 ); //scale would be something like 30.0f/distance.GetLength()
}

bool cUtils::bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
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

DWORD cUtils::dwFindPattern(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, char* szMask)
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

void cUtils::pTraceLine( const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter *pFilter, trace_t *ptr )
{ 
     Ray_t ray; 
     ray.Init( vecAbsStart, vecAbsEnd ); 
 
     g_pEnginetrace->TraceRay( ray, mask, pFilter, ptr ); 
}

void cUtils::FillRGBA( int x, int y, int w, int h, int r, int g,int b, int a )
{
	g_pMatSystemSurface->DrawSetColor(r, g, b, a );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}

void cUtils::FillRGBA1( int x, int y, int w, int h, DWORD dwColor )
{
	g_pMatSystemSurface->DrawSetColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}

bool cUtils::IsVisible( C_BaseEntity* pEntity )
{
	
	Ray_t	ray;
	trace_t tr;
	
	ray.Init( GetEyePosition( GetLocalEntity() ), GetEyePosition( pEntity ) );

	g_pEnginetrace->TraceRay( ray, TRACE_FLAGS_ISVISIBLE, NULL, &tr );

	return ( tr.m_pEnt == pEntity || tr.fraction == 1.0f);

}

//Color cUtils::GetTeamColor( CBaseEntity *pEntity, bool Visible )
//{
//	Color ReturnColor( 255, 255, 255, 255 );
//
//	switch( this->GetBaseEntityTeamNum( pEntity ) )
//	{
//	case TEAM_COUNTER_TERRORIST:
//		{
//			ReturnColor = Color( 8, 255, 29, 255 );
//
//			break;
//		}
//	case TEAM_TERRORIST:
//		{
//			ReturnColor = Color( 255, 255, 0, 255 );
//			
//
//			break;
//		}
//	}
//
//	//if( Visible == false )
//	//{
//	//	ReturnColor.SetColor( 
//	//		255 - ReturnColor.r(),
//	//		255 - ReturnColor.g(),
//	//		255 - ReturnColor.b(),
//	//		ReturnColor.a() );
//	//}
//		if( Visible == false)
//	{
//		switch( this->GetBaseEntityTeamNum( pEntity ) )
//	{
//	case TEAM_COUNTER_TERRORIST:
//		{
//			ReturnColor = Color( 8, 29, 255, 255 );
//
//			break;
//		}
//	case TEAM_TERRORIST:
//		{
//			ReturnColor = Color( 255, 16, 16, 255 );
//
//			break;
//		}
//	}
//	}
//
//	return ReturnColor;
//}


void cUtils::Normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if(flLen == 0){
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}