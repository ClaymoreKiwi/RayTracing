#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
public:
	//vector3 Default Constructor
	vec3() 
		: m_e{ 0,0,0 } {}
	//Vector Constructor to establish the 3 array values for e
	vec3(double e0, double e1, double e2) 
		: m_e{e0,e1,e2} {}

	double X() { return m_e[0]; }
	double Y() { return m_e[1]; }
	double Z() { return m_e[2]; }

	//returns a negated vector
	vec3 operator-() const { return vec3(-m_e[0], -m_e[1], -m_e[2]); }

	//a read-only accessor
	double operator[](int i) const { return m_e[i]; }

	//both read and write and returns a referance for i
	double& operator[](int i) { return m_e[i]; }

	vec3& operator+=(const vec3 &v) 
	{
		m_e[0] += v.m_e[0];
		m_e[1] += v.m_e[1];
		m_e[2] += v.m_e[2];
		return *this;
	}

	vec3& operator*=(const double t)
	{
		m_e[0] *= t;
		m_e[1] *= t;
		m_e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t)
	{
		return *this *= (1 / t);
	}

	//returns the magnitude of the vector using a sqrt operation
	double Length() const
	{
		return std::sqrt(length_squared());
	}

	//
	double length_squared() const {
		return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
	}

	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

public:
	double m_e[3];
};


//Creation of aliases (for better descriptions within the main code)
using point3 = vec3; //3D Point
using colour = vec3; // RGB

#endif

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.m_e[0] << ' ' << v.m_e[1] << ' ' << v.m_e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.m_e[0] + v.m_e[0], u.m_e[1] + v.m_e[1], u.m_e[2] + v.m_e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.m_e[0] - v.m_e[0], u.m_e[1] - v.m_e[1], u.m_e[2] - v.m_e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.m_e[0] * v.m_e[0], u.m_e[1] * v.m_e[1], u.m_e[2] * v.m_e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.m_e[0], t * v.m_e[1], t * v.m_e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.m_e[0] * v.m_e[0]
		+ u.m_e[1] * v.m_e[1]
		+ u.m_e[2] * v.m_e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.m_e[1] * v.m_e[2] - u.m_e[2] * v.m_e[1],
		u.m_e[2] * v.m_e[0] - u.m_e[0] * v.m_e[2],
		u.m_e[0] * v.m_e[1] - u.m_e[1] * v.m_e[0]);
}

inline vec3 unit_vector(vec3 v) 
{
	return v / v.Length();
}


vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1)
			continue;
		return p;
	}
}

vec3 random_unit_vector()
{
	return unit_vector(random_in_unit_sphere());
}