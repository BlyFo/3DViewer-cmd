#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "Headers/Vector3.hpp"
#include "Headers/Object.hpp"
#include "Headers/Donut.hpp"
#include "Headers/Sphere.hpp"
#include "Headers/Cube.hpp"
#include "Headers/Display.hpp"

using namespace std;

int main()
{
    Vector3 positionDonut = {0, 0, 5};
    Vector3 positionSphere = {0, -4.5, 6};
    Vector3 positionDonut2 = {-6, -4.5, 6};
    Vector3 positionDonut3 = {6, -4.5, 6};
    Vector3 rotationOverTime = {1, 0.2, 1.5};

    Donut donut(1, 3);
    donut.setPosition(positionDonut);
    donut.setRotationOverTime(rotationOverTime);

    Donut donut2(0.7, 1.5);
    donut2.setPosition(positionDonut2);
    donut2.setRotationOverTime(rotationOverTime);

    Donut donut3(0.7, 1.5);
    donut3.setPosition(positionDonut3);
    donut3.setRotationOverTime(rotationOverTime);

    Sphere sphere(1.5);
    sphere.setPosition(positionSphere);
    sphere.setRotationOverTime(rotationOverTime);

    const int height = 50;
    const int width = 150;
    Vector3 lightSource = {0, -1, -1};
    string color = "green";

    Display canvas;

    std::vector<Object *> objectsVector;

    // objectsVector.push_back(&sphere);
    objectsVector.push_back(&donut);
    // objectsVector.push_back(&donut2);
    // objectsVector.push_back(&donut3);

    canvas.setSize(height, width);
    canvas.addObjects(objectsVector);
    canvas.setLightSource(lightSource);
    canvas.setColor(color);
    canvas.drawObjects();

    return 0;
}
// g++ main.cpp Sources/Object.cpp Sources/Donut.cpp Sources/Sphere.cpp Sources/Display.cpp -o main