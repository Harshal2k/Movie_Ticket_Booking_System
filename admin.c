#include <stdio.h>
#include <stdlib.h>
/*FUNCTION TO PRINT LIST OF AVAILABLE MOVIES*/
void displayMovieList(struct Movie **head)
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
void displayAllShows(struct Screen **sHead1, struct Screen **sHead2, struct Screen **sHead3)
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
void addMovie(struct Movie **head, struct Screen **sHead1, struct Screen **sHead2, struct Screen **sHead3)
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
        char romanNum[4];
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
    int removeFlag = 0, movieExists = 0;
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
                movieExists = 1;
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

        if (movieExists == 0)
        {
            printf("\n%s%s Movie %s has not been added %s\n", RED_BG, WHITE_TXT, movieName, RESET);
        }
    }
}
