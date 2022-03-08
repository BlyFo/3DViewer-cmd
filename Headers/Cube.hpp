#include <iostream>
#include <stdio.h>
#include <cstring>

#include "Vector3.hpp"
#include "Object.hpp"

#ifndef _CUBE_H
#define _CUBE_H

class Cube : public Object
{
private:
    float size;

public:
    Vector3 DrawObject(float theta, float phi);
    void objectType();
    Cube();
    Cube(float newSize);
};
#endif