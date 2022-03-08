#include <iostream>
#include <stdio.h>

#include "Vector3.hpp"
#include "Object.hpp"
#include <vector>

#ifndef _Display_H
#define _Display_H

class Display
{
private:
    Vector3 position;
    // rotation in degres
    Vector3 rotation;
    Vector3 rotationOverTime;
    Vector3 scale;
    Vector3 lightSource;
    std::string lightAscii;

    std::vector<Object *> objects;

    const float theta_spacing = 0.07;
    const float phi_spacing = 0.02;

    int height;
    int width;
    void displayObjects(char *buffer);

public:
    Display();
    void setPosition(Vector3 newPosition);
    void setRotation(Vector3 newRotation);
    void setScale(Vector3 newScale);
    void setRotationOverTime(Vector3 newRotationOverTime);
    void setLightSource(Vector3 newLightSource);
    void setSize(int newHeight, int newWidth);
    void addObjects(std::vector<Object *> newObjects);
    void drawObjects();
};
#endif