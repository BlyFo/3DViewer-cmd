#include <stdio.h>
#include <math.h>
#include <string.h>

struct Vector3
{
  float x;
  float y;
  float z;
};

struct Vector3 RotationOverTime = {0, 0, 0};

const float theta_spacing = 0.07;
const float phi_spacing = 0.02;

const float PI = 3.1415;
const float Deg2Rad = (PI * 2) / 360;
const float Rad2Deg = 180 / (PI * 2);

char lightAscii[] = {'.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'};

void display_Object(char *buffer, size_t height, size_t width)
{
  const size_t buffer_size = height * width;

  printf("\x1b[H");

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

    if(k%width==0){
      putchar(10);
    }else{
      putchar(buffer[k]);
    }
  }
  printf("\033[0m");
}

struct Vector3 DrawDonut(float innerRadius, float outerRadius, float theta, float phi)
{
  struct Vector3 result;
  result.x = (outerRadius + innerRadius * cos(theta)) * cos(phi);
  result.y = innerRadius * sin(theta);
  result.z = (outerRadius + innerRadius * cos(theta)) * sin(phi);
  return result;
}
struct Vector3 RotateObject(struct Vector3 position, struct Vector3 rotation)
{
  struct Vector3 result;

  float radX = rotation.x * Deg2Rad;
  float radY = rotation.y * Deg2Rad;
  float radZ = rotation.z * Deg2Rad;
  float sinX = sin(radX);
  float cosX = cos(radX);
  float sinY = sin(radY);
  float cosY = cos(radY);
  float sinZ = sin(radZ);
  float cosZ = cos(radZ);

  struct Vector3 xAxis = {
      cosY * cosZ,
      cosX * sinZ + sinX * sinY * cosZ,
      sinX * sinZ - cosX * sinY * cosZ,
  };

  struct Vector3 yAxis = {
      -cosY * sinZ,
      cosX * cosZ - sinX * sinY * sinZ,
      sinX * cosZ + cosX * sinY * sinZ,
  };
  struct Vector3 zAxis = {
      sinY,
      -sinX * cosY,
      cosX * cosY,
  };

  result.x = xAxis.x * position.x + yAxis.x * position.y + zAxis.x * position.z;
  result.y = xAxis.y * position.x + yAxis.y * position.y + zAxis.y * position.z;
  result.z = xAxis.z * position.x + yAxis.z * position.y + zAxis.z * position.z;
  return result;
}
struct Vector3 MoveObject(struct Vector3 position, struct Vector3 newPosition)
{
  struct Vector3 result;
  result.x = position.x + newPosition.x;
  result.y = position.y + newPosition.y;
  result.z = position.z + newPosition.z;
  return result;
}
struct Vector3 ScaleObject(struct Vector3 position, struct Vector3 newScale)
{
  struct Vector3 result;
  result.x = position.x * newScale.x;
  result.y = position.y * newScale.y;
  result.z = position.z * newScale.z;
  return result;
}

float CalculateLigth(struct Vector3 lightSource, struct Vector3 rotation, float theta, float phi)
{
  struct Vector3 startRotation = {
      cos(theta) * cos(phi),
      sin(theta),
      cos(theta) * sin(phi),
  };

  struct Vector3 normal = RotateObject(startRotation, rotation);

  float light = normal.x * lightSource.x + normal.y * lightSource.y + normal.z * lightSource.z;

  return light;
}

void Draw_Object(char *objectDrawBuffer, float *objectMathBuffer, size_t height, size_t width, float innerRadius, float outerRadius, float distance)
{
  const size_t buffer_size = height * width;

  memset(objectDrawBuffer, 32, buffer_size); // 32 => ' ' so the backsground is black

  memset(objectMathBuffer, 0, buffer_size * sizeof(float));

  for (float theta = 0; 2 * PI > theta; theta += theta_spacing)
  {
    
    for (float phi = 0; 2 * PI > phi; phi += phi_spacing)
    {

      struct Vector3 object = DrawDonut(innerRadius, outerRadius, theta, phi);

      struct Vector3 scale = {1, 1, 1};
      object = ScaleObject(object, scale);

      struct Vector3 rotation = {
          RotationOverTime.x * Rad2Deg * 6,
          RotationOverTime.y * Rad2Deg * 6,
          RotationOverTime.z * Rad2Deg * 2,
      };
      object = RotateObject(object, rotation);

      struct Vector3 position = {0, 0, distance};
      object = MoveObject(object, position);

      struct Vector3 lightSource = {0, -1, -1};
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
  }
}

int main()
{

  const size_t height = 50;
  const size_t width = 100;

  const float innerRadius = 1;
  const float outerRadius = 3;
  const float distance = 6;

  const size_t buffer_size = height * width;

  float objectMathBuffer[buffer_size];
  char objectDrawBuffer[buffer_size];

  printf("\x1b[2J");
  for (;;)
  {
    Draw_Object(objectDrawBuffer, objectMathBuffer, height, width, innerRadius, outerRadius, distance);

    display_Object(objectDrawBuffer, height, width);
    //   Rotation Speed and angle
    RotationOverTime.x += 0.008;
    RotationOverTime.y += 0.0005;
    RotationOverTime.z += 0.004;
  }
}

// gcc donutRefactor.c -o donut -lm