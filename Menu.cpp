#include "Menu.h"
#include "cMouse.h"

cMenu new_Menu("Private hack by hehe");
tagPOINT Mouse;
Position::Position()
{
	Init(0, 0);
	m_flPos[0] = PosX;
	m_flPos[1] = PosY;
}
void Position::Init(float x, float y)
{
	PosX = x;
	PosY = y;
	m_flPos[0] = PosX;
	m_flPos[1] = PosY;
}
void Position::PositionCopy(Position src, Position dest)
{
	src = dest;
}
void Position::PositionAdd(Position src, Position add)
{
	src.PosX += add.PosX;
	src.PosY += add.PosY;
}
void drawtxt(int x, int y, const char *pszText, ...)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start(va_alist, pszText);
	vsprintf(szBuffer, pszText, va_alist);
	va_end(va_alist);

	wsprintfW(szString, L"%S", szBuffer);
	g_pSurface->DrawSetTextPos(x, y);
	//SurfaceSDK->DrawSetTextColor(150,150,150,255);
	g_pSurface->DrawPrintText(szString, strlen(szBuffer));
}
var_s g_vars;
cMenu::cMenu(char* Menu_name)
{
	bMenuopen = false;
	pMenuPos.Init(300.0f, 75.0f);
	Menusection.aimbot = 0;
	Menusection.misc = 0;
	Menusection.removals = 0;
	Menusection.visuals = 0;
	flSize[width] = 175.0f;
	flSize[height] = 20.0f;
	nMenuindex = 0;
	nMenuitems = 0;
	szMenuname = Menu_name;
	//Menu colours
	Menucolour[R] = 0;
	Menucolour[G] = 255;
	Menucolour[B] = 0;
	Menucolour[A] = 255;
	Bordercolour[R] = 255;
	Bordercolour[G] = 0;
	Bordercolour[B] = 0;
	Bordercolour[A] = 255;
	Textcolour[R] = 255;
	Textcolour[G] = 255;
	Textcolour[B] = 255;
	Textcolour[A] = 255;
	Selectedtextcolour[R] = 128;
	Selectedtextcolour[G] = 128;
	Selectedtextcolour[B] = 128;
	Selectedtextcolour[A] = 255;
	//Preset the hack
	//-----------------Aimbot-------------------
	g_vars.aimbot = 1;
	g_vars.autoshoot = 1;
	g_vars.aimsilent = 1;
	g_vars.aimwall = 1;
	g_vars.hitscan = 1;
	g_vars.fakelagfix = 1;
	g_vars.antiaim = 1;
	g_vars.autopistol = 1;
	g_vars.bhop = 1;
	g_vars.newstrafer = 1;
	g_vars.attargets = 1;
	g_vars.fakeduck = 1;
	g_vars.psilent = 1;
	g_vars.edge = 1;
	//------------------------------------------

	//-----------------Visual-------------------
	//------------------------------------------

	//-----------------Removals-----------------
	//------------------------------------------

	//-----------------Misc---------------------

	//------------------------------------------
}

void blackBorder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 2, 1, 0, 0, 0, 254); //top
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 0, 0, 0, 254);	//left
	gUtils.FillRGBA(x + w, y, 1, h - 1, 0, 0, 0, 254);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 0, 0, 0, 254); //bottom
}

void blackthickborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 3, 25, 0, 0, 0, 255); //top
	gUtils.FillRGBA(x - 1, y, 2, h - 1, 0, 0, 0, 255);	//left
	gUtils.FillRGBA(x + w, y, 2, h - 1, 0, 0, 0, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 3, 5, 0, 0, 0, 255); //bottom
}
void whiteborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 2, 1, 255, 255, 255, 255); //top
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 255, 255, 255, 255);	//left
	gUtils.FillRGBA(x + w, y, 1, h - 1, 255, 255, 255, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 255, 255, 255, 255); //bottom
}
void backgroundborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 3, 2, 0, 0, 0, 254); //top
	gUtils.FillRGBA(x - 1, y, 2, h - 1, 0, 0, 0, 254);	//left
	gUtils.FillRGBA(x + w, y, 2, h - 1, 0, 0, 0, 254);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 3, 2, 0, 0, 0, 254); //bottom
}
void lightgreyborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 1, 1, 192, 192, 192, 255); //top
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 192, 192, 192, 255);	//left
	gUtils.FillRGBA(x + w, y - 1, 1, h, 192, 192, 192, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 192, 192, 192, 254); //bottom
}
void blueborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 6, 25, 50, 205, 50, 255); //top
	gUtils.FillRGBA(x - 1, y, 5, h - 1, 50, 205, 50, 255);	//left
	gUtils.FillRGBA(x + w, y, 5, h - 1, 50, 205, 50, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 6, 5, 50, 205, 50, 255); //bottom
}

void playerlistborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 6, 25, 50, 205, 50, 255); //top
	gUtils.FillRGBA(x - 1, y, 5, h - 1, 50, 205, 50, 255);	//left
	gUtils.FillRGBA(x + w, y, 5, h - 1, 50, 205, 50, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 6, 5, 50, 205, 50, 255); //bottom
}

void blueborder2(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 1, 2, 255, 119, 0, 255); //top
	gUtils.FillRGBA(x - 1, y, 2, h - 1, 255, 119, 0, 255);	//left
	gUtils.FillRGBA(x + w, y, 2, h - 1, 255, 119, 0, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 1, 2, 255, 119, 0, 255); //bottom
}

int cMenu::AddEntry(int i, char title[100], float* cvar, float max, float min, float step)
{
	strcpy(Item[i].title, title);
	Item[i].cvar = cvar;
	Item[i].min = min;
	Item[i].max = max;
	Item[i].step = step;
	return (i + 1);
}
void cMenu::InitMenuItems()
{
	int i = 0;

	//if(!Menusection.misc)
	//i = AddEntry(i,"[+]Misc",&Menusection.misc,1,0,1);
	//if(Menusection.misc){
	//i = AddEntry(i,"[-]Misc",&Menusection.misc,1,0,1);
	//i = AddEntry(i,"   Bunnyhop",&CvarList.MiscVars.Bunnyhop,1,0,1);
	//i = AddEntry(i,"   Autopistol",&CvarList.MiscVars.Autopistol,1,0,1);
	//i = AddEntry(i,"   Anti-Aim",&CvarList.MiscVars.Antiaim,1,0,1);
	//}


	nMenuitems = i;
}

void cMenu::PageOne(float *var, int x, int y, char *name, char *desc)
{
	//blackBorder(437, y + 0, 13, 13); //On/off box
	//blackBorder(91, y + 1, 17, 17);
	if (gMouse.OneLeftclick(160, y + 6.5, 9, 9))
	{
		if (*var == 0)
		{
			*var = 1;
		}
		else
			*var = 0;
	}

	if (gMouse.IsOver(160, y + 7, 11, 11))
	{
		gUtils.FillRGBA(160, y + 7, 9, 9, 255, 255, 255, 100);//grey
	}

	if (*var == 1)
	{
		//	blackBorder(437, y + 0, 11, 11);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
		gUtils.FillRGBA(157, y + 5, 13, 13, 255, 255, 255, 255);
		gUtils.FillRGBA(159, y + 7, 9, 9, 0, 0, 0, 255);
	}
	else if (*var == 0)
	{
		//blackBorder(437, y + 0, 13, 13);
		gUtils.FillRGBA(157, y + 5, 13, 13, 255, 255, 255, 255);//grey
		gUtils.FillRGBA(159, y + 7, 9, 9, 119, 136, 153, 255);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
	}
	gMouse.DrawFeatureString(x, y + 5, 255, 255, 255, false, name);
}

