#include "main.h"

cAimbot g_cAimbot;

cAimbot::cAimbot()
{
	DropTarget();
}

class CTraceFilterNoPlayers : public CTraceFilter
{
public:

	CTraceFilterNoPlayers( void )
	{
		m_maxClients = -1;
	}

	virtual bool ShouldHitEntity( IHandleEntity *pEntity, int contentsMask )
	{
		if ( m_maxClients == -1 )
		{
			m_maxClients = g_pEngine->GetMaxClients();
		}


		C_BaseEntity *Entity = (C_BaseEntity*)g_pEntList->GetClientEntityFromHandle( pEntity->GetRefEHandle() );

		return ( ( Entity->entindex() < 1 ) || ( Entity->entindex() > m_maxClients ) );
	}


private:

	int m_maxClients;
};

void cAimbot::DropTarget()
{
	m_flBestDist = 99999.9f;
	m_nTarget = -1;
	m_vPosition = 0;
}

void cAimbot::PredictTarget(C_BaseEntity* pBaseEntity, Vector &vEyePos, C_BaseEntity *pMe)
{
	Vector vOld[65];
	Vector vOldMe;
	Vector vAccel[65];
	Vector vMyAccel;
	Vector vecEnemyVelocity = *(Vector*)((DWORD)pBaseEntity + 0xF4);
	Vector vMyVel = *(Vector*)((DWORD)pMe + 0xF4);
	Vector vDelta = vecEnemyVelocity - vOld[pBaseEntity->index];
	vOld[pBaseEntity->index] = vecEnemyVelocity;
	if (vDelta != Vector(0, 0, 0))
		vAccel[pBaseEntity->index] = vDelta;
	Vector vDeltaMe = vMyVel - vOldMe;
	vOldMe = vMyVel;
	if (vDeltaMe != Vector(0, 0, 0))
		vMyAccel = vDeltaMe;

	if (vAccel[pBaseEntity->index] != Vector(0, 0, 0) || vMyAccel != Vector(0, 0, 0))
		m_vPosition += (1 / 2 * (vAccel[pBaseEntity->index] - vMyAccel) * Square(g_pGlobals->interval_per_tick) + (vecEnemyVelocity - vMyVel) * g_pGlobals->interval_per_tick + m_vPosition - vEyePos);
}


float GetDistance(Vector &vAbsStart, Vector &vAbsStop)
{
	float flLength = Vector(vAbsStop - vAbsStart).Length();
	float flDistance = sqrt(flLength);

	if(flDistance < 1.0f)
		flDistance = 1.0f;

	return flDistance;
}

void cAimbot::CalcAngle(Vector &vSource, Vector &vDestination, QAngle &qAngle)
{
	Vector vDelta(vSource - vDestination);
	double flHyp = sqrt((vDelta.x * vDelta.x) + (vDelta.y * vDelta.y));

	qAngle.x = RAD2DEG(atan(vDelta.z / flHyp));
	qAngle.y = RAD2DEG(atan(vDelta.y / vDelta.x));

	if(vDelta.x >= 0.0f)
		qAngle.y += 180.0f;
}

bool cAimbot::GetHitboxPositiondays(int nIndex, /*int SPOT, Vector lol[12],*/ C_BaseEntity * pEnemy)
{
	static matrix3x4_t pMatrix[MAXSTUDIOBONES];
	static Vector vOut;
	static mstudiohitboxset_t* pHitboxSet;
	static mstudiobbox_t* pBox;
	float pitch = *(float*) ( ( DWORD )pEnemy + ( DWORD )0x149C);
	const model_t* pModel = pEnemy->GetModel();
	static studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
	C_BasePlayer *playerE = reinterpret_cast< C_BasePlayer * >(pEnemy);
	if(pEnemy->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, g_pGlobals->interval_per_tick))
	{
		//Prediction here. cause seems to dont works on other places so now for be sure.
		pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pEnemy ) + 0x520 ) );

		pBox = pHitboxSet->pHitbox(nIndex);//1->8 = noob. 
		QAngle AADETECT;
		AADETECT.x = *(float*) ( ( DWORD )pEnemy + ( DWORD )0x149C);
		AADETECT.y = *(float*) ( ( DWORD )pEnemy + ( DWORD )0x14A0); 
		AADETECT.z = 0.0f;

		Vector corners[12];

		vec_t kik = 1;

		vec_t set = 2;

		Vector compensation;
		if(( AADETECT.x > (180/3)) && (AADETECT.x < 120.f))
		{
			compensation = (pBox->bbmax + pBox->bbmin) * .5f; 
			compensation.x += 3.6;
			compensation.y += 3.6;
			VectorTransform(compensation, pMatrix[pBox->bone], vOut);
			m_vPosition = vOut;
		}
		else
		{
			static Vector compensation;
			compensation = (pBox->bbmax + pBox->bbmin) * 0.5f;
			VectorTransform(compensation, pMatrix[pBox->bone], vOut);
			m_vPosition = vOut;
		}
		return true;
	}
	return false;
}


