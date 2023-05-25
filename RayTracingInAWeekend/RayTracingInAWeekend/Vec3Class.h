#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
public:
	//vector3 Default Constructor
	vec3() 
		: e{ 0,0,0 } {}
	//Vector Constructor to establish the 3 array values for e
	vec3(double e0, double e1, double e2) 
		: e{e0,e1,e2} {}

private:
	double e[3];
};

#endif