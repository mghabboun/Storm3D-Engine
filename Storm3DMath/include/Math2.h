#ifndef APP_WORLD_MATH_H_
#define APP_WORLD_MATH_H_
//
//#include "AppWorldVector2.h"
//#include "AppWorldVector3.h"
//#include "AppWorldRay.h"
#include <cmath>
#include <limits> 
#include <utility>
#include <assert.h>
#include <algorithm> 

class Math 
{
public:

    static inline int IAbs (int iValue) { return ( iValue >= 0 ? iValue : -iValue ); }
    static inline int ICeil (float fValue) { return int(ceil(fValue)); }
    static inline int IFloor (float fValue) { return int(floor(fValue)); }
    static int ISign (int iValue);

    static inline float Abs (float fValue) { return float(fabs(fValue)); }
    static float ACos (float fValue);
    static float ASin (float fValue);
    static inline float ATan (float fValue) { return atan(fValue); }
    static inline float ATan2 (float fY, float fX) { return atan2(fY,fX); }
    static inline float Ceil (float fValue) { return float(ceil(fValue)); }
    static inline bool IsNaN(float f)
    {
        // std::isnan() is C99, not supported by all compilers
        // However NaN always fails this next test, no other number does.
        return f != f;
    }

    // Cosine function.
    static inline float Cos (float rad) { return float(cos(rad)); }

    static inline float Exp (float rad) { return float(exp(rad)); }

    static inline float Floor (float value) { return float(floor(value)); }

    static inline float Log (float value) { return float(log(value)); }

    /// Stored value of log(2) for frequent use
    static const float LOG2;

    static inline float Log2 (float fValue) { return float(log(fValue)/LOG2); }

    static inline float LogN (float base, float fValue) { return float(log(fValue)/log(base)); }

    static inline float Pow (float fBase, float fExponent) { return float(pow(fBase,fExponent)); }

    static float Sign (float fValue);       

    static inline float Sin (float rad){  return float(sin(rad));  }

    static inline float Sqr (float fValue) { return fValue*fValue; }

    static inline float Sqrt (float fValue) { return float(sqrt(fValue)); }

    static float InvSqrt(float fValue); // Inverse square root i.e. 1 / Sqrt(x), good for vector   normalisation.

    static float UnitRandom ();  // in [0,1]

    static float RangeRandom (float fLow, float fHigh);  // in [fLow,fHigh]

    static float SymmetricRandom ();  // in [-1,1]

    // Tangent function. rad Angle in radians
    static inline float Tan(const float& rad){ return float(tan(rad)); }

    static inline float DegreesToRadians(float degrees) { return degrees * fDeg2Rad; }
    static inline float RadiansToDegrees(float radians) { return radians * fRad2Deg; }

    // Compare 2 floats, using tolerance for inaccuracies.
    static bool floatEqual(float a, float b,  float tolerance = std::numeric_limits<float>::epsilon());

    /// Clamp a value within an inclusive range. */
    template <typename T>
    static T Clamp(T val, T minval, T maxval)
    {
        assert (minval < maxval && "Invalid clamp range");
        return std::max(std::min(val, maxval), minval);            
    }

    //
    ///** Calculates the tangent space vector for a given set of positions / texture coords. */
    //static Vector3 calculateTangentSpaceVector( const Vector3& position1, const Vector3& position2, const Vector3& position3, float u1, float v1, float u2, float v2, float u3, float v3);

    ///** Build a reflection matrix for the passed in plane. */
    //static Matrix4 BuildReflectionMatrix(const Plane& p);
    ///** Calculate a face normal, including the w component which is the offset from the origin. */
    //static Vector4 CalculateFaceNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    ///** Calculate a face normal, no w-information. */
    //static Vector3 CalculateBasicFaceNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    ///** Calculate a face normal without normalize, including the w component which is the offset from the origin. */
    //static Vector4 CalculateFaceNormalWithoutNormalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    ///** Calculate a face normal without normalize, no w-information. */
    //static Vector3 CalculateBasicFaceNormalWithoutNormalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);

    ///** Generates a value based on the Gaussian (normal) distribution function
    //with the given offset and scale parameters.
    //*/
    //static float GaussianDistribution(float x, float offset = 0.0f, float scale = 1.0f);        

    //static Matrix4 MakeViewMatrix(const Vector3& position, const Quaternion& orientation, 
    //    const Matrix4* ReflectMatrix = 0);

    ///** Get a bounding radius value from a bounding box. */
    //static float BoundingRadiusFromAABB(const AxisAlignedBox& aabb);

    static const float POS_INFINITY;
    static const float NEG_INFINITY;
    static const float PI;
    static const float TWO_PI;
    static const float HALF_PI;
    static const float fDeg2Rad;
    static const float fRad2Deg;

};
#endif