bool cAimbot::GetHitboxPosition(int nIndex, int rofl)
{

	matrix3x4_t pMatrix[MAXSTUDIOBONES];
	Vector vMin, vMax, Bone;
	QAngle qAngle;
	mstudiohitboxset_t* pHitboxSet;
	mstudiobbox_t* pBox;
	C_BaseAnimating * pEnemyAnim = reinterpret_cast<C_BaseAnimating*>(nIndex);
	IClientEntity* pEnemyClient = g_pEntList->GetClientEntity(nIndex);
	float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pEnemyClient ) + 0x6C );
	const model_t* pModel = pEnemyClient->GetModel();
	studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
	if(pEnemyClient->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, GetTickCount64() + flSimulationTime + GetTickCount()))
	{
		MatrixAngles( pMatrix[ nIndex ], qAngle, Bone );
		pHitboxSet = pStudioHdr->pHitboxSet(0);// pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pEnemyClient ) + 0x4E8 ) ); //netvar names?
		pBox = pHitboxSet->pHitbox(rofl);
		VectorTransform(pBox->bbmin, pMatrix[pBox->bone], vMin);
		VectorTransform(pBox->bbmax, pMatrix[pBox->bone], vMax);
		m_vPosition = (vMin + vMax) * 0.5;


		return true;
	}

	return false;
}

bool cAimbot::GetVisible(Vector &vAbsStart, C_BaseEntity * pMe)
{
	trace_t Trace;
	Ray_t Ray;

	//DWORD dwTemp[5];
	//static CTraceFilterSkipTwoEntities_t TraceFilter = reinterpret_cast< CTraceFilterSkipTwoEntities_t >( ( DWORD )( GetModuleHandle( "client.dll" ) ) + 0x19BEA0 ); // Address 62dbcb70 Base 62c20000
	//TraceFilter(&dwTemp, pMe, pMe, 0);

	CTraceFilterNoPlayers Filter;

	Ray.Init(vAbsStart, m_vPosition);
	//g_pEnginetrace->TraceRay(Ray, MASK_NPCWORLDSTATIC|MASK_VISIBLE_AND_NPCS|MASK_SHOT, NULL, &Trace);
	g_pEnginetrace->TraceRay( Ray, 0x46004003, (ITraceFilter*)&Filter, &Trace );

	if(Trace.fraction >= 0.97f)
		return true;

	if(Trace.fraction <= 0.70f)
		return false;

	if(Trace.startsolid || Trace.allsolid)
		return false;

	return false;
}

bool CGameTrace::DidHitWorld() const 
{ 
	return m_pEnt == g_pEntList->GetClientEntity( 0 ); 
}

void ClipTraceToPlayers( const Vector& start, const Vector& end, unsigned int mask, void* filter, void* data )
{
	typedef void ( *ClipTraceToPlayers_t )( const Vector& start, const Vector& end, unsigned int mask, void* filter, void* data );
	static ClipTraceToPlayers_t clipTraceToPlayers = (ClipTraceToPlayers_t)((DWORD)GetModuleHandleA( "client.dll" )+0x14F910); // ( "client.dll" )+0x1AC950);
	//static ClipTraceToPlayers_t clipTraceToPlayers = (ClipTraceToPlayers_t)dwFindPattern( (DWORD)GetModuleHandle( "client.dll" ), 0x3d9000, (PBYTE)"\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x81\xEC\x00\x00\x00\x00\x8B\x43\x18\xF3\x0F\x10\x40\x2C", "xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxx" );

	( (ClipTraceToPlayers_t)clipTraceToPlayers )( start, end, mask, filter, data );
}

void GetTraceFilterSkipTwoEntities( void *first, void *second, DWORD* thisptr )
{
	typedef void ( __thiscall *TraceFilterSkipTwoEntities_t )( DWORD *thisptr, void *first, void *second, int group );
	static TraceFilterSkipTwoEntities_t traceFilterskiptwoentities = (TraceFilterSkipTwoEntities_t)((DWORD)GetModuleHandleA( "client.dll" )+ 0x14FC30 ); // 0x14F0B0
	traceFilterskiptwoentities( thisptr, first, second, 0);
}

BYTE m_MoveType2( C_BaseEntity *pLocal )
{ 
	return *( BYTE* )( ( DWORD )pLocal + 0x178 );
}

void cAimbot::EDGE( C_BaseEntity *localPlayer, CUserCmd *cmd ,float angleyaw)
{
	CTraceFilterNoPlayers Filter;

	int iFlags = *(PINT)((DWORD)localPlayer + 0x350);

	Vector localPosition = gUtils.GetEyePosition(localPlayer);

	if(m_MoveType2(localPlayer) != MOVETYPE_LADDER)
	{
		for ( int y = 0; y < 360; ++y )
		{
			QAngle tmp( 17.f, cmd->viewangles.y, 0.f );
			tmp.y += y;

			MyMath::NormalizeAngles( tmp );

			Vector forward;
			AngleVectors( tmp, &forward, 0, 0 );

			float length = ( ( 16 + 3 ) + ( ( 16 + 3 ) * sin( MyMath::DegreesToRadians( 10.f ) ) ) ) + 5; // our collision bb is 32x32x64, the eyepos is in the center of (x,y), + 5 for rounding up if we're close enough to the wall

			forward *= length;

			Ray_t ray;
			trace_t traceData;

			ray.Init( localPosition, ( localPosition + forward ) );
			g_pEnginetrace->TraceRay( ray, 0x200400B, (ITraceFilter*)&Filter, &traceData );

			trace_t leftTrace, rightTrace;

			if ( traceData.fraction != 1.f )
			{
				QAngle angles;
				VectorAngles( -traceData.plane.normal, angles );

				tmp.y = angles.y;

				MyMath::NormalizeAngles( tmp );

				Vector left, right;
				MyMath::AngleToVectors( tmp + QAngle( 0.f, 48, 0.f ), &left, 0, 0 );
				MyMath::AngleToVectors( tmp - QAngle( 0.f, 48.f, 0.f ), &right, 0, 0 );

				left *= ( length + ( length * sin( MyMath::DegreesToRadians( 48 ) ) ) );
				right *= ( length + ( length * sin( MyMath::DegreesToRadians( 48 ) ) ) );

				ray.Init( localPosition, ( localPosition + left ) );
				g_pEnginetrace->TraceRay( ray, 0x200400B, (ITraceFilter*)&Filter, &leftTrace );

				ray.Init( localPosition, ( localPosition + right ) );
				g_pEnginetrace->TraceRay( ray, 0x200400B, (ITraceFilter*)&Filter, &rightTrace );


				if ( ( leftTrace.fraction == 1.f )
					&& ( rightTrace.fraction != 1.f ) )
				{
					tmp.x = 180.087936f;
					tmp.y -= 90.0f;
				}
				if ( ( leftTrace.fraction != 1.f )
					&& ( rightTrace.fraction == 1.f ) )
				{
					tmp.y += 90.0f;
				}

				cmd->viewangles.y = tmp.y;
				cmd->viewangles.y -= angleyaw;
			}
		}
	}
}

void cAimbot::MakeVector(QAngle angle, QAngle& vector)
{
	float pitch; 
	float yaw; 
	float tmp;           
	pitch	= (float)(angle[0] * M_PI/180); 
	yaw		= (float)(angle[1] * M_PI/180); 
	tmp		= (float) cos(pitch);
	vector[0] = (float) (-tmp * -cos(yaw)); 
	vector[1] = (float) (sin(yaw)*tmp);
	vector[2] = (float) -sin(pitch);
}

