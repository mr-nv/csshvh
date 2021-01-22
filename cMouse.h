#pragma once;
#include "main.h"

class cMouse
{
public:
	cMouse();
	bool ActiveMouse;
	float MousePos[2];
	float OldPos[2];
	void Buttons();
	void DrawMouse();
	bool CheckMouse(int,int,int,int);
	bool CheckMouse(bool,int,int,int,int);
	bool MousePeekMessage(UINT,WPARAM,LPARAM);
	bool Mouse1Press;
	bool Mouse1Hold;
	bool Mouse2Press;
	bool Mouse2Hold;
	void DrawString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void DrawFeatureString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void DrawString2( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void DrawTabName( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... );
	void DrawString1( int x, int y, int r, int g,int b, bool bCenter);
	bool HideMouse;
    void ClickHandler();
	bool Leftclick(int x,int y,int w,int h);
	bool OneLeftclick(int x,int y,int w,int h);
	bool Rightclick(int x,int y,int w,int h);
	bool OneRightclick(int x,int y,int w,int h);
	bool IsOver(int x,int y,int w,int h);
	bool mouse1pressed;
	bool mouse1released;
	bool mouse2pressed;
	bool mouse2released;
	bool mousescrollpressed;
	bool mousescrollreleased;
private:
	void FillRGBA( int x, int y, int w, int h, DWORD dwColor );
};

extern cMouse gMouse;