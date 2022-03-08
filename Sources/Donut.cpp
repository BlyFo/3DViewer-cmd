#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "../Headers/Vector3.hpp"
#include "../Headers/Object.hpp"
#include "../Headers/Donut.hpp"

using namespace std;

Vector3 Donut::DrawObject(float theta, float phi)
{
    Vector3 result;
    result.x = (outerRadius + innerRadius * cos(theta)) * cos(phi);
    result.y = innerRadius * sin(theta);
    result.z = (outerRadius + innerRadius * cos(theta)) * sin(phi);
    return result;
}
void Donut::objectType()
{
    printf("Donut \n");
}

Donut::Donut()
{
    innerRadius = 1;
    outerRadius = 2;
}

Donut::Donut(float newInnerRadius, float newOuterRadius)
{
    innerRadius = newInnerRadius;
    outerRadius = newOuterRadius;
}