#include "objects.h"

/**
* Function to be called to load an object.
* desc should be an array of doubles which represent:
*/
Object* load_object(double desc[], char modelname[], GLuint tex_id)
{
	Object* obj = malloc(sizeof(Object));
	load_model(&(obj->model), modelname);
	obj->texture_id = tex_id;
	obj->pos.x = desc[0];
	obj->pos.y = desc[1];
	obj->pos.z = desc[2];
	obj->rot.x = desc[3];
	obj->rot.y = desc[4];
	obj->rot.z = desc[5];	
	obj->material.ambient.red = desc[6];
	obj->material.ambient.green = desc[7];
	obj->material.ambient.blue = desc[8];
	obj->material.diffuse.red = desc[9];
	obj->material.diffuse.green = desc[10];
	obj->material.diffuse.blue = desc[11];
	obj->material.specular.red = desc[12];
	obj->material.specular.green = desc[13];
	obj->material.specular.blue = desc[14];
	obj->material.shininess = desc[15];
	obj->next = NULL;
	return obj;
}