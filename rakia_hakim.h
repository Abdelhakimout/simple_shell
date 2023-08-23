#ifndef RAKIA_HAKIM_H
#define RAKIA_HAKIM_H

#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* main function */

int execute_command(char **pt);
char *_path(char *cmd);
char *_getenvironment(char *gb_va);

#endif
