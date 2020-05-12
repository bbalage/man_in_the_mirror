#include "man.h"

#include "utils.h"

void move(vec3 newpos, vec3 newrot)
{
	;
}

void init_man(Man* man, vec3 pos, vec3 rot, GLuint tex_id, Model_List* mlist)
{
	man->pos = pos;
	man->rot = rot;
	double desc[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 100.0};
	man->leg1 = *(load_object(desc, &mlist->mlegmodel, tex_id));
	desc[1] = 0.01;
	man->leg2 = *(load_object(desc, &mlist->mlegmodel, tex_id)); //trimmed to 0.045!!
	desc[1] = 0.02;
	desc[2] = 0.038;
	desc[5] = 90;
	man->body = *(load_object(desc, &mlist->mbodymodel, tex_id)); //trimmed to 0.04
	desc[1] = 0.002;
	desc[2] = 0.075;
	desc[5] = 0;
	man->head = *(load_object(desc, &mlist->mheadmodel, tex_id)); //trimmed to 0.015
	desc[1] = -0.004;
	desc[2] = 0.025;
	desc[5] = 90;
	man->arm1 = *(load_object(desc, &mlist->marmmodel, tex_id)); //trimmed to 0.045
	desc[1] = 0.026;
	//desc[2] = 0.025;
	//desc[5] = 90;
	man->arm2 = *(load_object(desc, &mlist->marmmodel, tex_id)); //trimmed to 0.045
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