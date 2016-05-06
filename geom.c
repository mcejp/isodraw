#include "cmd.h"
#include "draw.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int cx = 0;
int cy = 0;
int cz = 0;

int draw_floor();
int draw_wall();

int exec_box() {
	short xs,ys,zs, sx,sy,sz;

	xs = parm[1].val.s;
	ys = parm[2].val.s;
	zs = parm[3].val.s;

	SETPARM_6S(WALL_N, cx + xs, cy, cz, xs, zs);
	draw_wall();

	SETPARM_6S(WALL_W, cx, cy, cz, ys, zs);
	draw_wall();

	SETPARM_6S(WALL_S, cx, cy + ys, cz, xs, zs);
	draw_wall();

	SETPARM_6S(WALL_E, cx + xs, cy + ys, cz, ys, zs);
	draw_wall();

	SETPARM_6S(WALL_F, cx, cy, cz, xs, ys);
	draw_floor();

	SETPARM_6S(WALL_C, cx, cy, cz + zs, xs, ys);
	draw_floor();

	return 0;
}

int exec_cursor() {
	cx = parm[1].val.s;
	cy = parm[2].val.s;
	cz = parm[3].val.s;
	return 0;
}
