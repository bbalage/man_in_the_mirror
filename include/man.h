#ifndef MAN_H
#define MAN_H

#include "objects.h"

#define TOP_MOVE_PHASE 20
#define MAN_SLOWDOWN 0.05
#define START_Z 0
/**
 * A structure representing a man.
 */
typedef struct Man
{
	vec3 pos;
	vec3 rot;
	vec3 nextrot;
	int movephase;
	double since_last_move;
	Object leg1;
	Object leg2;
	Object head;
	Object arm1;
	Object arm2;
	Object body;
} Man;

/**
 * Function to be called to move the man.
 */
void move_man(Man* man, vec3 newpos);

/**
 * Function to be called to determine man's next position and rotation.
 */
vec3 get_new_man_pos(Man* man);

/**
 * Function to be called to check if the man should already move.
 */
int check_if_man_moves(Man* man, double elapsed_time);
/**
 * Function for initializing a man.
 */
void init_man(Man* man, GLuint tex_id, Model_List* mlist);
#endif