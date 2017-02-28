#include "Storm3DMath/include/AABB.h"
#include "Storm3DMath/include/Math2.h"

#include <iostream>

const AxisAlignedBox AxisAlignedBox::BOX_NULL = AxisAlignedBox(0,0,0,0,0,0);
const AxisAlignedBox AxisAlignedBox::BOX_INFINITE = AxisAlignedBox(0,0,0,0,0,0);

AxisAlignedBox& AxisAlignedBox::operator = (const AxisAlignedBox& rhs)
{
    // Specifically override to avoid copying mpCorners
    if (rhs.IsNull())
        SetNull();
    else if (rhs.IsInfinite())
        SetInfinite();
    else
        SetExtents(rhs.m_Minimum, rhs.m_Maximum);

    return *this;
}



// gets the position of one of the corners		
glm::vec3 AxisAlignedBox::GetCorner(NodePosition cornerToGet) const
{
    switch(cornerToGet)
    {
    case FAR_BOTTOM_LEFT:
        return m_Minimum;
    case FAR_TOP_LEFT:
        return glm::vec3(m_Minimum.x, m_Maximum.y, m_Maximum.z);
    case FAR_TOP_RIGHT:
        return glm::vec3(m_Maximum.x, m_Maximum.y, m_Maximum.z);
    case FAR_BOTTOM_RIGHT:
        return glm::vec3(m_Maximum.x, m_Minimum.y, m_Maximum.z);
    case NEAR_BOTTOM_RIGHT:
        return glm::vec3(m_Maximum.x, m_Minimum.y, m_Minimum.z);
    case NEAR_BOTTOM_LEFT:
        return glm::vec3(m_Minimum.x, m_Minimum.y, m_Minimum.z);
    case NEAR_TOP_LEFT:
        return glm::vec3(m_Minimum.x, m_Maximum.y, m_Minimum.z);
    case NEAR_TOP_RIGHT:
        return m_Maximum;
    default:
        return glm::vec3();
    }
}

std::ostream& operator<<( std::ostream& o, const AxisAlignedBox aab )
{
    //switch (aab.m_Extent)
    //{
    //case AxisAlignedBox::EXTENT_NULL:
    //    o << "AxisAlignedBox(null)";
    //    return o;

    //case AxisAlignedBox::EXTENT_FINITE:
    //    o << "AxisAlignedBox(min=" << aab.m_Minimum << ", max=" << aab.m_Maximum << ")";
    //    return o;

    //case AxisAlignedBox::EXTENT_INFINITE:
    //    o << "AxisAlignedBox(infinite)";
    //    return o;

    //default: // shut up compiler
    //    assert( false && "Never reached" );
    //    return o;
    //}
    return o;
}

// Merges the passed in box into the current box. The result is the box which encompasses both.		
void AxisAlignedBox::Union( const AxisAlignedBox& rhs )
{
    // Do nothing if rhs null, or this is infinite
    if ((rhs.m_Extent == AxisAlignedBox::EXTENT_NULL) || (m_Extent == AxisAlignedBox::EXTENT_INFINITE))
    {
        return;
    }
    // Otherwise if rhs is infinite, make this infinite, too
    else if (rhs.m_Extent == AxisAlignedBox::EXTENT_INFINITE)
    {
        m_Extent = AxisAlignedBox::EXTENT_INFINITE;
    }
    // Otherwise if current null, just take rhs
    else if (m_Extent == AxisAlignedBox::EXTENT_NULL)
    {
        SetExtents(rhs.m_Minimum, rhs.m_Maximum);
    }
    // Otherwise merge
    else
    {
        glm::vec3 min = m_Minimum;
        glm::vec3 max = m_Maximum;
        glm::ceil( rhs.m_Maximum );
        glm::floor(rhs.m_Minimum);

        SetExtents(min, max);
    }

}

// Extends the box to encompass the specified point (if needed).
inline void AxisAlignedBox::Union( const glm::vec3& point )
{
    switch (m_Extent)
    {
    case AxisAlignedBox::EXTENT_NULL: // if null, use this point
        SetExtents(point, point);
        return;

    case AxisAlignedBox::EXTENT_FINITE:
        //TODO fix here.
        //m_Maximum.MakeCeil(point);
        //m_Minimum.MakeFloor(point);
        return;

    case AxisAlignedBox::EXTENT_INFINITE: // if infinite, makes no difference
        return;
    }

    assert( false && "Never reached" );
}

