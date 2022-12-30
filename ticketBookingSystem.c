#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define RED_BG "\033[48;5;9m"
#define YLW_BG "\033[48;5;11m"
#define GRN_BG "\033[48;5;34m"
#define BLK_BG "\033[48;5;0m"
#define BLU_BG "\033[48;5;32m"
#define WHT_BG "\033[48;5;15m"
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

/*FUNCTION TO CLEAR THE CONSOLE*/
void clear()
{
    system("clear");
}

/*FUNCTION TO PRINT LIST OF AVAILABLE MOVIES*/
void showMovies(struct Movie **head)
{
    printf("\n%s%s            MOVIES LIST           %s", BLK_BG, WHITE_TXT, RESET);
    struct Movie *temp;
    temp = *head;
    int count = 1;
    while (temp != NULL)
    {
        printf("\n%s%s %d. %-30s%s", count % 2 == 0 ? BLU_BG : WHT_BG, count % 2 == 0 ? WHITE_TXT : BLACK_TXT, count, temp->name, RESET);
        temp = temp->next;
        count++;
    }
    printf("\n%s%s                                  %s\n\n", BLK_BG, WHITE_TXT, RESET);
}

/*FUNCTION TO CREATE SHOW FOR A GIVEN MOVIE*/
void setScreen(struct Screen **screenHead, int screenNum, int showId, struct Movie **movie)
{
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    struct Screen *newShow = (struct Screen *)malloc(sizeof(struct Screen));
    newShow->screenNum = screenNum;
    newShow->showID = showId;
    newShow->movie = *movie;
    newShow->seatsCount = 0;
    newShow->next = NULL;
    snprintf(newShow->date, 20, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    if (showId == 1)
    {
        snprintf(newShow->time, 20, "9:00 AM");
    }
    else
    {
        int minutes = ((newShow->movie->durationMin + 30) * (showId - 1)) + 540;
        int hours = minutes / 60;
        int minu = minutes % 60;
        if ((hours - 12) < 0)
        {
            snprintf(newShow->time, 20, "%d:%s%d AM", hours, minu > 10 ? "" : "0", minu);
        }
        else if ((hours - 12) == 0)
        {
            snprintf(newShow->time, 20, "%d:%s%d PM", hours, minu > 10 ? "" : "0", minu);
        }
        else
        {
            snprintf(newShow->time, 20, "%d:%s%d PM", (hours - 12), minu > 10 ? "" : "0", minu);
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

/*FUNCTION TO LIST ALL THE SHOWS BEING SHOWN FOR THE DAY ON SCREEN I, SCREEN II AND SCREEN III*/
void displayShows(struct Screen **sHead1, struct Screen **sHead2, struct Screen **sHead3)
{
    struct Screen *temp;
    temp = *sHead1;
    for (int i = 0; i < 3; i++)
    {
        int count = 1;
        if (i == 0)
        {
            printf("\n\n%s%s              SCREEN I SHOW              %s", BLK_BG, WHITE_TXT, RESET);
            temp = *sHead1;
        }
        else if (i == 1)
        {
            printf("\n\n%s%s              SCREEN II SHOW             %s", BLK_BG, WHITE_TXT, RESET);
            temp = *sHead2;
        }
        else
        {
            printf("\n\n%s%s             SCREEN III SHOW             %s", BLK_BG, WHITE_TXT, RESET);
            temp = *sHead3;
        }
        while (temp != NULL)
        {
            printf("\n%s%s Movie:    %-30s%s", count % 2 == 0 ? BLU_BG : WHT_BG, count % 2 == 0 ? WHITE_TXT : BLACK_TXT, temp->movie->name, RESET);
            printf("\n%s%s Duration: %-4d Minutes                  %s", count % 2 == 0 ? BLU_BG : WHT_BG, count % 2 == 0 ? WHITE_TXT : BLACK_TXT, temp->movie->durationMin, RESET);
            printf("\n%s%s Screen:   %-30d%s", count % 2 == 0 ? BLU_BG : WHT_BG, count % 2 == 0 ? WHITE_TXT : BLACK_TXT, temp->screenNum, RESET);
            printf("\n%s%s ShowId:   %-30d%s", count % 2 == 0 ? BLU_BG : WHT_BG, count % 2 == 0 ? WHITE_TXT : BLACK_TXT, temp->showID, RESET);
            printf("\n%s%s Time:     %-15s%-15s%s", count % 2 == 0 ? BLU_BG : WHT_BG, count % 2 == 0 ? WHITE_TXT : BLACK_TXT, temp->date, temp->time, RESET);
            temp = temp->next;
            count++;
        }
        printf("\n%s%s                                         %s\n", BLK_BG, WHITE_TXT, RESET);
    }
}

/*FUNCTION TO CHECK IF ALL THE SHOWS ON GIVEN SCREEN ARE EMPTY OR NOT, IF EMPTY RETURNS 1, ELSE RETURNS 0*/
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

/*FUNCTION TO DELETE SPECIFIED MOVIE NODE FROM LINKED LIST*/
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

/*FUNCTION TO DELETE SPECIFIED SHOW, SHOW WILL BE DELETED ONLY IF ALL THE SEATS ARE VACANT */
void removeShow()
{
    int screenNo, showId, flag = 0;
    struct Screen *temp, *prev = NULL;
    printf("\n%s%s ---------------------NOTE--------------------- %s", RED_BG, WHITE_TXT, RESET);
    printf("\n%s%s Show Once deleted cannot added be for that day %s\n", RED_BG, WHITE_TXT, RESET);
    printf("\n%s%s Enter screen No: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &screenNo);
    printf("\n%s%s Enter Show Id: %s ", YLW_BG, BLACK_TXT, RESET);
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

/*FUNCTION TO SETUP A MOVIE ON THE SCREEN [MOVIE DATA IS INITALIZED HERE]*/
void setMovie(struct Movie **head, struct Screen **sHead1, struct Screen **sHead2, struct Screen **sHead3)
{
    char movieName[30];
    int dd, mm, yy, duration, screens = 0, valid = 0, scre[3];
    printf("\n%s%s Enter Movie Name: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf(" ");
    fgets(movieName, 30, stdin);
    movieName[strcspn(movieName, "\n")] = 0;
    struct Movie *tempMov = movieHead;
    int movCheck = 0;
    while (tempMov != NULL)
    {
        if (strcmp(movieName, tempMov->name) == 0)
        {
            movCheck = 1;
            break;
        }
        tempMov = tempMov->next;
    }
    if (movCheck == 1)
    {
        printf("\n%s%s Movie with same name already exists! %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }

    printf("\n%s%s Enter Movie Duration (in minutes): %s ", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &duration);
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
        printf("\n%s%s Do you want to play this movie on Screen %s ? %s ", GRN_BG, WHITE_TXT, romanNum, RESET);
        printf("\n%s%s Press Y for YES or any other character as NO: %s ", YLW_BG, BLACK_TXT, RESET);
        scanf(" %c", &option);
        if (option == 'y' || option == 'Y')
        {
            int shows = (960 / (duration + 30));
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
            printf("\n%s%s Movie Added on Screen %s %s\n", BLU_BG, WHITE_TXT, i == 0 ? "I" : i == 1 ? "II"
                                                                                                    : "III",
                   RESET);
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

/*FUNCTION TO DELETE ALL THE SHOWS OF THE GIVEN MOVIE, MOVIE WILL BE DELETED ONLY IF IT IS NOT BEING
  SHOWN ON ANY SCREEN, AND SHOWS WILL BE DELETED ONLY IF ALL THE SEATS ARE VACANT
 */
void removeMovie(struct Movie **head)
{
    char movieName[20];
    int removeFlag = 0;
    printf("\n%s%s Enter name of the movie to be removed: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf(" ");
    fgets(movieName, 20, stdin);
    movieName[strcspn(movieName, "\n")] = 0;
    struct Movie *temp, *previous = NULL;
    temp = *head;
    if (temp == NULL)
    {
        printf("\n%s%s No Movies has been added for the day %s\n", RED_BG, WHITE_TXT, RESET);
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
                        printf("\n%s%s Cannot remove movie from Screen I, some of the shows for the movie in Screen I are already booked for the day %s\n", RED_BG, WHITE_TXT, RESET);
                    }
                    else
                    {
                        printf("\n%s%s Movie Removed from Screen I %s\n", GRN_BG, WHITE_TXT, RESET);
                        screen1 = NULL;
                    }
                }
                if (temp->screen2 == 1)
                {
                    if (areShowsEmpty(&screen2) == 0)
                    {
                        removeFlag = 1;
                        printf("\n%s%s Cannot remove movie from Screen II, some of the shows for the movie in Screen II are already booked for the day %s\n", RED_BG, WHITE_TXT, RESET);
                    }
                    else
                    {
                        printf("\n%s%s Movie Removed from Screen II %s\n", GRN_BG, WHITE_TXT, RESET);
                        screen2 = NULL;
                    }
                }
                if (temp->screen3 == 1)
                {
                    if (areShowsEmpty(&screen3) == 0)
                    {
                        removeFlag = 1;
                        printf("\n%s%s Cannot remove movie from Screen III, some of the shows for the movie in Screen III are already booked for the day %s\n", RED_BG, WHITE_TXT, RESET);
                    }
                    else
                    {
                        printf("\n%s%s Movie Removed from Screen III %s\n", GRN_BG, WHITE_TXT, RESET);
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

/*FUNCTION TO PRINT THE THEATER SEATS [AVAILABLE AND BOOKED SEATS ARE SHOWN]*/
void displaySeats(struct Screen **shead)
{
    struct Screen *vacant;
    vacant = *shead;
    int no;
    printf("\n                            %s%s         SCREEN         %s                            \n", BLK_BG, WHITE_TXT, RESET);
    for (int i = 0; i < 100; i++)
    {
        if (i % 10 == 0)
        {
            printf("\n%s%s                                                                                %s\n", i <= 29 ? RED_BG : i > 79 ? GRN_BG
                                                                                                                                           : BLU_BG,
                   WHITE_TXT, RESET);
        }
        if (vacant->seats[i] == 1)
        {
            printf("%s%s    %-4s%s", i <= 29 ? RED_BG : i > 79 ? GRN_BG
                                                               : BLU_BG,
                   WHITE_TXT, "🍿  ", RESET);
        }
        else
        {
            printf("%s%s    %-4d%s", i <= 29 ? RED_BG : i > 79 ? GRN_BG
                                                               : BLU_BG,
                   WHITE_TXT, i + 1, RESET);
        }
    }
    printf("\n%s%s                                                                                %s\n", GRN_BG, WHITE_TXT, RESET);
    printf("\n %s  %s %s%s %d Rs %s", GRN_BG, RESET, BLK_BG, WHITE_TXT, vacant->movie->price1, RESET);
    printf("\t %s  %s %s%s %d Rs %s", BLU_BG, RESET, BLK_BG, WHITE_TXT, vacant->movie->price2, RESET);
    printf("\t %s  %s %s%s %d Rs %s", RED_BG, RESET, BLK_BG, WHITE_TXT, vacant->movie->price3, RESET);
    printf("\t%s%s 🍿 = Booked Seats %s\n", BLK_BG, WHITE_TXT, RESET);
}

/*FUNCTION TO PRINT THE BILL*/
void displayBill(struct Screen **shead, int seatNo, char name[], int price)
{
    struct Screen *temp = *shead;
    char formattedMovie[43];
    snprintf(formattedMovie, 43, "Movie Name : %s", temp->movie->name);
    printf("\n\n");
    printf("\t%s%s------------------%s%s%s        VASCO 1920        %s%s%s------------------%s\n", BLK_BG, WHITE_TXT, RESET, YLW_BG, BLACK_TXT, RESET, BLK_BG, WHITE_TXT, RESET);
    printf("\t%s%s                            TICKET                            %s\n", BLK_BG, WHITE_TXT, RESET);
    printf("\t%s%s Show ID : %-2d     %43s %s\n", BLU_BG, WHITE_TXT, temp->showID, formattedMovie, RESET);
    printf("\t%s%s Customer  : %-30s                   %s\n", BLU_BG, WHITE_TXT, name, RESET);
    printf("\t%s%s     %s  %s   %s      %s   %s      %s   %s      %s    Date       : %-10s %s\n", WHT_BG, BLACK_TXT, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, temp->date, RESET);
    printf("\t%s%s     %s  %s   %s  %s  %s  %s       %s  %s   %s  %s  %s  %s    Time       : %-8s   %s\n", WHT_BG, BLACK_TXT, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, temp->time, RESET);
    printf("\t%s%s     %s  %s   %s      %s   %s      %s   %s  %s  %s  %s    Screen No. : %-2d         %s\n", WHT_BG, BLACK_TXT, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, temp->screenNum, RESET);
    printf("\t%s%s     %s  %s       %s  %s   %s  %s       %s  %s  %s  %s    Seats No.  : %-2d         %s\n", WHT_BG, BLACK_TXT, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, seatNo, RESET);
    printf("\t%s%s     %s  %s       %s  %s   %s      %s   %s      %s    Price      : %-3d        %s\n", WHT_BG, BLACK_TXT, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, RED_BG, WHT_BG, price, RESET);
    printf("\t%s%s                        HAPPY WATCHING                        %s\n", BLK_BG, WHITE_TXT, RESET);

    return;
}

/*FUNCTION TO BOOK TICKETS FOR A SPECIFIED MOVIE*/
void bookTicket()
{
    char movieNam[30], name[30];
    int shid, quantity, seatno, scrno;
    int arr[100];
    int count = 0;
    int price1 = 0, total = 0, price2 = 0, price3 = 0;
    printf("\n%s%s Enter name of the movie: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf(" ");
    fgets(movieNam, 30, stdin);
    movieNam[strcspn(movieNam, "\n")] = 0;
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
        printf("\n%s%s Movie %s is not being shown here. %s\n", RED_BG, WHITE_TXT, movieNam, RESET);
        return;
    }
    printf("\n%s%s Enter your name: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf(" ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
ScreenNo:
    printf("\n%s%s Enter Screen No: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &scrno);
    if (scrno == 1 && screen1 == NULL)
    {
        printf("\n%s%s No shows available on screen I %s\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
    else if (scrno == 2 && screen2 == NULL)
    {
        printf("\n%s%s No shows available on screen II %s\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
    else if (scrno == 3 && screen3 == NULL)
    {
        printf("\n%s%s No shows available on screen III %s\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }

    struct Screen *temp1 = screen1;
    struct Screen *temp2 = screen2;
    struct Screen *temp3 = screen3;
SHID:
    printf("\n%s%s Enter show Id: %s ", YLW_BG, BLACK_TXT, RESET);
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
                    printf("\n%s%s How Many Tickets: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);
                    if (temp1->seatsCount == 100)
                    {
                        printf("\n%s%s Show is Housefull, No seats are available! %s\n", RED_BG, WHITE_TXT, RESET);
                        return;
                    }
                    else if (quantity + temp1->seatsCount > 100)
                    {
                        printf("\n%s%s Only %d seats are available %s\n", RED_BG, WHITE_TXT, (100 - temp1->seatsCount), RESET);
                        goto SHID;
                    }
                    for (int i = 0; i < quantity; i++)
                    {
                        clear();
                        displaySeats(&temp1);
                        while (1)
                        {
                            printf("\n%s%s Select seat No: %s ", YLW_BG, BLACK_TXT, RESET);
                            scanf("%d", &seatno);
                            if (seatno <= 0 || seatno > 100)
                            {
                                printf("\n%s%s Invalid Seat No. %s\n", RED_BG, WHITE_TXT, RESET);
                                continue;
                            }
                            seatno = seatno - 1;
                            if (temp1->seats[seatno] == 1)
                            {
                                printf("\n%s%s Seat Already Booked Please Select another seat %s\n", RED_BG, WHITE_TXT, RESET);
                            }
                            else
                            {
                                temp1->seats[seatno] = 1;
                                arr[count] = seatno;
                                count++;
                                temp1->seatsCount++;
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
        if (flag == 0)
        {
            printf("\n\n%s%s Invalid ShowId %s\n\n", RED_BG, WHITE_TXT, RESET);
            temp1 = screen1;
            goto SHID;
        }

        clear();
        displaySeats(&temp1);

        for (int i = 0; i < count; i++)
        {
            int tempCount = arr[i] + 1;
            if (tempCount <= 30)
            {
                price3 = temp->price3 + price3;
                displayBill(&temp1, tempCount, name, temp->price3);
            }
            else if (tempCount >= 80)
            {
                price1 = temp->price1 + price1;
                displayBill(&temp1, tempCount, name, temp->price1);
            }
            else if (tempCount > 30 && tempCount < 80)
            {
                price2 = temp->price2 + price2;
                displayBill(&temp1, tempCount, name, temp->price2);
            }
        }

        total = price1 + price2 + price3;
        printf("\n\t%s%s                       TOTAL : %-31d%s\n\n", YLW_BG, BLACK_TXT, total, RESET);
        price1 = 0;
        price2 = 0;
        price3 = 0;
        temp1 = screen1;
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

                    printf("\n%s%s How Many Tickets: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);
                    if (temp2->seatsCount == 100)
                    {
                        printf("\n%s%s Show is Housefull, No seats are available! %s\n", RED_BG, WHITE_TXT, RESET);
                        return;
                    }
                    else if (quantity + temp2->seatsCount > 100)
                    {
                        printf("\n%s%s Only %d seats are available %s\n", RED_BG, WHITE_TXT, (100 - temp2->seatsCount), RESET);
                        goto SHID;
                    }
                    for (int i = 0; i < quantity; i++)
                    {
                        clear();
                        displaySeats(&temp2);
                        while (1)
                        {
                            printf("\n%s%s Select seat No: %s ", YLW_BG, BLACK_TXT, RESET);
                            scanf("%d", &seatno);
                            if (seatno <= 0 || seatno > 100)
                            {
                                printf("\n%s%s Invalid Seat No. %s\n", RED_BG, WHITE_TXT, RESET);
                                continue;
                            }
                            seatno = seatno - 1;
                            if (temp2->seats[seatno] == 1)
                            {
                                printf("\n%s%s Seat Already Booked Please Select another seat %s\n", RED_BG, WHITE_TXT, RESET);
                            }
                            else
                            {
                                temp2->seats[seatno] = 1;
                                arr[count] = seatno;
                                count++;
                                temp2->seatsCount++;
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
        if (flag == 0)
        {
            printf("\n\n%s%s Invalid ShowId %s\n\n", RED_BG, WHITE_TXT, RESET);
            temp2 = screen2;
            goto SHID;
        }

        clear();
        displaySeats(&temp2);
        total = price1 + price2 + price3;
        for (int i = 0; i < count; i++)
        {
            int tempCount = arr[i] + 1;
            if (tempCount <= 30)
            {
                price3 = temp->price3 + price3;
                displayBill(&temp2, tempCount, name, temp->price3);
            }
            else if (tempCount >= 80)
            {
                price1 = temp->price1 + price1;
                displayBill(&temp2, tempCount, name, temp->price1);
            }
            else if (tempCount > 30 && tempCount < 80)
            {
                price2 = temp->price2 + price2;
                displayBill(&temp2, tempCount, name, temp->price2);
            }
        }
        printf("\n\t%s%s                       TOTAL : %-31d%s\n\n", YLW_BG, BLACK_TXT, total, RESET);
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

                    printf("\n%s%s How Many Tickets: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);
                    if (temp2->seatsCount == 100)
                    {
                        printf("\n%s%s Show is Housefull, No seats are available! %s\n", RED_BG, WHITE_TXT, RESET);
                        return;
                    }
                    else if (quantity + temp2->seatsCount > 100)
                    {
                        printf("\n%s%s Only %d seats are available %s\n", RED_BG, WHITE_TXT, (100 - temp2->seatsCount), RESET);
                        goto SHID;
                    }
                    for (int i = 0; i < quantity; i++)
                    {
                        clear();
                        displaySeats(&temp3);
                        while (1)
                        {
                            printf("\n%s%s Select seat No: %s ", YLW_BG, BLACK_TXT, RESET);
                            scanf("%d", &seatno);
                            if (seatno <= 0 || seatno > 100)
                            {
                                printf("\n%s%s Invalid Seat No. %s\n", RED_BG, WHITE_TXT, RESET);
                                continue;
                            }
                            seatno = seatno - 1;
                            if (temp3->seats[seatno] == 1)
                            {
                                printf("\n%s%s Seat Already Booked Please Select another seat %s\n", RED_BG, WHITE_TXT, RESET);
                            }
                            else
                            {
                                temp3->seats[seatno] = 1;
                                arr[count] = seatno;
                                count++;
                                temp3->seatsCount++;
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
        if (flag == 0)
        {
            printf("\n\n%s%s Invalid ShowId %s\n\n", RED_BG, WHITE_TXT, RESET);
            temp3 = screen3;
            goto SHID;
        }
        clear();
        displaySeats(&temp3);
        total = price1 + price2 + price3;
        for (int i = 0; i < count; i++)
        {
            int tempCount = arr[i] + 1;
            if (tempCount <= 30)
            {
                price3 = temp->price3 + price3;
                displayBill(&temp3, tempCount, name, temp->price3);
            }
            else if (tempCount >= 80)
            {
                price1 = temp->price1 + price1;
                displayBill(&temp3, tempCount, name, temp->price1);
            }
            else if (tempCount > 30 && tempCount < 80)
            {
                price2 = temp->price2 + price2;
                displayBill(&temp3, tempCount, name, temp->price2);
            }
        }
        printf("\n\t%s%s                       TOTAL : %-31d%s\n\n", YLW_BG, BLACK_TXT, total, RESET);
    }

    else
    {
        printf("\n%s%s Invalid Screen Number %s", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
}

/*FUNCTION TO CANCEL A SPECIFIED TICKET*/
void cancelTicket()
{
    struct Movie *temp = movieHead;
    struct Screen *temp1;
    struct Screen *temp2;
    struct Screen *temp3;
    int scrno, shid, seatno, quantity;
ScreenNo:
    printf("\n%s%s Enter screen number: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &scrno);
    if (scrno == 1 && screen1 == NULL)
    {
        printf("\n%s%s No shows available on screen I %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else if (scrno == 2 && screen2 == NULL)
    {
        printf("\n%s%s No shows available on screen II %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else if (scrno == 3 && screen3 == NULL)
    {
        printf("\n%s%s No shows available on screen III %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else if (scrno > 3)
    {
        printf("\n\n%s%s Invalid Screen No. %s\n\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
    if (scrno == 1)
    {
        temp1 = screen1;
    }
    if (scrno == 2)
    {
        temp2 = screen2;
    }
    if (scrno == 3)
    {
        temp3 = screen3;
    }
SH:
    printf("\n%s%s Enter showId: %s ", YLW_BG, BLACK_TXT, RESET);
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
                    printf("\n%s%s How Many Tickets You Want To Cancel: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);

                    if (quantity > temp1->seatsCount)
                    {
                        printf("\n%s%s Only %d seats have been booked for the show %s\n", RED_BG, WHITE_TXT, temp1->seatsCount, RESET);
                        continue;
                    }
                    else if (quantity < 1)
                    {
                        printf("\n%s%s Quantity cannot be less then 1 %s\n", RED_BG, WHITE_TXT, RESET);
                        continue;
                    }

                    for (int i = 0; i < quantity; i++)
                    {
                        while (1)
                        {
                        seat:
                            printf("\n%s%s Select seat No: %s ", YLW_BG, BLACK_TXT, RESET);
                            scanf("%d", &seatno);
                            if (seatno <= 0 || seatno > 100)
                            {
                                printf("\n%s%s Invalid Seat No. %s\n", RED_BG, WHITE_TXT, RESET);
                                goto seat;
                            }
                            seatno = seatno - 1;
                            if (temp1->seats[seatno] == 1)
                            {
                                temp1->seats[seatno] = 0;
                                temp1->seatsCount--;
                                break;
                            }
                            else
                            {
                                printf("\n%s%s Enter valid seat number %s\n", RED_BG, WHITE_TXT, RESET);
                                goto seat;
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
        if (flag == 0)
        {
            printf("\n\n%s%s Enter valid showId %s\n", RED_BG, WHITE_TXT, RESET);
            temp1 = screen1;
            goto SH;
        }

        printf("\n\n%s%s SEAT DELETED %s\n\n", GRN_BG, WHITE_TXT, RESET);
        displaySeats(&temp1);
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
                    printf("\n%s%s How Many Tickets You Want To Cancel: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);

                    if (quantity > temp2->seatsCount)
                    {
                        printf("\n%s%s Only %d seats have been booked for the show %s\n", RED_BG, WHITE_TXT, temp2->seatsCount, RESET);
                        continue;
                    }
                    else if (quantity < 1)
                    {
                        printf("\n%s%s Quantity cannot be less then 1 %s\n", RED_BG, WHITE_TXT, RESET);
                        continue;
                    }

                    for (int i = 0; i < quantity; i++)
                    {
                        while (1)
                        {
                            printf("\n%s%s Select seat No: %s ", YLW_BG, BLACK_TXT, RESET);
                            scanf("%d", &seatno);
                            if (seatno <= 0 || seatno > 100)
                            {
                                printf("\n%s%s Invalid Seat No. %s\n", RED_BG, WHITE_TXT, RESET);
                                goto seat;
                            }
                            seatno = seatno - 1;
                            if (temp2->seats[seatno] == 1)
                            {
                                temp2->seats[seatno] = 0;
                                temp2->seatsCount--;
                                break;
                            }
                            else
                            {
                                printf("\n%s%s Enter valid seat number %s\n", RED_BG, WHITE_TXT, RESET);
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
        if (flag == 0)
        {
            printf("\n\n%s%s Enter valid showId %s\n", RED_BG, WHITE_TXT, RESET);
            temp2 = screen2;
            goto SH;
        }

        printf("\n\n%s%s SEAT DELETED %s\n\n", GRN_BG, WHITE_TXT, RESET);
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
                    printf("\n%s%s How Many Tickets You Want To Cancel: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);

                    if (quantity > temp3->seatsCount)
                    {
                        printf("\n%s%s Only %d seats have been booked for the show %s\n", RED_BG, WHITE_TXT, temp3->seatsCount, RESET);
                        continue;
                    }
                    else if (quantity < 1)
                    {
                        printf("\n%s%s Quantity cannot be less then 1 %s\n", RED_BG, WHITE_TXT, RESET);
                        continue;
                    }

                    for (int i = 0; i < quantity; i++)
                    {
                        while (1)
                        {
                            printf("\n%s%s Select seat No: %s ", YLW_BG, BLACK_TXT, RESET);
                            scanf("%d", &seatno);
                            if (seatno <= 0 || seatno > 100)
                            {
                                printf("\n%s%s Invalid Seat No. %s\n", RED_BG, WHITE_TXT, RESET);
                                goto seat;
                            }
                            seatno = seatno - 1;
                            if (temp3->seats[seatno] == 1)
                            {
                                temp3->seats[seatno] = 0;
                                temp3->seatsCount--;
                                break;
                            }
                            else
                            {
                                printf("\n%s%s Enter valid seat number %s\n", RED_BG, WHITE_TXT, RESET);
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
        if (flag == 0)
        {
            printf("\n\n%s%s Enter valid showId %s\n", RED_BG, WHITE_TXT, RESET);
            temp3 = screen3;
            goto SH;
        }

        printf("\n\n%s%s SEAT DELETED %s\n\n", GRN_BG, WHITE_TXT, RESET);
        displaySeats(&temp1);
    }
    else
    {
        printf("\n%s%s Invalid Screen Number %s\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
}

/*FUNCTION TO DISPLAY AVAILABILITY OF SEATS [DISPLAYS SEATS]*/
void showAvailability()
{
    int scrno, shid, flag = 0;
ScreenNo:
    printf("\n%s%s Enter screen number: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &scrno);
    if (scrno == 1 && screen1 == NULL)
    {
        printf("\n%s%s No shows available on screen I %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else if (scrno == 2 && screen2 == NULL)
    {
        printf("\n%s%s No shows available on screen II %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else if (scrno == 3 && screen3 == NULL)
    {
        printf("\n%s%s No shows available on screen  III %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else if (scrno > 3)
    {
        printf("\n\n%s%s Invalid Screen No. %s\n\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
    struct Screen *tempScr = scrno == 1 ? screen1 : scrno == 2 ? screen2
                                                               : screen3;
    printf("\n%s%s Enter Show Id: %s ", YLW_BG, BLACK_TXT, RESET);
    scanf("%d", &shid);
    while (tempScr != NULL)
    {
        if (tempScr->showID == shid)
        {
            flag = 1;
            break;
        }
        tempScr = tempScr->next;
    }

    if (flag == 0)
    {
        printf("\n%s%s Invalid Show Id %s\n", RED_BG, WHITE_TXT, RESET);
        return;
    }
    else
    {
        displaySeats(&tempScr);
    }
}

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
        printf("\n%s%s Invalid Password %s\n", RED_BG, WHITE_TXT, RESET);
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
                setMovie(&movieHead, &screen1, &screen2, &screen3);
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
            showMovies(&movieHead);
            break;
        case 5:
            clear();
            displayShows(&screen1, &screen2, &screen3);
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
            displayShows(&screen1, &screen2, &screen3);
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
            showAvailability();
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
    while (1)
    {
        printf("\n%s%s   MOVIE TICKET BOOKING SYSTEM   %s", BLK_BG, WHITE_TXT, RESET);
        printf("\n%s%s  1. Admin                       %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s  2. User                        %s", WHT_BG, BLACK_TXT, RESET);
        printf("\n%s%s  3. Exit                        %s", BLU_BG, WHITE_TXT, RESET);
        printf("\n%s%s                                 %s", BLK_BG, WHITE_TXT, RESET);
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