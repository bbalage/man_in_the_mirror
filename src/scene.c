#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    scene->tex_wall = load_texture("textures/brick3.jpg");
	scene->tex_floor = load_texture("textures/floor.jpeg");
	scene->tex_darkcloth = load_texture("textures/darkcloth.jpg");
	init_models(scene);
}

void set_lighting()
{
    float ambient_light[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    float diffuse_light[] = { 0.5f, 0.5f, 0.5, 0.5f };
    float specular_light[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    set_lighting();
    draw_origin();
    draw_models(&(scene->olist));
}

void draw_models(const Object* olist){
	Object *obj = olist->next;
	glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
	while(obj != NULL){
		glBindTexture(GL_TEXTURE_2D, obj->texture_id);
		set_material(&(obj->material));
		glTranslatef(obj->pos.x,obj->pos.y,obj->pos.z);
		glRotatef(obj->rot.x, 1.0, 0, 0);
		glRotatef(obj->rot.y, 0, 1.0, 0);
		glRotatef(obj->rot.z, 0, 0, 1.0);
		draw_model(&(obj->model));
		glRotatef(-obj->rot.z, 0, 0, 1.0);
		glRotatef(-obj->rot.y, 0, 1.0, 0);
		glRotatef(-obj->rot.x, 1.0, 0, 0);
		glTranslatef(-obj->pos.x,-obj->pos.y,-obj->pos.z);
		obj = obj->next;
	}
}

void init_models(Scene* scene){
	Object *obj = &scene->olist;
	int i, j, k;
	for(k = 0; k < 2; k++){
		for(i = 0; i < 6; i++){
			for(j = 0; j < 6; j++){
				obj->next = malloc(sizeof(Object));
				obj = obj->next;
				load_model(&(obj->model), "models/wall.obj");
				obj->texture_id = scene->tex_floor;
				obj->pos.x = 0.1*j;
				obj->pos.y = 0.1*i;
				obj->pos.z = 0.1*k;
				obj->rot.x = 0;
				obj->rot.y = 0;
				obj->rot.z = 0;	
				obj->material.ambient.red = 0.6;
				obj->material.ambient.green = 0.6;
				obj->material.ambient.blue = 0.6;
				obj->material.diffuse.red = 0.6;
				obj->material.diffuse.green = 0.6;
				obj->material.diffuse.blue = 0.6;
				obj->material.specular.red = 0.6;
				obj->material.specular.green = 0.6;
				obj->material.specular.blue = 0.6;
				obj->material.shininess = 100.0;
			}
		}
	}
	for(i = 0; i < 6; i++){
		obj->next = malloc(sizeof(Object));
		obj = obj->next;
		load_model(&(obj->model), "models/wall.obj");
		obj->texture_id = scene->tex_wall;
		obj->pos.x = 0.1*i;
		obj->pos.y = 0;
		obj->pos.z = 0;
		obj->rot.x = 90;
		obj->rot.y = 0;
		obj->rot.z = 0;
		obj->material.ambient.red = 0.5;
		obj->material.ambient.green = 0.5;
		obj->material.ambient.blue = 0.5;
		obj->material.diffuse.red = 0.5;
		obj->material.diffuse.green = 0.5;
		obj->material.diffuse.blue = 0.5;
		obj->material.specular.red = 0.5;
		obj->material.specular.green = 0.5;
		obj->material.specular.blue = 0.5;
		obj->material.shininess = 100.0;
	}
	for(i = 0; i < 6; i++){
		obj->next = malloc(sizeof(Object));
		obj = obj->next;
		load_model(&(obj->model), "models/wall.obj");
		obj->texture_id = scene->tex_wall;
		obj->pos.x = 0.1*i;
		obj->pos.y = 0.6;
		obj->pos.z = 0;
		obj->rot.x = 90;
		obj->rot.y = 0;
		obj->rot.z = 0;
		obj->material.ambient.red = 0.5;
		obj->material.ambient.green = 0.5;
		obj->material.ambient.blue = 0.5;
		obj->material.diffuse.red = 0.5;
		obj->material.diffuse.green = 0.5;
		obj->material.diffuse.blue = 0.5;
		obj->material.specular.red = 0.5;
		obj->material.specular.green = 0.5;
		obj->material.specular.blue = 0.5;
		obj->material.shininess = 100.0;
	}
	for(i = 0; i < 6; i++){
		obj->next = malloc(sizeof(Object));
		obj = obj->next;
		load_model(&(obj->model), "models/wall.obj");
		obj->texture_id = scene->tex_wall;
		obj->pos.x = 0;
		obj->pos.y = 0.1*i;
		obj->pos.z = 0;
		obj->rot.x = 90;
		obj->rot.y = 90;
		obj->rot.z = 0;
		obj->material.ambient.red = 0.5;
		obj->material.ambient.green = 0.5;
		obj->material.ambient.blue = 0.5;
		obj->material.diffuse.red = 0.5;
		obj->material.diffuse.green = 0.5;
		obj->material.diffuse.blue = 0.5;
		obj->material.specular.red = 0.5;
		obj->material.specular.green = 0.5;
		obj->material.specular.blue = 0.5;
		obj->material.shininess = 100.0;
	}
	for(i = 0; i < 6; i++){
		obj->next = malloc(sizeof(Object));
		obj = obj->next;
		load_model(&(obj->model), "models/wall.obj");
		obj->texture_id = scene->tex_wall;
		obj->pos.x = 0.6;
		obj->pos.y = 0.1*i;
		obj->pos.z = 0;
		obj->rot.x = 90;
		obj->rot.y = 90;
		obj->rot.z = 0;
		obj->material.ambient.red = 0.5;
		obj->material.ambient.green = 0.5;
		obj->material.ambient.blue = 0.5;
		obj->material.diffuse.red = 0.5;
		obj->material.diffuse.green = 0.5;
		obj->material.diffuse.blue = 0.5;
		obj->material.specular.red = 0.5;
		obj->material.specular.green = 0.5;
		obj->material.specular.blue = 0.5;
		obj->material.shininess = 100.0;
	}
	obj->next = malloc(sizeof(Object));
	obj = obj->next;
	load_model(&(obj->model), "models/proba3_2.obj");
	obj->texture_id = scene->tex_darkcloth;
	obj->pos.x = 0.5;
	obj->pos.y = 0.5;
	obj->pos.z = 0;
	obj->rot.x = 90;
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
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

int checkhit_wall(vec3 newpos, double precision){
	if(newpos.x < WALL_MIN_X + precision || newpos.x > WALL_MAX_X - precision || newpos.y < WALL_MIN_Y + precision || newpos.y > WALL_MAX_Y - precision) return FALSE;
	return TRUE;
}

int checkhit(Object* olist, vec3 newpos, double precision){
	Object* obj = olist->next;
	while(obj != NULL){
		if(newpos.x < obj->pos.x + precision && newpos.x > obj->pos.x - precision && newpos.y > obj->pos.y - precision && newpos.y < obj->pos.y + precision) return FALSE;
		obj = obj->next;
	}
	return TRUE;
}

void move_model(Model* model, double xm, double ym, double zm)
{
    int i;
    
    for (i = 0; i < model->n_vertices; i++) {
        model->vertices[i].x += xm;
        model->vertices[i].y += ym;
        model->vertices[i].z += zm;
    }
}