/** Transforms the box according to the matrix supplied.
@remarks
By calling this method you get the axis-aligned box which
surrounds the transformed version of this box. Therefore each
corner of the box is transformed by the matrix, then the
extents are mapped back onto the axes to produce another
AABB. Useful when you have a local AABB for an object which
is then transformed.
*/
void AxisAlignedBox::Transform( const glm::mat4& matrix )
{
    // Do nothing if current null or infinite
    if( m_Extent != AxisAlignedBox::EXTENT_FINITE )
        return;

    glm::vec3 oldMin, oldMax, currentCorner;

    // Getting the old values so that we can use the existing merge method.
    oldMin = m_Minimum;
    oldMax = m_Maximum;

    // reset
    SetNull();
}

/** Transforms the box according to the affine matrix supplied.
@remarks
By calling this method you get the axis-aligned box which
surrounds the transformed version of this box. Therefore each
corner of the box is transformed by the matrix, then the
extents are mapped back onto the axes to produce another
AABB. Useful when you have a local AABB for an object which
is then transformed.
@note
The matrix must be an affine matrix. @see Matrix4::IsAffine.
*/
void AxisAlignedBox::TransformAffine(const glm::mat4& m)
{
    //assert(m.IsAffine());

    // Do nothing if current null or infinite
   /* if ( m_Extent != EXTENT_FINITE )
        return;

    glm::vec3 centre = GetCenter();
    glm::vec3 halfSize = GetHalfSize();

    
    glm::vec3 newCentre = (glm::vec3)(m * (glm::vec4)centre);
    glm::vec3 newHalfSize(
        Math::Abs(m[0][0]) * halfSize.x + Math::Abs(m[0][1]) * halfSize.y + Math::Abs(m[0][2]) * halfSize.z, 
        Math::Abs(m[1][0]) * halfSize.x + Math::Abs(m[1][1]) * halfSize.y + Math::Abs(m[1][2]) * halfSize.z,
        Math::Abs(m[2][0]) * halfSize.x + Math::Abs(m[2][1]) * halfSize.y + Math::Abs(m[2][2]) * halfSize.z);

    SetExtents(newCentre - newHalfSize, newCentre + newHalfSize);*/
}


/** Returns true if the box is infinite.
*/
bool AxisAlignedBox::IsInfinite() const
{
    return (m_Extent == EXTENT_INFINITE);
}

/** Returns whether or not this box intersects another. */
inline bool AxisAlignedBox::Intersects(const AxisAlignedBox& b2) const
{
    // Early-fail for nulls
    if (this->IsNull() || b2.IsNull())
        return false;

    // Early-success for infinites
    if (this->IsInfinite() || b2.IsInfinite())
        return true;

    // Use up to 6 separating planes
    if (m_Maximum.x < b2.m_Minimum.x)
        return false;
    if (m_Maximum.y < b2.m_Minimum.y)
        return false;
    if (m_Maximum.z < b2.m_Minimum.z)
        return false;

    if (m_Minimum.x > b2.m_Maximum.x)
        return false;
    if (m_Minimum.y > b2.m_Maximum.y)
        return false;
    if (m_Minimum.z > b2.m_Maximum.z)
        return false;

    // otherwise, must be intersecting
    return true;
}

/// Calculate the area of intersection of this box and another
inline AxisAlignedBox AxisAlignedBox::Intersection(const AxisAlignedBox& b2) const
{
    if (this->IsNull() || b2.IsNull())
    {
        return AxisAlignedBox();
    }
    else if (this->IsInfinite())
    {
        return b2;
    }
    else if (b2.IsInfinite())
    {
        return *this;
    }

    glm::vec3 intMin = m_Minimum;
    glm::vec3 intMax = m_Maximum;

   /* intMin.MakeCeil(b2.GetMinimum());
    intMax.MakeFloor(b2.GetMaximum());*/

    // Check intersection isn't null
    if (intMin.x < intMax.x &&
        intMin.y < intMax.y &&
        intMin.z < intMax.z)
    {
        return AxisAlignedBox(intMin, intMax);
    }

    return AxisAlignedBox();
}

/// Calculate the volume of this box
float AxisAlignedBox::Volume(void) const
{
    switch (m_Extent)
    {
    case EXTENT_NULL:
        return 0.0f;

    case EXTENT_FINITE:
        {
            glm::vec3 diff = m_Maximum - m_Minimum;
            return diff.x * diff.y * diff.z;
        }

    case EXTENT_INFINITE:
        return Math::POS_INFINITY;

    default: // shut up compiler
        assert( false && "Never reached" );
        return 0.0f;
    }
}

/** Scales the AABB by the vector given. */
inline void AxisAlignedBox::Scale(const glm::vec3& s)
{
    // Do nothing if current null or infinite
    if (m_Extent != EXTENT_FINITE)
        return;

    // NB assumes centered on origin
    glm::vec3 min = m_Minimum * s;
    glm::vec3 max = m_Maximum * s;
    SetExtents(min, max);
}

/** Tests whether this box intersects a sphere. */
/*   bool AxisAlignedBox::Intersects(const Sphere& s) const
{
return Math::Intersects(s, *this); 
}*/
/** Tests whether this box intersects a plane. */
/* bool AxisAlignedBox::Intersects(const Plane& p) const
{
return Math::Intersects(p, *this);
}*/

// Tests whether the vector point is within this box. 
bool AxisAlignedBox::Intersects(const glm::vec3& v) const
{
    switch (m_Extent)
    {
    case EXTENT_NULL:
        return false;

    case EXTENT_FINITE:
        return(v.x >= m_Minimum.x  &&  v.x <= m_Maximum.x  && 
            v.y >= m_Minimum.y  &&  v.y <= m_Maximum.y  && 
            v.z >= m_Minimum.z  &&  v.z <= m_Maximum.z);

    case EXTENT_INFINITE:
        return true;

    default: // shut up compiler
        assert( false && "Never reached" );
        return false;
    }
}


/// Gets the size of the box
glm::vec3 AxisAlignedBox::GetSize(void) const
{
    switch (m_Extent)
    {
    case EXTENT_NULL:
        return glm::vec3();

    case EXTENT_FINITE:
        return m_Maximum - m_Minimum;

    case EXTENT_INFINITE:
        return glm::vec3(
            Math::POS_INFINITY,
            Math::POS_INFINITY,
            Math::POS_INFINITY);

    default:
        assert( false && "Never reached" );
        return glm::vec3();
    }
}
/// Gets the half-size of the box
glm::vec3 AxisAlignedBox::GetHalfSize(void) const
{
	return (m_Maximum - m_Minimum) * 0.5f;

    switch (m_Extent)
    {
    case EXTENT_NULL:
        return glm::vec3();

    case EXTENT_FINITE:
        return (m_Maximum - m_Minimum) * 0.5f;

    case EXTENT_INFINITE:
        return glm::vec3(
            Math::POS_INFINITY,
            Math::POS_INFINITY,
            Math::POS_INFINITY);

    default: // shut up compiler
        assert( false && "Never reached" );
        return glm::vec3();
    }
}

/** Tests whether the given point contained by this box.
*/
bool AxisAlignedBox::Contains(const glm::vec3& v) const
{
    if (IsNull())
        return false;
    if (IsInfinite())
        return true;

    return m_Minimum.x <= v.x && v.x <= m_Maximum.x &&
        m_Minimum.y <= v.y && v.y <= m_Maximum.y &&
        m_Minimum.z <= v.z && v.z <= m_Maximum.z;
}

/** Tests whether another box contained by this box.
*/
bool AxisAlignedBox::Contains(const AxisAlignedBox& other) const
{
    if (other.IsNull() || this->IsInfinite())
        return true;

    if (this->IsNull() || other.IsInfinite())
        return false;

    return this->m_Minimum.x <= other.m_Minimum.x &&
        this->m_Minimum.y <= other.m_Minimum.y &&
        this->m_Minimum.z <= other.m_Minimum.z &&
        other.m_Maximum.x <= this->m_Maximum.x &&
        other.m_Maximum.y <= this->m_Maximum.y &&
        other.m_Maximum.z <= this->m_Maximum.z;
}


bool AxisAlignedBox::operator== (const AxisAlignedBox& rhs) const
{
    if (this->m_Extent != rhs.m_Extent)
        return false;

    if (!this->IsFinite())
        return true;

    return this->m_Minimum == rhs.m_Minimum &&
        this->m_Maximum == rhs.m_Maximum;
}

