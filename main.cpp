#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "Headers/Vector3.hpp"
#include "Headers/Object.hpp"
#include "Headers/Donut.hpp"
#include "Headers/Sphere.hpp"
#include "Headers/Display.hpp"

using namespace std;

int main()
{
    const int height = 50;
    const int width = 100;

    Vector3 position = {0, -2, 6};
    Vector3 position2 = {0, 7, 7};
    Vector3 rotation = {0, 0, 6};
    Vector3 scale = {1, 1, 1};
    Vector3 rotationOverTime = {1, 0.2, 1.5};
    Vector3 lightSource = {0, -1, -1};
    string color = "red";

    Donut donut;
    donut.setPosition(position);
    donut.setRotation(rotation);
    donut.setScale(scale);
    donut.setRotationOverTime(rotationOverTime);
    donut.setColor(color);

    Sphere sphere;
    sphere.setPosition(position2);
    sphere.setRotation(rotation);
    sphere.setScale(scale);
    sphere.setRotationOverTime(rotationOverTime);
    sphere.setColor(color);

    Display canvas;

    std::vector<Object *> objectsVector;

    objectsVector.push_back(&sphere);
    objectsVector.push_back(&donut);
    canvas.setSize(height, width);
    canvas.addObjects(objectsVector);
    canvas.setLightSource(lightSource);
    canvas.drawObjects();

    return 0;
}
// g++ main.cpp Sources/Object.cpp Sources/Donut.cpp Sources/Sphere.cpp Sources/Display.cpp -o main