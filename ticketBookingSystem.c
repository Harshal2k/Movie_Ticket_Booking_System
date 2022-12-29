#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
struct Movie
{
    char name[30];
    int durationMin;
    int screen1;
    int screen2;
    int screen3;
    struct Movie *next;
} *movieHead = NULL;

struct Screen
{
    int screenNum;
    int showID;
    struct Movie *movie;
    int seats[100];
    int day;
    int month;
    int year;
    char time[20];
    int seatsCount;
    struct Screen *next;
} *screen1 = NULL, *screen2 = NULL, *screen3 = NULL;

void showMovies(struct Movie **head)
{
    printf("\n-------MOVIES LIST---------------");
    struct Movie *temp;
    temp = *head;
    while (temp != NULL)
    {
        printf("\nMovie = %s", temp->name);
        temp = temp->next;
    }
}

void setScreen(struct Screen **screenHead, int screenNum, int showId, struct Movie **movie)
{
    char date[30];
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    // printf("Current Date: %d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("\n====== IN SETSCREEN %d", showId);
    snprintf(date, 30, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    // strcat(date, 1);
    // strcat(date, "-");
    // strcat(date, (tm.tm_mon + 1));
    // strcat(date, "-");
    // strcat(date, (tm.tm_year + 1900));
    printf("\nDATE: %s", date);
    struct Screen *newShow = (struct Screen *)malloc(sizeof(struct Screen));
    newShow->screenNum = screenNum;
    newShow->showID = showId;
    newShow->movie = *movie;
    newShow->next = NULL;
    if (showId == 1)
    {
        printf("\nHOURS: 9:00 AM");
    }
    else
    {
        int minutes = ((newShow->movie->durationMin + 30) * (showId - 1)) + 540;
        int hours = minutes / 60;
        int minu = minutes % 60;
        if ((hours - 12) < 0)
        {
            printf("\nHOURS: %d:%d AM", hours, minu);
        }
        else if ((hours - 12) == 0)
        {
            printf("\nHOURS: %d:%d PM", hours, minu);
        }
        else
        {
            printf("\nHOURS: %d:%d PM", (hours - 12), minu);
        }
    }
    struct Screen *temp;
    temp = *screenHead;
    if (temp == NULL)
    {
        *screenHead = newShow;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newShow;
    }
}

void displayShows(struct Screen **sHead1, struct Screen **sHead2, struct Screen **sHead3)
{
    printf("\n-------SHOW LIST 1---------------");
    struct Screen *temp;
    temp = *sHead1;
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            printf("\n-------SHOW LIST 1---------------");
            temp = *sHead1;
        }
        else if (i == 1)
        {
            printf("\n-------SHOW LIST 2---------------");
            temp = *sHead2;
        }
        else
        {
            printf("\n-------SHOW LIST 3---------------");
            temp = *sHead3;
        }
        while (temp != NULL)
        {
            printf("\n-----------------------------------");
            printf("\nMovie: %s", temp->movie->name);
            printf("\nDuration: %d", temp->movie->durationMin);
            printf("\nScreenNum: %d", temp->screenNum);
            printf("\nShowId: %d", temp->showID);
            printf("\n-----------------------------------");
            temp = temp->next;
        }
    }
}

void extraFunction5()
{
}

void extraFunction6()
{
}

void extraFunction7()
{
}

void extraFunction8()
{
}

void extraFunction9()
{
}

void extraFunction10()
{
}

int isDateValid(int dd, int mm, int yy)
{
    // check year
    if (yy >= 1900 && yy <= 9999)
    {
        // check month
        if (mm >= 1 && mm <= 12)
        {
            // check days
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
                return 1;
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                return 1;
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
                return 1;
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
                return 1;
            else
                printf("Day is invalid.\n");
            return 0;
        }
        else
        {
            printf("Month is not valid.\n");
            return 0;
        }
    }
    else
    {
        printf("Year is not valid.\n");
        return 0;
    }
}

