#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "../Headers/Vector3.hpp"
#include "../Headers/Object.hpp"
#include "../Headers/Cube.hpp"

using namespace std;

Vector3 Cube::DrawObject(float theta, float phi)
{
    Vector3 result = {0, 0, 0};
    // result.x = (outerRadius + innerRadius * cos(theta)) * cos(phi);
    // result.y = innerRadius * sin(theta);
    // result.z = (outerRadius + innerRadius * cos(theta)) * sin(phi);
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