#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>
#include "utils.h"
#include <obj/load.h>
#include <obj/draw.h>

typedef enum Object_types {BOUND, PAINTING, MAN} Object_types;

/**
* A general 3D object in the program.
*/
typedef struct Object
{
	Model* model;
	Object_types type;
	Material material;
	GLuint texture_id;
	vec3 pos;
	vec3 rot;
	struct Object* next;
} Object;

typedef struct Model_List
{
	Model boundmodel;
	Model paintingmodel;
	Model mlegmodel;
	Model marmmodel;
	Model mheadmodel;
	Model mbodymodel;
	Model refmbodymodel;
	Model refmheadmodel;
	/*Model plegmodel;
	Model parmmodel;
	Model pheadmodel;
	Model pbodymodel;
	Model refpbodymodel;
	Model refpheadmodel;*/
	Model refboundmodel;
} Model_List;

/**
* Function to be called to load an object.
* desc should be an array of doubles which represent:
*/
Object* load_object(double desc[], Model* model, GLuint tex_id, enum Object_types);
#endif