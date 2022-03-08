#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "../Headers/Vector3.hpp"
#include "../Headers/Object.hpp"
#include "../Headers/Display.hpp"

using namespace std;

const float PI = 3.1415;
const float Deg2Rad = (PI * 2) / 360;
const float Rad2Deg = 180 / (PI * 2);

Display::Display()
{
    position = {0, 0, 0};
    rotation = {0, 0, 0};
    rotationOverTime = {0, 0, 0};
    lightAscii = ".,-~:;=!*#$@";
    scale = {1, 1, 1};
    lightSource = {0, 0, 0};
    height = 0;
    width = 0;
    color = "white";
    colorCode = 0;
}
void Display::setPosition(Vector3 newPosition)
{
    position = newPosition;
}
void Display::setRotation(Vector3 newRotation)
{
    rotation = newRotation;
}
void Display::setScale(Vector3 newScale)
{
    scale = newScale;
}
void Display::setRotationOverTime(Vector3 newRotationOverTime)
{
    rotationOverTime = newRotationOverTime;
}
void Display::setLightSource(Vector3 newLightSource)
{
    lightSource = newLightSource;
}
void Display::setSize(int newHeight, int newWidth)
{
    height = newHeight;
    width = newWidth;
}
void Display::addObjects(std::vector<Object *> newObjects)
{

    while (!newObjects.empty())
    {
        objects.push_back(newObjects.back());
        newObjects.pop_back();
    }
}
void Display::drawObjects()
{
    const size_t buffer_size = height * width;

    float objectMathBuffer[buffer_size];
    char objectDrawBuffer[buffer_size];

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->setLightSource(lightSource);
        objects[i]->objectType();
    }
    if (height <= 0 || width <= 0)
    {
        printf("height and width can't be 0 or below \n");
        return;
    }

    printf("\x1b[2J");
    for (;;)
    {
        // 32 => ' ' so the backsground is black
        // 45 => '-' usefull for debug
        memset(objectDrawBuffer, 32, buffer_size);

        // used to store information of each point in screen
        memset(objectMathBuffer, 0, buffer_size * sizeof(float));
        for (float theta = 0; 2 * PI > theta; theta += theta_spacing)
        {
            for (float phi = 0; 2 * PI > phi; phi += phi_spacing)
            {
                for (int i = 0; i < objects.size(); i++)
                {
                    objects[i]->Draw_Point(objectDrawBuffer, objectMathBuffer, height, width, theta, phi);
                }
            }
        }

        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->IncreaseRotation();
        }

        displayObjects(objectDrawBuffer);
    }
}
void Display::displayObjects(char *buffer)
{
    const size_t buffer_size = height * width;
    printf("\x1b[H");

    for (int k = 0; buffer_size >= k; k++)
    {
        if (buffer[k] == '@' || buffer[k] == '$' || buffer[k] == '#' || buffer[k] == '*')
        {
            printf("\033[1;%dm", colorCode);
        }
        if (buffer[k] == '!' || buffer[k] == '=' || buffer[k] == ';' || buffer[k] == ':')
        {
            printf("\033[0;%dm", colorCode);
        }
        if (buffer[k] == '~' || buffer[k] == '-' || buffer[k] == ',' || buffer[k] == '.')
        {
            printf("\033[2;%dm", colorCode);
        }

        if (k % width == 0)
        {
            putchar(10);
        }
        else
        {
            putchar(buffer[k]);
        }
    }
    printf("\033[0m");
}
void Display::setColor(string newColor)
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