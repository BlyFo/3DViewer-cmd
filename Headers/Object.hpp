#include <iostream>
#include <stdio.h>

#include "Vector3.hpp"

#ifndef _OBJECT_H
#define _OBJECT_H

class Object
{
private:
    Vector3 position;
    // rotation in degres
    Vector3 rotation;
    Vector3 rotationOverTime;
    std::string lightAscii;
    Vector3 scale;
    Vector3 lightSource;

    const float theta_spacing = 0.004;
    const float phi_spacing = 0.001;

    virtual Vector3 DrawObject(float theta, float phi) = 0;

    Vector3 RotateObject(Vector3 position, Vector3 rotation);

    Vector3 MoveObject(Vector3 position, Vector3 newPosition);

    Vector3 ScaleObject(Vector3 position, Vector3 newScale);

    float CalculateLigth(Vector3 lightSource, Vector3 rotation, float theta, float phi);

public:
    Object();
    void setPosition(Vector3 newPosition);
    void setRotation(Vector3 newRotation);
    void setScale(Vector3 newScale);
    void setRotationOverTime(Vector3 newRotationOverTime);
    void setLightSource(Vector3 newLightSource);
    void IncreaseRotation();
    void Draw_Object(char *objectDrawBuffer, float *objectMathBuffer, size_t height, size_t width);
    void Draw_Point(char *objectDrawBuffer, float *objectMathBuffer, int height, int width, float theta, float phi);
    virtual void objectType() = 0;
};
#endif