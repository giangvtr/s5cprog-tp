#include "multimedia-object.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static Date createDate(int j, int m, int a)
{
    Date d;
    d.year = a;
    d.day = j;
    d. month = m;
    return d;
}

void fillMO (MultimediaObject * o, char * name, char * path, int day, int month, int year, TypeMultimediaObject type)
{
    /* to be completed*/
    strncpy(o->name, name, sizeof(o->name));
    strncpy(o->path, path, sizeof(o->path));
    o->date = createDate(day, month, year);
    o->type         = type;
}

void changeNameMO(MultimediaObject * o, char * name) {
    strncpy(o->name, name, sizeof(o->name));
}

void displayConsoleOM(MultimediaObject * o) {
    printf("Name : %s\n", o -> name);
    printf("Path : %s\n", o -> path);
    printf("Date : %d/%d/%d\n", o -> date.day, o -> date.month, o -> date.year);
    switch (o -> type) {
        case 0: printf("Type : %s\n", "PHOTO"); break;
        case 1: printf("Type : %s\n", "VIDEO"); break;
        case 2: printf("Type : %s\n", "UNDEFINED"); break;
        default : printf("Type : %s\n", "UNKNOWN"); break;
    }
}

#include "test.h"
/*!
* \brief  Unit testing of the functions provided in the multimedia-object.c file
*/
void test_MO()
{
    char name[] = "jump";
    char path[] = "~/Documents";
    int day = 6;
    int month = 8;
    int year = 2004;
    Date date = createDate(day, month, year);
    TypeMultimediaObject type = VIDEO;
    printf("Tests unitaires du module multimedia-object :\n");
	/* To be completed*/
    MultimediaObject * mo = (MultimediaObject *) malloc(sizeof(MultimediaObject));
    if (mo == NULL) {
        fprintf(stderr, "Error allocating memory for multimedia object\n");
        exit(EXIT_FAILURE);
    }
    fillMO(mo,name,path,day,month,year, type);

    display_test_int("Test createDate()", 6, date.day);
    display_test_int("Test createDate()", 8, date.month);
    display_test_int("Test createDate()", 2004, date.year);

    display_test_string("Test fillMO()", "jump", mo->name);
    display_test_string("Test fillMO()", "~/Documents", mo->path);
    display_test_int("Test fillMO()", 6, mo->date.day);
    display_test_int("Test fillMO()", 8, mo->date.month);
    display_test_int("Test fillMO()", 2004, mo->date.year);
    display_test_string("Test fillMO()", "VIDEO", (char*)mo->type);

}

