#include <stdio.h>
#include <string.h>
struct Movie
{
    char name[30];
    int durationMin;
};

struct Screen
{
    int screenNum;
    int showID;
    struct Movie *movie;
    int seats[15];
    char dateTime[20];
    struct Screen *next;
};

void admin()
{

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
    scanf("%d",&choice);
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
    struct Movie *u1=(struct Movie *)malloc(sizeof(struct Movie));
    struct Screen *sc=(struct Screen *)malloc(sizeof(struct Screen));
    int seatNo;
    char movieName[50];
    char userName[50];
    char mobileNo[10];
    displayMovies();
    printf("\nWhich show would you like to watch");
    fgets(u1->name, 30, stdin);

    printf("\nEnter your name\n");
    fgets(userName, 30, stdin);

    printf("\nEnter your 10 digit mobile number\n");
    fgets(mobileNo, 30, stdin);
    int len=strlen(mobileNo);
    if (len> 10 )   
    {
       printf("\nInvalid mobile number\nPlease re-enter mobile no\n");
       fgets(mobileNo, 30, stdin);
    }
    displaySeats();
    printf("\nSelect seat no: ");
    scanf("%d",&seatNo);
    if (sc->seats[seatNo]==1)
    {
        printf("\nSeat already booked\n");
        printf("Please Select another seat\n");
        scanf("%d",seatNo);
        sc->seats[seatNo]=1;
    }
    else
    {
        sc->seats[seatNo]=1;
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

void extraFunction1()
{
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