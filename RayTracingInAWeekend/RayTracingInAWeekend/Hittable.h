#pragma once
#ifndef HITTABLE_h
#define HITTABLE_h

#include "Ray.h"

struct hit_record
{
	point3 p;
	vec3 normal;
	double t;
};

class hittable
{
public:
	//pure virtual class function
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif