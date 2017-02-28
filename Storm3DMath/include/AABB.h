#ifndef AABB_H_
#define AABB_H_

#include <glm/glm.hpp>
#include <iostream>
#include <vector> 

#include "Storm3DMath/include/Ray.h"
	

enum NodePosition
	{
		NEAR_BOTTOM_LEFT = 4,
		NEAR_BOTTOM_RIGHT = 0,
		NEAR_TOP_LEFT = 6,
		NEAR_TOP_RIGHT = 2,

		FAR_BOTTOM_LEFT = 5,
		FAR_BOTTOM_RIGHT = 1,
		FAR_TOP_RIGHT = 3,
		FAR_TOP_LEFT = 7,
		MAX_NODE_COUNT =8 //any defined node should be < 8
	};

class AxisAlignedBox
{

public:
	enum Extent
	{
		EXTENT_NULL,
		EXTENT_FINITE,
		EXTENT_INFINITE
	};

public:

	AxisAlignedBox();

	AxisAlignedBox(Extent e);
	AxisAlignedBox(const AxisAlignedBox & rkBox);

	AxisAlignedBox( const glm::vec3& min, const glm::vec3& max );
	AxisAlignedBox( float mx, float my, float mz,float Mx, float My, float Mz );
	AxisAlignedBox& operator=(const AxisAlignedBox& rhs);
	// Gets the minimum corner of the box.
	const glm::vec3&	GetMinimum(void) const;
	// Gets a modifiable version of the minimum	corner of the box.
	glm::vec3&			GetMinimum(void);	
	const glm::vec3&	GetMaximum(void) const;// Gets the maximum corner of the box.	
	glm::vec3&			GetMaximum(void);// Gets a modifiable version of the maximum corner of the box.

	void SetMinimum( float x, float y, float z );	// Sets the minimum corner of the box.

	void SetMinimumX(float x);
	void SetMinimumY(float y);
	void SetMinimumZ(float z);

	void SetMaximum( const glm::vec3& vec );
	void SetMaximum( float x, float y, float z );

	void SplitToEight( AxisAlignedBox boxes[8] );

	// Changes one of the components of the maximum corner of the box used to resize only one dimension of the box		
	void SetMaximumX( float x );
	void SetMaximumY( float y );
	void SetMaximumZ( float z );

	void SetMinimum( const glm::vec3& vec );

	// Sets both minimum and maximum extents at once.		
	void				SetExtents( const glm::vec3& min, const glm::vec3& max );
	void				SetExtents( float mx, float my, float mz, float Mx, float My, float Mz );
	std::vector<glm::vec3>	GetAllCorners(void) const;
	// Gets the position of one of the corners		
	glm::vec3			GetCorner(NodePosition cornerToGet) const;
	friend std::ostream& operator<<( std::ostream& o, const AxisAlignedBox aab );

	// Merges the passed in box into the current box. The result is the box which encompasses both.		
	void				Union( const AxisAlignedBox& rhs );
	void				Union( const glm::vec3& point );	// Extends the box to encompass the specified point (if needed).

	AxisAlignedBox		CalcCube();
	
	float				CalcRadius();

	void				SplitAlongX( AxisAlignedBox& negativeSide, AxisAlignedBox& positiveSide );
	void				SplitAlongY( AxisAlignedBox& negativeSide, AxisAlignedBox& positiveSide );
	void				SplitAlongZ( AxisAlignedBox& negativeSide, AxisAlignedBox& positiveSide );

	void				Transform( const glm::mat4& matrix );
	void				TransformAffine(const glm::mat4& m);
	void				SetNull();

	
	bool				IsNull(void) const;	// Returns true if the box is null i.e. empty.

	// Returns true if the box is finite.
	bool IsFinite(void) const;


	// Sets the box to 'infinite'
	void SetInfinite()
	{
		*this = BOX_INFINITE;
		this->m_Extent = Extent::EXTENT_INFINITE;
	}