Vector &cAimbot::GetPredictedEyePosition(C_BaseEntity* pEntity)
{
	Vector vel = *(Vector*)((DWORD)pEntity + 0xF4);
	Vector m_vecOrigin = *(Vector*)((DWORD)pEntity + 0x338);
	Vector m_vecViewOffsetX = *(Vector*)((DWORD)pEntity + 0xE8);
	Vector vEyePosition = (m_vecOrigin + m_vecViewOffsetX);
	vEyePosition += vel*(g_pGlobals->interval_per_tick);
	return vEyePosition;
}

bool cAimbot::IsAlive(C_BaseEntity* pEntity)
{
	char szLifeState = *(char*)((DWORD)pEntity + 0x93);

	return (szLifeState == LIFE_ALIVE);
}

int cAimbot::GetTeamNumber(C_BaseEntity* pEntity)
{
	int m_iTeamNum = *(int*)((DWORD)pEntity + 0x9C);
	return m_iTeamNum;
}

bool CGameTrace::DidHitNonWorldEntity() const 
{ 
	return m_pEnt != NULL && !DidHitWorld(); 
}

void cAimbot::SilentAim ( CUserCmd* pCmd, QAngle angAim )
{
	Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	QAngle qMove, qRealView(pCmd->viewangles);
	VectorAngles(vMove, qMove);

	Vector vForward,vRight,vUp,aForward,aRight,aUp,nForward,nRight,nUp;
	QAngle angles;

	float forward = pCmd->forwardmove;
	float right = pCmd->sidemove;
	float up = pCmd->upmove;

	angles.Init(0.0f,pCmd->viewangles.y,0.0f);
	angles.Init(0.0f,pCmd->viewangles.x,0.0f);

	AngleVectors(angles,&vForward,&vRight,&vUp);
	AngleVectors(pCmd->viewangles,&vForward,&vRight,&vUp);

	pCmd->viewangles = angAim;

	angles.Init(pCmd->viewangles.x,pCmd->viewangles.x,pCmd->viewangles.x);//
	angles.Init(pCmd->viewangles.y,pCmd->viewangles.y,pCmd->viewangles.y); 

	AngleVectors(angles,&aForward,&aRight,&aUp);
	AngleVectors(pCmd->viewangles,&aForward,&aRight,&aUp);

	gUtils.Normalize(vForward,nForward);
	gUtils.Normalize(vRight,nRight);
	gUtils.Normalize(vUp,nUp);

	flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
	pCmd->forwardmove = cos(flYaw) * flSpeed;
	pCmd->sidemove = sin(flYaw) * flSpeed;
}

bool cAimbot::autowall( Vector nigg, Vector vPos, C_BaseEntity* pMe )
{

	//DWORD TheTemp[5];
	//static CTraceFilterSkipTwoEntities_t TraceFilter = reinterpret_cast< CTraceFilterSkipTwoEntities_t >( ( DWORD )( GetModuleHandle( "client.dll" ) ) + 0x19BEA0 ); // Address 62dbcb70 Base 62c20000
	//TraceFilter(&TheTemp, pMe, pMe, 0);

	CTraceFilterNoPlayers Filter;

	Ray_t ray;
	trace_t tr;
	ray.Init( nigg, vPos );
	g_pEnginetrace->TraceRay( ray, 0x46004003, (ITraceFilter*)&Filter, &tr ); //0x46004003

	if( tr.startsolid )
		return false;

	if(GetVisible(nigg,pMe))
		return true;

	if(!g_vars.aimwall)
		return false;

	int iMaterial = g_pPhysicAPI->GetSurfaceData( tr.surface.surfaceProps )->game.material;// looks bad? umad its best

	Ray_t ray2;
	ray2.Init( vPos, nigg );
	trace_t tr2;
	g_pEnginetrace->TraceRay( ray2, 0x46004003, (ITraceFilter*)&Filter, &tr2 ); //0x4600400B

	if( tr2.startsolid )
		return false;

	int iMaterial2 = g_pPhysicAPI->GetSurfaceData( tr2.surface.surfaceProps )->game.material;

	float thickness = tr.endpos.DistTo( tr2.endpos );

	bool Wood = iMaterial == 'W' && iMaterial2 == 'W' && thickness <= 128.0f;

	return thickness <= 20 || Wood || tr.fraction == 1.0f || ( tr.DidHitNonWorldEntity() && ( tr.m_pEnt == pMe || (C_BaseEntity*)((DWORD)tr.m_pEnt + 0x46C) == pMe ) );
}

bool bIsDefaultHit( trace_t *pTrace, C_BaseEntity *pEnt )
{
	if( pTrace->allsolid || pTrace->startsolid )
		return false;

	if( pTrace->m_pEnt && ( pTrace->m_pEnt->entindex() == pEnt->entindex() ) )
		return true;

	if( pTrace->fraction >= 2.97f )
		return false;

	return false;
}

__forceinline void Trace( Vector vecStart, Vector vecEnd, unsigned int uiMask, ITraceFilter* pFilter, trace_t *trMain )
{
	Ray_t ray;

	ray.Init( vecStart, vecEnd );

	g_pEnginetrace->TraceRay( ray, MASK_SHOT, NULL, trMain );
}

bool cAimbot::bCheckVisible( Vector &vecAbs ,Vector &vecDest, C_BaseEntity *pEnt )
{
	if (!pEnt)
		return false;

	C_BaseEntity *pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();

	if (!pLocal)
		return false;

	trace_t trTrace;

	Trace(vecAbs, vecDest, 0x46004003, NULL, &trTrace);

	if (bIsDefaultHit(&trTrace, pEnt))
		return true;

	return false;
}

bool cAimbot::getvis(C_BaseEntity *TargetEntity, C_BaseEntity *LocalPlayer, const Vector &TargetPosition, const Vector &EyePos) // tracefilter som ikke skal updates<< :o
{
	CTraceFilterNoPlayers Filter;
	trace_t Trace;
	Ray_t Ray;

	Ray.Init(EyePos, TargetPosition);

	//DWORD TraceFilter[5];

	g_pEnginetrace->TraceRay(Ray, 0x46004003, (ITraceFilter*)&Filter, &Trace);

	return (Trace.fraction == 1.f);
}

bool cAimbot::weaponsawp()
{
	C_BaseEntity*pLocalPlayer = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocalPlayer);
	if(!pWeapon)
		return false;
	int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
	bool MiscWpn = ((iWeaponID == 3) ? true : false);
	if(MiscWpn)
		return true;
	return false;
}

bool cAimbot::weaponsawp2()
{
	C_BaseEntity*pLocalPlayer = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocalPlayer);
	if(!pWeapon)
		return false;
	int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
	bool MiscWpn = ((iWeaponID == 25) ? true : false);
	if(MiscWpn)
		return true;
	return false;
}

bool cAimbot::weaponsawp3()
{
	C_BaseEntity*pLocalPlayer = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocalPlayer);
	if(!pWeapon)
		return false;
	int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
	bool MiscWpn = ((iWeaponID == 27) ? true : false);
	if(MiscWpn)
		return true;
	return false;
}

float cAimbot::GetRadius( Vector MyEyePosition, C_BaseEntity* pEntity )
{
	QAngle View;
	g_pEngine->GetViewAngles( View );

	Vector Direction;
	AngleVectors( View, &Direction );

	Vector EnemyEyePosition = ( pEntity->GetAbsOrigin() + *reinterpret_cast<Vector*>( (size_t)pEntity + 0xE8 ) );

	Vector EyeDelta = ( EnemyEyePosition - MyEyePosition );
	EyeDelta.NormalizeInPlace();

	float Distance = RAD2DEG( acos( Direction.Dot( EyeDelta ) ) );

	if ( Distance > 0 )
	{
		return Distance;
	}
	else
	{
		return 0;
	}
}



Vector positions[64];
struct lelez{
	Vector vectorens;//sec lookikng on my pc
};
typedef std::vector<lelez> lawlzor_t;
lawlzor_t lele;
void cAimbot::Main(CUserCmd* pUserCmd)
{
	IClientEntity* pBaseEntClient;
	C_BaseEntity* pLocal, *pBaseEnt;
	Vector vMyEyePosition, vDelta, vTemp;
	C_BasePlayer*pLocalPlayer = (C_BasePlayer*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	CUserCmd *Cmd;
	C_BaseCombatWeapon* weapon = gNospread.GetBaseCombatActiveWeapon(pLocalPlayer);
	int gay = *(int*)((DWORD)pLocalPlayer + 0x1430); //m_iShotsFired
	int m_iClip1 = *(int*)((DWORD)weapon + 0x8BC);
	C_BaseCombatWeapon *m_pWeapon = weapon;
	player_info_t pInfo;

	pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
	if(IsAlive(pLocal))
	{
		vMyEyePosition = Fakelagfix.PredictTheEyePosition(pLocal);
		DropTarget();
		for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
		{
			if(nIndex != g_pEngine->GetLocalPlayer())
			{
				pBaseEntClient = g_pEntList->GetClientEntity(nIndex);
				if(pBaseEntClient && !pBaseEntClient->IsDormant())
				{
					pBaseEnt = pBaseEntClient->GetBaseEntity();
					g_pEngine->GetPlayerInfo(pBaseEntClient->entindex(), &pInfo);
					PredictTarget(pBaseEnt,m_vMyLastEyePosition,pLocalPlayer);
					if(IsAlive(pBaseEnt))
					{
						if(GetTeamNumber(pBaseEnt) != GetTeamNumber(pLocal))
						{
							int hitbox;
							for (int hIndex = 12; hIndex >= 0; --hIndex)
							{
								hitbox = hIndex;
								if (GetHitboxPosition(nIndex, hitbox)) //hitbox
								{
									if(autowall(vMyEyePosition, m_vPosition, pBaseEnt))
									{
										float dick = GetDistance(vMyEyePosition, m_vPosition);
										if(m_flBestDist > dick)
										{
											m_flBestDist = dick;
											m_nTarget = nIndex;
											m_vFinalPosition = m_vPosition;

											lelez lel;
											lel.vectorens = m_vPosition;
											lele.push_back(lel);
										}

									}
									break;
								}
							}
						}
					}
				}
			}


			float closest = 999999999999999;
			Vector finaleh;
			for (lawlzor_t::iterator it = lele.begin(); it != lele.end(); it++){
				if(vMyEyePosition.DistTo(it->vectorens)<closest){
					closest = vMyEyePosition.DistTo(it->vectorens);
					finaleh = (it->vectorens);
				}
			}

			if(m_nTarget != -1)
			{
				C_BaseCombatWeapon *m_pWeapon = weapon;

				if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_HE_GRENADE))
					if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_KNIFE))
						if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_SMOKE_GRENADE))
							if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_FLASHBANG))
								if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_C4))
									pUserCmd->buttons |= IN_ATTACK;

				CalcAngle(vMyEyePosition, m_vFinalPosition, pUserCmd->viewangles);

			}
		}	
	}
}

void cAimbot::MainP100AWP(CUserCmd* pUserCmd, QAngle &ang, bool& bAim, QAngle &aimalways)
{
	IClientEntity* pBaseEntClient;
	C_BaseEntity* pLocal, *pBaseEnt;
	Vector vMyEyePosition, vDelta, vTemp;
	C_BaseCombatWeapon* weapon = gNospread.GetBaseCombatActiveWeapon(pLocal);
	int m_iClip1 = *(int*)((DWORD)weapon + 0x8BC);
	C_BasePlayer*pLocalPlayer = (C_BasePlayer*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	int gay = *(int*)((DWORD)pLocalPlayer + 0x1430); //m_iShotsFired
	player_info_t pInfo;

	pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
	if(IsAlive(pLocal))
	{
		vMyEyePosition = Fakelagfix.PredictTheEyePosition(pLocal);
		DropTarget();
		for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
		{
			if(nIndex != g_pEngine->GetLocalPlayer())
			{
				pBaseEntClient = g_pEntList->GetClientEntity(nIndex);
				if(pBaseEntClient && !pBaseEntClient->IsDormant())
				{
					pBaseEnt = pBaseEntClient->GetBaseEntity();
					g_pEngine->GetPlayerInfo(pBaseEntClient->entindex(), &pInfo);
					PredictTarget(pBaseEnt,m_vMyLastEyePosition,pLocalPlayer);
					if(IsAlive(pBaseEnt))
					{
						if(GetTeamNumber(pBaseEnt) != GetTeamNumber(pLocal))
						{
							if (GetHitboxPosition(nIndex, 10)) //9
							{

								//if(autowall(vMyEyePosition, m_vPosition, pBaseEnt))
								if(getvis(pLocal, pBaseEnt, vMyEyePosition, m_vPosition))
								{
									m_flBestDist = GetDistance(vMyEyePosition, m_vPosition);
									m_nTarget = nIndex;
									m_vFinalPosition = m_vPosition;
								}
							}
						}
					}
				}
			}
			C_BaseCombatWeapon* weapon = gNospread.GetBaseCombatActiveWeapon(pLocalPlayer);
			if(m_nTarget != -1)
			{
				C_BaseCombatWeapon *m_pWeapon = weapon;

				if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_HE_GRENADE))
					if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_KNIFE))
						if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_SMOKE_GRENADE))
							if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_FLASHBANG))
								if (!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_C4))
								{
									pUserCmd->buttons |= IN_ATTACK;
								}

								CalcAngle(vMyEyePosition, m_vFinalPosition, pUserCmd->viewangles);

			}
		}	
	}
}

