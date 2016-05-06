#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"

char line[MAXLINE];
int lineno;
int nparm;
struct parm parm[MAXPARM];

int process_cmd() {
	char* sub;
	char* p;
	cmd_t* cmd;
	int i;

	p = line;

	while (*p == ' ')
		p++;

	if (!*p || *p == '#')
		return 0;

	for (nparm = 0; ; nparm++) {
		if (nparm == MAXPARM) {
			fprintf(stderr, "TOO MANY PARAMETERS\n");
			return -1;
		}

		parm[nparm].begin = p;
		sub = strchr(p, '/');

		if (sub) {
			*sub = 0;
			parm[nparm].end = sub;
			p = sub + 1;
		}
		else {
			p = p + strlen(p);
			while (p > parm[nparm].begin && *p < 32) {
				*p = 0;
				p--;
			}
			parm[nparm].end = p;
			break;
		}
	}

	cmd = which(parm[0].begin);

	if (!cmd) {
		fprintf(stderr, "UNDEFINED COMMAND %s\n", parm[0].begin);
		return -1;
	}

	for (i = 0; i < nparm; i++) {
		if (!cmd->arg[i]) {
			fprintf(stderr, "TOO MANY PARAMETERS\n");
			return -1;
		}

		if (cmd->arg[i] == 's')
			parm[1 + i].val.s = atoi(parm[1 + i].begin);
		else if (cmd->arg[i] == 't')
			parm[1 + i].val.t = !strcmp(parm[1 + i].begin, "ON");
	}

	if (cmd->arg[i]) {
		fprintf(stderr, "TOO FEW PARAMETERS\n");
		return -1;
	}

	return cmd->exec();
}

int main(int argc, char** argv) {
	const char* input;
	int i;

	fprintf(stderr, "ISODRAW 1.0\n");

	input = NULL;

	for (i = 1; i < argc; i++) {
		input = argv[i];
	}

	if (input) {
		FILE* input_file;
		input_file = fopen(input, "rt");

		if (!input_file) {
			fprintf(stderr, "%s: %s\n", input, strerror(errno));
			return errno;
		}

		for (lineno = 1; fgets(line, sizeof(line), input_file); lineno++)
			process_cmd();

		fclose(input_file);
	}
	else {
		fprintf(stderr, ">");

		for (lineno = 1; fgets(line, sizeof(line), stdin); lineno++) {
			process_cmd();
			fprintf(stderr, ">");
		}
	}

	return 0;
}
