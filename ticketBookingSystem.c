#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "colours.c"
#include "structures.c"
#include "utilities.c"
#include "admin.c"
#include "user.c"

/*FUNCTION TO INITIALIZE MENU DRIVEN ADMIN SECTION*/
void admin()
{
    char password[20];
    char movieName[30];
    int dd, mm, yy;
    struct Movie *temp = movieHead;
    printf("\n%s%s Enter Admin Password: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf(" ");
    fgets(password, 20, stdin);
    if (0 != strcmp(password, "pass\n"))
    {
        printf("\n%s%s Invalid Password %s\n\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    int option;
    while (1)
    {
        printf("\n%s%s   WELCOME TO ADMIN SECTION   %s", BLK_BG, WHITE_TXT, RESET);
        printf("\n%s%s 1. Add Movie                 %s", WHT_BG, BLACK_TXT, RESET);
        printf("\n%s%s 2. Remove Movie              %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s 3. Remove Show               %s", WHT_BG, BLACK_TXT, RESET);
        printf("\n%s%s 4. Display Movies            %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s 5. Display Shows             %s", WHT_BG, BLACK_TXT, RESET);
        printf("\n%s%s 6. Exit                      %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s                              %s", BLK_BG, BLACK_TXT, RESET);
        printf("\n\n%s%sEnter your option: %s ", YLW_BG, BLACK_TXT, RESET);
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            clear();
            if (screen1 == NULL || screen2 == NULL || screen3 == NULL)
            {
                addMovie(&movieHead, &screen1, &screen2, &screen3);
            }
            else
            {
                printf("\n%s%s No Screens Available %s\n", RED_BG, WHITE_TXT, RESET);
            }
            break;
        case 2:
            clear();
            removeMovie(&movieHead);
            break;
        case 3:
            clear();
            removeShow();
            break;
        case 4:
            clear();
            displayMovieList(&movieHead);
            break;
        case 5:
            clear();
            displayAllShows(&screen1, &screen2, &screen3);
            break;
        case 6:
            clear();
            return;
        default:
            clear();
            printf("\n%s%s Invalid Option %s\n", RED_BG, WHITE_TXT, RESET);
            break;
        }
    }
}

/*FUNCTION TO INITIALIZE MENU DRIVEN USER SECTION*/
void user()
{
    int choice;
    while (1)
    {
        printf("\n%s%s   WELCOME TO USER SECTION   %s\n", BLK_BG, WHITE_TXT, RESET);
        printf("%s%s 1. Show Available Shows     %s\n", WHT_BG, BLACK_TXT, RESET);
        printf("%s%s 2. Book Seat                %s\n", BLU_BG, WHITE_TXT, RESET);
        printf("%s%s 3. Cancel Seat              %s\n", WHT_BG, BLACK_TXT, RESET);
        printf("%s%s 4. Check Seats Availability %s\n", BLU_BG, WHITE_TXT, RESET);
        printf("%s%s 5. Exit                     %s\n", WHT_BG, BLACK_TXT, RESET);
        printf("%s%s                             %s\n", BLK_BG, WHITE_TXT, RESET);
        printf("\n%s%sEnter your option: %s ", YLW_BG, BLACK_TXT, RESET);
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            clear();
            displayAllShows(&screen1, &screen2, &screen3);
            break;
        case 2:
            clear();
            bookTicket();
            break;
        case 3:
            clear();
            cancelTicket();
            break;
        case 4:
            clear();
            showSeatsAvailability();
            break;
        case 5:
            clear();
            return;
            break;
        default:
            clear();
            printf("\n%s%s Invalid Option %s\n", RED_BG, WHITE_TXT, RESET);
            break;
        }
    }
}

/*DRIVER FUNCTION [MAIN FUNCTION]*/
int main()
{
    int option;
    clear();
    while (1)
    {
        printBillboard();

        printf("\n%s%s   MOVIE TICKET BOOKING SYSTEM   %s", BLK_BG, WHITE_TXT, RESET);
        printf("\n%s%s  1. Admin                       %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s  2. User                        %s", WHT_BG, BLACK_TXT, RESET);
        printf("\n%s%s  3. Exit                        %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s                                 %s\n", BLK_BG, WHITE_TXT, RESET);
        printf("\n\n%s%sEnter your option: %s ", YLW_BG, BLACK_TXT, RESET);
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            clear();
            admin();
            break;
        case 2:
            clear();
            user();
            break;
        case 3:
            exit(0);
            break;
        default:
            clear();
            printf("\n%s%s Invalid Option %s\n", RED_BG, WHITE_TXT, RESET);
            break;
        }
    }

    return 0;
}