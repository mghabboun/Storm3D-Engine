#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Triangle
{
	Triangle( unsigned int A, unsigned int B, unsigned int C)
	{
		a = A; 
		b = B;
		c = C;
	}

	unsigned int a,b,c; 

}

#endif