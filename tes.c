#include <stdio.h>
#include <time.h>

int main() {
    time_t rawtime;
    struct tm * timeinfo;
    int A;
    FILE *F;
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    printf("time\n%d %d %d %d:%d:%d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    F = fopen("slot.txt", "w");
    fprintf(F, "lala\nlala");
    scanf("%d", &A);
    return 0;
}