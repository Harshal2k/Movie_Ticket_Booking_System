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
    int seats[20];
    char dateTime[20];
    struct Screen *next;
} *scree1=NULL, *screen2, *screen3;

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
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayMovies();
            break;
        case 2:
            scree1=bookTicket(scree1);
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

struct Screen *bookTicket(struct Screen *scree1)
{
    struct Screen *temp=scree1;
    struct Screen *sc;
    sc = (struct Screen *)malloc(sizeof(struct Screen));
    int seatNo;
    char userName[50];
    char mobileNo[10];
    displayMovies();
    // printf("\nWhich show would you like to watch\n");
    // scanf(" ");
    // fgets(sc->movie->name, 30, stdin);

    printf("\nEnter your name");
    scanf(" ");
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
    if (scree1==NULL)
    {
        printf("\nHHHHEEERRREEE\n");
        scree1=sc;
        scree1->next=NULL;
        
    }
    else
    {
        
        while (temp->next!=NULL)
        {
            temp=temp->next;
        }
        
        temp->next=sc;
        sc->next=NULL;
        return scree1;
    }
    
    while (temp!=NULL)
    {
        printf("%d ",temp->seats[seatNo]);
        temp=temp->next;
    }
    
    return scree1;
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