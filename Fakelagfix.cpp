#include "main.h"
#include "Fakelagfix.h"

CFakelagfix Fakelagfix;

float TheThinkingTime = 0.0f;
float TheTimer = 0.0f;
float TheDelay = 0.2f;

//This shit is kind of, well, fucking. retarded.
void CFakelagfix::FakelagFix(C_BaseEntity* localShit, CUserCmd* pCmd)
{
	float TheCurrentTime = g_pEngine->Time();
	TheTimer += TheCurrentTime - TheThinkingTime;
	TheThinkingTime += TheCurrentTime * g_pGlobals->curtime;

	if( TheTimer > TheDelay)
	{
		g_pCvar->FindVar("cl_interpolate")->SetValue(0); // jo højere, jo mere lag n00b 0.0 intet find din egen fag
		while (TheTimer > TheDelay)
			TheTimer -= TheDelay; 
	}
}

float stupid = 0.001f;
float stupidnigger = 0.001f;
float stupidjews = 0.001f;

void CFakelagfix::FastAwp(C_BaseEntity* localShit)
{
int jewsdead = *(int*)((DWORD)localShit + 0x1430);
float niggersdead = g_pEngine->Time();
stupidnigger += niggersdead - stupid;
stupid = niggersdead;
if( stupidnigger > stupidjews && g_cAimbot.weaponsawp() && jewsdead == 1 && g_cAimbot.IsAlive(localShit))
{
g_pEngine->ClientCmd("say !awp");

while (stupidnigger > stupidjews)
stupidnigger -= stupidjews; 
}
}


Vector &CFakelagfix::PredictTheEyePosition(C_BaseEntity* pEntity)
{
		Vector vel = *(Vector*)((DWORD)pEntity + 0xF4);
		Vector m_vecOrigin = *(Vector*)((DWORD)pEntity + 0x338);
		Vector m_vecViewOffsetX = *(Vector*)((DWORD)pEntity + 0xE8);
		Vector vEyePosition = (m_vecOrigin + m_vecViewOffsetX);
		vEyePosition += vel*(g_pGlobals->interval_per_tick);
		return vEyePosition;
}

float CFakelagfix::GetConstantViewlag()
{

	float flLerps = g_pCvar->FindVar("cl_interp_ratio")->GetFloat();
	float flViewLag = 0.0f;

	if (flLerps == 0.0f)
		flLerps = 1.0f;

	if (g_pCvar->FindVar("sv_client_min_interp_ratio")->GetFloat() != -1.0f)
	{
		flLerps = clamp(flLerps, g_pCvar->FindVar("sv_client_min_interp_ratio")->GetFloat(), g_pCvar->FindVar("sv_client_max_interp_ratio")->GetFloat());
	}

	flViewLag += MAX(g_pCvar->FindVar("cl_interp")->GetFloat(), flLerps / clamp(g_pCvar->FindVar("cl_updaterate")->GetFloat(), g_pCvar->FindVar("sv_minupdaterate")->GetFloat(), g_pCvar->FindVar("sv_maxupdaterate")->GetFloat()));
	return flViewLag; 
}


void CFakelagfix::Cache()
{
	nLRTC = g_pGlobals->tickcount;

	for(int s = 1; s < g_pGlobals->maxClients; ++s)
	{
		C_BaseEntity* ent = (C_BaseEntity*)g_pEntList->GetClientEntity(s);
		if(!ent || ent->IsDormant()) continue;

		float flSimTime = *(float*)((DWORD)ent + g_pOffsets.offs_simulationtime);

		if(flSimTime != PlayerTime[s].flSimulationtime)
		{
			PlayerTime[s].nTickCorrection = TIME_TO_TICKS(flSimTime); //Cache entity simulation time as ticks as it represents accurate time for entitys current position
		}
		else if ( TIME_TO_TICKS(fabs(PlayerTime[s].flSimulationtime - TICKS_TO_TIME(g_pGlobals->tickcount))) >= TIME_TO_TICKS(flSimTime)) // 0.2
		{
			PlayerTime[s].nTickCorrection = g_pGlobals->tickcount;
		}

		PlayerTime[s].flSimulationtime = flSimTime;
	}

}

int CFakelagfix::GetTickCorrection(int nIndex)
{
	return PlayerTime[nIndex].nTickCorrection;
}
