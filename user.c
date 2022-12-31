#include <stdio.h>
#include <stdlib.h>

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
void printTicket(struct Screen **shead, int seatNo, char name[], int price)
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
                printTicket(&temp1, tempCount, name, temp->price3);
            }
            else if (tempCount >= 80)
            {
                price1 = temp->price1 + price1;
                printTicket(&temp1, tempCount, name, temp->price1);
            }
            else if (tempCount > 30 && tempCount < 80)
            {
                price2 = temp->price2 + price2;
                printTicket(&temp1, tempCount, name, temp->price2);
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
        for (int i = 0; i < count; i++)
        {
            int tempCount = arr[i] + 1;
            if (tempCount <= 30)
            {
                price3 = temp->price3 + price3;
                printTicket(&temp2, tempCount, name, temp->price3);
            }
            else if (tempCount >= 80)
            {
                price1 = temp->price1 + price1;
                printTicket(&temp2, tempCount, name, temp->price1);
            }
            else if (tempCount > 30 && tempCount < 80)
            {
                price2 = temp->price2 + price2;
                printTicket(&temp2, tempCount, name, temp->price2);
            }
        }
        total = price1 + price2 + price3;
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
        for (int i = 0; i < count; i++)
        {
            int tempCount = arr[i] + 1;
            if (tempCount <= 30)
            {
                price3 = temp->price3 + price3;
                printTicket(&temp3, tempCount, name, temp->price3);
            }
            else if (tempCount >= 80)
            {
                price1 = temp->price1 + price1;
                printTicket(&temp3, tempCount, name, temp->price1);
            }
            else if (tempCount > 30 && tempCount < 80)
            {
                price2 = temp->price2 + price2;
                printTicket(&temp3, tempCount, name, temp->price2);
            }
        }
        total = price1 + price2 + price3;
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
    if (scrno == 1)
    {
        int flag = 0;

        while (temp1 != NULL)
        {
            while (1)
            {

                if (shid == temp1->showID)
                {
                    if (temp1->seatsCount == 0)
                    {
                        printf("\n%s%s No seats has been booked yet! %s\n", RED_BG, WHITE_TXT, RESET);
                        return;
                    }
                    printf("\n%s%s How Many Tickets You Want To Cancel: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);

                    if (quantity > temp1->seatsCount)
                    {
                        printf("\n%s%s Only %d seats have been booked for the show %s\n", RED_BG, WHITE_TXT, temp1->seatsCount, RESET);
                        return;
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
    else if (scrno == 2)
    {
        int flag = 0;

        while (temp2 != NULL)
        {
            while (1)
            {

                if (shid == temp2->showID)
                {
                    if (temp2->seatsCount == 0)
                    {
                        printf("\n%s%s No seats has been booked yet! %s\n", RED_BG, WHITE_TXT, RESET);
                        return;
                    }
                    printf("\n%s%s How Many Tickets You Want To Cancel: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);

                    if (quantity > temp2->seatsCount)
                    {
                        printf("\n%s%s Only %d seats have been booked for the show %s\n", RED_BG, WHITE_TXT, temp2->seatsCount, RESET);
                        return;
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
        displaySeats(&temp2);
    }
    else if (scrno == 3)
    {
        int flag = 0;

        while (temp3 != NULL)
        {
            while (1)
            {

                if (shid == temp3->showID)
                {
                    if (temp3->seatsCount == 0)
                    {
                        printf("\n%s%s No seats has been booked yet! %s\n", RED_BG, WHITE_TXT, RESET);
                        return;
                    }
                    printf("\n%s%s How Many Tickets You Want To Cancel: %s ", YLW_BG, BLACK_TXT, RESET);
                    scanf("%d", &quantity);

                    if (quantity > temp3->seatsCount)
                    {
                        printf("\n%s%s Only %d seats have been booked for the show %s\n", RED_BG, WHITE_TXT, temp3->seatsCount, RESET);
                        return;
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
        displaySeats(&temp3);
    }
    else
    {
        printf("\n%s%s Invalid Screen Number %s\n", RED_BG, WHITE_TXT, RESET);
        goto ScreenNo;
    }
}

/*FUNCTION TO DISPLAY AVAILABILITY OF SEATS [DISPLAYS SEATS]*/
void showSeatsAvailability()
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