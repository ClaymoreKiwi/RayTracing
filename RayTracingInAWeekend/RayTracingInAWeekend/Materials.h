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
	metal(const colour& a, double f)
		: albedo(a), fuzz(f < 1? f : 1) {}

		virtual bool scatter(const Ray & r_in, const hit_record & rec, colour & attenuation, Ray & scattered)const override
		{
			vec3 reflected = reflect(unit_vector(r_in.Direction()), rec.normal);
			scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
			attenuation = albedo;
			return (dot(scattered.Direction(), rec.normal) > 0);
		}

public:
	colour albedo;
	double fuzz;
};

class dielectric : public material
{
public:
	dielectric(double index_of_refraction) : refraction(index_of_refraction){}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, colour& attenuation, Ray& scattered)const override
	{
		attenuation = colour(1.0, 1.0, 1.0);
		double refraction_ratio = rec.front_face ? (1 / refraction) : refraction;

		vec3 unit_direction = unit_vector(r_in.Direction());
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
		{
			direction = reflect(unit_direction, rec.normal);
		}
		else
		{
			direction = refract(unit_direction, rec.normal, refraction_ratio);
		}

		scattered = Ray(rec.p, direction);
		return true;
	}
public:
	double refraction;

private:
	static double reflectance(double cosine, double ref_idx)
	{
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

#endif