bool AxisAlignedBox::RayIntersect(const glm::vec3& origin, const glm::vec3& dir, float& distance, glm::vec3 &intrsctPoint)
{
	 //float tmin = std::numeric_limits<float>::min();  //max of the u,v,w min
	  //float tmax = std::numeric_limits<float>::max(); //min of the u,v,w max
	 
	  float tmin = -9999999;  //max of the u,v,w min
      float tmax = 9999999; //min of the u,v,w max
	  
	  //Loop for every pair of planes (Slab) to check for intersection
	  for (int i = 0; i < 3; i++)
	  {
		  if (dir[i] == 0 && origin[i] < m_Minimum[i] && origin[i] > m_Maximum[i])
		  { //if Ray direction is parallel return false
			  intrsctPoint = glm::vec3(0.0f,0.0f,0.0f); 
			  distance = 0;
			  return false;
		  }

		  float Tl = (m_Minimum[i] - origin[i]) / dir[i]; //Calculate t near and t far foreach slab
		  float Th = (m_Maximum[i] - origin[i]) / dir[i];

		  if (Tl > Th)
		  { 
			 std::swap( Tl, Th ); 
		  } //swap


		  if (Tl > tmin) tmin = Tl; // the largest tnear
		  if (Th < tmax) tmax = Th;//the smallest tfar

		  if (tmin > tmax) 
		  {
			  intrsctPoint = glm::vec3(0.0f,0.0f,0.0f); 
			  distance = 0; 
			  return false; 
		  }//
		  
		  if (tmax < 0) 
		  {
			  intrsctPoint = glm::vec3(0.0f,0.0f,0.0f); 
			  distance = 0;
			  return false; 
		  }
	  } // end the for loop 

	  //IntrsctPoint = ray.GetPoint(tmin);
      intrsctPoint = glm::vec3(origin + dir * tmin);
	  distance = tmin;
	  return true;
 }


//=======================================================================================
void AxisAlignedBox::SplitAlongX(AxisAlignedBox& negativeSide, AxisAlignedBox& positiveSide)
{

}

//=======================================================================================
void AxisAlignedBox::SplitAlongY( AxisAlignedBox& negativeSide, AxisAlignedBox& positiveSide )
{
	negativeSide.SetExtents( m_Minimum, glm::vec3( m_Maximum.x, (m_Minimum.y + m_Maximum.y)*0.5f, m_Maximum.z ) );
	positiveSide.SetExtents( glm::vec3( m_Minimum.x, (m_Minimum.y + m_Maximum.y)*0.5f, m_Minimum.z ), m_Maximum );
}

//=======================================================================================
void AxisAlignedBox::SplitAlongZ( AxisAlignedBox& negativeSide, AxisAlignedBox& positiveSide )
{
	negativeSide.SetExtents( m_Minimum, glm::vec3( m_Maximum.x, (m_Minimum.y + m_Maximum.y)*0.5f, m_Maximum.z ) );
	positiveSide.SetExtents( glm::vec3( m_Minimum.x, (m_Minimum.y + m_Maximum.y)*0.5f, m_Minimum.z ), m_Maximum );
}


void AxisAlignedBox::SplitToEight( AxisAlignedBox boxes[8] )
{
	glm::vec3 mid = (m_Minimum + m_Maximum)*0.5f;
	glm::vec3 halfSize = GetHalfSize();
	glm::vec3 min = m_Minimum;
	glm::vec3 max = m_Maximum;
	
	boxes[NEAR_BOTTOM_RIGHT].SetExtents ( glm::vec3(min.x, min.y,min.z),  glm::vec3(min.x, min.y,min.z)+halfSize );
	boxes[NEAR_BOTTOM_LEFT].SetExtents( glm::vec3(mid.x, min.y, min.z ),glm::vec3(mid.x, min.y, min.z )+halfSize );

	boxes[NEAR_TOP_RIGHT].SetExtents( glm::vec3 (min.x, mid.y, min.z ), glm::vec3 (min.x, mid.y, min.z )+halfSize );	
	boxes[NEAR_TOP_LEFT].SetExtents( glm::vec3(mid.x, mid.y, min.z), glm::vec3(mid.x, mid.y, min.z) +halfSize);	
	
	boxes[FAR_BOTTOM_RIGHT].SetExtents ( glm::vec3(min.x, min.y, mid.z), glm::vec3(min.x, min.y, mid.z)  + halfSize );
	boxes[FAR_BOTTOM_LEFT].SetExtents( glm::vec3(mid.x, min.y, mid.z ),  glm::vec3(mid.x, min.y, mid.z ) + halfSize);

	boxes[FAR_TOP_RIGHT].SetExtents( glm::vec3 (min.x, mid.y, mid.z ), glm::vec3 (min.x, mid.y, mid.z ) + halfSize );	
	boxes[FAR_TOP_LEFT].SetExtents( glm::vec3(mid.x, mid.y, mid.z), glm::vec3(mid.x, mid.y, mid.z) + halfSize  );
}