void setMovie(struct Movie **head, struct Screen **sHead1, struct Screen **sHead2, struct Screen **sHead3)
{
    char movieName[30];
    int dd, mm, yy, duration, screens = 0, valid = 0, scre[3];
    printf("\nEnter Movie Name: ");
    scanf(" ");
    fgets(movieName, 30, stdin);
    movieName[strcspn(movieName, "\n")] = 0;
    printf("\nEnter Movie Duration (in minutes): ");
    scanf("%d", &duration);
    // printf("\nEnter Release date (in format dd/mm/yyyy): ");
    // scanf("%d/%d/%d", &dd, &mm, &yy);
    // if (isDateValid(dd, mm, yy) == 0)
    // {
    //     return;
    // }
    // printf("\nEnter total screens (MAX 3): ");
    // scanf("%d", &screens);
    // if (screens > 3)
    // {
    //     printf("\nOnly 3 screens are avialable");
    //     return;
    // }
    // else if (screens <= 0)
    // {
    //     printf("\nScreens cannot be less then or equal to Zero");
    //     return;
    // }

    struct Movie *newMovie = (struct Movie *)malloc(sizeof(struct Movie));
    newMovie->screen1 = 0;
    newMovie->screen2 = 0;
    newMovie->screen3 = 0;
    newMovie->next = NULL;
    strcpy(newMovie->name, movieName);
    newMovie->durationMin = duration;
    for (int i = 0; i < 3; i++)
    {
        char romanNum[3];
        if (i == 0 && screen1 == NULL)
        {
            strcpy(romanNum, "I");
        }
        else if (i == 1 && screen2 == NULL)
        {
            strcpy(romanNum, "II");
        }
        else if (i == 2 && screen3 == NULL)
        {
            strcpy(romanNum, "III");
        }
        else
        {
            continue;
        }
        char option;
        printf("\nDo you want to play this movie on Screen %s", romanNum);
        printf("\nPress Y for yes OR any other character as NO: ");
        scanf(" %c", &option);
        if (option == 'y' || option == 'Y')
        {
            int shows = (960 / (duration + 30));
            printf("\nSHOWS: %d", shows);
            for (int j = 0; j < shows; j++)
            {
                printf("\ni = %d", j);
                if (i == 0)
                {
                    setScreen(&screen1, 1, (j + 1), &newMovie);
                    newMovie->screen1 = 1;
                }
                else if (i == 1)
                {
                    setScreen(&screen2, 2, (j + 1), &newMovie);
                    newMovie->screen2 = 1;
                }
                else
                {
                    setScreen(&screen3, 3, (j + 1), &newMovie);
                    newMovie->screen3 = 1;
                }
            }
        }
    }
    struct Movie *temp;
    temp = *head;
    if (temp == NULL)
    {
        *head = newMovie;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newMovie;
    }
}

void removeMovie(struct Movie **head)
{
    char movieName[20];
    printf("\nEnter name of the movie to be removed: ");
    scanf(" ");
    fgets(movieName, 20, stdin);
    movieName[strcspn(movieName, "\n")] = 0;
    struct Movie *temp, *previous = NULL;
    temp = *head;
    if (temp == NULL)
    {
        printf("\nNo Movies has been added for the day");
        return;
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(movieName, temp->name) == 0)
            {
                if (temp->screen1 == 1)
                {
                    screen1 = NULL;
                }
                if (temp->screen2 == 1)
                {
                    screen2 = NULL;
                }
                if (temp->screen3 == 1)
                {
                    screen3 = NULL;
                }
                if (previous == NULL && temp->next == NULL)
                {
                    movieHead = NULL;
                }
                else if (previous == NULL)
                {
                    *head = temp->next;
                }
                else
                {
                    previous->next = temp->next;
                }
                free(temp);
                break;
            }
            previous = temp;
            temp = temp->next;
        }
    }
}

void displaySeats(struct Screen **shead)
{
    struct Screen *vacant;
    vacant = *shead;
    for (int i = 0; i < 100; i++)
    {
        if(i%10==0)
				printf("\n");
        if (vacant->seats[i] == 1)
        {
            printf("*\t", vacant->seats[i]);
        }
        else
        {
            printf("0\t");
        }
    }
}

void displayMovies()
{
}

void showsAvailable()
{
}

void bookedShows()
{
}

