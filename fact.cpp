#include <iostream>

#define SHIFT_ARGS(argc, argv)                                                 \
    do                                                                         \
    {                                                                          \
        --argc;                                                                \
        ++argv;                                                                \
    } while (0)

int fact(int f)
{
    if (f <= 1)
        return 1;
    return f * fact(f - 1);
}

void usage()
{
    std::cout << __FILE_NAME__ << " <number>, [Optional: <number>, ... ]" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        usage();
        return 1;
    }
    SHIFT_ARGS(argc, argv);

    for (int i = 0; i < argc; ++i)
    {
        std::cout << fact(std::atoi(argv[i])) << std::endl;
    }
    return 0;
}
