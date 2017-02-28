#include "Storm3DCore/include/SubMesh.h"

SubMesh::SubMesh()
{

}

//============================================
void SubMesh::MakeCube(float size)
{
    // cube ///////////////////////////////////////////////////////////////////////
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3
    // vertex coords array
    glm::vec3 vertices[] = 
    {
        glm::vec3(size,size,size),  glm::vec3(-size,size,size),  glm::vec3(-size,-size,size),  glm::vec3(size,-size,size),        // v0-vsize-v2-v3
        glm::vec3(size,size,size),  glm::vec3(size,-size,size),  glm::vec3(size,-size,-size),  glm::vec3(size,size,-size),        // v0-v3-v4-v5
        glm::vec3(size,size,size),  glm::vec3(size,size,-size),  glm::vec3(-size,size,-size),  glm::vec3(-size,size,size),        // v0-v5-v6-vsize
        glm::vec3(-size,size,size),  glm::vec3(-size,size,-size),  glm::vec3(-size,-size,-size),  glm::vec3(-size,-size,size),    // vsize-v6-v7-v2
        glm::vec3(-size,-size,-size), glm::vec3(size,-size,-size),  glm::vec3(size,-size,size),  glm::vec3(-size,-size,size),    // v7-v4-v3-v2
        glm::vec3(size,-size,-size),  glm::vec3(-size,-size,-size),  glm::vec3(-size,size,-size),  glm::vec3(size,size,-size) };   // v4-v7-v6-v5

        m_vertices.assign( vertices, vertices+24 );
        glm::vec3 normals[] = { glm::vec3(0, 0,1),  glm::vec3(0, 0, 1),  glm::vec3(0, 0, 1),    glm::vec3(0, 0, 1),
            glm::vec3(1,0,0),  glm::vec3(1,0,0),  glm::vec3(1,0,0),  glm::vec3(1,0,0),
            glm::vec3(0,1,0),  glm::vec3(0,1,0),  glm::vec3(0,1,0),  glm::vec3(0,1,0),
            glm::vec3(-1,0,0),  glm::vec3(-1,0,0),  glm::vec3(-1,0,0),  glm::vec3(-1,0,0),
            glm::vec3(0,-1,0),  glm::vec3(0,-1,0),  glm::vec3(0,-1,0),  glm::vec3(0,-1,0),
            glm::vec3(0,0,-1),  glm::vec3(0,0,-1),  glm::vec3(0,0,-1),  glm::vec3(0,0,-1) }; 

        m_normals.assign( normals, normals+24);

        glm::vec2 texCoords[] = {glm::vec2(1,1), glm::vec2(0,1), glm::vec2(0,0), glm::vec2(1,0),  glm::vec2(0,1), glm::vec2(0,0), glm::vec2(1,0), glm::vec2(1,1), glm::vec2(0,1), glm::vec2(0,0), glm::vec2(1,0),
            glm::vec2(1,1),  glm::vec2(0,1), glm::vec2(0,0), glm::vec2(1,0), glm::vec2(1,1), glm::vec2(0,1), glm::vec2(0,0), glm::vec2(1,0), glm::vec2(1,1) ,glm::vec2(0,1), glm::vec2(0,0) , glm::vec2(1,0) , glm::vec2(1,1)};

        m_UV1.assign( texCoords, texCoords+24);
        unsigned int triangles[]= { 
            0,1,2, 0,2,3, 
            0,3,4, 0,4,5,
            0,5,6, 0,6,1,
            1,6,7, 1,7,2,
            7,4,3, 7,3,2,
            4,6,7, 4,6,5};

            m_triangles.assign( triangles, triangles+36);
}

//============================================
void SubMesh::MakeTriangle()
{
    m_vertices.push_back(glm::vec3(-1,0,1));
    m_vertices.push_back(glm::vec3(1,0,1));
    m_vertices.push_back(glm::vec3(1,1,1));
    m_vertices.push_back(glm::vec3(-1,1,1));   

    m_triangles.push_back(0);
    m_triangles.push_back(1);
    m_triangles.push_back(2);
    
    m_triangles.push_back(0);
    m_triangles.push_back(2);
    m_triangles.push_back(3);    
}

//============================================
void SubMesh::MakeQuad()
{
	this->AddVertex( -1.0f, -1.0f, 0.0f );
	this->AddVertex( 1.0f, -1.0f, 0.0f );
	this->AddVertex( 1.0f, 1.0f, 0.0f );
	this->AddVertex( -1.0f, 1.0f, 0.0f );

	this->AddUV0( 0.0f, 0.0f);
	this->AddUV0( 1.0f, 0.0f);
	this->AddUV0( 1.0f, 1.0f);
	this->AddUV0( 0.0f, 1.0f);

	this->AddTriangle( 0,1,2 );
	this->AddTriangle( 0,2,3 );

}

void SubMesh::MakePlane( int length, int width )
{	
	int vRowCount = length+1; // length is the row count, moves along Z 
	int vColCount = width+1;  // width is the column count, moves along X

	m_vertices.reserve( (length+1) * (width+1) );
	// Create vertices by row
	float rowStartPos = (length/2.0f);
	float colStartPos = -(width/2.0f);
	for (int j= 0; j < vRowCount; ++j)
	{
		for (int i= 0; i < vColCount; ++i)
		{
			m_vertices.push_back( glm::vec3( colStartPos + i, 0, rowStartPos  - j ) );
			//m_UV1.push_back();
		}
	}

	// Connect the vertices 
	for (int j=0; j < length; ++j)
	{
		for (int i=0; i < width; ++i)
		{
			// cell indices 
			//j*width + i
			//j*width + i+1
			//j*(width+1) + i
			//j*(width+1) + i+1
			const int vertexInRow = width+1; 
			m_triangles.push_back( j*vertexInRow + i  );
			m_triangles.push_back( j*vertexInRow + i+1 );
			m_triangles.push_back( (j+1)*vertexInRow + i );
			
			m_triangles.push_back( j*vertexInRow + i+1 );
			m_triangles.push_back( (j+1)*vertexInRow + i+1 );
			m_triangles.push_back( (j+1)*vertexInRow + i   );
		}
	}

	//
	this->CalculateNormals();
	this->CalculateBounds();
}

//============================================
void  SubMesh::MakePlaneFromImage( int imagelength, int imagewidth, unsigned char* imageData )
{
	int vRowCount = imagelength; 
	int vColCount = imagewidth; 

	int length = (imagelength-1);
	int width = (imagewidth-1);

	m_vertices.reserve( (length+1) * (width+1) );
	m_UV1.reserve( (length+1) * (width+1) );
	
	// Create vertices by row
	float rowStartPos = (length/2.0f);
	float colStartPos = -(width/2.0f);
	for (int j= 0; j < vRowCount; ++j)
	{
		for (int i= 0; i < vColCount; ++i)
		{
			m_vertices.push_back( glm::vec3( colStartPos + i, 0, rowStartPos  - j ) );
			//m_UV1.push_back();
		}
	}

	// Modify the vertices height. 
	// Note. A better aproach is to modify the height while creating the vertices.
	for (int j = 0; j < length; j++)
	{
		for (int i = 0; i < width; i++)
		{
			float height = imageData[(i*width + j)*4 + 0];
			imageData[(i*width + j)*4 + 1] + imageData[(i*width + j)*4 + 2];
			height = height*0.1f;

			m_vertices[j*width + i].y = height;
		}
	}

	// Connect the vertices 
	for (int j=0; j < length-1; ++j)
	{
		for (int i=0; i < width-1; ++i)
		{
			// cell indices 
			//j*width + i
			//j*width + i+1
			//j*(width+1) + i
			//j*(width+1) + i+1
			const int vertexInRow = width+1; 

			m_triangles.push_back( (j+1)*vertexInRow + i );
			m_triangles.push_back( j*vertexInRow + i  );
			m_triangles.push_back( j*vertexInRow + i+1 );
		
			m_triangles.push_back( j*vertexInRow + i+1 );
			m_triangles.push_back( (j+1)*vertexInRow + i+1 );
			m_triangles.push_back( (j+1)*vertexInRow + i   );		}
	}
	
	//
	this->CalculateNormals();
	this->CalculateBounds();
}


