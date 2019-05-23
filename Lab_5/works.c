#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260

void input(char *user, char *dir, char *paths)
{
    printf("Enter path: \n");
    scanf("%s", paths);
}

int check(char delim, char *paths, char *reject, char *dir)
{
    int pathNum = 1;
    int character = 1;
    int pathlen = 0;

    if (sspn(paths, reject) != slen(paths))
    {
        printf("Присутствуют запрещённые символы %d\n", sspn(paths, reject));
        return 0;
    }

    if (paths[0] != '~' && paths[0] != '/')
    {
        printf("Неверное начало, путь %d: (символ %d \"%c\")\n", pathNum, character,
               paths[0]);
        return 0;
    }

    for (char *bufp = paths; *bufp != '\0'; ++bufp)
    {
        pathlen++;
        if (*bufp == delim)
        {
            pathNum++;
            if (*(bufp + 1) != '/' && *(bufp + 1) != '~')
            {
                printf("Неверное начало, путь %d: (символ %d \"%c\")\n", pathNum,
                       character, *bufp);
                return 0;
            }
            if (pathlen > MAX_PATH)
            {
                printf("Слишком длинный путь %d", pathNum);
                return 0;
            }
            else
            {
                pathlen = 0;
            }
        }

        if (*bufp == '.' && *(bufp + 1) == '/' && *(bufp - 1) != '.' &&
            *(bufp - 1) != '/')
        {
            printf("Неверно задан путь %d: (символ %d \"%с%с%c\")\n", pathNum,
                   character, *(bufp - 1), *bufp, *(bufp + 1));
            return 0;
        }

        if (*bufp == '/' && *(bufp + 1) == '/')
        {
            printf("Неверная конструкция, путь %d: (символ %d \"//\")\n", pathNum, character);
            return 0;
        }

        if (*bufp == '.' && *(bufp - 1) == '/' && *(bufp - 2) == delim)
        {
            printf("Неверная конструкция, путь %d: (символ %d \"%c/.\")\n", delim, pathNum, character);
            return 0;
        }
        character++;
    }

    if (sspn(dir, reject) != slen(dir))
    {
        printf("Присутствуют запрещённые символы в корневой(%d)\n", sspn(paths, reject));
        return 0;
    }

    for (char *bufp = dir; *bufp != '\0'; ++bufp)
    {

        if (*bufp == '.' && *(bufp + 1) == '/' && *(bufp - 1) != '.' &&
            *(bufp - 1) != '/')
        {
            printf("Неверно задан корневой путь");
            return 0;
        }

        if (*bufp == '/' && *(bufp + 1) == '/')
        {
            printf("Неверно задан корневой путь");
            return 0;
        }

        if (*bufp == '.' && *(bufp - 1) == '/' && *(bufp - 2) == delim)
        {
            printf("Неверно задан корневой путь");
            return 0;
        }
    }
    return 1;
}
void process(char *paths, char *user, char *delim, char *dir)
{
	char path[MAX_PATH] = "\0";
	char result[MAX_PATH] = "\0";
    int flag = 1; 
	int i = 1, count = 0;
	while(paths[i-1] != 0) {
		if (paths[i-1] == '.' && paths[i] == '.') {
			int j = i;
			while (flag == 1) {
				if (paths[j] == '/') count++;
				paths[j] = '\0';
				if (count == 2) {
					count = 0;
					break;
				};
				j--;
			}
			i++;
		}
		if (paths[i-1] == '.' && paths[i] == '/') {
			paths[i] = '\0';
			paths[i-1] = '\0';
		}
		i++;
	}
	int j = 0;
	for(i = 0; i < MAX_PATH; i++) {
		if (paths[i] != '\0') {
			result[j] = paths[i];
			j++;
		}
	}
	printf("New path: %s\n", result);
}

