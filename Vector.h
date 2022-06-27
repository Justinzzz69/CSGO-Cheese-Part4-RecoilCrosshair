#include "include.h"

struct Vector2
{
	float x, y;
};

struct Vector3
{
	float x, y, z;

	Vector3 operator+(Vector3 D) 
	{
		return { x + D.x, y + D.y, z + D.z };
	}
	Vector3 operator-(Vector3 D)
	{
		return { x - D.x, y - D.y, z - D.z };
	}
	Vector3 operator*(float D)
	{
		return { x * D,y * D,z * D };
	}
	Vector3 operator/(float D)
	{
		return { x / D, y / D, z / D };
	}

	void Normalize()
	{
		while (y < -180)
			y = 179.99;

		while (y > 180)
			y = -179.99;

		while (x < -89)
			x = -89;

		while (x > 89)
			x = 89;
		z = 0;

		
	}
};

struct Vector4
{
	float x, y, z, w;
};