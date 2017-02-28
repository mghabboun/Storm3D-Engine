#ifndef APP_WORLD_GPU_STREAM
#define APP_WORLD_GPU_STREAM


class Mesh;
class SubMesh;

class VertexStream 
{

public:  

    enum StreamComponent
    {
        Vertex   = 0x1,
        Normal   = 0x2,
        UV1      = 0x4,
        UV2      = 0x8,
        Tangent  = 0x10
    };
  
    enum StreamType
    {
        V  = Vertex ,
        VN = Vertex | Normal,
        VNU = Vertex | Normal | UV1,
        VNUU = Vertex | Normal | UV1 | UV2,
        VNUT = Vertex | Normal | UV1| Tangent,
        VNUUT = Vertex | Normal | UV1| UV2 | Tangent,
//        VNUUT = 0x20
    };
    VertexStream(); 
    void GenerateStream(SubMesh* pMesh);
    void            BindStream();


private: 
//    void GenerateStream();
    void            AnalyzeMeshStreamType(SubMesh* pMesh);

    unsigned int    m_vao;
    StreamType      m_type;
};

#endif