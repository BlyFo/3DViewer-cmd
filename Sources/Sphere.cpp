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
    result.x = radius * cos(theta) * sin(phi / 2);
    result.z = radius * cos(phi / 2);
    result.y = radius * sin(theta) * sin(phi / 2);
    return result;
}
void Sphere::objectType()
{
    printf("Sphere \n");
}

Sphere::Sphere()
{
    radius = 1;
}
Sphere::Sphere(float newRadius)
{
    radius = newRadius;
}