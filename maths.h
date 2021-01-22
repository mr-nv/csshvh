#ifndef MATHS
#define MATHS

#include "main.h"
//creds to kiro

namespace Maths
{
	static double inline __declspec (naked) __fastcall SquareRoot( double n )
	{
		_asm fld qword ptr [esp+4]
		_asm fsqrt
		_asm ret 8
	}

	static float RadiansToDegrees( const float &radians )
	{
		return (float)( radians * (float)( 180.f / M_PI_F ) );
	}

	static float DegreesToRadians( const float &degrees )
	{
		return (float)( degrees * (float)( M_PI_F / 180.f ) );
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

	static void NormalizeAngle( float &angle )
	{
		while ( angle > 180.f )
		{
			angle -= 360.f;
		}

		while ( angle < -180.f )
		{
			angle += 360.f;
		}
	}

	static void NormalizeVector2D( Vector2D &vec )
	{
		float length = SquareRoot( (float)( vec.x * vec.x ) + (float)( vec.y * vec.y ) );

		if ( length != 0.f )
		{
			vec /= length;
		}
	}

	static void NormalizeVector( Vector &vec )
	{
		float length = SquareRoot( (float)( vec.x * vec.x ) + (float)( vec.y * vec.y ) + (float)( vec.z * vec.z ) );

		if ( length != 0.f )
		{
			vec /= length;
		}
	}

	static void NormalizeVector( float *vec )
	{
		float length = SquareRoot( (float)( vec[0] * vec[0] ) + (float)( vec[1] * vec[1] ) + (float)( vec[2] * vec[2] ) );

		if ( length != 0.f )
		{
			vec[0] /= length;
			vec[1] /= length;
			vec[2] /= length;
		}
	}

	static Vector NormalizeVectorSecond( Vector vec )
	{
		float length = SquareRoot( (float)( vec.x * vec.x ) + (float)( vec.y * vec.y ) + (float)( vec.z * vec.z ) );

		if ( length != 0.f )
		{
			vec /= length;
		}

		return vec;
	}

	static void VectorToAngles( const Vector &direction, QAngle &angles )
	{
		if ( ( direction.y == 0.f ) && ( direction.x == 0.f ) )
		{
			if ( direction.z > 0.f )
			{
				angles.x = 270.f;
			}
			else
			{
				angles.x = 90.f;
			}

			angles.y = 0.f;
		}
		else
		{
			angles.x = RadiansToDegrees( atan2f( -direction.z, SquareRoot( ( direction.x * direction.x ) + ( direction.y * direction.y ) ) ) );

			angles.y = RadiansToDegrees( atan2f( direction.y, direction.x ) );

			if ( angles.y < 0.f )
			{
				angles.y += 360.f;
			}
		}

		angles.z = 0.f;

		Maths::NormalizeAngles( angles );
	}

	static float DotProduct(const float *v1, const float *v2)
	{
		return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
	}

	static float DotProduct(const Vector v1, const float *v2)
	{
		return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
	}

	static void VectorTransform (const float *in1, const matrix3x4_t& in2, float *out)
	{
		out[0] = DotProduct(in1, in2[0]) + in2[0][3];
		out[1] = DotProduct(in1, in2[1]) + in2[1][3];
		out[2] = DotProduct(in1, in2[2]) + in2[2][3];
	}

	static void VectorTransform (const Vector &in1, const matrix3x4_t& in2, Vector &out)
	{
		out[0] = DotProduct(in1, in2[0]) + in2[0][3];
		out[1] = DotProduct(in1, in2[1]) + in2[1][3];
		out[2] = DotProduct(in1, in2[2]) + in2[2][3];
	}

	static void CrossProduct( const Vector &vector1, const Vector &vector2, Vector &cross )
	{
		cross.x = ( ( vector1.y * vector2.z ) - ( vector1.z * vector2.y ) );
		cross.y = ( ( vector1.z * vector2.x ) - ( vector1.x * vector2.z ) );
		cross.z = ( ( vector1.x * vector2.y ) - ( vector1.y * vector2.x ) );
	}

	static void CrossProduct( const float *vector1, const float *vector2, float *cross )
	{
		cross[0] = ( ( vector1[1] * vector2[2] ) - ( vector1[2] * vector2[1] ) );
		cross[1] = ( ( vector1[2] * vector2[0] ) - ( vector1[0] * vector2[2] ) );
		cross[2] = ( ( vector1[0] * vector2[1] ) - ( vector1[1] * vector2[0] ) );
	}


	static void VectorToAngles( const Vector &direction, const Vector &up, QAngle &angles )
	{
		Vector left;

		Maths::CrossProduct( up, direction, left );
		NormalizeVector( left );		

		float len2D = SquareRoot( ( direction.x * direction.x ) + ( direction.y * direction.y ) );

		angles.x = RadiansToDegrees( atan2( -direction.z, len2D ) );


		if ( len2D > .001f )
		{
			angles.y = RadiansToDegrees( atan2( direction.y, direction.x ) );

			// todo: if > 84 || < -84, sqrt / dunno if this is needed
			float zUp =  ( ( left.y * direction.x ) - (left.x * direction.y ) );

			angles.z = RadiansToDegrees( atan2( left.z, zUp ) );
		}
		// gimbal lock
		else
		{
			angles.y = RadiansToDegrees( atan2( -left.x, left.y ) );
			angles.z = 0.f;
		}


		Maths::NormalizeAngles( angles );
	}

	static void AngleToVectors (const QAngle &angles, Vector *forward)
	{
		float	sp, sy, cp, cy;

		SinCos( DegreesToRadians( angles[YAW] ), &sy, &cy );
		SinCos( DegreesToRadians( angles[PITCH] ), &sp, &cp );

		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
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

			NormalizeVector( *forward );
		}

		if (right)
		{
			right->x = (-1*sr*sp*cy+-1*cr*-sy);
			right->y = (-1*sr*sp*sy+-1*cr*cy);
			right->z = -1*sr*cp;

			NormalizeVector( *right );
		}

		if (up)
		{
			up->x = (cr*sp*cy+-sr*-sy);
			up->y = (cr*sp*sy+-sr*cy);
			up->z = cr*cp;

			NormalizeVector( *up );
		}
	}

	template <class T> T Lerp( float flPercent, T const &A, T const &B )
	{
		return B + (B - A) * flPercent;
	}

};

#endif