void cMenu::page2(float *var, int x, int y, char *name, char *desc)
{
	//blackBorder(437, y + 0, 13, 13); //On/off box
	//blackBorder(91, y + 1, 17, 17);
	if (gMouse.OneLeftclick(320, y + 2.5, 11, 11))
	{
		if (*var == 0)
		{
			*var = 1;
		}
		else
			*var = 0;
	}

	//if (gMouse.IsOver(321, y + 3, 11, 11))
	//{
	//	gUtils.FillRGBA(321, y + 3, 11, 11, 128, 128, 128, 100);//grey
	//}

	if (*var == 1)
	{
		//	blackBorder(437, y + 0, 11, 11);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
		gUtils.FillRGBA(320, y + 1, 15, 15, 128, 128, 128, 255);
		gUtils.FillRGBA(323, y + 4, 9, 9, 255, 255, 255, 235);
	}
	else if (*var == 0)
	{
		//blackBorder(437, y + 0, 13, 13);
		gUtils.FillRGBA(320, y + 1, 15, 15, 128, 128, 128, 255);//grey
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
	}
	gMouse.DrawFeatureString(x, y + 3, 255, 255, 255, false, name);
}

void cMenu::PageThree(float *var, int x, int y, char *name, char *desc)
{
	//blackBorder(437, y + 0, 13, 13); //On/off box
	//blackBorder(91, y + 1, 17, 17);
	if (gMouse.OneLeftclick(546, y + 2.5, 11, 11))
	{
		if (*var == 0)
		{
			*var = 1;
		}
		else
			*var = 0;
	}

	//if (gMouse.IsOver(321, y + 3, 11, 11))
	//{
	//	gUtils.FillRGBA(321, y + 3, 11, 11, 128, 128, 128, 100);//grey
	//}

	if (*var == 1)
	{
		//	blackBorder(437, y + 0, 11, 11);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
		gUtils.FillRGBA(546, y + 1, 15, 15, 128, 128, 128, 255);
		gUtils.FillRGBA(549, y + 4, 9, 9, 255, 255, 255, 235);
	}
	else if (*var == 0)
	{
		//blackBorder(437, y + 0, 13, 13);
		gUtils.FillRGBA(546, y + 1, 15, 15, 128, 128, 128, 255);//grey
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
	}
	gMouse.DrawFeatureString(x, y + 3, 255, 255, 255, false, name);
}


void cMenu::PageTwo(float *var, int x, int y, char *name, char *desc)
{
	//blackBorder(437, y + 0, 13, 13); //On/off box
	blackBorder(226, y + 1, 17, 17);
	if (gMouse.OneLeftclick(227.5, y + 2.5, 12.5, 12.5))
	{
		if (*var == 0)
		{
			*var = 1;
		}
		else
			*var = 0;
	}

	if (gMouse.IsOver(226, y + 3, 12.5, 12.5))
	{
		gUtils.FillRGBA(227.5, y + 3, 12.5, 12.5, 128, 128, 128, 100);//orange
	}

	if (*var == 1)
	{
		//	blackBorder(437, y + 0, 11, 11);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
		gUtils.FillRGBA(226, y + 1, 17, 16, 128, 128, 128, 255);
		gUtils.FillRGBA(228, y + 3, 13, 12, 50, 205, 50, 255);
	}
	else if (*var == 0)
	{
		//blackBorder(437, y + 0, 13, 13);
		gUtils.FillRGBA(226, y + 1, 17, 16, 128, 128, 128, 255);//grey
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
	}
	gMouse.DrawFeatureString(x, y + 3, 255, 255, 255, false, name);
}

void cMenu::page3(float *var, int x, int y, char *name, char *desc)
{
	//blackBorder(437, y + 0, 13, 13); //On/off box
	blackBorder(230, y + 1, 17, 17);
	if (gMouse.OneLeftclick(231.5, y + 2.5, 12.5, 12.5))
	{
		if (*var == 0)
		{
			*var = 1;
		}
		else
			*var = 0;
	}

	if (gMouse.IsOver(230, y + 3, 12.5, 12.5))
	{
		gUtils.FillRGBA(231.5, y + 3, 12.5, 12.5, 128, 128, 128, 100);//orange
	}

	if (*var == 1)
	{
		//	blackBorder(437, y + 0, 11, 11);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
		gUtils.FillRGBA(230, y + 1, 17, 16, 128, 128, 128, 255);
		gUtils.FillRGBA(232, y + 3, 13, 12, 50, 205, 50, 255);
	}
	else if (*var == 0)
	{
		//blackBorder(437, y + 0, 13, 13);
		gUtils.FillRGBA(230, y + 1, 17, 16, 128, 128, 128, 255);//grey
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
	}
	gMouse.DrawFeatureString(x, y + 3, 255, 255, 255, false, name);
}

