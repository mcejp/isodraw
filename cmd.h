#ifndef CMD_H
#define CMD_H

#define MAXCMD 100
#define MAXPARM 10
#define MAXLINE 80

#define SETPARM_1S(a) parm[1].val.s = (a)
#define SETPARM_2S(a,b) SETPARM_1S(a); parm[2].val.s = (b)
#define SETPARM_3S(a,b,c) SETPARM_2S(a,b); parm[3].val.s = (c)
#define SETPARM_4S(a,b,c,d) SETPARM_3S(a,b,c); parm[4].val.s = (d)
#define SETPARM_5S(a,b,c,d,e) SETPARM_4S(a,b,c,d); parm[5].val.s = (e)
#define SETPARM_6S(a,b,c,d,e,f) SETPARM_5S(a,b,c,d,e); parm[6].val.s = (f)
#define SETPARM_7S(a,b,c,d,e,f,g) SETPARM_6S(a,b,c,d,e,f); parm[7].val.s = (g)

typedef struct {
	char* canon;
	char* arg;
	char* help;
	int (*exec)();
}
cmd_t;

struct parm {
	char *begin, *end;
	union {
		short s;
		int t;
	} val;
};

extern cmd_t cmdlist[MAXCMD];
extern int ncmd;

extern char line[MAXLINE];
extern int lineno;
extern int nparm;
extern struct parm parm[MAXPARM];

cmd_t* which(const char* name);

#endif
