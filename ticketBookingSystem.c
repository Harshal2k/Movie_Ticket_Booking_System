#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define RED_BG "\033[48;5;9m"
#define YLW_BG "\033[48;5;11m"
#define GRN_BG "\033[48;5;34m"
#define WHITE_TXT "\033[38;5;15m"
#define BLACK_TXT "\033[38;5;0m"
#define RESET "\033[0m"
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
    printf("\nSHOWID = %d", showId);
    char date[20];
    char hour[20];
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, 20, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    struct Screen *newShow = (struct Screen *)malloc(sizeof(struct Screen));
    newShow->screenNum = screenNum;
    newShow->showID = showId;
    newShow->movie = *movie;
    newShow->seatsCount = 0;
    newShow->next = NULL;
    if (showId == 1)
    {
        snprintf(hour, 20, "9:00 AM");
    }
    else
    {
        int minutes = ((newShow->movie->durationMin + 30) * (showId - 1)) + 540;
        int hours = minutes / 60;
        int minu = minutes % 60;
        if ((hours - 12) < 0)
        {
            snprintf(hour, 20, "%d:%s%d AM", hours, minu > 10 ? "" : "0", minu);
        }
        else if ((hours - 12) == 0)
        {
            snprintf(hour, 20, "%d:%s%d PM", hours, minu > 10 ? "" : "0", minu);
        }
        else
        {
            snprintf(hour, 20, "%d:%s%d PM", (hours - 12), minu > 10 ? "" : "0", minu);
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
            printf("\nSeatsCount: %d", temp->seatsCount);
            printf("\n-----------------------------------");
            temp = temp->next;
        }
    }
}

int areShowsEmpty(struct Screen **head)
{
    int empty = 1;
    struct Screen *temp;
    temp = *head;
    while (temp != NULL)
    {
        if (temp->seatsCount > 0)
        {
            empty = 0;
            break;
        }
        temp = temp->next;
    }
    return empty;
}

