#pragma once
#ifndef HITTABLE_h
#define HITTABLE_h

#include "Ray.h"
#include "mathutil.h"

class material;

struct hit_record
{
	point3 p;
	vec3 normal;
	shared_ptr<material> mat_ptr;
	double t;
	bool front_face;

	inline void set_face_normal(const Ray& r, const vec3& outward_Normal)
	{
		front_face = dot(r.Direction(), outward_Normal) < 0;
		//turnary statement to return the correct ray location
		normal = front_face ? outward_Normal : -outward_Normal;
	}
};

class hittable
{
public:
	//pure virtual class function
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif