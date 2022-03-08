#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "../Headers/Vector3.hpp"
#include "../Headers/Object.hpp"

using namespace std;

const float PI = 3.1415;
const float Deg2Rad = (PI * 2) / 360;
const float Rad2Deg = 180 / (PI * 2);

Vector3 Object::RotateObject(Vector3 position, Vector3 rotation)
{
    Vector3 result;

    float radX = rotation.x * Deg2Rad;
    float radY = rotation.y * Deg2Rad;
    float radZ = rotation.z * Deg2Rad;
    float sinX = sin(radX);
    float cosX = cos(radX);
    float sinY = sin(radY);
    float cosY = cos(radY);
    float sinZ = sin(radZ);
    float cosZ = cos(radZ);

    Vector3 xAxis = {
        cosY * cosZ,
        cosX * sinZ + sinX * sinY * cosZ,
        sinX * sinZ - cosX * sinY * cosZ,
    };

    Vector3 yAxis = {
        -cosY * sinZ,
        cosX * cosZ - sinX * sinY * sinZ,
        sinX * cosZ + cosX * sinY * sinZ,
    };
    Vector3 zAxis = {
        sinY,
        -sinX * cosY,
        cosX * cosY,
    };

    result.x = xAxis.x * position.x + yAxis.x * position.y + zAxis.x * position.z;
    result.y = xAxis.y * position.x + yAxis.y * position.y + zAxis.y * position.z;
    result.z = xAxis.z * position.x + yAxis.z * position.y + zAxis.z * position.z;
    return result;
}

Vector3 Object::MoveObject(Vector3 position, Vector3 newPosition)
{
    Vector3 result;
    result.x = position.x + newPosition.x;
    result.y = position.y + newPosition.y;
    result.z = position.z + newPosition.z;
    return result;
}

Vector3 Object::ScaleObject(Vector3 position, Vector3 newScale)
{
    Vector3 result;
    result.x = position.x * newScale.x;
    result.y = position.y * newScale.y;
    result.z = position.z * newScale.z;
    return result;
}

float Object::CalculateLigth(Vector3 lightSource, Vector3 rotation, float theta, float phi)
{
    Vector3 startRotation = {
        cos(theta) * cos(phi),
        sin(theta),
        cos(theta) * sin(phi),
    };

    Vector3 normal = RotateObject(startRotation, rotation);

    float light = normal.x * lightSource.x + normal.y * lightSource.y + normal.z * lightSource.z;

    return light;
}

Object::Object()
{
    position = {0, 0, 0};
    rotation = {0, 0, 0};
    rotationOverTime = {0, 0, 0};
    lightAscii = ".,-~:;=!*#$@";
    scale = {1, 1, 1};
    lightSource = {0, 0, 0};
    color = "white";
    colorCode = 0;
}
void Object::setPosition(Vector3 newPosition)
{
    position = newPosition;
}
void Object::setRotation(Vector3 newRotation)
{
    rotation = newRotation;
}
void Object::IncreaseRotation()
{
    rotation.x += rotationOverTime.x;
    rotation.y += rotationOverTime.y;
    rotation.z += rotationOverTime.z;
}
void Object::setScale(Vector3 newScale)
{
    scale = newScale;
}
void Object::setRotationOverTime(Vector3 newRotationOverTime)
{
    rotationOverTime = newRotationOverTime;
}
void Object::setColor(string newColor)
{
    color = newColor;
    if (newColor == "black")
    {
        colorCode = 30;
    }
    if (newColor == "red")
    {
        colorCode = 31;
    }
    if (newColor == "green")
    {
        colorCode = 32;
    }
    if (newColor == "yellow")
    {
        colorCode = 33;
    }
    if (newColor == "blue")
    {
        colorCode = 34;
    }
    if (newColor == "magenta")
    {
        colorCode = 35;
    }
    if (newColor == "cyan")
    {
        colorCode = 36;
    }
    if (newColor == "white")
    {
        colorCode = 37;
    }
}
void Object::setLightSource(Vector3 newLightSource)
{
    lightSource = newLightSource;
}
int Object::getColorCode()
{
    return colorCode;
}

void Object::Draw_Object(char *objectDrawBuffer, float *objectMathBuffer, size_t height, size_t width)
{
    const size_t buffer_size = height * width;
    // used to draw the shape in screen
    memset(objectDrawBuffer, 32, buffer_size); // 32 => ' ' so the backsground is black

    // used to store information of each point in screen
    memset(objectMathBuffer, 0, buffer_size * sizeof(float));

    for (float theta = 0; 2 * PI > theta; theta += theta_spacing)
    {
        for (float phi = 0; 2 * PI > phi; phi += phi_spacing)
        {

            Vector3 object = DrawObject(theta, phi);

            object = ScaleObject(object, scale);
            object = RotateObject(object, rotation);
            object = MoveObject(object, position);

            float pointLight = CalculateLigth(lightSource, rotation, theta, phi);

            float inverseZ = 1 / object.z;

            if (pointLight > 0)
            {
                int arrayX = width / 2 + 30 * inverseZ * object.x;
                int arrayY = height / 2 + 30 * inverseZ * object.y;

                int arrayPosition = arrayX + width * arrayY;
                if (inverseZ > objectMathBuffer[arrayPosition])
                {
                    int lightAmount = (12 * pointLight);

                    objectMathBuffer[arrayPosition] = inverseZ;
                    objectDrawBuffer[arrayPosition] = lightAscii[lightAmount];
                }
            }
        }
    }
    IncreaseRotation();
}
void Object::Draw_Point(char *objectDrawBuffer, float *objectMathBuffer, int height, int width, float theta, float phi)
{

    Vector3 object = DrawObject(theta, phi);

    object = ScaleObject(object, scale);
    object = RotateObject(object, rotation);
    object = MoveObject(object, position);

    float pointLight = CalculateLigth(lightSource, rotation, theta, phi);
    float inverseZ = 1 / object.z;

    if (pointLight > 0)
    {
        int arrayX = width / 2 + 30 * inverseZ * object.x;
        int arrayY = height / 2 + 15 * inverseZ * object.y;

        int arrayPosition = arrayX + width * arrayY;
        if (inverseZ > objectMathBuffer[arrayPosition])
        {
            int lightAmount = (8 * pointLight);

            objectMathBuffer[arrayPosition] = inverseZ;
            objectDrawBuffer[arrayPosition] = lightAscii[lightAmount];
        }
    }
}