# pragma once

#include "izCompileConfig.h"
#include"izTypes.h"
#include<math.h>
#include<float.h>

namespace iz
{
	namespace core
	{
		//! Rounding error constant often used when comparing f32 values.

		const s32 ROUNDING_ERROR_S32 = 0;
		const s64 ROUNDING_ERROR_S64 = 0;

		const f32 ROUNDING_ERROR_f32 = 0.000001f;
		const f64 ROUNDING_ERROR_f64 = 0.00000001;

		//! Constant for PI.
		const f32 PI = 3.14159265359f;
		//! Constant for reciprocal of PI.
		const f32 RECIPROCAL_PI = 1.0f / PI;
		//! Constant for half of PI.
		const f32 HALF_PI = PI / 2.0f;

		//! Constant for 64bit PI.
		const f64 PI64 = 3.1415926535897932384626433832795028841971693993751;
		//! Constant for 64bit reciprocal of PI.
		const f64 RECIPROCAL_PI64 = 1.0 / PI64;

		//! 32bit Constant for converting from degrees to radians
		const f32 DEGTORAD = PI / 180.0f;
		//! 32bit constant for converting from radians to degrees (formally known as GRAD_PI)
		const f32 RADTODEG = 180.0f / PI;

		//! 64bit constant for converting from degrees to radians (formally known as GRAD_PI2)
		const f64 DEGTORAD64 = PI64 / 180.0;
		//! 64bit constant for converting from radians to degrees
		const f64 RADTODEG64 = 180.0 / PI64;

		//! Utility function to convert a radian value to degrees
		/** Provided as it can be clearer to write radToDeg(X) than RADTODEG * X
		\param radians	The radians value to convert to degrees.
		*/
		inline f32 radToDeg(f32 radians)
		{
			return RADTODEG * radians;
		}
		//! Utility function to convert a radian value to degrees
		/** Provided as it can be clearer to write radToDeg(X) than RADTODEG * X
		\param radians	The radians value to convert to degrees.
		*/
		inline f64 radToDeg(f64 radians)
		{
			return RADTODEG64 * radians;
		}

		//! Utility function to convert a degrees value to radians
		/** Provided as it can be clearer to write degToRad(X) than DEGTORAD * X
		\param degrees	The degrees value to convert to radians.
		*/
		inline f32 degToRad(f32 degrees)
		{
			return DEGTORAD * degrees;
		}
		//! Utility function to convert a degrees value to radians
		/** Provided as it can be clearer to write degToRad(X) than DEGTORAD * X
		\param degrees	The degrees value to convert to radians.
		*/
		inline f64 degToRad(f64 degrees)
		{
			return DEGTORAD64 * degrees;
		}

		//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& min_(const T& a, const T& b)
		{
			return a < b ? a : b;
		}
		//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& min_(const T& a, const T& b, const T& c)
		{
			return a < b ? min_(a, c) : min_(b, c);
		}

		//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& max_(const T& a, const T& b)
		{
			return a < b ? b : a;
		}

		//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& max_(const T& a, const T& b, const T& c)
		{
			return a < b ? max_(b, c) : max_(a, c);
		}

		//! return abs of two values. Own implementation to get rid of STL(VS6 problems)
		template<class T>
		inline T abs_(const T& a)
		{
			return a < (T)0 ? -a : a;
		}

		//! returns linear interpolation of a and b with ratio t
		//! \return: a if t==0, b if t==1, and the linear interpolation else
		template<class T>
		inline T lerp(const T& a, const T& b, const f32 t)
		{
			return (T)(a*(1.0f - t)) + (b*t);
		}

		//! clamps a value between low and high
		template<class T>
		inline const T clamp(const T& value, const T& low, const T& high)
		{
			return min_(max_(value, low), high);
		}

		//! swaps the content of the passed parameters
		template<class T1, class T2>
		inline void swap(T1& a, T2& b)
		{
			T1 c(a);
			a = b;
			b = c;
		}

		//! returns if a equals b, taking possible rounding errors into account
		inline bool equals(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_f64)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals b, taking possible rounding errors into account
		inline bool equals(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_f32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		union FloatIntUnion32
		{
			FloatIntUnion32(float f1 = 0.0f) :f(f1){}

			bool sign()const{ return (i >> 31) != 0; }

			iz::s32 i;
			iz::f32 f;
		};

		//! skip this function,never be used
		//inline bool equalsByUlp(f32 a, f32 b, int maxUlpDiff)


		//! returns if a equals b, taking an explicit rounding tolerance(摄入误差) into account
		inline bool equals(const s32 a, const s32 b, const s32 tolerance = ROUNDING_ERROR_S32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//! returns if a equals b, taking an explicit rounding tolerance into account
		inline bool equals(const u32 a, const u32 b, const s32 tolerance = ROUNDING_ERROR_S32)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}
		//! returns if a equals b, taking an explicit rounding tolerance into account
		inline bool equals(const s64 a, const s64 b, const s64 tolerance = ROUNDING_ERROR_S64)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const f64 a, const f64 tolerance = ROUNDING_ERROR_f64)
		{
			return fabs(a) <= tolerance;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const f32 a, const f32 tolerance = ROUNDING_ERROR_f32)
		{
			return fabsf(a) <= tolerance;
		}
		//! returns if a equals not zero, taking rounding errors into account
		inline bool isnotzero(const f32 a, const f32 tolerance = ROUNDING_ERROR_f32)
		{
			return fabsf(a) > tolerance;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const s32 a, const s32 tolerance = 0)
		{
			return (a & 0x7ffffff) <= tolerance;//2的27次方为134217728。0x7ffffff为134217727
		}
		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const u32 a, const u32 tolerance = 0)
		{
			return a <= tolerance;
		}
		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const s64 a, const s64 tolerance = 0)
		{
			return abs_(a) <= tolerance;
		}


		inline s32 s32_min(s32 a, s32 b)
		{
			const s32 mask = (a - b) >> 31;
			return (a & mask) | (b & ~mask);
		}
		inline s32 s32_max(s32 a, s32 b)
		{
			const s32 mask = (a - b) >> 31;
			return (b & mask) | (a & ~mask);
		}
		inline s32 s32_clamp(s32 value, s32 low, s32 high)
		{
			return s32_min(s32_max(value, low), high);
		}


		typedef union { u32 u; s32 s; f32 f; } inttofloat;
		inline u32 IR(f32 x) { inttofloat tmp; tmp.f = x; return tmp.u; }


		//! Absolute integer representation of a floating-point value
