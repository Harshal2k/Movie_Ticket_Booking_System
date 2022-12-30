#include <stdio.h>
struct Movie
{
    char name[30];
    int durationMin;
    int screen1;
    int screen2;
    int screen3;
    int price1;
    int price2;
    int price3;
    struct Movie *next;
} *movieHead = NULL;

struct Screen
{
    int screenNum;
    int showID;
    struct Movie *movie;
    int seats[100];
    char date[20];
    char time[20];
    int seatsCount;
    struct Screen *next;
} *screen1 = NULL, *screen2 = NULL, *screen3 = NULL;