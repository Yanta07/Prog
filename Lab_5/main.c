#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MAX_PATH 260
#define MAX_USERNAME 15

int check(char delim, char *paths, char *reject);
void input(char *user, char *dir, char *paths);
void process(char *paths, char *user, char *delim, char *dir);
void output(char *paths);

int main()
{
    char *user = malloc(MAX_USERNAME * sizeof(char));
    char *dir = malloc(MAX_PATH * sizeof(char));
    char delim = '+';
    char *paths = malloc(MAX_PATH * 4 * sizeof(char));
    char reject[10] = {'\\', ':', '*', '?', '\"', '<', '>', '|'};
    input(user, dir, paths);
    if (check(delim, paths, reject))
        process(paths, user, &delim, dir);
    return 0;
}