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
    Camera camera;
	GLuint tex_floor;
	GLuint tex_wall;
	GLuint tex_darkcloth;
	GLuint tex_painting;
	Model_List mlist;
	Model_List rmlist;
    Object olist; //the first element of the olist must be blank!
	Object ornlist; //the first element of the ornlist must be blank!
	Object rolist; //the first element of the rolist must be blank!
	Man man;
	vec3 mir_plane;
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
 * Sets up the list containing the ornaments, like the painting.
 */
//void init_ornaments(scene);

/**
 * Makes a list of everything in the scene that cannot change and has a reflection, then places it in the scene's st_refl object list.
 */
void create_static_reflection(Scene* scene);

/**
 * Creates mirrored models for the scene.
 */
//void create_mirrored_models(Scene* scene);

/**
 * Draws the man using the ready data.
 */
void draw_man(Man* man);

/**
 * Draws the walls, floors and roof.
 */
void draw_bounds(const Object* olist);

/**
 * Draws the ornaments.
 */
//void draw_ornaments(const Object ornlist);
/**
 * Initialize the scene by calling other init functions and setting up textures.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Check if the position given with newx and newy would be a hit with any object in the scene.
 */
int checkhit(Object* olist, vec3 newpos, double precision);

/**
 * Check if the position given with newx and newy would be a hit with static wall boundaries.
 */
int checkhit_wall(vec3 newpos, double precision);
/**
 * Move the loaded model.
 */
void move_model(Model* model, double xm, double ym, double zm);
#endif /* SCENE_H */