void cMenu::playerlistcheckbox(float *var, int x, int y, char *name, char *desc)
{
	//blackBorder(437, y + 0, 13, 13); //On/off box
	blackBorder(80, y + 1, 17, 17);
	if (gMouse.OneLeftclick(81.5, y + 2.5, 12.5, 12.5))
	{
		if (*var == 0)
		{
			*var = 1;
		}
		else
			*var = 0;
	}

	if (gMouse.IsOver(80, y + 3, 12.5, 12.5))
	{
		gUtils.FillRGBA(81.5, y + 3, 12.5, 12.5, 128, 128, 128, 100);//orange
	}

	if (*var == 1)
	{
		//	blackBorder(437, y + 0, 11, 11);
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
		gUtils.FillRGBA(80, y + 1, 17, 16, 128, 128, 128, 255);
		gUtils.FillRGBA(82, y + 3, 13, 12, 50, 205, 50, 255);
	}
	else if (*var == 0)
	{
		//blackBorder(437, y + 0, 13, 13);
		gUtils.FillRGBA(80, y + 1, 17, 16, 128, 128, 128, 255);//grey
		//Draw.FillRGBA(230, y + 0, 16, 16, 0, 0, 0, 255);
	}
	gMouse.DrawFeatureString(x, y + 3, 255, 255, 255, false, name);
}

void redBorder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 2, 1, 255, 0, 0, 254); //top
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 255, 0, 0, 254);	//left
	gUtils.FillRGBA(x + w, y, 1, h - 1, 255, 0, 0, 254);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 255, 0, 0, 254); //bottom
}

void darkredBorder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y - 1, w + 2, 1, 189, 23, 23, 254); //top
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 189, 23, 23, 254);	//left
	gUtils.FillRGBA(x + w, y, 1, h - 1, 189, 23, 23, 254);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 189, 23, 23, 254); //bottom
}
void blackBorder2(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 0, 0, 0, 254);	//left
	gUtils.FillRGBA(x + w, y, 1, h - 1, 0, 0, 0, 254);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 0, 0, 0, 254); //bottom
}
void cvarborder(int x, int y, int w, int h)
{
	gUtils.FillRGBA(x - 1, y, 1, h - 1, 192, 192, 192, 255);	//left
	gUtils.FillRGBA(x + w, y, 1, h - 1, 192, 192, 192, 255);	//right
	gUtils.FillRGBA(x - 1, y + h - 1, w + 2, 1, 192, 192, 192, 255); //bottom
}

bool bKeyPressed[256];
bool IsKeyPressed(int iKey){
	//used for menu toggle
	if (GetAsyncKeyState(iKey)){
		if (!bKeyPressed[iKey]){
			bKeyPressed[iKey] = true;
			return true;
		}
	}
	else
		bKeyPressed[iKey] = false;

	return false;
}

void DrawInfo(char* Text)
{
	int x = 100;
	int y = 100;
	drawtxt(x + 165, x + 445, Text);
}

