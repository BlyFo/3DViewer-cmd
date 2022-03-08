#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#include "../Headers/Vector3.hpp"
#include "../Headers/Object.hpp"
#include "../Headers/Cube.hpp"

using namespace std;

Vector3 Cube::DrawObject(float theta, float phi)
{
    Vector3 result = {0, 0, 0};

    float clampValue = 45 * ((3.1415 * 2) / 360);

    float cosT = min(cos(clampValue), max(cos(theta), cos(-clampValue)));
    float sinT = min(sin(clampValue), max(sin(theta), sin(-clampValue)));

    result.x = (size * cosT) * cos(phi);
    result.y = size * sinT;
    result.z = (size * cosT) * sin(phi);

    printf("cos= %f ", cosT);
    printf("sin= %f \n", sinT);
    printf("x= %f ", result.x);
    printf("y= %f ", result.y);
    printf("z= %f \n", result.z);
    return result;
}
void Cube::objectType()
{
    printf("Cube \n");
}

Cube::Cube()
{
    size = 1;
}
Cube::Cube(float newSize)
{
    size = newSize;
}