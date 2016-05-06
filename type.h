
#define MAXCMD 100
#define MAXPARM 10
#define MAXLINE 80

typedef struct {
	char* canon;
	char* arg;
	char* help;
	int (*exec)();
}
cmd_t;

extern cmd_t cmdlist[MAXCMD];
extern int ncmd;

char line[MAXLINE];
int lineno;
int nparm;
struct {
	char *begin, *end;
	union {
		short svalue;
	};
} parm[MAXPARM];