void removeShow()
{
    int screenNo, showId, flag = 0;
    struct Screen *temp, *prev = NULL;
    printf("\n%s%s ---------------------NOTE--------------------- %s", RED_BG, WHITE_TXT, RESET);
    printf("\n%s%s Show Once deleted cannot added be for that day %s\n", RED_BG, WHITE_TXT, RESET);
    printf("\n%s%s Enter screen No: %s", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &screenNo);
    printf("\n%s%s Enter Show Id: %s", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &showId);
    if (screenNo == 1)
    {
        temp = screen1;
    }
    else if (screenNo == 2)
    {
        temp = screen2;
    }
    else if (screenNo == 3)
    {
        temp = screen3;
    }
    else
    {
        printf("\n%s%s Invalid Screen Number %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }

    while (temp != NULL)
    {
        if (temp->showID == showId)
        {
            flag = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("\n%s%s Entered Show Id does not exist %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else
    {
        if (temp->seatsCount > 0)
        {
            printf("\n%s%s Cannot Delete show, seats are already booked %s\n", RED_BG, WHITE_TXT, RESET);
            return;
        }
        else
        {
            if (prev == NULL && temp->next == NULL)
            {
                if (screenNo == 1)
                {
                    screen1 = NULL;
                }
                else if (screenNo == 2)
                {
                    screen2 = NULL;
                }
                else
                {
                    screen3 = NULL;
                }
                deleteMovie(&temp->movie);
            }
            else if (prev == NULL)
            {
                if (screenNo == 1)
                {
                    screen1 = temp->next;
                }
                else if (screenNo == 2)
                {
                    screen2 = temp->next;
                }
                else
                {
                    screen3 = temp->next;
                }
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            printf("\n%s%s Show Deleted Successfully %s\n", GRN_BG, WHITE_TXT, RESET);
        }
    }
}

void deleteMovie(struct Movie **movie)
{
    struct Movie *temp;
    temp = *movie;
    int todelete = 0;
    if (temp->screen1 == 1 && screen1 != NULL)
    {
        todelete = 1;
    }
    if (temp->screen2 == 1 && screen2 != NULL)
    {
        todelete = 1;
    }
    if (temp->screen3 == 1 && screen3 != NULL)
    {
        todelete = 1;
    }
    if (todelete == 0)
    {
        struct Movie *temp2 = movieHead, *prev = NULL;
        while (temp2 != NULL)
        {
            if (strcmp(temp2->name, temp->name) == 0)
            {
                break;
            }
            prev = temp2;
            temp2 = temp2->next;
        }
        if (temp2 != NULL)
        {
            if (prev == NULL && temp2->next == NULL)
            {
                movieHead = NULL;
            }
            else if (prev == NULL)
            {
                movieHead = temp2->next;
            }
            else
            {
                prev->next = temp2->next;
            }
            free(temp2);
        }
    }
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
    newMovie->price1 = 500;
    newMovie->price2 = 350;
    newMovie->price3 = 250;
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
    int removeFlag = 0;
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
                    if (areShowsEmpty(&screen1) == 0)
                    {
                        removeFlag = 1;
                        printf("\n%s%sCannot remove movie from Screen I, some of the shows for the movie in Screen I are already booked for the day%s", RED_BG, WHITE_TXT, RESET);
                    }
                    else
                    {
                        printf("\n%s%s Movie Removed from Screen I %s", GRN_BG, WHITE_TXT, RESET);
                        screen1 = NULL;
                    }
                }
                if (temp->screen2 == 1)
                {
                    if (areShowsEmpty(&screen2) == 0)
                    {
                        removeFlag = 1;
                        printf("\nCannot remove movie from Screen II, some of the shows for the movie in Screen II are already booked for the day");
                    }
                    else
                    {
                        printf("\n%s%s Movie Removed from Screen II %s", GRN_BG, WHITE_TXT, RESET);
                        screen2 = NULL;
                    }
                }
                if (temp->screen3 == 1)
                {
                    if (areShowsEmpty(&screen3) == 0)
                    {
                        removeFlag = 1;
                        printf("\nCannot remove movie from Screen III, some of the shows for the movie in Screen III are already booked for the day");
                    }
                    else
                    {
                        printf("\n%s%s Movie Removed from Screen III %s", GRN_BG, WHITE_TXT, RESET);
                        screen3 = NULL;
                    }
                }
                if (removeFlag == 0)
                {
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
                }
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
    for (int i = 1; i <= 100; i++)
    {
        if (i % 9 == 0)
            printf("\n\n");
        if (vacant->seats[i] == 1)
        {
            printf("*\t");
        }
        else
        {
            printf("%d\t", i);
        }
    }
}

void displayBill(struct Screen **shead, struct Movie **mhead, int quantity, char name[], int price)
{
    struct Screen *temp = *shead;
    struct Movie *mov = *mhead;
    int no;
    for (int i = 0; i < 100; i++)
    {
        if (temp->seats[i] == 1)
        {
            no = i + 1;
            printf("\n\n");
            printf("\t-----------------        VASCO 1920        ----------------\n");
            printf("\t============================================================\n");
            printf("\t Booking ID : %d \t\t\tShow Name : %s\n", temp->showID, mov->name);
            printf("\t Customer  : %s \n", name);
            printf("\t\t\t                              Date      : %s\n", temp->date);
            printf("\t                                              Time       : %s\n", temp->time);
            printf("\t                                              Screen No. : %d\n", temp->screenNum);
            printf("\t                                              seats No.  : %d  \n", no);
            printf("\t                                              price      : %d  \n\n", price);
            printf("\t============================================================\n");
        }
    }

    return;
}

void showsAvailable()
{
}

void bookedShows()
{
}

void bookTicket()
{

    char movieNam[20], name[20];
    int shid, quantity, seatno, scrno;
    int price1 = 0, total = 0, price2 = 0, price3 = 0;
    printf("\nEnter name of the movie: ");
    scanf(" ");
    fgets(movieNam, 20, stdin);
    movieNam[strcspn(movieNam, "\n")] = 0;
    printf("\nEnter your name: ");
    scanf(" ");
    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = 0;
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
    if (scrno == 1 && screen1 == NULL)
    {
        printf("\nNo shows available on screen\n");
        goto ScreenNo;
    }
    else if (scrno == 2 && screen2 == NULL)
    {
        printf("\nNo shows available on screen\n");
        goto ScreenNo;
    }
    else if (scrno == 3 && screen3 == NULL)
    {
        printf("\nNo shows available on screen\n");
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
                    // displaySeats(&temp1);

                    for (int i = 0; i < quantity; i++)
                    {
                        while (1)
                        {
                            printf("\nSelect seat No :");
                            scanf("%d", &seatno);
                            if (seatno <= 30)
                            {
                                price3 = temp->price3 + price3;
                            }
                            else if (seatno >= 80)
                            {
                                price1 = temp->price1 + price1;
                            }
                            else if (seatno > 30 && seatno < 80)
                            {
                                price2 = temp->price2 + price2;
                            }
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
        printf("\n\n");
        printf("\nYou have booked seats that are starred ( * )\n");
        displaySeats(&temp1);

        total=price1+price2+price3;
        if (price1 != 0)
        {
            displayBill(&temp1, &temp, quantity, name, temp->price1);
        }
        else if (price2 != 0)
        {
            displayBill(&temp1, &temp, quantity, name, temp->price2);
        }
        else if (price3 != 0)
        {
            displayBill(&temp1, &temp, quantity, name, temp->price3);
        }
         printf("\t                      Total      : %d  \n\n", total);
        printf("\t============================================================\n");
    }

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
        // displayBill(&temp2, &temp, quantity, name);
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

            temp3 = temp3->next;
        }
        printf("\nYou have booked seats that are starred ( * )\n");
        displaySeats(&temp3);
        // displayBill(&temp3, &temp, quantity, name);
    }

    else
    {
        printf("\nEnter valid Screen Number: ");
        goto ScreenNo;
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
            removeShow();
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