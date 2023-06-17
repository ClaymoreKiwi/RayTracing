#pragma once
#ifndef MATERIALS_H
#define MATERIALS_H

#include "mathutil.h"
#include "Hittable.h"

struct hit_record;

class material
{
public:
	virtual bool scatter
	(const Ray& r_in, const hit_record& rec, colour & attenuation, Ray& scattered)const = 0;
};

class lambertian : public material
{
public:
	lambertian(const colour& a)
		: albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered) const override
	{
		auto scatter_direction = rec.normal + random_unit_vector();
		//so the ray will bounce directly back if head on with the normal direciton of the surface
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

public:
	colour albedo;
};

class metal : public material
{
public:
	metal(const colour& a)
		: albedo(a) {}

		virtual bool scatter(const Ray & r_in, const hit_record & rec, colour & attenuation, Ray & scattered)const override
		{
			vec3 reflected = reflect(unit_vector(r_in.Direction()), rec.normal);
			scattered = Ray(rec.p, reflected);
			attenuation = albedo;
			return (dot(scattered.Direction(), rec.normal) > 0);
		}

public:
	colour albedo;
};

#endif