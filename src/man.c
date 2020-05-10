#include "man.h"

#include "utils.h"

void move(vec3 newpos, vec3 newrot)
{
	;
}

void init_man(Man* man, vec3 pos, vec3 rot, GLuint tex_id)
{
	man->pos = pos;
	man->rot = rot;
	int desc[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 100.0};
	man->leg1 = *(load_object(desc, "models/nleg.obj", tex_id));
}

/*
	vec3 pos;
	vec3 rot;
	Object leg1;
	Object leg2;
	Object head;
	Object arm1;
	Object arm2;
	Object torso;
	
	obj->next = malloc(sizeof(Object));
	obj = obj->next;
	load_model(&(obj->model), "models/nleg.obj");
	obj->texture_id = scene->tex_darkcloth;
	obj->pos.x = 0.5;
	obj->pos.y = 0.5;
	obj->pos.z = 0;
	obj->rot.x = 0;
	obj->rot.y = 0;
	obj->rot.z = 0;
	obj->material.ambient.red = 1;
	obj->material.ambient.green = 1;
	obj->material.ambient.blue = 1;
	obj->material.diffuse.red = 1;
	obj->material.diffuse.green = 1;
	obj->material.diffuse.blue = 1;
	obj->material.specular.red = 1;
	obj->material.specular.green = 1;
	obj->material.specular.blue = 1;
	obj->material.shininess = 100.0;
	obj->next = NULL;
*/