#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>     //open,creat
#include <sys/types.h> //open
#include <sys/stat.h>
#include <errno.h> //perror, errno
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void handler(int signumber)
{
    printf("%i-es azonositoju kisbusz keszen all az indulasra\n", signumber);
}

struct uzenet
{
    long mtype;
    char mtext[1024];
};

int kuld(int uzenetsor, struct uzenet uz)
{
    int status;

    status = msgsnd(uzenetsor, &uz, strlen(uz.mtext) + 1, 0);

    if (status < 0)
        perror("msgsnd");
    return 0;
}

int fogad(int uzenetsor)
{
    struct uzenet uz;
    int status;

    status = msgrcv(uzenetsor, &uz, 1024, 5, 0);

    if (status < 0)
        perror("msgsnd");
    else
        printf("Szoleszet fogadta egy kisbusz uzenetet: %s\n", uz.mtext);
    return 0;
}

void add(char string[])
{
    char *jelentkezes[6];
    char *t = strtok(string, " ");
    int inpind = 0;

    while (t != NULL)
    {
        jelentkezes[inpind] = t;
        t = strtok(NULL, " ");
        inpind++;
    }

    if (!(inpind < 7))
    {
        perror("Tul sok input\n");
        exit(1);
    }

    // newline-ok leszedese
    for (int i = 0; i < inpind; i++)
    {
        for (int j = 0; j < strlen(jelentkezes[i]); j++)
        {
            if (jelentkezes[i][j] == '\n')
                jelentkezes[i][j] = '\0';
        }
    }

    // file beolvas
    FILE *fp;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    char **napok = malloc(100 * sizeof(char *));

    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        perror("File opening error\n");
        exit(1);
    }

    int y = 0;
    while ((getline(&line, &bufsize, fp)) != -1)
    {
        napok[y] = malloc(strlen(line) + 1);
        strcpy(napok[y], line);
        y++;
    }

    // felbontja a file sorait nevekre
    char *hetfo[10], *kedd[10], *szerda[10], *csut[10], *pentek[10];
    int ind;
    char *token;
    for (int g = 0; g < 5; g++)
    {
        if (g == 0)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                hetfo[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 1)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                kedd[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 2)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                szerda[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 3)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                csut[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 4)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                pentek[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
    }

    // megvizsgalja, hogy a jelentkezes napjai barmelyike tele van-e
    bool vanureshely = false;
    char *unders[1] = {"_"};
    char *h[1] = {"hetfo"};
    char *k[1] = {"kedd"};
    char *s[1] = {"szerda"};
    char *c[1] = {"csutortok"};
    char *p[1] = {"pentek"};

    for (int i = 0; i < strlen(h[0]); i++)
    {
        if (h[0][i] == '\n')
            printf("newline\n");
    }

    for (int i = 1; i < inpind; i++) // jelentkezes napjain lepked
    {
        if (strcmp(jelentkezes[i], h[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(hetfo[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    hetfo[j] = jelentkezes[0];
                    break;
                }
            }
        }
        if (strcmp(jelentkezes[i], k[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(kedd[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    kedd[j] = jelentkezes[0];
                    break;
                }
            }
        }
        else if (strcmp(jelentkezes[i], s[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(szerda[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    szerda[j] = jelentkezes[0];
                    break;
                }
            }
        }
        else if (strcmp(jelentkezes[i], c[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(csut[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    csut[j] = jelentkezes[0];
                    break;
                }
            }
        }
        else if (strcmp(jelentkezes[i], p[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(pentek[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    pentek[j] = jelentkezes[0];
                    break;
                }
            }
        }
    }
    if (vanureshely == false)
    {
        printf("Betelt napra nem lehet jelentkezni\n");
    }
    fclose(fp);

    // file-ba iras
    fp = fopen("data.txt", "w");

    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", hetfo[0], hetfo[1], hetfo[2], hetfo[3], hetfo[4], hetfo[5], hetfo[6], hetfo[7], hetfo[8], hetfo[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", kedd[0], kedd[1], kedd[2], kedd[3], kedd[4], kedd[5], kedd[6], kedd[7], kedd[8], kedd[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", szerda[0], szerda[1], szerda[2], szerda[3], szerda[4], szerda[5], szerda[6], szerda[7], szerda[8], szerda[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", csut[0], csut[1], csut[2], csut[3], csut[4], csut[5], csut[6], csut[7], csut[8], csut[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", pentek[0], pentek[1], pentek[2], pentek[3], pentek[4], csut[5], csut[6], csut[7], csut[8], csut[9]);

    fclose(fp);
}

void daily()
{
    printf("Mely nap listaja:\n");

    char *string = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    lineSize = getline(&string, &len, stdin);

    // newline leszedese
    for (int j = 0; j < strlen(string); j++)
    {
        if (string[j] == '\n')
            string[j] = '\0';
    }

    FILE *fp;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    char **napok = malloc(100 * sizeof(char *));

    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        perror("File opening error\n");
        exit(1);
    }

    int ind = 0;
    while ((getline(&line, &bufsize, fp)) != -1)
    {
        napok[ind] = malloc(strlen(line) + 1);
        strcpy(napok[ind], line);
        ind++;
    }

    if (strcmp(string, "hetfo") == 0)
        printf("%s\n", napok[0]);
    else if (strcmp(string, "kedd") == 0)
        printf("%s\n", napok[1]);
    else if (strcmp(string, "szerda") == 0)
        printf("%s\n", napok[2]);
    else if (strcmp(string, "csutortok") == 0)
        printf("%s\n", napok[3]);
    else if (strcmp(string, "pentek") == 0)
        printf("%s\n", napok[4]);
    else
    {
        perror("Nem jol megadott nap\n");
        exit(1);
    }

    fclose(fp);
    free(line);
}

void all()
{
    printf("A munkasok beosztasa:\n");

    FILE *fp;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    char **napok = malloc(100 * sizeof(char *));

    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        perror("File opening error\n");
        exit(1);
    }

    int ind = 0;
    while ((getline(&line, &bufsize, fp)) != -1)
    {
        napok[ind] = malloc(strlen(line) + 1);
        strcpy(napok[ind], line);
        ind++;
    }

    for (int i = 0; i < ind; i++)
    {
        printf("%s", napok[i]);
    }
    printf("\n");

    fclose(fp);
    free(line);
}

void delete(char nev[])
{
    // file beolvas
    FILE *fp;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    char **napok = malloc(100 * sizeof(char *));

    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        perror("File opening error\n");
        exit(1);
    }

    int y = 0;
    while ((getline(&line, &bufsize, fp)) != -1)
    {
        napok[y] = malloc(strlen(line) + 1);
        strcpy(napok[y], line);
        y++;
    }
    // felbontja a file sorait nevekre
    char *hetfo[10], *kedd[10], *szerda[10], *csut[10], *pentek[10];
    int ind;
    char *token;
    for (int g = 0; g < 5; g++)
    {
        if (g == 0)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                hetfo[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 1)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                kedd[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 2)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                szerda[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 3)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                csut[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 4)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                pentek[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
    }

    // megvizsgalja, hol van a megadott nev es atirja _-ra
    for (int i = 0; i < 10; i++)
    {
        // printf("for %i\n", i);
        if (strcmp(hetfo[i], nev) == 0)
            strcpy(hetfo[i], "_");
        if (strcmp(kedd[i], nev) == 0)
            strcpy(kedd[i], "_");
        if (strcmp(szerda[i], nev) == 0)
            strcpy(szerda[i], "_");
        if (strcmp(csut[i], nev) == 0)
            strcpy(csut[i], "_");
        if (strcmp(pentek[i], nev) == 0)
            strcpy(pentek[i], "_");
    }
    fclose(fp);

    // file-ba iras
    fp = fopen("data.txt", "w");

    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", hetfo[0], hetfo[1], hetfo[2], hetfo[3], hetfo[4], hetfo[5], hetfo[6], hetfo[7], hetfo[8], hetfo[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", kedd[0], kedd[1], kedd[2], kedd[3], kedd[4], kedd[5], kedd[6], kedd[7], kedd[8], kedd[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", szerda[0], szerda[1], szerda[2], szerda[3], szerda[4], szerda[5], szerda[6], szerda[7], szerda[8], szerda[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", csut[0], csut[1], csut[2], csut[3], csut[4], csut[5], csut[6], csut[7], csut[8], csut[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", pentek[0], pentek[1], pentek[2], pentek[3], pentek[4], csut[5], csut[6], csut[7], csut[8], csut[9]);

    fclose(fp);
}

void modifyname()
{
    // felhasznalotol beolvas
    char nev[100];
    printf("Kit kell modositani:\n");
    fgets(nev, sizeof nev, stdin);

    char nev2[100];
    printf("Uj nev:\n");
    fgets(nev2, sizeof nev2, stdin);

    // newline leszedese
    for (int i = 0; i < strlen(nev); i++)
    {
        if (nev[i] == '\n')
            nev[i] = '\0';
    }
    for (int i = 0; i < strlen(nev2); i++)
    {
        if (nev2[i] == '\n')
            nev2[i] = '\0';
    }

    // file beolvas
    FILE *fp;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    char **napok = malloc(100 * sizeof(char *));

    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        perror("File opening error\n");
        exit(1);
    }

    int y = 0;
    while ((getline(&line, &bufsize, fp)) != -1)
    {
        napok[y] = malloc(strlen(line) + 1);
        strcpy(napok[y], line);
        y++;
    }
    // felbontja a file sorait nevekre
    char *hetfo[10], *kedd[10], *szerda[10], *csut[10], *pentek[10];
    int ind;
    char *token;
    for (int g = 0; g < 5; g++)
    {
        if (g == 0)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                hetfo[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 1)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                kedd[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 2)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                szerda[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 3)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                csut[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 4)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                pentek[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
    }

    // newline-ok leszedese
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < strlen(hetfo[i]); j++)
        {
            if (hetfo[i][j] == '\n')
                hetfo[i][j] = '\0';
        }
        for (int j = 0; j < strlen(kedd[i]); j++)
        {
            if (kedd[i][j] == '\n')
                kedd[i][j] = '\0';
        }
        for (int j = 0; j < strlen(szerda[i]); j++)
        {
            if (szerda[i][j] == '\n')
                szerda[i][j] = '\0';
        }
        for (int j = 0; j < strlen(csut[i]); j++)
        {
            if (csut[i][j] == '\n')
                csut[i][j] = '\0';
        }
        for (int j = 0; j < strlen(pentek[i]); j++)
        {
            if (pentek[i][j] == '\n')
                pentek[i][j] = '\0';
        }
    }

    char *h[10], *k[10], *s[10], *c[10], *p[10];
    // megvizsgalja, hol van a megadott nev es atirja masikra
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(hetfo[i], nev) == 0)
            h[i] = nev2;
        else
            h[i] = hetfo[i];
    }

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(kedd[i], nev) == 0)
            k[i] = nev2;
        else
            k[i] = kedd[i];
    }

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(szerda[i], nev) == 0)
            s[i] = nev2;
        else
            s[i] = szerda[i];
    }

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(csut[i], nev) == 0)
            c[i] = nev2;
        else
            c[i] = csut[i];
    }

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(pentek[i], nev) == 0)
            p[i] = nev2;
        else
            p[i] = pentek[i];
    }
    fclose(fp);
    fp = fopen("data.txt", "w");

    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s\n", h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7], h[8], h[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s\n", k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s\n", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);

    fclose(fp);
}

