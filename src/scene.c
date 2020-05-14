#include "scene.h"

void init_scene(Scene* scene)
{
    scene->tex_wall = load_texture("textures/brick3.jpg");
	scene->tex_floor = load_texture("textures/floor.jpeg");
	scene->tex_darkcloth = load_texture("textures/darkcloth.jpg");
	init_models(scene);
	init_bounds(scene);
	init_man(&scene->man, scene->tex_darkcloth, &scene->mlist);
	create_static_reflection(scene);
	scene->mir_plane.x = 1;
	scene->mir_plane.y = 0;
}

void init_models(Scene* scene){
	load_model(&scene->mlist.boundmodel, "models/wall.obj");
	load_model(&scene->mlist.mlegmodel, "models/mleg.obj");
	load_model(&scene->mlist.marmmodel, "models/marm.obj");
	load_model(&scene->mlist.mheadmodel, "models/mhead.obj");
	load_model(&scene->mlist.mbodymodel, "models/mbody.obj");
}

void init_bounds(Scene* scene){
	Object *obj = &scene->olist;
	int i, j, k;
	double desc[] = {0, 0, 0, 0, 0, 0, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 100};
	for(k = 0; k < 2; k++){
		for(i = 0; i < 6; i++){
			for(j = 0; j < 6; j++){
				desc[0] = 0.1*j;
				desc[1] = 0.1*i;
				desc[2] = 0.1*k;
				obj->next = load_object(desc, &scene->mlist.boundmodel, scene->tex_floor);
				obj = obj->next;
			}
		}
	}
	desc[1] = desc[2] = 0;
	desc[3] = 90;
	for(i = 6; i < 15; i++) desc[i] = 0.5;
	for(i = 0; i < 6; i++){
		if(i == 1) break;
		desc[0] = 0.1*i;
		obj->next = load_object(desc, &scene->mlist.boundmodel, scene->tex_wall);
		obj = obj->next;
	}
	desc[1] = 0.6;
	for(i = 0; i < 6; i++){
		if(i == 3) continue;
		desc[0] = 0.1*i;
		obj->next = load_object(desc, &scene->mlist.boundmodel, scene->tex_wall);
		obj = obj->next;
	}
	desc[0] = 0;
	desc[4] = 90;
	for(i = 0; i < 6; i++){
		if(i == 3) continue;
		desc[1] = 0.1*i;
		obj->next = load_object(desc, &scene->mlist.boundmodel, scene->tex_wall);
		obj = obj->next;
	}
	desc[0] = 0.6;
	for(i = 0; i < 6; i++){
		if(i == 3) continue;
		desc[1] = 0.1*i;
		obj->next = load_object(desc, &scene->mlist.boundmodel, scene->tex_wall);
		obj = obj->next;
	}
}

void create_static_reflection(Scene* scene)
{
	Model md;
	Model *mdp, *rmd;
	int i, j, iter;
	Object *obj1 = scene->olist.next, *obj2 = &scene->rolist;
	printf("Into first loop.\n");
	while(obj1 != NULL){
		obj2->next = malloc(sizeof(Object));
		obj2 = obj2->next;
		*obj2 = *obj1;
		obj2->pos.y *= -1;
		//obj2->pos.y -= 0.2;
		obj2->rot.x *= -1;
		//obj2->rot.z *= -1;
		obj1 = obj1->next;
	}
	printf("Out of first loop.\n");
	for(iter = 0; iter < 1; iter++){
		switch(iter){
			case 0: md = scene->mlist.boundmodel; rmd = &scene->rmlist.boundmodel; mdp = &scene->mlist.boundmodel; break;
		}
		md.vertices = malloc(sizeof(Vertex)*(md.n_vertices+1));
		md.texture_vertices = malloc(sizeof(Vertex)*(md.n_texture_vertices+1));
		md.normals = malloc(sizeof(Vertex)*(md.n_normals+1));
		md.triangles = malloc(sizeof(Triangle)*(md.n_triangles));
		printf("Vertices: %d\n", md.n_vertices);
		for(i = 0; i <= md.n_vertices; i++){
			*(md.vertices+i) = *(mdp->vertices+i);
			printf("Vertices:%d\n", i);
			(*(md.vertices+i)).y = (*(mdp->vertices+i)).y*-1;
		}
		for(i = 0; i <= md.n_normals; i++){
			*(md.normals+i) = *(mdp->normals+i);
			printf("Normals: %d\n", i);
			(*(md.normals+i)).y = (*(mdp->normals+i)).y*-1;
		}
		for(i = 0; i <= md.n_texture_vertices; i++){
			*(md.texture_vertices+i) = *(mdp->texture_vertices+i);
			(*(md.texture_vertices+i)).u = 1-(*(mdp->texture_vertices+i)).u;
			(*(md.texture_vertices+i)).v = 1-(*(mdp->texture_vertices+i)).v;
		}
		for(i = 0; i < md.n_triangles; i++){
			printf("Triangles:%d\n", i);
			for(j = 0; j < 3; j++){
				(*(md.triangles+i)).points[j] = (*(mdp->triangles+i)).points[j];
			}
		}
		(*rmd) = md;
		obj1 = scene->rolist.next;
		printf("Into second loop.\n");
		while(obj1 != NULL){
			if(obj1->model == mdp){
				obj1->model = rmd;
			}
			obj1 = obj1->next;
		}
		printf("Out of second loop.\n");
	}
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

void draw_scene(Scene* scene)
{
    set_lighting();
    draw_origin();
    draw_bounds(&(scene->olist));
	draw_bounds(&(scene->rolist));
	draw_man(&(scene->man));
}

void draw_man(Man* man)
{
	Object* obj;
	int i;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(man->pos.x,man->pos.y,man->pos.z);
	glRotatef(man->rot.x, 1.0, 0, 0);
	glRotatef(man->rot.y, 0, 1.0, 0);
	glRotatef(man->rot.z, 0, 0, 1.0);
	for(i = 0; i < 6; i++){
		switch(i){
			case 0: obj = &man->leg1; break;
			case 1: obj = &man->leg2; break;
			case 2: obj = &man->body; break;
			case 3: obj = &man->head; break;
			case 4: obj = &man->arm1; break;
			case 5: obj = &man->arm2; break;
		}
		glBindTexture(GL_TEXTURE_2D, obj->texture_id);
		glPushMatrix();
		glTranslatef(obj->pos.x,obj->pos.y,obj->pos.z);
		glRotatef(obj->rot.x, 1.0, 0, 0);
		glRotatef(obj->rot.y, 0, 1.0, 0);
		glRotatef(obj->rot.z, 0, 0, 1.0);
		draw_model(obj->model);
		glPopMatrix();
	}
	glPopMatrix();
}

void draw_bounds(const Object* olist){
	Object *obj = olist->next;
	glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
	while(obj != NULL){
		glBindTexture(GL_TEXTURE_2D, obj->texture_id);
		set_material(&(obj->material));
		glPushMatrix();
		glTranslatef(obj->pos.x,obj->pos.y,obj->pos.z);
		glRotatef(obj->rot.x, 1.0, 0, 0);
		glRotatef(obj->rot.y, 0, 1.0, 0);
		glRotatef(obj->rot.z, 0, 0, 1.0);
		draw_model(obj->model);
		glPopMatrix();
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