#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "man.h"

#define WALL_MIN_X 0
#define WALL_MAX_X 0.6
#define WALL_MIN_Y 0
#define WALL_MAX_Y 0.6

typedef struct Scene
{
	GLuint tex_floor;
	GLuint tex_wall;
	GLuint tex_darkcloth;
	GLuint tex_painting;
	GLuint tex_lightcloth;
	GLuint tex_help;
	Model_List mlist;
    Object olist; //the first element of the olist must be blank!
	Object rolist; //the first element of the rolist must be blank!
	Object glass;
	Man man;
	Man refman;
	Man player;
	Man refplayer;
	float light;
} Scene;

/**
 * Sets up a variable for each models located in the scene. Every model is included once.
 */
void init_models(Scene* scene);

/**
 * Sets up the list containing the walls, floor and roof of the scene.
 */
void init_bounds(Scene* scene);

/**
 * Draws the glass representing the mirror.
 */
void draw_glass(Object *glass);

/**
 * Makes a list of everything in the scene that cannot change and has a reflection, then places it in the scene's st_refl object list.
 */
void create_static_reflection(Scene* scene);

/**
 * Draws the man using the ready data.
 */
void draw_man(Man* man);

/**
 * Draws the walls, floors and roof.
 */
void draw_bounds(const Object* olist);

/**
 * Initialize the scene by calling other init functions and setting up textures.
 */
void init_scene(Scene* scene, Camera camera);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float r, float g, float b, float alpha);

/**
 * Set the current material.
 */
void set_material(const Material* material, float alpha);

/**
 * Draw the scene objects.
 */
void draw_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Check if the position given with newx and newy would be a hit with the static boundaries or the other man.
 */
int checkhit(Man man, vec3 newpos, double precision);

#endif /* SCENE_H */
