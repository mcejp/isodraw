#include "cmd.h"
#include "draw.h"
#include "geom.h"
#include "meta.h"

#include <string.h>

cmd_t cmdlist[MAXCMD] = {
	{"backface", "t", "enable drawing of backfaces (default ON)", exec_backface},
	{"box", "sss", "draw a box", exec_box},
	{"canvas", "ss", "initialize canvas", exec_canvas},
	{"cursor", "sss", "set cursor position", exec_cursor},
	{"help", "", "list available commands", exec_help},
	{"scale", "s", "set draw scale", exec_scale},
	{"which", "*", "help for command", exec_which},
	{"writepgm", "*", "save a PGM file", exec_writepgm},
};
int ncmd = 8;

cmd_t* which(const char* name) {
	int i;

	for (i = 0; i < ncmd; i++)
		if (strcmp(cmdlist[i].canon, name) == 0)
			return &cmdlist[i];

	return NULL;
}
