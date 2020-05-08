#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>
#include "utils.h"
#include <obj/load.h>
#include <obj/draw.h>

/**
* A general 3D object in the program.
*/
typedef struct Object
{
	Model model;
	Material material;
	GLuint texture_id;
	vec3 pos;
	vec3 rot;
	struct Object* next;
} Object;

/**
* Function to be called to load an object.
* desc should be an array of doubles which represent:
*/
Object* load_object(double desc[], char modelname[], GLuint tex_id);
#endif