//===================================================================================
void cMenu::MenuButtons()
{

	// --------------------------------------------------- //
	//Menu Positions
	int x = 71;
	int y = 140;
	int w = 300;
	int h = 150;

	//black border outside menu
	blackBorder(x, y, w, 20);

	//Background @ title
	gUtils.FillRGBA(x, y, w, 19, 36, 36, 36, 255);

	//Title of menu
	gUtils.DrawString(x + 40, y + 4, 255, 255, 255, false, "[ProClub] Snt Framework | WwW.ProClub0wnz.com");

	blackBorder(x, y + 21, w, h);
	
	gUtils.FillRGBA(x, y +21, w, h - 1, 153, 153, 153, 255);

	

	// If mouse is over Legitbot tab
	if (gMouse.IsOver(x, y+20, 50, 20))
	{
		gUtils.FillRGBA(x, y + 20, 50, 20, 255, 255, 255, 200);
		gUtils.DrawString(x + 9, y + 25, 255, 255, 255, false, "Legitbot");
	}
	// If legitbot is clicked on
	if (gMouse.OneLeftclick(x, y + 20, 50, 20))
	{
		g_vars.menu_page = 1;
	}
	// If ragebot is clicked on
	if (gMouse.OneLeftclick(x + 51, y + 20, 50, 20))
	{
		g_vars.menu_page = 2;
	}
	// If esp is clicked on
	if (gMouse.OneLeftclick(x + 101, y + 20, 50, 20))
	{
		g_vars.menu_page = 3;
	}
	// If misc is clicked on
	if (gMouse.OneLeftclick(x + 151, y + 20, 50, 20))
	{
		g_vars.menu_page = 4;
	}


	


	//menu buttons active
	//if (gMouse.OneLeftclick(x + 5, y + 24, 82, 26))
	//{
	//	g_vars.menu_page = 1;
	//	//	Draw.FillRGBA2(x + 4, y + 23, 120, 30, Color(2, 149, 219, 255));
	//}

	//if (gMouse.OneLeftclick(x + 88, y + 25, 82, 20))
	//{
	//	g_vars.menu_page = 2;
	//	//Draw.FillRGBA2(x + 123, y + 23, 120, 30, Color(2, 149, 219, 255));
	//}

	//if (gMouse.OneLeftclick(x + 173, y + 25, 82, 20))
	//{
	//	g_vars.menu_page = 3;
	//	//Draw.FillRGBA2(x + 123, y + 23, 120, 30, Color(2, 149, 219, 255));
	//}

	//if (gMouse.OneLeftclick(x + 257, y + 25, 82, 20))
	//{
	//	g_vars.menu_page = 4;
	//	//Draw.FillRGBA2(x + 123, y + 23, 120, 30, Color(2, 149, 219, 255));
	//}


	// MOUSE OVER BUTTONS

	//if (gMouse.IsOver(x + 4, y + 25, 82, 20))
	//{

	//	gUtils.FillRGBA1(x + 5, y + 24, 82, 26, COLORCODE(50, 205, 50, 255));
	//}

	//if (gMouse.IsOver(x + 88, y + 25, 82, 20))
	//{
	//	gUtils.FillRGBA1(x + 89, y + 24, 82, 26, COLORCODE(50, 205, 50, 255));
	//}

	//if (gMouse.IsOver(x + 173, y + 25, 82, 20))
	//{
	//	gUtils.FillRGBA1(x + 173, y + 24, 82, 26, COLORCODE(50, 205, 50, 255));
	//}

	//if (gMouse.IsOver(x + 257, y + 25, 82, 20))
	//{
	//	gUtils.FillRGBA1(x + 257, y + 24, 82, 26, COLORCODE(50, 205, 50, 255));
	//}

	//if (g_vars.menu_page == 1)
	//{
		////Tab Color (Aimbot)
		//gUtils.FillRGBA1(x + 5, y + 24, 82, 26, COLORCODE(50, 205, 50, 255));//255, 119, 0, 255

		////left
		//gUtils.FillRGBA1(x + 10, y + 60, 10, 1, COLORCODE(0, 0, 0, 255));
		////right
		//gUtils.FillRGBA1(x + 54, y + 60, 91, 1, COLORCODE(0, 0, 0, 255));
		////border for aimbot
		//cvarborder(x + 10, y + 60, 135, 160);//70
		////name in border for cvars aimbot
		//gUtils.DrawString(x + 22, y + 57, 255, 255, 255, false, "Aimbot");

		//new_Menu.PageOne(&g_vars.aimbot, x + 45, y + 70, "Active aimbot", "");
		//new_Menu.PageOne(&g_vars.autoshoot, x + 45, y + 90, "Autoshoot", "");
		//new_Menu.PageOne(&g_vars.aimsilent, x + 45, y + 110, "Silent aim", "");
		//new_Menu.PageOne(&g_vars.hitscan, x + 45, y + 130, "Hitscans", "");
		//new_Menu.PageOne(&g_vars.aimwall, x + 45, y + 150, "Autowall", "");
		//new_Menu.PageOne(&g_vars.fakelagfix, x + 45, y + 170, "Position adjustment", "");
		//new_Menu.PageOne(&g_vars.psilent, x + 45, y + 190, "Perfect Silent Aim", "");


		////left top extra
		//gUtils.FillRGBA1(x + 10, y + 250, 10, 1, COLORCODE(0, 0, 0, 255));
		////top right extra
		//gUtils.FillRGBA1(x + 62, y + 250, 204, 1, COLORCODE(0, 0, 0, 255));
		////bottom extra
		//gUtils.FillRGBA1(x + 146, y + 349, 120, 1, COLORCODE(0, 0, 0, 255));
		////right extra
		//gUtils.FillRGBA1(x + 266, y + 250, 1, 100, COLORCODE(0, 0, 0, 255));
		////border for aimbot
		//cvarborder(x + 10, y + 250, 135, 100);//70
		////name in border for cvars aimbot
		//gUtils.DrawString(x + 22, y + 247, 255, 255, 255, false, "Anti-Aim");
		//
		////Cvars
		//new_Menu.PageOne(&g_vars.antiaim, x + 45, y + 260, "Active Jitter AA", "");
		//new_Menu.PageOne(&g_vars.normalx, x + 45, y + 280, "X Angle: Normal", "");
		//new_Menu.PageOne(&g_vars.fakedownx, x + 45, y + 300, "X Angle: Fakedown", "");
		//new_Menu.PageOne(&g_vars.emotionx, x + 45, y + 320, "X Angle: Emotion", "");

		////Cvars for Extra (Antiaim)
		//new_Menu.PageTwo(&g_vars.edge, x + 180, y + 260, "Edge", "");
		//new_Menu.PageTwo(&g_vars.fakeduck, x + 180, y + 280, "Fake duck", "");
		//new_Menu.PageTwo(&g_vars.fakelag, x + 180, y + 300, "Fake lag", "");
		//new_Menu.PageTwo(&g_vars.attargets, x + 180, y + 320, "At target", "");
		////new_Menu.PageOne(&g_vars.fakedownx, x + 145, y + 300, "X Angle: Fakedown", "");
		////new_Menu.PageOne(&g_vars.emotionx, x + 145, y + 320, "X Angle: Emotion", "");
	//}
	//gMouse.DrawString(x + 28, y + 32, 255, 255, 255, false, "Ragebot"); //text (tabpage)

	//if (g_vars.menu_page == 4)
	//{
	//	//Tab color
	//	gUtils.FillRGBA1(x + 257, y + 24, 82, 26, COLORCODE(50, 205, 50, 255));

	//	////left
	//	//gUtils.FillRGBA1(x + 10, y + 60, 10, 1, COLORCODE(0, 0, 0, 255));
	//	////right
	//	//gUtils.FillRGBA1(x + 95, y + 60, 51, 1, COLORCODE(0, 0, 0, 255));
	//	////border for aimbot
	//	//cvarborder(x + 10, y + 60, 135, 100);//70
	//	////name in border for cvars aimbot
	//	//gUtils.DrawString(x + 22, y + 57, 255, 255, 255, false, "Whitelist Players:");

	//	//new_Menu.PageOne(&g_vars.whitezylx, x + 45, y + 70, "Zylx", "");
	//	//new_Menu.PageOne(&g_vars.whiteneo, x + 45, y + 90, "Fox", "");
	//	//new_Menu.PageOne(&g_vars.whitepara, x + 45, y + 110, "Paradoxxx", "");
	//	//new_Menu.PageOne(&g_vars.whitevane, x + 45, y + 130, "Vane", "");
	//}
	//gMouse.DrawString(x + 281, y + 32, 255, 255, 255, false, "Console");
}
void cMenu::Body(int x, int y, int w, int h)
{
	gUtils.FillRGBA(0, 0, 1800, 32, 30, 30, 30, 255);
	blackBorder(0, 0, 1800, 33);
}


