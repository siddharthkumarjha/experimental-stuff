#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void cleanup_heap_pointer(void *ptr)
{
    void **ptr_indirection = (void **)ptr;
    if (*ptr_indirection)
        free(*ptr_indirection);
}

#define UNIQUE_PTR(type)                                                       \
    __attribute__((__cleanup__(cleanup_heap_pointer))) type *
#define DECLARE_UNIQUE_PTR(type, name) UNIQUE_PTR(type) name
#define TAKE_PTR_OWNERSHIP(NEW_OWNER, OLD_OWNER)                               \
    do                                                                         \
    {                                                                          \
        NEW_OWNER = OLD_OWNER;                                                 \
        OLD_OWNER = NULL;                                                      \
    } while (0);

const size_t SIZE_OF_ARR = 24;

static void print_ptr_arr(int **a)
{
    DECLARE_UNIQUE_PTR(int, tmp_unq_ptr) = NULL;
    TAKE_PTR_OWNERSHIP(tmp_unq_ptr, *a);

    for (int i = 0; i < SIZE_OF_ARR; ++i)
        printf("%d ", tmp_unq_ptr[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    DECLARE_UNIQUE_PTR(int, a) = malloc(sizeof(int[SIZE_OF_ARR]));
    if (!a)
        return ENOMEM;

    for (int i = 0; i < SIZE_OF_ARR; ++i)
        a[i] = i;

    print_ptr_arr(&a);
    return EXIT_SUCCESS;
}
