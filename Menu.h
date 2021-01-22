#include "main.h"

#ifndef _MENU_H_
#define _MENU_H_

enum /*MenuSize_t*/
{
	width = 0,
	height = 1
};
enum /*RGBA_t*/
{
	RGBA = 4,
	R = 0,
	G = 1,
	B = 2,
	A = 3
};


//struct Aimbot2
//{
//	float Aim;
//	float Autoshoot;
//	float Silentaim;
//	float silentaim;
//	float fastawp;
//	float autowall;
//};
//struct Removals
//{
//	float VisualRecoil;
//};
//struct Visuals
//{
//	float Crosshair;
//	float BoxESP;
//	float Chams;
//	float EntESP;
//	float WeaponESP;
//	float Level;
//	float hp;
//	float armoresp;
//	float nazi;
//	float steamid;
//	float asus;
//	float nosmoke;
//	float name;
//	float noflash;
//	float hitboxesp;
//	float roundsay;
//	float nameesp;
//	float hpesp;
//	float healthbar;
//	float weaponesp;
//	float boxesp;
//	float asuswall;
//	float bypass;
//	float vane;
//	float smokeweed;
//	float daxe;
//	float poke;
//	float l$;
//	float crownt;
//	float christina;
//	float normal;
//	float fakedown;
//	float GangsterParadise;
//	float emotion;
//	float fakelagvalue4;
//	float fakelagvalue5;
//	float fakelagvalue6;
//	float fakelagvalue7;
//	float fakelagvalue8;
//	float fakelagvalue9;
//	float fakelagvalue10;
//	float antiaimknife;
//	float crosshair1;
//	float crosshair2;
//	float fakecrouch;
//	float bunnyhop;
//	float autostrafe;
//	float crosshair3;
//
//};
//struct Misc
//{
//	float silentaim;
//	float antiaim;
//	float iplogger;
//	float jitter;
//	float antiaim1;
//	float antiaim2;
//	float roundsay;
//	float antiaim3;
//	float antiaim4;
//	float antiaim5;
//	float antiaim6;
//	float antiaim7;
//	float antiaim8;
//	float Bunnyhop;
//	float Autopistol;
//	float fakelag;
//	float camp;
//	float rush;
//	float test;
//	float normal;
//	float aimbot;
//	float inattackcmd;
//	float autowall;
//	float psilent;
//	float runaimplayerbehindwall;
//	float smartaim;
//	float hvh;
//	float whitelist;
//	float r;
//	float g;
//	float b;
//	float a;
//	float prediction;
//	float menu_page;
//	float zylx;
//	float fox;
//	float crownt;
//	float daxe;
//	float kattix;
//	float ville;
//	float vane;
//	float ls;
//	float hitscans;
//	float pitch;
//	float autoshoot;
//	float knifebot;
//	float fastrun;
//	float nospread;
//	float visrec;
//	float runfast;
//	float autostrafer;
//	float rage_page_enabled;
//	float legit_page_enabled;
//	float triggerbot_page_enabled;
//	float esp_page_enabled;
//	float visual_page_enabled;
//	float radar_page_enabled;
//	float colours_page_enabled;
//	float misc_page_enabled;
//	float settings_page_enabled;
//	float hackvshack_page_enabled;
//	float radar_enable;
//	int pos_by;
//	int pos_bw;
//	int pos_bh;
//};

//class cCvars
//{
//public:
//	Aimbot2 AimVars;
//	Removals RemovalVars;
//	Visuals VisualVars;
//	Misc MiscVars;
//};

struct anitem
{
	float *cvar;
	float max;
	float min;
	float step;
	char title[100];
};
//
struct sections
{
	float aimbot;
	float visuals;
	float removals;
	float misc;
};
class Position
{
public:
	Position();
	float PosX;
	float PosY;
	void Init(float x, float y);
	void PositionCopy(Position src, Position dest);
	void PositionAdd(Position src, Position add);
private:
	float m_flPos[2];
};
class cMenu
{
public:
	cMenu(char* Menu_name);
	void InitMenuItems();
	void DrawMenu();
	void DrawMenu1(int x, int y, int w, int h, char *title);
	void DrawMenu2(int x, int y, int w, int h, char *title);
	void MenuText(bool Centered, int x, int y, DWORD dwColor, const char *pszText, ...);
	//cCvars CvarList;
private:
	int AddEntry(int i, char title[100], float* cvar, float max, float min, float step);
	int nMenuindex;
	int nMenuitems;
	BOOL KeyHandle();
	anitem Item[150];
	Position pMenuPos;
	float flSize[2];
	int Menucolour[RGBA];
	int Bordercolour[RGBA];
	int Textcolour[RGBA];
	void playerlistcheckbox(float *var, int x, int y, char *name, char *desc);
	void page2(float *var, int x, int y, char *name, char *desc);
	void page3(float *var, int x, int y, char *name, char *desc);
	void PageOne(float *var, int x, int y, char *name, char *desc);
	void PageTwo(float *var, int x, int y, char *name, char *desc);
	void PageThree(float *var, int x, int y, char *name, char *desc);
	void PageFour(float *var, int x, int y, char *name, char *desc);
	void PageFive(float *var, int x, int y, char *name, char *desc);
	void PageSix(float *var, int x, int y, char *name, char *desc);
	void PageSeven(float *var, int x, int y, char *name, char *desc);
	void PageEight(float *var, int x, int y, char *name, char *desc);
	void PageNine(float *var, int x, int y, char *name, char *desc);
	void PageTen(float *var, int x, int y, char *name, char *desc);
	void Outline(int x, int y, int w, int h, DWORD Color);
	void OnOff(float *var, int x, int y, char *name, char *desc);
	void MenuPages();
	void MenuButtons();
	void TabControl(int x, int y, int w, int h);
	void Body(int x, int y, int w, int h);
	int Selectedtextcolour[RGBA];
	bool bMenuopen;
	sections Menusection;
	char* szMenuname;
};

extern cMenu new_Menu;

#endif