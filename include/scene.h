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
	Model_List mlist;
    Object olist;
	Man man;
} Scene;

void init_models(Scene* scene);

void init_bounds(Scene* scene);

void draw_man(const Man* man);

void draw_bounds(const Object* olist);
/**
 * Initialize the scene by loading models.
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
void draw_scene(const Scene* scene);

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
