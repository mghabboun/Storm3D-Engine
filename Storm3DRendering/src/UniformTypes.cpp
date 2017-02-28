#include "Storm3DRendering/include/UniformTypes.h" 

#include "glew/include/GL/glew.h" 

//============================================================
//UniformFloat::UniformFloat(Shader* sh, const std::string& name, int location): Uniform( sh,name, location)
//{
//    m_type = FLOAT_;
//}
//
////============================================================
//UniformFloat::UniformFloat(const std::string& name): Uniform( name)
//{
//    m_type = FLOAT_;
//}
////============================================================
//void UniformFloat::SetValue(const float* value, int elementCount)
//{
//    if (m_value != *value)
//    {
//        NotifyOwners();
//        m_value = value[0];
//    }
//}
//
////============================================================
//UniformMat4::UniformMat4(Shader* sh, const std::string& name, int location): Uniform( sh, name, location)
//{
//    m_type = FLOAT_MAT4;
//}
//
////============================================================
//UniformMat4::UniformMat4(const std::string& name): Uniform( name )
//{
//    m_type = FLOAT_MAT4;
//}
//
////============================================================
//void UniformMat4::SetValue(const float* value, int elementCount)
//{
//    NotifyOwners();
//    for (int i=0; i < elementCount; ++i)
//        m_value[i] = value[i];
//}
//



////============================================================
// UniformVec4::UniformVec4(Shader* sh, const std::string& name, int location): Uniform( sh, name, location)
// {
//     m_type = UniformType::FLOAT_VEC4;
// }
//
////============================================================
// UniformVec4::UniformVec4(const std::string& name): Uniform( name )
// {
//     m_type = UniformType::FLOAT_VEC4;
// }
//
////============================================================
//void UniformVec4::SetValue(const float* value, int elementCount)
//{
//    NotifyOwners();
//
//	//TODO use memcpy instead
//    for (int i=0; i < elementCount; ++i)
//        m_value[i] = value[i];
//}

//============================================================
// UniformVec3::UniformVec3(Shader* sh, const std::string& name, int location): Uniform( sh, name, location)
// {
//     m_type = UniformType::FLOAT_VEC3;
// }
//
////============================================================
// UniformVec3::UniformVec3(const std::string& name): Uniform( name )
// {
//     m_type = UniformType::FLOAT_VEC3;
// }

//============================================================
//void UniformVec3::SetValue(const float* value, int elementCount)
//{
//    NotifyOwners();
//    for (int i=0; i < elementCount; ++i)
//        m_value[i] = value[i];
//}
//
////============================================================
//UniformMat3::UniformMat3(Shader* sh, const std::string& name, int location): Uniform( sh, name, location)
//{
//    m_type = FLOAT_MAT3;
//}
//
////============================================================
//UniformMat3::UniformMat3(const std::string& name): Uniform( name )
//{
//    m_type = FLOAT_MAT3;
//}
//
////============================================================
//void UniformMat3::SetValue(const float* value, int elementCount)
//{
//    NotifyOwners();
//    for (int i=0; i < elementCount; ++i)
//        m_value[i] = value[i];
//}
//
////============================================================
//UniformSampler::UniformSampler(Shader* sh, const std::string& name, int location): Uniform( sh, name, location)
//{
//    m_type = SAMPLER_2D;
//}
//
////============================================================
//UniformSampler::UniformSampler(const std::string& name): Uniform( name )
//{
//    m_type = SAMPLER_2D;
//}
//
////============================================================
//void UniformSampler::SetValue(const float* value, int elementCount)
//{
//    NotifyOwners();
//    m_value = (int)(*value);
//}
//
//
//void UniformSampler::SetTargetUnit(int unit)
//{
//    NotifyOwners();
//    m_value = unit;
//}
//
//



