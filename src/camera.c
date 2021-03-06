#include "camera.h"

#include <GL/glut.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.2;
    camera->position.y = 0.2;
    camera->position.z = WALK_HEIGHT;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    is_help_visible = FALSE;
}

void update_camera(Camera* camera, vec3 newpos){
	camera->position.x = newpos.x;
	camera->position.y = newpos.y;
	camera->position.z = newpos.z;
}

vec3 get_new_camera_pos(Camera* camera, double time)
{
    double angle;
    double side_angle;
	double newx, newy;
	vec3 new;
	
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    new.x = camera->position.x + cos(angle) * camera->speed.y * time;
    new.y = camera->position.y + sin(angle) * camera->speed.y * time;
    new.x += cos(side_angle) * camera->speed.x * time;
    new.y += sin(side_angle) * camera->speed.x * time;
	new.z = WALK_HEIGHT;
	return new;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    if(camera->rotation.x + vertical > 60) camera->rotation.x = 60;
	else if(camera->rotation.x + vertical < -60) camera->rotation.x = -60;
	else camera->rotation.x += vertical;
	camera->rotation.z += horizontal;
    
    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

/*void show_help(Camera camera)
{
	int i, len;
	char text[] = "This is my help text.";
	len = strlen(text);
	glColor3f(0,0,1.0);
	glRasterPos3f(camera.position.x+0.01, camera.position.y+0.01, camera.position.z+0.01);
	for(i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		//printf(" %c",text[i]);
	}
}*/

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.5, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1.5, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1.5, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1.5, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}