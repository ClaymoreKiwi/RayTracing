#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "mathutil.h"

class camera
{
public:
	camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspec_ratio, double aperture, double focus_dist)
	{
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2 * h;
		auto viewport_width = aspec_ratio * viewport_height;
		auto focal_length = 1;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

		lense_radius = aperture / 2;
	}

	Ray get_ray(double s, double t) const
	{
		vec3 rd = lense_radius * random_in_unit_disk();
		vec3 offset = u * rd.X() + v * rd.Y();

		auto direction = lower_left_corner + (s * horizontal) + (t * vertical) - origin - offset;
		return Ray(origin + offset, direction);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lense_radius;
};
#endif