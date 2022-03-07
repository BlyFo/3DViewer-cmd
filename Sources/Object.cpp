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

Vector3 Object::DrawObject(float innerRadius, float outerRadius, float theta, float phi)
{
    Vector3 result;
    result.x = (outerRadius + innerRadius * cos(theta)) * cos(phi);
    result.y = innerRadius * sin(theta);
    result.z = (outerRadius + innerRadius * cos(theta)) * sin(phi);
    return result;
}

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
    // theta_spacing = 0.07;
    // phi_spacing = 0.02;
    innerRadius = 1;
    outerRadius = 3;
    color = "white";
}
void Object::setPosition(Vector3 newPosition)
{
    position = newPosition;
}
void Object::setRotation(Vector3 newRotation)
{
    rotation = newRotation;
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
}
void Object::setLightSource(Vector3 newLightSource)
{
    lightSource = newLightSource;
}
void Object::Draw_Object(char *objectDrawBuffer, float *objectMathBuffer, size_t height, size_t width)
{
    const size_t buffer_size = height * width;
    // used to draw the shape in screen
    memset(objectDrawBuffer, 32, buffer_size); // 32 => ' ' so the backsground is black

    // used to store information of each point in screen
    memset(objectMathBuffer, 0, buffer_size * sizeof(float)); // sizeof float = 4 1760*4 = 7040

    // struct Vector3 position;
    for (float theta = 0; 2 * PI > theta; theta += theta_spacing)
    {
        for (float phi = 0; 2 * PI > phi; phi += phi_spacing)
        {

            Vector3 object = DrawObject(innerRadius, outerRadius, theta, phi); // works
            // printf("DrawDonut: x=%f y=%f z=%f \n",object.x,object.y,object.z);

            object = ScaleObject(object, scale);
            // printf("ScaleObject: x=%f y=%f z=%f\n",object.x,object.y,object.z);

            // printf("rotation: x=%f y=%f z=%f \n",rotation.x,rotation.y,rotation.z);
            object = RotateObject(object, rotation); // works
            // printf("rotateObject: x=%f y=%f z=%f\n",object.x,object.y,object.z);

            object = MoveObject(object, position);
            // printf("MoveObject: x=%f y=%f z=%f\n",object.x,object.y,object.z);

            float pointLight = CalculateLigth(lightSource, rotation, theta, phi);
            // printf("pointLight: %f\n",pointLight);
            float inverseZ = 1 / object.z;

            if (pointLight > 0)
            {
                int arrayX = width / 2 + 30 * inverseZ * object.x;
                int arrayY = height / 2 + 15 * inverseZ * object.y;
                // printf("Array: x=%d y=%d \n",arrayX,arrayY);

                int arrayPosition = arrayX + width * arrayY;
                if (inverseZ > objectMathBuffer[arrayPosition])
                {
                    int lightAmount = (8 * pointLight);

                    objectMathBuffer[arrayPosition] = inverseZ;
                    objectDrawBuffer[arrayPosition] = lightAscii[lightAmount];
                }
            }
            // printf("---------- \n");
        }
    }
    rotation.x += rotationOverTime.x;
    rotation.y += rotationOverTime.y;
    rotation.z += rotationOverTime.z;
}
/*

void display_Object(char *buffer, size_t height, size_t width)
{
    const size_t buffer_size = height * width;
    printf("\x1b[H"); // linux
    // system("cls"); // windows
    for (int k = 0; buffer_size >= k; k++)
    {
        if (buffer[k] == '@' || buffer[k] == '$' || buffer[k] == '#' || buffer[k] == '*')
        {
            printf("\033[1;34m");
        }
        if (buffer[k] == '!' || buffer[k] == '=' || buffer[k] == ';' || buffer[k] == ':')
        {
            printf("\033[0;34m");
        }
        if (buffer[k] == '~' || buffer[k] == '-' || buffer[k] == ',' || buffer[k] == '.')
        {
            printf("\033[2;34m");
        }

        // putchar(k % width ? buffer[k] : 10); // 10 => new line ASCII
        // printf("k=%d width=%lu = %lu ",k,width,(k%width));
        if (k % width == 0)
        {
            putchar(10);
            // printf("entro \n");
        }
        else
        {
            putchar(buffer[k]);
            // printf("no entro <------ \n");
        }
    }
    printf("\033[0m");
}

int main()
{
    const size_t height = 40;
    const size_t width = 80;
    const float innerRadius = 1;
    const float outerRadius = 3;

    const size_t buffer_size = height * width;

    float objectMathBuffer[buffer_size];
    char objectDrawBuffer[buffer_size];

    // Create Car objects and call the constructor with different values
    Vector3 position = {0, 0, 6};
    Vector3 rotation = {0, 0, 6};
    Vector3 scale = {1, 1, 1};
    Vector3 rotationOverTime = {1, 0.2, 1.5};
    Vector3 lightSource = {0, -1, -1};
    string color = "red";
    Object donut;
    donut.setPosition(position);
    donut.setRotation(rotation);
    donut.setScale(scale);
    donut.setLightSource(lightSource);
    donut.setRotationOverTime(rotationOverTime);
    donut.setColor(color);

    printf("\x1b[2J");
    for (;;)
    {
        donut.Draw_Object(objectDrawBuffer, objectMathBuffer, height, width);
        display_Object(objectDrawBuffer, height, width);
    }

    return 0;
}
*/