 /* 
  * -std=c89 
  *  K&R style C code.
  *  Deprecated in favor of ANSI style C code
  */

#include <stdlib.h>
#include <stdio.h>

void shift_args();

int main(argc, argv)
int argc;
char *argv[];
{
    printf("prog name: %s\n", argv[0]);
    shift_args(&argc, &argv);
    printf("Num of args provided: %d\n", argc);
    while (argc > 0)
    {
        printf("provided: %s\n", argv[0]);
        shift_args(&argc, &argv);
    }
    return EXIT_SUCCESS;
}

void shift_args(argc, argv)
int *argc;
char **argv[];
{
    --(*argc);
    ++(*argv);
}
