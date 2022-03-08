#include <iostream>
#include <stdio.h>
#include <cstring>

#include "Vector3.hpp"
#include "Object.hpp"

#ifndef _SPHERE_H
#define _SPHERE_H

class Sphere : public Object
{
private:
    float radius;

public:
    Vector3 DrawObject(float theta, float phi);
    void objectType();
    Sphere();
    Sphere(float newRadius);
};
#endif