void cMenu::DrawMenu2(int x, int y, int w, int h, char *title)
{
	if (IsKeyPressed(VK_INSERT))
	{
		gMouse.ActiveMouse = !gMouse.ActiveMouse;
	}

	if (gMouse.ActiveMouse)
	{
		//drag(&gCvar.pos_bx, &gCvar.pos_by, gCvar.pos_bw, gCvar.pos_bh);
		//Title(x, y - 17, w, 12 + 3, title);
		//Body(x, y, w, h);

		//MenuPages();
		MenuButtons();
	}

}

void cMenu::DrawMenu()
{
	if (GetAsyncKeyState(VK_DELETE) & 1)
		bMenuopen = !bMenuopen;
	if (!bMenuopen)
		return;

	int x = 5;
	int y = 5;
	int w = 200;
	int h = 250;

	KeyHandle();
	int i = nMenuitems;
	g_pSurface->DrawSetTextColor(Color(255, 255, 255, 255));
	COLORREF rofl = RGB(255, 255, 255);

	for (int i = 0; i<nMenuitems; i++)
		if (i != nMenuindex)//Not selected item
		{
			g_pSurface->DrawSetTextColor(Color(255, 255, 255, 255));
			drawtxt(pMenuPos.PosX + 17, pMenuPos.PosY + (20 * i), Item[i].title);
			drawtxt(pMenuPos.PosX + 147, pMenuPos.PosY + (20 * i), "%2.2f", Item[i].cvar[0]);
			//Draw.DrawStringMenu(false, pMenuPos.PosX + 7, pMenuPos.PosY + (12 * i), COLORCODE(Textcolour[R], Textcolour[G], Textcolour[B], Textcolour[A]), Item[i].title);
			//Draw.DrawStringMenu(false, pMenuPos.PosX + 137, pMenuPos.PosY + (12 * i), COLORCODE(Textcolour[R], Textcolour[G], Textcolour[B], Textcolour[A]), "%2.2f", Item[i].cvar[0]);

		}
		else//selected item
		{
			g_pSurface->DrawSetTextColor(Color(255, 0, 0, 255));
			drawtxt(pMenuPos.PosX + 17, pMenuPos.PosY + (20 * i), Item[i].title);
			drawtxt(pMenuPos.PosX + 147, pMenuPos.PosY + (20 * i), "%2.2f", Item[i].cvar[0]);
			//Draw.DrawStringMenu(false, pMenuPos.PosX + 7, pMenuPos.PosY + (12 * i), COLORCODE(0, 0, 0, 0), Item[i].title);
			//Draw.DrawStringMenu(false, pMenuPos.PosX + 137, pMenuPos.PosY + (12 * i), COLORCODE(0, 0, 0, 0), "%2.2f", Item[i].cvar[0]);
		}

}

BOOL cMenu::KeyHandle()
{
	if (GetAsyncKeyState(VK_UP) & 1)
	{
		if (nMenuindex>0) nMenuindex--;
		else nMenuindex = nMenuitems - 1;
		return FALSE;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 1)
	{
		if (nMenuindex<nMenuitems - 1) nMenuindex++;
		else nMenuindex = 0;
		return FALSE;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 1)
	{
		if (Item[nMenuindex].cvar){
			Item[nMenuindex].cvar[0] -= Item[nMenuindex].step;
			if (Item[nMenuindex].cvar[0] < Item[nMenuindex].min)
				Item[nMenuindex].cvar[0] = Item[nMenuindex].max;
		}
		return FALSE;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 1)
	{
		if (Item[nMenuindex].cvar)
		{
			Item[nMenuindex].cvar[0] += Item[nMenuindex].step;
			if (Item[nMenuindex].cvar[0] > Item[nMenuindex].max)
				Item[nMenuindex].cvar[0] = Item[nMenuindex].min;
		}
		return FALSE;
	}
	return TRUE;
}