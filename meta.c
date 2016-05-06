#include "cmd.h"

#include <stdio.h>

int exec_help() {
	int i;
	for (i = 0; i < ncmd; i++)
		fprintf(stderr, "%s\t", cmdlist[i].canon);
	fprintf(stderr, "\n");
	return 0;
}

int exec_which() {
	cmd_t* cmd;

	cmd = which(parm[1].begin);

	if (!cmd)
		fprintf(stderr, "not found\n");
	else {
		fprintf(stderr, "CANONICAL:\t%s\n", cmd->canon);
		fprintf(stderr, "PARAMETERS:\t%s\n", cmd->arg);
		fprintf(stderr, "DESCRIPTION:\t%s\n", cmd->help);
	}

	return 0;
}
