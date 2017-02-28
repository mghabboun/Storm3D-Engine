#ifndef STORM3D_UNIFORMS
#define STORM3D_UNIFORMS

#include "Uniform.h" 

template < typename T, int count, UniformType uniformType >
class UniformDerived : public Uniform
{
	typedef T type;
	const enum values{ elementCount = count , elementSize = sizeof(T) };
	//============================================================
public:

	const enum {Type = uniformType };


	UniformDerived(Shader* sh, const std::string& name, int location): Uniform( sh, name, location)
	{
		m_type = uniformType;
	}

	//============================================================
	UniformDerived(const std::string& name): Uniform( name )
	{
		m_type = uniformType;
	}

	void SetValue(T* values)
	{
		memcpy( m_elements, values, values::elementCount * values::elementSize  );
		NotifyOwners();
	}

	type* GetValue()
	{
		return m_elements;
	}

	type operator[]( unsigned int i)const
	{
		assert ( i < values::elementCount );
		return m_elements[i];
	}

	typename type m_elements[ values::elementCount ];
};


typedef UniformDerived< float, 4, UniformType::FLOAT_VEC4 > UniformVec4;
typedef UniformDerived< float, 3, UniformType::FLOAT_VEC3 > UniformVec3;
typedef UniformDerived< float, 1, UniformType::FLOAT_ > UniformFloat;

typedef UniformDerived< float, 16, UniformType::FLOAT_MAT4> UniformMat4;
typedef UniformDerived< float, 9, UniformType::FLOAT_MAT3> UniformMat3;
typedef UniformDerived< int, 1, UniformType::SAMPLER_1D> UniformSampler;

#endif 