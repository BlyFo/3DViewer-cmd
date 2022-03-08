#include <iostream>
#include <stdio.h>
#include <cstring>

#include "Vector3.hpp"
#include "Object.hpp"

#ifndef _DONUT_H
#define _DONUT_H

class Donut : public Object
{
private:
    float innerRadius;
    float outerRadius;

public:
    Vector3 DrawObject(float theta, float phi);
    void objectType();
    Donut();
};
#endif