	bool				IsInfinite() const;	// Returns true if the box is infinite.	
	bool				Intersects(const AxisAlignedBox& b2) const;// Returns whether or not this box intersects another.
	AxisAlignedBox		Intersection(const AxisAlignedBox& b2) const;	/// Calculate the area of intersection of this box and another
	float				Volume(void) const;	/// Calculate the volume of this box
	void				Scale(const glm::vec3& s);	/** Scales the AABB by the vector given. */

	bool				Intersects(const glm::vec3& v) const;	/** Tests whether the vector point is within this box. */
	bool				RayIntersect(const glm::vec3& origin, const glm::vec3& dir, float& distance, glm::vec3 &intrsctPoint);	//bool RayIntersect( const glm::vec3 &origin, const glm::vec3& dir, float& distance );
	
	//bool RayIntersect(Ray ray, float &distance);
	/// Gets the centre of the box
	glm::vec3			GetCenter(void) const;	
	glm::vec3			GetSize(void) const; // Gets the size of the box	
	glm::vec3			GetHalfSize(void) const;// Gets the half-size of the box	 
	
	bool				Contains(const glm::vec3& v)	const;// Tests whether the given point contained by this box.
	bool				Contains(const AxisAlignedBox& other) const;  // Tests whether another box contained by this box.	
	bool				operator== (const AxisAlignedBox& rhs) const; // Tests 2 boxes for equality.	*/	
	bool				operator!= (const AxisAlignedBox& rhs) const; // Tests 2 boxes for inequality.


protected:

	glm::vec3 m_Minimum;
	glm::vec3 m_Maximum;
	Extent m_Extent;
	mutable glm::vec3* mpCorners;

	// special values
	static const AxisAlignedBox BOX_NULL;
	static const AxisAlignedBox BOX_INFINITE;

};



inline AxisAlignedBox::AxisAlignedBox() 
	: m_Minimum(), m_Maximum(), mpCorners(0)
{
	// Default to a null box 
	SetMinimum( -0.5, -0.5, -0.5 );
	SetMaximum( 0.5, 0.5, 0.5 );
	m_Extent = EXTENT_NULL;
}

inline AxisAlignedBox:: AxisAlignedBox(Extent e) : m_Minimum(), m_Maximum(), mpCorners(0)
{
	SetMinimum( -0.5, -0.5, -0.5 );
	SetMaximum( 0.5, 0.5, 0.5 );
	m_Extent = e;
}

inline AxisAlignedBox::AxisAlignedBox(const AxisAlignedBox & rkBox) : m_Minimum(), m_Maximum(), mpCorners(0)
{
	if (rkBox.IsNull())
		SetNull();
	else if (rkBox.IsInfinite())
		SetInfinite();
	else
		SetExtents( rkBox.m_Minimum, rkBox.m_Maximum );
}

inline AxisAlignedBox::AxisAlignedBox( const glm::vec3& min, const glm::vec3& max ) : m_Minimum(), m_Maximum(), mpCorners(0)
{
	SetExtents( min, max );
}

inline AxisAlignedBox::AxisAlignedBox( float mx, float my, float mz,float Mx, float My, float Mz ) 
	: m_Minimum(), m_Maximum(), mpCorners(0)
{
	SetExtents( mx, my, mz, Mx, My, Mz );
}

// Gets the minimum corner of the box.
inline const glm::vec3& AxisAlignedBox::GetMinimum(void) const
{ 
	return m_Minimum; 
}

// Gets a modifiable version of the minimum	corner of the box.
inline glm::vec3& AxisAlignedBox::GetMinimum(void)
{ 
	return m_Minimum; 
}

// Gets the maximum corner of the box.
inline const glm::vec3& AxisAlignedBox::GetMaximum(void) const
{ 
	return m_Maximum;
}

/* Gets a modifiable version of the maximum
corner of the box.
*/
inline glm::vec3& AxisAlignedBox::GetMaximum(void)
{ 
	return m_Maximum;
}