void bookTicket()
{

    char movieNam[20];
    int shid, quantity, seatno, scrno;

    printf("\nWhich Movie you want to see?\n");
    scanf("%s", movieNam);
    struct Movie *temp;
    temp = movieHead;
    int flagMovie = 0;
    while (temp != NULL)
    {
        if (strcmp(movieNam, temp->name) == 0)
        {
            flagMovie = 1;
            break;
        }
        temp = temp->next;
    }
    if (flagMovie == 0)
    {
        printf("Enter valid movie name");
        bookTicket();
    }
ScreenNo:
    printf("\nEnter Screen No :");
    scanf("%d", &scrno);
    if (!(scrno == 1 && screen1->screenNum == 1) ||
        (scrno == 2 && screen2->screenNum == 1) ||
        (scrno == 3 && screen3->screenNum == 1))
    {
        printf("\nEnter valid Screen Number: ");
        goto ScreenNo;
    }

    struct Screen *temp1 = screen1;
    struct Screen *temp2 = screen2;
    struct Screen *temp3 = screen3;
SHID:
    printf("\nEnter  show ID :");
    scanf("%d", &shid);
    if (scrno == 1 && temp->screen1 == 1)
    {
        int flag = 0;

        while (temp1 != NULL)
        {
            while (1)
            {

                if (shid == temp1->showID)
                {
                    printf("\nHow Many Tickets :");
                    scanf("%d", &quantity);
                    displaySeats(&temp1);
                    
                    for (int i = 0; i < quantity; i++)
                    {
                        while (1)
                        {
                            printf("\nSelect seat No :");
                            scanf("%d", &seatno);
                            seatno = seatno - 1;
                            if (temp1->seats[seatno] == 1)
                            {
                                printf("Seat Already Booked Please Select another seat\n");
                            }
                            else
                            {
                                temp1->seats[seatno] = 1;
                                break;
                            }
                        }
                    }
                    flag = 1;
                }
                break;
            }
            if (flag == 1)
            {
                break;
            }

            temp1 = temp1->next;
        }
        printf("\nYou have booked seats that are starred ( * )\n");
         displaySeats(&temp1);
         
        // printf("\nYou have booked\n");
        // for (int i = 0; i < 100; i++)
        // {
        //     if (temp1->seats[i] == 1)
        //     {
        //         printf("%d ", temp1->seats[i]);
        //     }
        //     else
        //     {
        //         printf("0 ");
        //     }
        // }
    }
    // else{
    //     printf("\nNo Movies Today GO HOME :)\n");
    //     user();
    // }
    else if (scrno == 2 && temp->screen2 == 1)
    {
        int flag = 0;
        while (temp2 != NULL)
        {
            while (1)
            {

                if (shid == temp2->showID)
                {

                    printf("How Many Tickets :");
                    scanf("%d", &quantity);
                     displaySeats(&temp1);
                    for (int i = 0; i < quantity; i++)
                    {
                        // displaySeats();
                        while (1)
                        {
                            printf("\nSelect seat No :");
                            scanf("%d", &seatno);
                            seatno = seatno - 1;
                            if (temp2->seats[seatno] == 1)
                            {
                                printf("Seat Already Booked Please Seclect another seat\n");
                            }
                            else
                            {
                                temp2->seats[seatno] = 1;
                                break;
                            }
                        }
                    }
                    flag = 1;
                }

                break;
            }
            if (flag == 1)
            {
                break;
            }
            
            temp2 = temp2->next;
           
        }
        printf("\nYou have booked seats that are starred ( * )\n");
         displaySeats(&temp1);
    }
    else if (scrno == 3 && temp->screen3 == 1)
    {
        int flag = 0;
        while (temp3 != NULL)
        {
            while (1)
            {

                if (shid == temp3->showID)
                {

                    printf("How Many Tickets :");
                    scanf("%d", &quantity);
                     displaySeats(&temp1);
                    for (int i = 0; i < quantity; i++)
                    {
                        // displaySeats();
                        while (1)
                        {
                            printf("\nSelect seat No :");
                            scanf("%d", &seatno);
                            seatno = seatno - 1;
                            if (temp3->seats[seatno] == 1)
                            {
                                printf("Seat Already Booked Please Seclect another seat\n");
                            }
                            else
                            {
                                temp3->seats[seatno] = 1;
                                break;
                            }
                        }
                    }
                    flag = 1;
                }

                break;
            }
            if (flag == 1)
            {
                break;
            }
           
            temp2 = temp2->next;
            
        }
        printf("\nYou have booked seats that are starred ( * )\n");
         displaySeats(&temp1);
    }
    else
    {
        printf("\nEnter Valid Screen NO :\n");
        scanf("%d", &scrno);
    }
}

void cancelTicket()
{
    struct Screen *p = screen1;
    int i = 0;
    while (p != NULL)
    {
        printf("%d ", p->seats[i]);
        p = p->next;
        i++;
    }
}

void admin()
{
    char password[20];
    char movieName[30];
    int dd, mm, yy;
    struct Movie *temp = movieHead;
    printf("\nEnter Admin Password:");
    scanf(" ");
    fgets(password, 20, stdin);
    if (0 != strcmp(password, "pass\n"))
    {
        printf("\nInvalid Password");
        return;
    }
    int option;
    while (1)
    {
        printf("\n****WELCOME ADMIN****");
        printf("\n1. Add Movie");
        printf("\n2. Remove Movie");
        printf("\n3. Remove Show");
        printf("\n4. Display Movies");
        printf("\n5. Display Shows");
        printf("\n6. Exit");
        printf("\nEnter your option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if (screen1 == NULL || screen2 == NULL || screen3 == NULL)
            {
                setMovie(&movieHead, &screen1, &screen2, &screen3);
            }
            else
            {
                printf("\nNo Screens Available");
            }
            break;
        case 2:
            removeMovie(&movieHead);
            break;
        case 3:
            // remove show()
            break;
        case 4:
            showMovies(&movieHead);
            break;
        case 5:
            displayShows(&screen1, &screen2, &screen3);
            break;
        case 6:
            return;
        default:
            break;
        }
    }
}

void user()
{
    int choice;
    while (1)
    {
        printf("\n *** Welcome to user section *** \n");
        printf("1. Shows Available Shows\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Seat\n");
        printf("4. Go to previous Menu\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayShows(&screen1, &screen2, &screen3);
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            cancelTicket();
            break;
        case 4:
            main();
            break;
        default:
            printf("\nInvalid Option :(");
            break;
        }
    }
}

int main()
{
    int option;
    printf("\nMOVIE TICKET BOOKING SYSTEM");
    while (1)
    {
        printf("\n1. Admin");
        printf("\n2. User");
        printf("\n3. Exit");
        printf("\nEnter your option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            admin();
            break;
        case 2:
            printf("\n In User");
            user();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("\nInvalid Option :(");
            break;
        }
    }

    return 0;
}