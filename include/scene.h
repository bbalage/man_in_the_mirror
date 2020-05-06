#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct Object
{
	Model model;
	Material material;
	GLuint texture_id;
	vec3 pos;
	vec3 rot;
	struct Object* next;
} Object;

typedef struct Scene
{
    Camera camera;
	GLuint tex_floor;
	GLuint tex_wall;
    Object olist;
} Scene;

void init_models(Scene* scene);
void draw_models(const Object* olist);
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
 * Move the loaded model.
 */
void move_model(Model* model, double xm, double ym, double zm);
#endif /* SCENE_H */
