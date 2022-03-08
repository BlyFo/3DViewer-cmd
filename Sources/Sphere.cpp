#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "../Headers/Vector3.hpp"
#include "../Headers/Object.hpp"
#include "../Headers/Sphere.hpp"

using namespace std;

Vector3 Sphere::DrawObject(float theta, float phi)
{
    Vector3 result;
    result.x = (radius * cos(theta)) * cos(phi);
    result.y = radius * sin(theta);
    result.z = (radius * cos(theta)) * sin(phi);
    return result;
}

Sphere::Sphere()
{
    radius = 3;
}