inline void AxisAlignedBox::SetMinimum( float x, float y, float z )
{
	m_Extent = EXTENT_FINITE;
	m_Minimum.x = x;
	m_Minimum.y = y;
	m_Minimum.z = z;
}

/** Sets the minimum corner of the box.
*/

inline void AxisAlignedBox::SetMinimumX(float x)
{
	m_Minimum.x = x;
}

inline void AxisAlignedBox::SetMinimumY(float y)
{
	m_Minimum.y = y;
}

inline void AxisAlignedBox::SetMinimumZ(float z)
{
	m_Minimum.z = z;
}

/** Sets the maximum corner of the box.
*/
inline void AxisAlignedBox::SetMaximum( const glm::vec3& vec )
{
	m_Extent = EXTENT_FINITE;
	m_Maximum = vec;
}

inline void AxisAlignedBox::SetMaximum( float x, float y, float z )
{
	m_Extent = EXTENT_FINITE;
	m_Maximum.x = x;
	m_Maximum.y = y;
	m_Maximum.z = z;
}

// Changes one of the components of the maximum corner of the box used to resize only one dimension of the box		
inline void AxisAlignedBox::SetMaximumX( float x )
{
	m_Maximum.x = x;
}

inline void AxisAlignedBox::SetMaximumY( float y )
{
	m_Maximum.y = y;
}

inline void AxisAlignedBox::SetMaximumZ( float z )
{
	m_Maximum.z = z;
}

inline void AxisAlignedBox::SetMinimum( const glm::vec3& vec )
{
	m_Extent = EXTENT_FINITE;
	m_Minimum = vec;
}

// Sets both minimum and maximum extents at once.		
inline void  AxisAlignedBox::SetExtents( const glm::vec3& min, const glm::vec3& max )
{
	assert( (min.x <= max.x && min.y <= max.y && min.z <= max.z) &&
		"The minimum corner of the box must be less than or equal to maximum corner" );

	m_Extent = EXTENT_FINITE;
	m_Minimum = min;
	m_Maximum = max;
}

inline void AxisAlignedBox::SetExtents(	float mx, float my, float mz, float Mx, float My, float Mz )
{
	assert( (mx <= Mx && my <= My && mz <= Mz) &&
		"The minimum corner of the box must be less than or equal to maximum corner" );

	m_Extent = EXTENT_FINITE;

	m_Minimum.x = mx;
	m_Minimum.y = my;
	m_Minimum.z = mz;

	m_Maximum.x = Mx;
	m_Maximum.y = My;
	m_Maximum.z = Mz;
}

// Sets the box to a 'null' value i.e. not a box.
inline void AxisAlignedBox::SetNull()
{    	
	m_Extent = EXTENT_NULL;
}

// Returns true if the box is null i.e. empty.
inline bool AxisAlignedBox::IsNull(void) const
{
	return (m_Extent == EXTENT_NULL);
}

// Returns true if the box is finite.
inline  bool AxisAlignedBox::IsFinite(void) const
{
	return (m_Extent == EXTENT_FINITE);
}

// Tests 2 boxes for inequality.
inline bool AxisAlignedBox::operator!= (const AxisAlignedBox& rhs) const
{
	return !(*this == rhs);
}

inline AxisAlignedBox AxisAlignedBox::CalcCube()
{
	int maxIndex = 0;
	float maxLength = m_Maximum[0] - m_Minimum[0];
	for (int i=1; i < 3;++i)
	{
		float currentLength = m_Maximum[i] - m_Minimum[i];
		if ( currentLength > maxLength  )
		{
			maxLength = currentLength;
			maxIndex = i;
		}
	}
	glm::vec3 center = this->GetCenter();
	glm::vec3 halfSize = this->GetHalfSize();
	/*return AxisAlignedBox(glm::vec3(m_Minimum[maxIndex],m_Minimum[maxIndex],m_Minimum[maxIndex] ),
		glm::vec3(m_Maximum[maxIndex],m_Maximum[maxIndex],m_Maximum[maxIndex] ) ); 
*/
	glm::vec3 offset( halfSize[maxIndex], halfSize[maxIndex],halfSize[maxIndex]);
	return AxisAlignedBox(center-offset, center+offset );
}

