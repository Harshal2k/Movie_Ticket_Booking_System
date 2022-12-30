#include <stdio.h>
#include <stdlib.h>
/*FUNCTION TO CLEAR THE CONSOLE*/
void clear()
{
    system("clear");
}

void printBillboard()
{
    for (int i = 1; i < 44; i++)
    {
        printf("%s  ", i % 2 == 0 ? YLW_BG : BLU_BG);
    }
    printf("%s\n", RESET);
    printf("%s  %s%s  __     _____   _______  _______             _______  _______  _______  _______  %s  %s", YLW_BG, BLK_BG, WHITE_TXT, YLW_BG, RESET);
    printf("\n%s  %s%s /  \\   / ___ \\ / ___   )(  __   )  |\\     /|(  ___  )(  ____ \\(  ____ \\(  ___  ) %s  %s", BLU_BG, BLK_BG, WHITE_TXT, BLU_BG, RESET);
    printf("\n%s  %s%s \\/) ) ( (   ) )\\/   )  || (  )  |  | )   ( || (   ) || (    \\/| (    \\/| (   ) | %s  %s", YLW_BG, BLK_BG, WHITE_TXT, YLW_BG, RESET);
    printf("\n%s  %s%s   | | ( (___) |    /   )| | /   |  | |   | || (___) || (_____ | |      | |   | | %s  %s", BLU_BG, BLK_BG, WHITE_TXT, BLU_BG, RESET);
    printf("\n%s  %s%s   | |  \\____  |  _/   / | (/ /) |  ( (   ) )|  ___  |(_____  )| |      | |   | | %s  %s", YLW_BG, BLK_BG, WHITE_TXT, YLW_BG, RESET);
    printf("\n%s  %s%s   | |       ) | /   _/  |   / | |   \\ \\_/ / | (   ) |      ) || |      | |   | | %s  %s", BLU_BG, BLK_BG, WHITE_TXT, BLU_BG, RESET);
    printf("\n%s  %s%s __) (_/\\____) )(   (__/\\|  (__) |    \\   /  | )   ( |/\\____) || (____/\\| (___) | %s  %s", YLW_BG, BLK_BG, WHITE_TXT, YLW_BG, RESET);
    printf("\n%s  %s%s \\____/\\______/ \\_______/(_______)     \\_/   |/     \\|\\_______)(_______/(_______) %s  %s", BLU_BG, BLK_BG, WHITE_TXT, BLU_BG, RESET);
    printf("\n%s  %s%s                                                                                  %s  %s\n", YLW_BG, BLK_BG, WHITE_TXT, YLW_BG, RESET);
    for (int i = 1; i < 44; i++)
    {
        printf("%s  ", i % 2 == 0 ? YLW_BG : BLU_BG);
    }
    printf("%s\n", RESET);
}