//============================================
void SubMesh::CalculateTangents()
{
	if ( m_normals.size() == 0 )
		return; 

    long vertexCount = m_vertices.size();
    glm::vec3 *tan1 = new glm::vec3[vertexCount * 2];
    glm::vec3 *tan2 = tan1 + vertexCount;
    memset( tan1, 0, vertexCount*2*sizeof(glm::vec3));

    long triangleCount = this->TringleCount();
    for (long a = 0; a < triangleCount; a++)
    {
        long i1 = m_triangles[a*3];
        long i2 = m_triangles[a*3 +1];
        long i3 = m_triangles[a*3 +2];

        const glm::vec3& v1 = m_vertices[i1];
        const glm::vec3& v2 = m_vertices[i2];
        const glm::vec3& v3 = m_vertices[i3];

        const glm::vec2& w1 = m_UV1[i1];
        const glm::vec2& w2 = m_UV1[i2];
        const glm::vec2& w3 = m_UV1[i3];

        float x1 = v2.x - v1.x;
        float x2 = v3.x - v1.x;
        float y1 = v2.y - v1.y;
        float y2 = v3.y - v1.y;
        float z1 = v2.z - v1.z;
        float z2 = v3.z - v1.z;

        float s1 = w2.x - w1.x;
        float s2 = w3.x - w1.x;
        float t1 = w2.y - w1.y;
        float t2 = w3.y - w1.y;

        float r = 1.0F / (s1 * t2 - s2 * t1);
        glm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
            (t2 * z1 - t1 * z2) * r);
        glm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
            (s1 * z2 - s2 * z1) * r);

        tan1[i1] += sdir;
        tan1[i2] += sdir;
        tan1[i3] += sdir;

        tan2[i1] += tdir;
        tan2[i2] += tdir;
        tan2[i3] += tdir;
    }

    m_tangents.resize(vertexCount);
    for (long a = 0; a < vertexCount; a++)
    {
        const glm::vec3& n = m_normals[a];
        const glm::vec3& t = tan1[a];

        // Gram-Schmidt orthogonalize
        float nDotT = glm::dot (n, t);
        m_tangents[a] =  glm::vec4 (glm::normalize( (t - n) * nDotT), 0.0f);
        
        // Calculate handedness
        glm::vec3 nCrossT = glm::cross(n, t);
        m_tangents[a].w = ( glm::dot( nCrossT, tan2[a]) < 0.0F) ? -1.0F : 1.0F;
    }

    delete[] tan1;
}

size_t SubMesh::GetDataSizeInBytes()
{
    size_t size = sizeof(glm::vec3)*m_vertices.size()+ sizeof(glm::vec3)*m_normals.size()+ sizeof(glm::vec2)*m_UV1.size() + sizeof(glm::vec2)*m_UV2.size();
    return size; 
}


//============================================
AxisAlignedBox SubMesh::CalculateBounds()
{
    glm::vec3 max(-99999999999.0f);
    glm::vec3 min(99999999999.0f);
    for (int i=0; i< m_vertices.size(); ++i )
    {        
        if( m_vertices[i].x > max.x)
        {
            max.x= m_vertices[i].x;
        }
        if( m_vertices[i].y > max.y)
        {
            max.y = m_vertices[i].y;
        }
        if( m_vertices[i].z > max.z)
        {
            max.z = m_vertices[i].z;
        }

        if( m_vertices[i].x < min.x)
        {
            min.x= m_vertices[i].x;
        }
        if( m_vertices[i].y < min.y)
        {
            min.y = m_vertices[i].y;
        }
        if( m_vertices[i].z < min.z)
        {
            min.z = m_vertices[i].z;
        }
    }

	m_bounds.SetExtents( min, max );
    return m_bounds;
}

//============================================
void SubMesh::CalculateNormals()
{
	size_t vertexCount = m_triangles.size();
	m_normals.clear();
	m_normals.resize( m_vertices.size() );
	
	for( int i = 0; i < vertexCount; i += 3 )
	{
		// get the three vertices that make the faces
		glm::vec3 p0 = m_vertices[m_triangles[i+0]];
		glm::vec3 p1 = m_vertices[m_triangles[i+1]];
		glm::vec3 p2 = m_vertices[m_triangles[i+2]];

		glm::vec3 e1 = p1 - p0;
		glm::vec3 e2 = p2 - p0;
		glm::vec3 normal = glm::cross( e1, e2 );
		normal = glm::normalize(normal);

		// Store the face's normal for each of the vertices that make up the face.
		m_normals[m_triangles[i+0]] += normal ;
		m_normals[m_triangles[i+1]] += normal ;
		m_normals[m_triangles[i+2]] += normal ;
	}


	// Now loop through each vertex vector, and avarage out all the normals stored.
	for( int i = 0; i < m_normals.size(); ++i )
	{
		//m_normals[i].y *= -1;
		m_normals[i] = glm::normalize(m_normals[i]);
	}
}