#define AIR(x)				(IR(x)&0x7fffffff)
		inline f32 FR(u32 x) { inttofloat tmp; tmp.u = x; return tmp.f; }
		inline f32 FR(s32 x) { inttofloat tmp; tmp.s = x; return tmp.f; }


		//! integer representation of 1.0
#define IEEE_1_0			0x3f800000
		//! integer representation of 255.0
#define IEEE_255_0			0x437f0000

#define	F32_LOWER_0(n)		((n) <  0.0f)
#define	F32_LOWER_EQUAL_0(n)	((n) <= 0.0f)
#define	F32_GREATER_0(n)	((n) >  0.0f)
#define	F32_GREATER_EQUAL_0(n)	((n) >= 0.0f)
#define	F32_EQUAL_1(n)		((n) == 1.0f)
#define	F32_EQUAL_0(n)		((n) == 0.0f)
#define	F32_A_GREATER_B(a,b)	((a) > (b))


#define REALINLINE __forceinline		//强制inline
		//! conditional set based on mask and arithmetic shift
		REALINLINE u32 if_c_a_else_b(const s32 condition, const u32 a, const u32 b)
		{
			return ((-condition >> 31)&(a^b)) ^ b;
		}
		//! conditional set based on mask and arithmetic shift
		REALINLINE u16 if_c_a_else_b(const s16 condition, const u16 a, const u16 b)
		{
			return ((-condition >> 15) & (a ^ b)) ^ b;
		}

		//! conditional set based on mask and arithmetic shift
		REALINLINE u32 if_c_a_else_0(const s32 condition, const u32 a)
		{
			return (-condition >> 31) & a;
		}

		REALINLINE void setbit_cond(u32 &state, s32 condition, u32 mask)
		{
			state ^= ((-condition >> 31) ^ state)&mask;
		}

		// rounding
		inline f32 round_(f32 x)
		{
			return floorf(x + 0.5f);
		}
		// calculate: sqrt ( x )
		REALINLINE f32 squareroot(const f32 f)
		{
			return sqrtf(f);
		}
		// calculate: sqrt ( x )
		REALINLINE f64 squareroot(const f64 f)
		{
			return sqrt(f);
		}
		//calculate: sqrt(x)
		REALINLINE s32 squareroot(const s32 f)
		{
			return static_cast<s32>(squareroot(static_cast<f32>(f)));
		}
		//calculate: sqrt(x)
		REALINLINE s64 squareroot(const s64 f)
		{
			return static_cast<s64>(squareroot(static_cast<f64>(f)));
		}
		// calculate: 1 / sqrt ( x )
		REALINLINE f64 reciprocal_squareroot(const f64 x)
		{
			return 1.0 / sqrt(x);
		}

		// calculate: 1 / sqrtf ( x )
		REALINLINE f32 reciprocal_squareroot(const f32 f)
		{
			return 1.f / sqrtf(f);
		}

		// calculate: 1 / sqrtf( x )
		REALINLINE s32 reciprocal_squareroot(const s32 x)
		{
			return static_cast<s32>(reciprocal_squareroot(static_cast<f32>(x)));
		}

		// calculate: 1 / x
		REALINLINE f32 reciprocal(const f32 f)
		{
			return 1.f / f;
		}
		// calculate: 1 / x
		REALINLINE f64 reciprocal(const f64 f)
		{
			return 1.0 / f;
		}

		// calculate: 1 / x, low precision allowed
		REALINLINE f32 reciprocal_approxim(const f32 f)
		{
			return 1.f / f;
		}
		//Downward rounding
		REALINLINE s32 floor32(f32 x)
		{
			return (s32)floorf(x);
		}
		//Upward rounding
		REALINLINE s32 ceil32(f32 x)
		{
			return (s32)ceilf(x);
		}

		REALINLINE s32 round32(f32 x)
		{
			return (s32)round_(x);
		}
		inline f32 f32_max3(const f32 a, const f32 b, const f32 c)
		{
			return a > b ? (a > c ? a : c) : (b > c ? b : c);
		}

		inline f32 f32_min3(const f32 a, const f32 b, const f32 c)
		{
			return a < b ? (a < c ? a : c) : (b < c ? b : c);
		}
		//Get the decimal part
		inline f32 fract(f32 x)
		{
			return x - floorf(x);
		}
	}//end namespace core

}//end namespace iz


