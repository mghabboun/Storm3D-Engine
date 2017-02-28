#ifndef STORM_3D_DEFS
#define STORM_3D_DEFS

typedef unsigned char byte;
typedef unsigned int  uint;
typedef long long     int64;


enum UniformType
{
    FLOAT_              = 0x1406,
    FLOAT_VEC2          = 0x8B50,
    FLOAT_VEC3          = 0x8B51,
    FLOAT_VEC4          = 0x8B52,
    INT_VEC2            = 0x8B53,
    INT_VEC3            = 0x8B54,
    INT_VEC4            = 0x8B55,
    BOOL_               = 0x8B56,
    BOOL_VEC2           = 0x8B57,
    BOOL_VEC3           = 0x8B58,
    BOOL_VEC4           = 0x8B59,
    FLOAT_MAT2          = 0x8B5A,
    FLOAT_MAT3          = 0x8B5B,
    FLOAT_MAT4          = 0x8B5C,
    SAMPLER_1D          = 0x8B5D,
    SAMPLER_2D          = 0x8B5E,
    SAMPLER_3D          = 0x8B5F,
    SAMPLER_CUBE        = 0x8B60,
    SAMPLER_1D_SHADOW   = 0x8B61,
    SAMPLER_2D_SHADOW   = 0x8B62
};

#endif