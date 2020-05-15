#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <time.h>
#define FALSE 0
#define TRUE 1
#define WALK_SPEED 0.2
#define WALK_HEIGHT 0.075


/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient; 
    struct Color diffuse; 
    struct Color specular; 
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);


#endif /* UTILS_H */
