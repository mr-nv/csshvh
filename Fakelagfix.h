#pragma once;
#include "main.h"

struct PlayerTimeTable_t
{
	float flSimulationtime;
	int nTickCorrection;
};

class CFakelagfix
{
public:

void FakelagFix(C_BaseEntity* localShit, CUserCmd* pCmd);
Vector &PredictTheEyePosition(C_BaseEntity*);
void FastAwp(C_BaseEntity* localShit);
void Fakelag();
float GetConstantViewlag();
void Cache();
int GetTickCorrection(int nIndex);

private:
	int nLRTC;
	PlayerTimeTable_t PlayerTime[MAX_PLAYERS];
};

extern CFakelagfix Fakelagfix;