void modifyday(char string[])
{
    char *jelentkezes[6];
    char *t = strtok(string, " ");
    int inpind = 0;

    while (t != NULL)
    {
        jelentkezes[inpind] = t;
        t = strtok(NULL, " ");
        inpind++;
    }

    if (!(inpind < 7))
    {
        perror("Tul sok input\n");
        exit(1);
    }

    // newline-ok leszedese
    for (int i = 0; i < inpind; i++)
    {
        for (int j = 0; j < strlen(jelentkezes[i]); j++)
        {
            if (jelentkezes[i][j] == '\n')
                jelentkezes[i][j] = '\0';
        }
    }

    delete (jelentkezes[0]);
    // add(string);
    FILE *fp;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read;

    char **napok = malloc(100 * sizeof(char *));

    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        perror("File opening error\n");
        exit(1);
    }

    int y = 0;
    while ((getline(&line, &bufsize, fp)) != -1)
    {
        napok[y] = malloc(strlen(line) + 1);
        strcpy(napok[y], line);
        y++;
    }

    // felbontja a file sorait nevekre
    char *hetfo[10], *kedd[10], *szerda[10], *csut[10], *pentek[10];
    int ind;
    char *token;
    for (int g = 0; g < 5; g++)
    {
        if (g == 0)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                hetfo[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 1)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                kedd[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 2)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                szerda[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 3)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                csut[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
        if (g == 4)
        {
            ind = 0;
            token = strtok(napok[g], " ");
            while (token != NULL)
            {
                pentek[ind] = token;
                token = strtok(NULL, " ");
                ind++;
            }
        }
    }

    // megvizsgalja, hogy a jelentkezes napjai barmelyike tele van-e
    bool vanureshely = false;
    char *unders[1] = {"_"};
    char *h[1] = {"hetfo"};
    char *k[1] = {"kedd"};
    char *s[1] = {"szerda"};
    char *c[1] = {"csutortok"};
    char *p[1] = {"pentek"};

    for (int i = 0; i < strlen(h[0]); i++)
    {
        if (h[0][i] == '\n')
            printf("newline\n");
    }

    for (int i = 1; i < inpind; i++) // jelentkezes napjain lepked
    {
        if (strcmp(jelentkezes[i], h[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(hetfo[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    hetfo[j] = jelentkezes[0];
                    break;
                }
            }
        }
        if (strcmp(jelentkezes[i], k[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(kedd[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    kedd[j] = jelentkezes[0];
                    break;
                }
            }
        }
        else if (strcmp(jelentkezes[i], s[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(szerda[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    szerda[j] = jelentkezes[0];
                    break;
                }
            }
        }
        else if (strcmp(jelentkezes[i], c[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(csut[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    csut[j] = jelentkezes[0];
                    break;
                }
            }
        }
        else if (strcmp(jelentkezes[i], p[0]) == 0)
        {
            for (int j = 0; j < 10; j++)
            {

                if (strcmp(pentek[j], unders[0]) == 0)
                {
                    vanureshely = true;
                    pentek[j] = jelentkezes[0];
                    break;
                }
            }
        }
    }
    if (vanureshely == false)
    {
        printf("Betelt napra nem lehet jelentkezni\n");
    }
    fclose(fp);

    // file-ba iras
    fp = fopen("data.txt", "w");

    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", hetfo[0], hetfo[1], hetfo[2], hetfo[3], hetfo[4], hetfo[5], hetfo[6], hetfo[7], hetfo[8], hetfo[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", kedd[0], kedd[1], kedd[2], kedd[3], kedd[4], kedd[5], kedd[6], kedd[7], kedd[8], kedd[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", szerda[0], szerda[1], szerda[2], szerda[3], szerda[4], szerda[5], szerda[6], szerda[7], szerda[8], szerda[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", csut[0], csut[1], csut[2], csut[3], csut[4], csut[5], csut[6], csut[7], csut[8], csut[9]);
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s", pentek[0], pentek[1], pentek[2], pentek[3], pentek[4], csut[5], csut[6], csut[7], csut[8], csut[9]);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    const char *tmp = "_";
    char *ret;
    char command[1];

    printf("Parancsok: \n");
    printf("1 - uj jelentkezes\n");
    printf("2 - egy munkas torlese\n");
    printf("3 - egy nap munkaslistaja\n");
    printf("4 - teljes lista\n");
    printf("5 - modositas\n");
    printf("6 - kisbusz(ok) inditasa\n");
    printf("Parancs: ");

    scanf("%c", &command[0]);
    getchar();

    if (command[0] == '1')
    {
        // nevet beolvas
        char string[100];

        printf("Nev nap1 nap2 ...:\n");
        fgets(string, sizeof string, stdin);

        add(string);
    }
    else if (command[0] == '2')
    {
        char nev[100];
        printf("Kit kell torolni:\n");
        fgets(nev, sizeof nev, stdin);

        // newline leszedese
        for (int i = 0; i < strlen(nev); i++)
        {
            if (nev[i] == '\n')
                nev[i] = '\0';
        }
        delete (nev);
    }
    else if (command[0] == '3')
    {
        daily();
    }
    else if (command[0] == '4')
    {
        all();
    }
    else if (command[0] == '5')
    {
        // modifyname();
        printf("1 - letezo munkas atnevezese\n");
        printf("2 - munkas attetele masik napra\n");
        printf("Parancs: ");
        scanf("%c", &command[0]);
        getchar();
        if (command[0] == '1')
        {
            modifyname();
        }
        else if (command[0] == '2')
        {
            char string[100];

            printf("Nev nap1 nap2 ...:\n");
            fgets(string, sizeof string, stdin);

            modifyday(string);
        }
        else
        {
            printf("Ismeretlen parancs");
            return -1;
        }
    }
    else if (command[0] == '6')
    {
        printf("Mely napra kell kivinni munkast:\n");

        char *string = NULL;
        size_t len = 0;
        ssize_t lineSize = 0;
        lineSize = getline(&string, &len, stdin);

        // newline leszedese
        for (int j = 0; j < strlen(string); j++)
        {
            if (string[j] == '\n')
                string[j] = '\0';
        }

        // file beolvas
        FILE *fp;
        char *line = NULL;
        size_t bufsize = 0;
        // ssize_t read;

        char **napok = malloc(100 * sizeof(char *));

        fp = fopen("data.txt", "r");
        if (fp == NULL)
        {
            perror("File opening error\n");
            exit(1);
        }

        int y = 0;
        while ((getline(&line, &bufsize, fp)) != -1)
        {
            napok[y] = malloc(strlen(line) + 1);
            strcpy(napok[y], line);
            y++;
        }
        // felbontja a file sorait nevekre
        char *hetfo[10], *kedd[10], *szerda[10], *csut[10], *pentek[10];
        int ind;
        char *token;
        for (int g = 0; g < 5; g++)
        {
            if (g == 0)
            {
                ind = 0;
                token = strtok(napok[g], " ");
                while (token != NULL)
                {
                    hetfo[ind] = token;
                    token = strtok(NULL, " ");
                    ind++;
                }
            }
            if (g == 1)
            {
                ind = 0;
                token = strtok(napok[g], " ");
                while (token != NULL)
                {
                    kedd[ind] = token;
                    token = strtok(NULL, " ");
                    ind++;
                }
            }
            if (g == 2)
            {
                ind = 0;
                token = strtok(napok[g], " ");
                while (token != NULL)
                {
                    szerda[ind] = token;
                    token = strtok(NULL, " ");
                    ind++;
                }
            }
            if (g == 3)
            {
                ind = 0;
                token = strtok(napok[g], " ");
                while (token != NULL)
                {
                    csut[ind] = token;
                    token = strtok(NULL, " ");
                    ind++;
                }
            }
            if (g == 4)
            {
                ind = 0;
                token = strtok(napok[g], " ");
                while (token != NULL)
                {
                    pentek[ind] = token;
                    token = strtok(NULL, " ");
                    ind++;
                }
            }
        }
        fclose(fp);
        free(line);
        // newline leszedese
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < strlen(hetfo[i]); j++)
            {
                if (hetfo[i][j] == '\n')
                    hetfo[i][j] = '\0';
            }
        }

        char *h[10], *k[10], *s[10], *c[10], *p[10];
        int hw = 10, kw = 10, sw = 10, cw = 10, pw = 10, hi = 0, ki = 0, si = 0, ci = 0, pi = 0;
        for (int i = 0; i < 10; i++)
        {
            ret = strstr(hetfo[i], "_");
            if (ret) // talalt
                hw--;
            else
            {
                h[hi] = hetfo[i];
                hi++;
            }

            ret = strstr(kedd[i], "_");
            if (ret) // talalt
                kw--;
            else
            {
                k[ki] = kedd[i];
                ki++;
            }

            ret = strstr(szerda[i], "_");
            if (ret) // talalt
                sw--;
            else
            {
                s[si] = szerda[i];
                si++;
            }

            ret = strstr(csut[i], "_");
            if (ret) // talalt
                cw--;
            else
            {
                c[ci] = csut[i];
                ci++;
            }

            ret = strstr(pentek[i], "_");
            if (ret) // talalt
                pw--;
            else
            {
                p[pi] = pentek[i];
                pi++;
            }
        }

        // kivalogatja a neveket
        int workers;
        char munkasok[255], extra[255];
        if (strcmp(string, "hetfo") == 0)
        {
            workers = hw;
            int x, y;
            if (hw < 6)
            {
                x = 0;
                for (int i = 0; i < hw; i++)
                {
                    for (int j = 0; j < strlen(h[i]); j++)
                    {
                        munkasok[x] = h[i][j];
                        x++;
                    }
                    munkasok[x] = ' ';
                    x++;
                }
            }
            else
            {
                x = 0;
                y = 0;
                for (int i = 0; i < hw; i++)
                {
                    if (i < 5)
                    {
                        for (int j = 0; j < strlen(h[i]); j++)
                        {
                            munkasok[x] = h[i][j];
                            x++;
                        }
                        munkasok[x] = ' ';
                        x++;
                    }
                    else
                    {
                        for (int j = 0; j < strlen(h[i]); j++)
                        {
                            extra[y] = h[i][j];
                            y++;
                        }
                        extra[y] = ' ';
                        y++;
                    }
                }
            }
        }
        if (strcmp(string, "kedd") == 0)
        {
            workers = kw;
            int x, y;
            if (kw < 6)
            {
                x = 0;
                for (int i = 0; i < kw; i++)
                {
                    for (int j = 0; j < strlen(k[i]); j++)
                    {
                        munkasok[x] = k[i][j];
                        x++;
                    }
                    munkasok[x] = ' ';
                    x++;
                }
            }
            else
            {
                x = 0;
                y = 0;
                for (int i = 0; i < kw; i++)
                {
                    if (i < 5)
                    {
                        for (int j = 0; j < strlen(k[i]); j++)
                        {
                            munkasok[x] = k[i][j];
                            x++;
                        }
                        munkasok[x] = ' ';
                        x++;
                    }
                    else
                    {
                        for (int j = 0; j < strlen(k[i]); j++)
                        {
                            extra[y] = k[i][j];
                            y++;
                        }
                        extra[y] = ' ';
                        y++;
                    }
                }
            }
        }
        if (strcmp(string, "szerda") == 0)
        {
            workers = sw;
            int x, y;
            if (sw < 6)
            {
                x = 0;
                for (int i = 0; i < sw; i++)
                {
                    for (int j = 0; j < strlen(s[i]); j++)
                    {
                        munkasok[x] = s[i][j];
                        x++;
                    }
                    munkasok[x] = ' ';
                    x++;
                }
            }
            else
            {
                x = 0;
                y = 0;
                for (int i = 0; i < sw; i++)
                {
                    if (i < 5)
                    {
                        for (int j = 0; j < strlen(s[i]); j++)
                        {
                            munkasok[x] = s[i][j];
                            x++;
                        }
                        munkasok[x] = ' ';
                        x++;
                    }
                    else
                    {
                        for (int j = 0; j < strlen(s[i]); j++)
                        {
                            extra[y] = s[i][j];
                            y++;
                        }
                        extra[y] = ' ';
                        y++;
                    }
                }
            }
        }
        if (strcmp(string, "csutortok") == 0)
        {
            workers = cw;
            int x, y;
            if (cw < 6)
            {
                x = 0;
                for (int i = 0; i < cw; i++)
                {
                    for (int j = 0; j < strlen(c[i]); j++)
                    {
                        munkasok[x] = c[i][j];
                        x++;
                    }
                    munkasok[x] = ' ';
                    x++;
                }
            }
            else
            {
                x = 0;
                y = 0;
                for (int i = 0; i < cw; i++)
                {
                    if (i < 5)
                    {
                        for (int j = 0; j < strlen(c[i]); j++)
                        {
                            munkasok[x] = c[i][j];
                            x++;
                        }
                        munkasok[x] = ' ';
                        x++;
                    }
                    else
                    {
                        for (int j = 0; j < strlen(c[i]); j++)
                        {
                            extra[y] = c[i][j];
                            y++;
                        }
                        extra[y] = ' ';
                        y++;
                    }
                }
            }
        }
        if (strcmp(string, "pentek") == 0)
        {
            workers = pw;
            int x, y;
            if (pw < 6)
            {
                x = 0;
                for (int i = 0; i < pw; i++)
                {
                    for (int j = 0; j < strlen(p[i]); j++)
                    {
                        munkasok[x] = p[i][j];
                        x++;
                    }
                    munkasok[x] = ' ';
                    x++;
                }
            }
            else
            {
                x = 0;
                y = 0;
                for (int i = 0; i < pw; i++)
                {
                    if (i < 5)
                    {
                        for (int j = 0; j < strlen(p[i]); j++)
                        {
                            munkasok[x] = p[i][j];
                            x++;
                        }
                        munkasok[x] = ' ';
                        x++;
                    }
                    else
                    {
                        for (int j = 0; j < strlen(p[i]); j++)
                        {
                            extra[y] = p[i][j];
                            y++;
                        }
                        extra[y] = ' ';
                        y++;
                    }
                }
            }
        }

        /* for (int i = 0; i < 50; i++)
        {
            printf("extra[%i] = %c\n", i, extra[i]);
        } */
        //printf("\n");
        printf("Munkasok szama: %i\n", workers);
        // egy kisbusz
        if (workers > 0 && workers < 6)
        {
            int uzenetsor, status;
            key_t kulcs;

            kulcs = ftok(argv[0], 1);
            uzenetsor = msgget(kulcs, 0600 | IPC_CREAT);
            if (uzenetsor < 0)
            {
                perror("msgget");
                return 1;
            }

            struct sigaction sigact;
            sigact.sa_handler = handler;
            sigemptyset(&sigact.sa_mask);
            sigact.sa_flags = 0;
            sigaction(SIGUSR1, &sigact, NULL);

            int pipefd[2];
            char sz[255];

            if (pipe(pipefd) == -1)
            {
                perror("Hiba a pipe nyitaskor!");
                exit(EXIT_FAILURE);
            }

            pid_t child = fork();
            if (child == -1)
            {
                perror("Fork hiba");
                exit(EXIT_FAILURE);
            }
            else if (child > 0) // szulo
            {
                sigset_t sigset;
                sigfillset(&sigset);
                sigdelset(&sigset, SIGUSR1);
                sigsuspend(&sigset);

                close(pipefd[0]);
                int l = strlen(munkasok) + 1;
                write(pipefd[1], munkasok, l);
                close(pipefd[1]);
                fflush(NULL);

                wait(&status);
                return fogad(uzenetsor);
            }
            else // gyerek
            {
                printf("3 masodperc mig felkeszul a busz, majd kuldi az azonositojat: %i \n", SIGUSR1);
                sleep(3);
                kill(getppid(), SIGUSR1);
                sleep(3);
                printf("%i-es azonositoju kisbusz olvas\n", SIGUSR1);
                // sleep(3);
                close(pipefd[1]);
                read(pipefd[0], sz, sizeof(sz));
                printf("Szallitando munkasok: %s\n", sz);
                close(pipefd[0]);

                srand(time(NULL));
                int r = rand() % workers;
                char mc = r + '0';
                char m[100];
                sprintf(m, "Beert %c munkas", mc);
                // printf("m: %s\n", m);
                struct uzenet uz;
                uz.mtype = 5;
                for (int i = 0; i < 15; i++)
                {
                    uz.mtext[i] = m[i];
                }
                kuld(uzenetsor, uz);
            }
        } // ket kisbusz
        else if (workers >= 6)
        {
            int uzenetsor1, uzenetsor2, status;
            key_t kulcs1, kulcs2;
            kulcs1 = ftok(argv[0], 1);
            kulcs2 = ftok(argv[0], 2);
            uzenetsor1 = msgget(kulcs1, 0600 | IPC_CREAT);
            if (uzenetsor1 < 0)
            {
                perror("Uzenetsor1 error");
                return 1;
            }
            uzenetsor2 = msgget(kulcs2, 0600 | IPC_CREAT);
            if (uzenetsor2 < 0)
            {
                perror("Uzenetsor2 error");
                return 1;
            }

            struct sigaction sigact;
            sigact.sa_handler = handler;
            sigemptyset(&sigact.sa_mask);
            sigact.sa_flags = 0;
            sigaction(SIGUSR1, &sigact, NULL);
            sigaction(SIGUSR2, &sigact, NULL);

            int pipefd1[2], pipefd2[2];
            char sz1[255], sz2[255];

            if (pipe(pipefd1) == -1)
            {
                perror("Hiba az elso pipe nyitaskor!");
                exit(EXIT_FAILURE);
            }
            if (pipe(pipefd2) == -1)
            {
                perror("Hiba a masodik pipe nyitaskor!");
                exit(EXIT_FAILURE);
            }

            pid_t child1, child2;

            (child1 = fork()) && (child2 = fork());
            if (child1 == -1)
            {
                perror("Child1 fork hiba");
                exit(EXIT_FAILURE);
            }
            if (child2 == -1)
            {
                perror("Child2 fork hiba");
                exit(EXIT_FAILURE);
            }

            if (child1 == 0) // elso kisbusz
            {
                printf("3 masodperc mig felkeszul a busz, majd kuldi az azonositojat: %i \n", SIGUSR1);
                sleep(3);
                kill(getppid(), SIGUSR1);

                sleep(3);
                printf("%i-es azonositoju kisbusz olvas\n", SIGUSR1);
                close(pipefd1[1]);
                read(pipefd1[0], sz1, sizeof(sz1));
                printf("Egyes kisbusz altal szallitando munkasok: %s\n", sz1);
                close(pipefd1[0]);
                struct uzenet uz1 = {5, "Beert 5 munkas\n"};
                kuld(uzenetsor1, uz1);
            }
            else if (child2 == 0) // masodik kisbusz
            {
                int st;
                waitpid(child1, &st, 0);
                printf("3 masodperc mig felkeszul a busz, majd kuldi az azonositojat: %i \n", SIGUSR2);
                sleep(3);
                kill(getppid(), SIGUSR2);

                sleep(3);
                printf("%i-es azonositoju kisbusz olvas\n", SIGUSR2);
                close(pipefd2[1]);
                read(pipefd2[0], sz2, sizeof(sz2));
                printf("Kettes kisbusz altal szallitando munkasok: %s\n", sz2);
                close(pipefd2[0]);
                int e = workers - 5;
                struct uzenet uz2;
                uz2.mtype = 5;
                char mc = e + '0';
                char m[100];
                sprintf(m, "Beert %c munkas", mc);
                for (int i = 0; i < 15; i++)
                {
                    uz2.mtext[i] = m[i];
                }
                kuld(uzenetsor2, uz2);
            }
            else // szoleszet
            {
                sigset_t sigset;
                sigfillset(&sigset);
                sigdelset(&sigset, SIGUSR1);
                sigdelset(&sigset, SIGUSR2);
                sigsuspend(&sigset);

                // elso busznak kuld
                close(pipefd1[0]);
                int l = strlen(munkasok) + 1;
                write(pipefd1[1], munkasok, l);
                close(pipefd1[1]);

                // masodik busznak kuld
                close(pipefd2[0]);
                l = strlen(extra) + 1;
                write(pipefd2[1], extra, l);
                close(pipefd2[1]);

                fflush(NULL);

                waitpid(child1, &status, 0);
                fogad(uzenetsor1);
                waitpid(child2, &status, 0);
                fogad(uzenetsor2);

            }
        }
        else if (workers == 0)
        {
            printf("Erre a napra nincs felvett munkas\n");
        }
    }
    else
    {
        printf("Ismeretlen parancs");
        return -1;
    }

    return 0;
}
/*
alap "szabalyok"
- munkanapok hetfo-pentek
- minden nap max 5 munkas
- ha a jelentkezo megjelolt napjai kozott van teli, akkor arra a napra nem lesz felveve, de a tobbire igen
- feltetelezem hogy ugyanolyan nevu munkasok nem jelentkeznek, es minden munkasnak egyszavas nevet ad meg
- azt is feltetelezem hogy nincs eliras a jelentkezesben a napok neveinel


pelda input
Axel hetfo szerda



data.txt
- adott sor egy napot jelent -> elso sor hetfo, masodik sor kedd stb
- ures poziciok '_'-al vannak jelolve


*/