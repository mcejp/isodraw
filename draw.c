#include "cmd.h"
#include "draw.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __WATCOMC__
#define __far
#endif

int w, h;
uint8_t __far* canvas = NULL;

int backface = 1;
short scale = 5, scale2 = 10;

#define PROJECT() sx = w / 2 + (wx - wy) * scale2; sy = h / 2 + (wx + wy) * scale; sz = 0;
#define PROJECT_CUR() sx = w / 2 + (cx - cy) * scale2; sy = h / 2 + (cx + cy) * scale; sz = 0;

/*
 *  SX = WX - WY
 *  SY = (WX + WY) / 2
 *
 *  WX = SY + SX / 2
 *  WY = SY - SX / 2
 */

static uint8_t get_pixel(int x, int y) {
	if (x >= 0 && y >= 0 && x < w && y < h)
		return canvas[y * w + x];
	else
		return 0;
}

static void put_pixel(int x, int y) {
	if (x >= 0 && y >= 0 && x < w && y < h)
		canvas[y * w + x] = 0xff;
}

void lineseghor(int x, int y, int dx, int dy, int len) {
	while (len > 1) {
		put_pixel(x, y);
		len--;
		x += dx;
		put_pixel(x, y);
		x += dx;
		y += dy;
		len--;
	}
}

/*void vlinedown(int x, int y, int h) {
	while (h--) {
		put_pixel(x, y++);
	}
}*/

void vlineup(int x, int y, int h) {
	while (h--) {
		put_pixel(x, --y);
	}
}

int draw_floor() {
	/* world xyz, xyz size, screen xyz */
	short dir, wx, wy, wz, xs, ys, sx, sy, sz;

	dir = parm[1].val.s;

	if (!backface && (dir == WALL_F))
		return 0;

	wx = parm[2].val.s;
	wy = parm[3].val.s;
	wz = parm[4].val.s;

	xs = scale2 * parm[5].val.s;
	ys = scale2 * parm[6].val.s;

	sx = w / 2 + (wx - wy) * scale2;
	sy = h / 2 + (wx + wy - 2 * wz) * scale;
	sz = wy;

	switch (dir) {
		case WALL_C:
		case WALL_F:
			lineseghor(sx + 1, sy + 1, 1, 1, xs);
			lineseghor(sx, sy, -1, 1, ys);

			lineseghor(sx + xs - ys, sy + (xs + ys) / 2, 1, -1, ys);
			lineseghor(sx + xs - ys - 1, sy + (xs + ys) / 2 - 1, -1, -1, xs);
			return 0;
	}

	return 0;
}

int draw_wall() {
	/* world xyz, xyz size, screen xyz */
	short dir, wx, wy, wz, len, height, sx, sy, sz;

	dir = parm[1].val.s;

	if (!backface && (dir == WALL_N || dir == WALL_W))
		return 0;

	wx = parm[2].val.s;
	wy = parm[3].val.s;
	wz = parm[4].val.s;

	len = scale2 * parm[5].val.s;
	height = scale2 * parm[6].val.s;

	sx = w / 2 + (wx - wy) * scale2;
	sy = h / 2 + (wx + wy - 2 * wz) * scale;
	sz = wy;

	switch (dir) {
		case WALL_N: lineseghor(sx, sy, -1, -1, len); lineseghor(sx, sy - height, -1, -1, len); break;
		case WALL_E: lineseghor(sx, sy,  1, -1, len); lineseghor(sx, sy - height,  1, -1, len); break;
		case WALL_S: lineseghor(sx, sy,  1,  1, len); lineseghor(sx, sy - height,  1,  1, len); break;
		case WALL_W: lineseghor(sx, sy, -1,  1, len); lineseghor(sx, sy - height, -1,  1, len); break;
	}

	vlineup(sx, sy, height);

	if (dir == WALL_N)
		vlineup(sx - len, sy - len / 2, height);

	if (dir == WALL_E)
		vlineup(sx + len, sy - len / 2 + 1, height);

	return 0;
}

int exec_backface() {
	backface = parm[1].val.t;
	return 0;
}

int exec_canvas() {
	free(canvas);
	w = parm[1].val.s;
	h = parm[2].val.s;
	canvas = malloc(w * h);

	if (!canvas) {
		perror("malloc");
		abort();
	}

	memset(canvas, 0, w * h);
	return 0;
}

int exec_scale() {
	scale = parm[1].val.s;
	scale2 = scale * 2;
	return 0;
}

int exec_writepgm() {
	int x, y;

	FILE* out = fopen(parm[1].begin, "wt");
	/* FIXME: error handling */
	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n", w, h);
	fprintf(out, "255\n");
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++)
			fprintf(out, "%3d ", get_pixel(x, y));
		fprintf(out, "\n");
	}
	fclose(out);

	return 0;
}