/// Gets the centre of the box
inline glm::vec3 AxisAlignedBox::GetCenter(void) const
{
    assert( (m_Extent == EXTENT_FINITE) && "Can't get center of a null or infinite AAB" );

    return  (m_Maximum + m_Minimum) * 0.5f;
}

inline float AxisAlignedBox::CalcRadius()
{
	return glm::length(m_Maximum - m_Minimum);
}


inline std::vector<glm::vec3> AxisAlignedBox::GetAllCorners(void) const
{
    assert( (m_Extent == EXTENT_FINITE) && "Can't get corners of a null or infinite AAB" );

    // The order of these items is, using right-handed co-ordinates:
    // Minimum Z face, starting with Min(all), then anticlockwise
    //   around face (looking onto the face)
    // Maximum Z face, starting with Max(all), then anticlockwise
    //   around face (looking onto the face)
    // Only for optimization/compatibility.
    //if (!mpCorners)
    //	mpCorners = OGRE_ALLOC_T(glm::vec3, 8, MEMCATEGORY_SCENE_CONTROL);
	std::vector<glm::vec3> corners(8);
    corners[0] = m_Minimum;
    corners[1].x = m_Minimum.x; corners[1].y = m_Maximum.y; corners[1].z = m_Minimum.z;
    corners[2].x = m_Maximum.x; corners[2].y = m_Maximum.y; corners[2].z = m_Minimum.z;
    corners[3].x = m_Maximum.x; corners[3].y = m_Minimum.y; corners[3].z = m_Minimum.z;            

    corners[4] = m_Maximum;
    corners[5].x = m_Minimum.x; corners[5].y = m_Maximum.y; corners[5].z = m_Maximum.z;
    corners[6].x = m_Minimum.x; corners[6].y = m_Minimum.y; corners[6].z = m_Maximum.z;
    corners[7].x = m_Maximum.x; corners[7].y = m_Minimum.y; corners[7].z = m_Maximum.z;

    return corners;
}
//
//
//bool RayIntersect(Ray ray, out float Distance)
//{
//	//throw new NotImplementedException();
//	Vector3 IntrsctPoint;
//
//	float tmin = 9999999;  //max of the u,v,w min
//	float tmax = -9999999; //min of the u,v,w max
//
//	float[] Direction = ray.Direction.GetArray3();
//	float[] Origin = ray.Origin.GetArray3();
//
//
//	//Loop for every pair of planes (Slab) to check for intersection
//	for (int i = 0; i < 3; i++)
//	{
//		if (Direction[i] == 0 && Origin[i] < this.m_Min[i] && Origin[i] > this.m_Max[i])
//		{ //if Ray direction is parallel return false
//			IntrsctPoint = Vector3.Zero; Distance = 0; return false;
//		}
//
//		float Tl = (m_Min[i] - Origin[i]) / Direction[i]; //Calculate t near and t far foreach slab
//		float Th = (m_Max[i] - Origin[i]) / Direction[i];
//
//		if (Tl > Th)
//		{ float temp = Tl; Tl = Th; Th = temp; } //swap
//
//
//		if (Tl > tmin) tmin = Tl; // the largest tnear
//		if (Th < tmax) tmax = Th;//the smallest tfar
//
//		if (tmin > tmax) { IntrsctPoint = Vector3.Zero; Distance = 0; return false; }//
//		if (tmax < 0) { IntrsctPoint = Vector3.Zero; Distance = 0; return false; }
//	} // end the for loop 
//
//	//   IntrsctPoint = ray.GetPoint(tmin);
//	Distance = tmin;
//
//	return true;
//
//}

#endif
