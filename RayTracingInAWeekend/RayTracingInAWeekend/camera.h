#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "mathutil.h"

class camera
{
public:
	camera(double vfov, double aspec_ratio)
	{
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2 * h;
		auto viewport_width = aspec_ratio * viewport_height;
		auto focal_length = 1;

		origin = point3(0, 0, 0);
		horizontal = vec3(viewport_width, 0, 0);
		vertical = vec3(0.0, viewport_height, 0.0);
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
	}

	Ray get_ray(double u, double v) const
	{
		auto direction = lower_left_corner + u * horizontal + v * vertical - origin;
		return Ray(origin, direction);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};
#endif