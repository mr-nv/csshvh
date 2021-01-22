#pragma once



#include "main.h"


#define PI_F (float)3.14159265358979323846264338f


enum ERotationMatrix
{
	FORWARD,
	UP,
	LEFT,
	ROTATION_MATRIX
};


// todo check sqrt val
double inline __declspec (naked) __fastcall SquareRoot( double n )
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
}


//__forceinline float SquareRoot( float squared )
//{
//	float sqrt = 0.0f;
//
//	_asm
//	{
//		SQRTSS XMM0, squared
//		MOVSS sqrt, XMM0
//	}
//
//	return sqrt;
//}



class MyMath
{
public:

	static __forceinline float RadiansToDegrees( const float &radians )
	{
		return (float)( radians * (float)( 180.f / PI_F ) );
	}


	static __forceinline float DegreesToRadians( const float &degrees )
	{
		return (float)( degrees * (float)( PI_F / 180.f ) );
	}


	static void NormalizeAngles( QAngle &angle )
	{
		for ( int axis = 2; axis >= 0; --axis )
		{
			while ( angle[axis] > 180.f )
			{
				angle[axis] -= 360.f;
			}

			while ( angle[axis] < -180.f )
			{
				angle[axis] += 360.f;
			}
		}
	}



	static void NormalizeVector( Vector &vec )
	{
		float length = SquareRoot( (float)( vec.x * vec.x ) + (float)( vec.y * vec.y ) + (float)( vec.z * vec.z ) );

		if ( length != 0.f )
		{
			vec /= length;
		}
		//else
		//{
		//	LOG_ERROR( "NormalizeVector: attempted devision by 0" );
		//}
	}

	static Vector NormalizeVectorSecond( Vector vec )
	{
		float length = SquareRoot( (float)( vec.x * vec.x ) + (float)( vec.y * vec.y ) + (float)( vec.z * vec.z ) );

		if ( length != 0.f )
		{
			vec /= length;
		}
		//else
		//{
		//	LOG_ERROR( "NormalizeVector: attempted devision by 0" );
		//}
		return vec;
	}

	// fixme



	static void CrossProduct( const Vector &vector1, const Vector &vector2, Vector &cross )
	{
		cross.x = ( ( vector1.y * vector2.z ) - ( vector1.z * vector2.y ) );
		cross.y = ( ( vector1.z * vector2.x ) - ( vector1.x * vector2.z ) );
		cross.z = ( ( vector1.x * vector2.y ) - ( vector1.y * vector2.x ) );
	}


	static void VectorToAngles( const Vector &direction, const Vector &up, QAngle &angles )
	{
		Vector left;

		MyMath::CrossProduct( up, direction, left );
		MyMath::NormalizeVector( left );		

		float len2D = SquareRoot( ( direction.x * direction.x ) + ( direction.y * direction.y ) );

		angles.x = MyMath::RadiansToDegrees( atan2( -direction.z, len2D ) );


		if ( len2D > .001f )
		{
			angles.y = MyMath::RadiansToDegrees( atan2( direction.y, direction.x ) );

			// todo: if > 84 || < -84, sqrt / dunno if this is needed
			float zUp =  ( ( left.y * direction.x ) - (left.x * direction.y ) );

			angles.z = MyMath::RadiansToDegrees( atan2( left.z, zUp ) );
		}
		// gimbal lock
		else
		{
			angles.y = MyMath::RadiansToDegrees( atan2( -left.x, left.y ) );
			angles.z = 0.f;
		}


		MyMath::NormalizeAngles( angles );
	}


	static void AngleToVectors( const QAngle &angles, Vector *forward, Vector *right, Vector *up )
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos( DegreesToRadians( angles.y ), &sy, &cy );
		SinCos( DegreesToRadians( angles.x ), &sp, &cp );
		SinCos( DegreesToRadians( angles.z ), &sr, &cr );

		if (forward)
		{
			forward->x = cp*cy;
			forward->y = cp*sy;
			forward->z = -sp;

			MyMath::NormalizeVector( *forward );
		}

		if (right)
		{
			right->x = (-1*sr*sp*cy+-1*cr*-sy);
			right->y = (-1*sr*sp*sy+-1*cr*cy);
			right->z = -1*sr*cp;

			MyMath::NormalizeVector( *right );
		}

		if (up)
		{
			up->x = (cr*sp*cy+-sr*-sy);
			up->y = (cr*sp*sy+-sr*cy);
			up->z = cr*cp;

			MyMath::NormalizeVector( *up );
		}
	}
};