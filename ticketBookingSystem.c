#include <stdio.h>

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
    int seats[15][15];
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
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        displayMovies();
        break;
    case 2:
        bookTicket();
        break;
    default:
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