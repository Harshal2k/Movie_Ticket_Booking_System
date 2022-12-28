#include <stdio.h>
#include <string.h>
struct Movie
{
    char name[30];
    int durationMin;
    int screen1;
    int screen2;
    int screen3;
};

struct Screen
{
    int screenNum;
    int showID;
    struct Movie *movie;
    int seats[15];
    int day;
    int month;
    int year;
    struct Screen *next;
} *screen1, *screen2, *screen3;

void admin()
{
    char password[20];
    printf("\nEnter Admin Password:");
    scanf(" ");
    gets(password, 20, stdin);
    if (0 != strcmp(password, "harshal2k"))
    {
        printf("\nInvalid Password");
        return;
    }
    int option;
    printf("\n****WELCOME ADMIN****");
    printf("\n1. Add Movie");
    printf("\n2. Remove Movie");
    printf("\n3. Remove Show");
    printf("\n4. Exit");
    switch (option)
    {
    case 1:
        char movieName[30];
        printf("\nEnter Movie Name: ");
        scanf(" ");
        gets(movieName, 30, stdin);
        int dd, mm, yy;
        printf("Enter date (DD/MM/YYYY format): ");
        scanf("%d/%d/%d", &dd, &mm, &yy);
        setMovie();
        break;
    case 2:
        removeMovie();
        break;

    default:
        break;
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
        scanf("%d ", &choice);
        fflush(stdin);
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

void setMovie()
{
}

void removeMovie()
{
}

void displaySeats()
{
}

void displayMovies()
{
}

void bookTicket()
{

    struct Screen *sc = (struct Screen *)malloc(sizeof(struct Screen));
    int seatNo;
    char movieName[50];
    char userName[50];
    char mobileNo[10];
    displayMovies();
    printf("\nWhich show would you like to watch");
    fgets(sc->movie->name, 30, stdin);

    printf("\nEnter your name\n");
    fgets(userName, 30, stdin);

    while (1)
    {
        printf("\nEnter your 10 digit mobile number\n");
        fgets(mobileNo, 30, stdin);
        int len = strlen(mobileNo);

        if (len == 11)
        {

            break;
        }
        else
        {
            printf("Invalid Mobile n0\n");
        }
    }

    displaySeats();
    while (1)
    {
        printf("\nEnter Seat No. : ");
        scanf("%d", &seatNo);
        if (sc->seats[seatNo] == 0)
        {
            sc->seats[seatNo] = 1;
            break;
        }
        else
        {
            printf("Seat Already Booked... Please select another seat :)");
        }
    }
}

void cancelTicket()
{
}

void showsAvailable()
{
}

void bookedShows()
{
}

void isDateValid(int dd, int mm, int yy)
{
    // check year
    if (yy >= 1900 && yy <= 9999)
    {
        // check month
        if (mm >= 1 && mm <= 12)
        {
            // check days
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
                printf("Date is valid.\n");
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                printf("Date is valid.\n");
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
                printf("Date is valid.\n");
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
                printf("Date is valid.\n");
            else
                printf("Day is invalid.\n");
        }
        else
        {
            printf("Month is not valid.\n");
        }
    }
    else
    {
        printf("Year is not valid.\n");
    }

    return 0;
}

void extraFunction2()
{
}

void extraFunction3()
{
}

void extraFunction4()
{
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
            printf("\n In Admin");
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