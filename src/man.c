#include "man.h"

#include "utils.h"

void init_man(Man* man, vec3 pos, vec3 rot, GLuint tex_id, Model_List* mlist)
{
	man->pos = pos;
	man->rot = rot;
	man->nextrot = rot;
	man->movephase = 0;
	man->since_last_move = 0;
	man->dir = 0;
	man->change_dir = CHANGE_DIR_INIT;
	double desc[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 100.0};
	man->leg1 = *(load_object(desc, &mlist->mlegmodel, tex_id, MAN));//trimmed to 0.045
	desc[1] = 0.01;
	man->leg2 = *(load_object(desc, &mlist->mlegmodel, tex_id, MAN)); //trimmed to 0.045
	desc[1] = 0.02;
	desc[2] = 0.038;
	desc[5] = 90;
	man->body = *(load_object(desc, &mlist->mbodymodel, tex_id, MAN)); //trimmed to 0.04
	desc[1] = 0.002;
	desc[2] = 0.075;
	desc[5] = 0;
	man->head = *(load_object(desc, &mlist->mheadmodel, tex_id, MAN)); //trimmed to 0.015
	desc[1] = -0.004;
	desc[2] = 0.025;
	desc[5] = 90;
	man->arm1 = *(load_object(desc, &mlist->marmmodel, tex_id, MAN)); //trimmed to 0.045
	desc[1] = 0.026;
	man->arm2 = *(load_object(desc, &mlist->marmmodel, tex_id, MAN)); //trimmed to 0.045
}

void move_man(Man* man, vec3 newpos, int player)
{
	Object tmpobj;
	double newz, rotshift, xshift;
	man->pos = newpos;
	if(!player)
		switch(man->dir){
		case 0: man->rot.z=0; break;
		case 1: man->rot.z=90; break;
		case 2: man->rot.z=180; break;
		case 3: man->rot.z=-90; break;
		}
	if(man->movephase != TOP_MOVE_PHASE){
		man->movephase++;
		rotshift = 1.5;
		xshift = 0.001;
		newz = rotshift*man->movephase*0.00027;
		newz = newz < 0 ? newz*-1 : newz;
		man->leg1.pos.x-= xshift;
		man->leg1.pos.z= newz;
		man->leg1.rot.y+= rotshift;
		man->leg2.pos.x+= xshift;
		man->leg2.pos.z= newz;
		man->leg2.rot.y-= rotshift;
		man->pos.z = START_Z-newz/2;
	}
	else{
		man->movephase = man->movephase*-1-1;
		tmpobj = man->leg1;
		man->leg1 = man->leg2;
		man->leg2 = tmpobj;
	}
	if(!player){
		srand(time(0));
		if(rand()%400 < man->change_dir++) set_new_course(man, -1);
	}
}

vec3 get_new_man_pos(Man* man)
{
	vec3 newpos = man->pos;
	switch(man->dir){
		case 0: newpos.x+=MAN_WALK_SPEED; break;
		case 1: newpos.y+=MAN_WALK_SPEED; break;
		case 2: newpos.x-=MAN_WALK_SPEED; break;
		case 3: newpos.y-=MAN_WALK_SPEED; break;
	}
	return newpos;
}

void set_new_course(Man* man, int chmod)
{
	int newdir;
	srand(time(0));
	if(chmod < 0) man->change_dir = CHANGE_DIR_INIT;
	else if(chmod == 0) man->change_dir = 0;
	else {
		man->change_dir-=chmod;
	}
	do{
		newdir = rand()%4;
	}
	while(newdir == man->dir);
	man->dir = newdir;
}

int check_if_man_moves(Man* man, double elapsed_time){
	man->since_last_move+=elapsed_time;
	if(man->since_last_move > MAN_SLOWDOWN) {
		man->since_last_move = 0;
		return 1;
	}
	else return 0;
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
*/