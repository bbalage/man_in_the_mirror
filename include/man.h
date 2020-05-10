#ifndef MAN_H
#define MAN_H

#include "objects.h"

/**
 * A structure representing a man.
 */
typedef struct Man
{
	vec3 pos;
	vec3 rot;
	Object leg1;
	Object leg2;
	Object head;
	Object arm1;
	Object arm2;
	Object torso;
} Man;

/**
 * Function to be called to move the man.
 */
void move(vec3 newpos, vec3 newrot);

/**
 * Function for initializing a man.
 */
void init_man(Man* man, vec3 pos, vec3 rot, GLuint tex_id);
#endif