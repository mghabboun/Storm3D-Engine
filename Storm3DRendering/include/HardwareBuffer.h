#ifndef APP_WORLD_HARDWARE_BUFFER
#define APP_WORLD_HARDWARE_BUFFER

#include "Storm3DRendering/include/VertexStream.h" 
#include "Storm3DRendering/include/DrawAttribs.h"

#include <vector>

class VertexStream;
class Mesh;

class HardwareBuffer
{
public: 

  enum BufferType
  {
    eVertexBuffer        
  };


  HardwareBuffer( Mesh* mesh );
  //HardwareBuffer(  );

  ~HardwareBuffer();


  bool            GenerateBuffer();
  void            AttachData();
  void			SetDrawMode( DrawMode drawMode ){ m_drawMode = drawMode; }
  void            DrawBuffer();
  void            BindBuffer();
  //bool            IsBuffer();

private:
  std::vector<unsigned int>   m_buffId; 
  std::vector<unsigned int>   m_idxBuffId;
  int                         m_vao;
  DrawMode		              m_drawMode;
  VertexStream                m_stream;
  Mesh*                       m_mesh;


  //==========================
  HardwareBuffer(const HardwareBuffer&);

};


#endif 