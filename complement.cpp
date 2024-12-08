#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
void swap(void *arg1, void *arg2)
{
        char arg3 = *(char *)arg2;
        *(char *)arg2 = *(char *)arg1;
        *(char *)arg1 = arg3;
}
char * comp(char * arg)
{
        int16_t start = 0;
        int16_t size = strlen(arg);
        int16_t stop = size-1;
        char *rizz = (char *)calloc(size, sizeof(char));
        while(start < stop)
        {
                swap(&arg[start++], &arg[stop--]);
        }
        stop = size-1;
        for(start = 0; start <= stop; start++)
        {
                switch(arg[start])
                {
                        case 'A':
                        rizz[start] = 'C';
                        break;
                        case 'C':
                        rizz[start] = 'A';
                        break;
                        case 'G':
                        rizz[start] = 'T';
                        break;
                        case 'T':
                        rizz[start] = 'G';
                }
        }
        rizz[start] = '\0';
        return rizz;
}
int main(void)
{
        char c[] = "GGGACCTA";
        printf("%s\n", comp(c));
        return 0;
}
