#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_models(Scene* scene){
	Object *obj = &scene->olist;
	int i, j;
	//for(i = 0; i < 5; i++){
		//for(j = 0; j < 5; j++){
			load_model(&(obj->model), "wall.obj");
			obj->texture_id = load_texture("brick3.jpg");
	
			obj->pos.x = 0.1;
			obj->pos.y = 0;
			obj->pos.z = 0;
			obj->rot.x = 90;
			obj->rot.y = 0;
			obj->rot.z = 0;
			glBindTexture(GL_TEXTURE_2D, obj->texture_id);
	
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
			obj->next = NULL;
		//}
	//}
}

void init_scene(Scene* scene)
{
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
	Object *obj = olist;
	glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
	while(obj != NULL){
		set_material(&(obj->material));
		glRotatef(obj->rot.x, 1.0, 0, 0);
		glRotatef(obj->rot.y, 0, 1.0, 0);
		glRotatef(obj->rot.z, 0, 0, 1.0);
		glTranslatef(obj->pos.x,obj->pos.y,obj->pos.z);
		draw_model(&(obj->model));
		glTranslatef(-obj->pos.x,-obj->pos.y,-obj->pos.z);
		glRotatef(-obj->rot.z, 0, 0, 1.0);
		glRotatef(-obj->rot.y, 0, 1.0, 0);
		glRotatef(-obj->rot.x, 1.0, 0, 0);
		obj = obj->next;
	}
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

void move_model(Model* model, double xm, double ym, double zm)
{
    int i;
    
    for (i = 0; i < model->n_vertices; i++) {
        model->vertices[i].x += xm;
        model->vertices[i].y += ym;
        model->vertices[i].z += zm;
    }
}