void cAimbot::AtTarget(CUserCmd* pUserCmd, QAngle &ang, bool& bAim, QAngle &aimalways)
{
	IClientEntity* pBaseEntClient;
	C_BaseEntity* pLocal, *pBaseEnt;
	Vector vMyEyePosition, vDelta, vTemp;
	C_BasePlayer*pLocalPlayer = (C_BasePlayer*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
	bool **sendpacket;
	int gay = *(int*)((DWORD)pLocalPlayer + 0x1430); //m_iShotsFired
	pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
	if(IsAlive(pLocal))
	{
		vMyEyePosition = Fakelagfix.PredictTheEyePosition(pLocal);
		DropTarget();
		for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
		{
			if(nIndex != g_pEngine->GetLocalPlayer())
			{
				pBaseEntClient = g_pEntList->GetClientEntity(nIndex);
				if(pBaseEntClient && !pBaseEntClient->IsDormant())
				{
					pBaseEnt = pBaseEntClient->GetBaseEntity();
					player_info_t pInfo;
					g_pEngine->GetPlayerInfo(pBaseEntClient->entindex(), &pInfo);
					//					if(g_vars.whitevane == 1)
					//{
					//	if(strcmp("STEAM_0:1:60528679", pInfo.guid))
					//		continue;
					//}
					//if(g_vars.whitezylx == 1)
					//{
					//	if(strcmp("STEAM_0:0:54354000", pInfo.guid))
					//		continue;
					//}
					//if(g_vars.whiteneo == 1)
					//{
					//	if(strcmp("STEAM_0:0:5686073", pInfo.guid))
					//		continue;
					//}
					if(IsAlive(pBaseEnt))
					{
						if(GetTeamNumber(pBaseEnt) != GetTeamNumber(pLocal))
						{
							if (GetHitboxPosition(nIndex, 10))
							{
								//CalcAngle(vMyEyePosition, m_vFinalPosition, aimalways);

								//if(autowall(vMyEyePosition, m_vPosition, pBaseEnt))
								//if(rasmustuderoveratdenikkeskyderladosfixedetez(pLocal, pBaseEnt, vMyEyePosition, m_vPosition))
								//{
								m_flBestDist = GetDistance(vMyEyePosition, m_vPosition);
								m_nTarget = nIndex;
								m_vFinalPosition = m_vPosition;
								//}
							}
						}
					}
				}
			}

			if(m_nTarget != -1)
			{
				float AtTargetAngle = 0;
				QAngle attargety;
				CalcAngle(vMyEyePosition, m_vFinalPosition, attargety);

				pUserCmd->viewangles.y = attargety.y;



				//pUserCmd->viewangles.x = 89;
				//pUserCmd->viewangles.y -= 360;


				//Vector TheAng;
				//CalcAngle(EyePosErP100, vFinal, TheAng);

				//Vector otherAngles;
				//TheAng.y = otherAngles.y;

				//angl->viewangles.y = TheAng.y;
				//angl->viewangles.y -= angleofthem;
			}
		}	
	}
}

