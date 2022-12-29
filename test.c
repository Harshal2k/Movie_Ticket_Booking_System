#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\033[48;5;9m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\033[38;5;15m"
#define RESET "\033[0m"

int main()
{
    printf("%s%sred%s\n", KRED,KWHT,RESET);
    printf("%sgreen\n", KGRN);
    printf("%syellow\n", KYEL);
    printf("%sblue\n", KBLU);
    printf("%smagenta\n", KMAG);
    printf("%scyan\n", KCYN);
    printf("%swhite\n", KWHT);
    printf("%snormal\n", KNRM);

    return 0;
}