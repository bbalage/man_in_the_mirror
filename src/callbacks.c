#include "callbacks.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible) {
        show_texture_preview();
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    rotate_camera(&camera, (mouse_position.x - x)/2, (mouse_position.y - y)/2);
	//scene.player.rot.x = camera.rotation.x;
	scene.player.rot.z = camera.rotation.z;
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        set_camera_speed(&camera, WALK_SPEED);
        break;
    case 's':
        set_camera_speed(&camera, -WALK_SPEED);
        break;
    case 'a':
        set_camera_side_speed(&camera, WALK_SPEED);
        break;
    case 'd':
        set_camera_side_speed(&camera, -WALK_SPEED);
        break;
    case 't':
        if (is_preview_visible) {
            is_preview_visible = FALSE;
        }
        else {
            is_preview_visible = TRUE;
        }
        break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
    vec3 newpos;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

	newpos = get_new_camera_pos(&camera, elapsed_time);
	if(checkhit_wall(newpos, 0.02) && camera.position.x != newpos.x && camera.position.y != newpos.y) {
		update_camera(&camera, newpos);
		//newpos change.
		newpos.x+=0.05;
		newpos.y+=0.05;
		newpos.z = START_Z;
		move_man(&scene.player, newpos, 1);
	}
	if(check_if_man_moves(&scene.man,elapsed_time)){
		newpos = get_new_man_pos(&scene.man);
		if(checkhit_wall(newpos, 0.05)) move_man(&scene.man, newpos, 0);
		else set_new_course(&scene.man, 10);
	}
    glutPostRedisplay();
}
