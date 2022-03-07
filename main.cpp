#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "Headers/Vector3.hpp"
#include "Headers/Object.hpp"
using namespace std;

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

// g++ main.cpp Sources/Object.cpp -o main