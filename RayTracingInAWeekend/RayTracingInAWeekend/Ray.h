#pragma once
#ifndef RAY_H
#define RAY_H

#include "Vec3Class.h"

class Ray
{
public:
	Ray() {}
	Ray(const point3& origin, const vec3& direction)
		:orig(origin), dir(direction)
	{
	//orig and dir can be set in here too, but setting them above is cleaner
	}

	point3 Origin() const { return orig; }
	vec3 Direction() const { return dir; }

	point3 at(double t) const 
	{ 
		return orig * t * dir; 
	}

public:
	point3 orig;
	vec3 dir;
};

#endif