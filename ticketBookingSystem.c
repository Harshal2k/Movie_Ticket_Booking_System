#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    int seats[15];
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
    printf("\n====== IN SETSCREEN %d", showId);
    struct Screen *newShow = (struct Screen *)malloc(sizeof(struct Screen));
    newShow->screenNum = screenNum;
    newShow->showID = showId;
    newShow->movie = *movie;
    newShow->next = NULL;
    int minutes = (newShow->movie->durationMin * showId) + 540 + 30;
    int hours = minutes / 60;
    int minu = minutes % 60;
    if ((hours - 12) <= 0)
    {
        printf("\nHOURS: %d:%d AM", hours, minu);
    }
    else
    {
        printf("\nHOURS: %d:%d PM", (hours - 12), minu);
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
            int shows = (960 / (duration + 30)) + 1;
            int count;
            for (int j = 0; j < shows; j++)
            {
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

void displaySeats()
{
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

    //    struct Screen *temp=screen1;
    // screen1 = (struct Screen *)malloc(sizeof(struct Screen));
    //     struct Movie *mov=(struct Movie *)malloc(sizeof(struct Movie));
    //     int seatNo;
    //     char movieName[50];
    //     char userName[50];
    //     char mobileNo[10];
    //     displayMovies();
    //     printf("\nWhich show would you like to watch\n");
    //     scanf(" ");
    //     fgets(mov->name,50,stdin);
    //     printf("\nEnter your name\n");
    //     scanf(" ");
    //     fgets(userName,50,stdin);
    //      printf("\nEnter your screen number\n");
    //     scanf("%d",&sc->screenNum);

    //     while (1)
    //     {
    //         printf("\nEnter your 10 digit mobile number\n");
    //         scanf(" ");
    //         fgets(mobileNo,10,stdin);

    //         int len = strlen(mobileNo);

    //         if (len == 2)
    //         {

    //             break;
    //         }
    //         else
    //         {
    //             printf("Invalid Mobile number\n");
    //         }
    //     }

    //     displaySeats();
    //     while (1)
    //     {
    //         printf("\nEnter Seat No. : ");
    //         scanf("%d", &seatNo);

    //         if (sc->seats[seatNo] != 0)
    //         {
    //             printf("Seat Already Booked... Please select another seat :)");
    //         }
    //         else
    //         {
    //             sc->seats[seatNo] = 1;
    //             break;

    //         }
    //     }

    //     for (int i = 0; i < 15; i++)
    //     {
    //         printf("%d ",sc->seats[i]);
    //     }
    char movieNam[20];
    int shid, quantity, seatno, scrno;
    printf("\nWhich Movie you want to see?\n");
    scanf("%s", movieNam);
    printf("\nEnter Screen No :");
    scanf("%d", &scrno);
    printf("\nEnter  show ID :");
    scanf("%d", &shid);
    struct Screen *temp1 = screen1;
    struct Screen *temp2 = screen2;
    struct Screen *temp3 = screen3;
    if (scrno == 1)
    {
        while (temp1 != NULL)
        {
            while (1)
            {

                if (shid == temp1->showID)
                {

                    printf("\nHow Many Tickets :");
                    scanf("%d", &quantity);
                    printf("Select Seact Numbers :");
                    for (int i = 0; i < quantity; i++)
                    {
                        // displaySeats();
                        while (1)
                        {
                            printf("\nSelect seat No :");
                            scanf("%d", &seatno);
                            seatno = seatno - 1;
                            if (screen1->seats[seatno] == 1)
                            {
                                printf("Seat Already Booked Please Select another seat\n");
                            }
                            else
                            {
                                screen1->seats[seatno] = 1;
                                break;
                            }
                        }
                    }
                }

                break;
            }
            printf("\n-----------------------------------");

            printf("\nShowId: %d", temp1->showID);
            temp1 = temp1->next;
            printf("\n-----------------------------------");
        }

        printf("\nYou have booked\n");
        for (int i = 0; i < 15; i++)
        {
            if (screen1->seats[i] == 1)
            {
                printf("%d ", screen1->seats[i]);
            }
            else
            {
                printf("0 ");
            }
        }
    }
    if (scrno == 2)
    {
        while (temp2 != NULL)
        {
            while (1)
            {

                if (shid == temp2->showID)
                {

                    printf("How Many Tickets :");
                    scanf("%d", &quantity);
                    printf("Select Seact Numbers :");
                    for (int i = 0; i < quantity; i++)
                    {
                        // displaySeats();
                        while (1)
                        {
                            printf("\nSelect seat No :");
                            scanf("%d", &seatno);
                            seatno = seatno - 1;
                            if (screen2->seats[seatno] == 1)
                            {
                                printf("Seat Already Booked Please Seclect another seat\n");
                            }
                            else
                            {
                                screen2->seats[seatno] = 1;
                                break;
                            }
                        }
                    }
                }

                break;
            }
            printf("\n-----------------------------------");

            printf("\nShowId: %d", temp2->showID);
            temp2 = temp2->next;
            printf("\n-----------------------------------");
        }
        printf("\nYou have booked\n");
        for (int i = 0; i < 15; i++)
        {
            if (screen2->seats[i] == 1)
            {
                printf("%d ", screen2->seats[i]);
            }
            else
            {
                printf("0 ");
            }
        }
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
            displayMovies();
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