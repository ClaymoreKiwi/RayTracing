#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3Class.h"

class sphere : public hittable
{
public:
    sphere() {};
	sphere(point3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {}

	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    //quadratic formula for calculating where points intersect rays
    vec3 oc = r.Origin() - center;
    auto a = r.Direction().length_squared();
    auto half_b = dot(oc, r.Direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_Normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_Normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif