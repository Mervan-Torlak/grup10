#ifndef Fonksiyonlar_h
#define Fonksiyonlar_h

#define YEL   "\x1B[33m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

static char* bulunanDizin;
extern char** environ;

int run(char **command, int backGround);
int commandBol(char * command[]);
void waitCommand();
int cDirectory(char **command);
int exit1(char **command);
int showpid(char **command);

#endif
