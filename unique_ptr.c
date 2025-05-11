#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef void *pointer;
typedef void (*dealloc_fn_t)(pointer);

typedef struct unique_ptr_t
{
    pointer ptr;
    dealloc_fn_t dealloc_fn;
} unique_ptr_t;

static void cleanup_heap_pointer(unique_ptr_t *ptr)
{
    if (ptr->ptr != NULL && ptr->dealloc_fn != NULL)
        ptr->dealloc_fn(ptr->ptr);
}

#define GET_TYPE_CAST_MACRO(_1, _2, NAME, ...) NAME
#define GET_WITH_TYPE_CAST(type, P) ((type *)(P.ptr))
#define GET_WITH_NO_CAST(P) (P.ptr)
#define GET(...)                                                               \
    GET_TYPE_CAST_MACRO(__VA_ARGS__, GET_WITH_TYPE_CAST,                       \
                        GET_WITH_NO_CAST)(__VA_ARGS__)

#define NULL_UNIQUE_PTR                                                        \
    (unique_ptr_t) { .ptr = NULL, .dealloc_fn = NULL }

#define GET_MK_UNQ_MACRO(_1, _2, _3, NAME, ...) NAME
#define ALLOC(type, size) ((size) > 0 ? malloc(sizeof(type[size])) : NULL)
#define MAKE_UNIQUE_WITH_CUSTOM_DELETER(type, size, deleter)                   \
    (unique_ptr_t) { .ptr = ALLOC(type, size), .dealloc_fn = deleter }
#define MAKE_UNIQUE_WITH_DEFAULT_DELETER(type, size)                           \
    (unique_ptr_t) { .ptr = ALLOC(type, size), .dealloc_fn = free }
#define MAKE_UNIQUE(...)                                                       \
    GET_MK_UNQ_MACRO(__VA_ARGS__, MAKE_UNIQUE_WITH_CUSTOM_DELETER,             \
                     MAKE_UNIQUE_WITH_DEFAULT_DELETER)(__VA_ARGS__)

#define UNIQUE_PTR                                                             \
    __attribute__((__cleanup__(cleanup_heap_pointer))) unique_ptr_t
#define DECLARE_UNIQUE_PTR(name) UNIQUE_PTR name

#define TAKE_PTR_OWNERSHIP(NEW_OWNER, OLD_OWNER)                               \
    do                                                                         \
    {                                                                          \
        cleanup_heap_pointer(&NEW_OWNER);                                      \
        NEW_OWNER = OLD_OWNER;                                                 \
        OLD_OWNER = NULL_UNIQUE_PTR;                                           \
    } while (0);

const size_t SIZE_OF_ARR = 24;

static void print_ptr_arr(unique_ptr_t *a)
{
    DECLARE_UNIQUE_PTR(tmp_unq_ptr) = NULL_UNIQUE_PTR;
    TAKE_PTR_OWNERSHIP(tmp_unq_ptr, *a);

    for (size_t i = 0; i < SIZE_OF_ARR; ++i)
        printf("%d ", GET(int, tmp_unq_ptr)[i]);
    printf("\n");
}

int main(void)
{
    DECLARE_UNIQUE_PTR(a) = MAKE_UNIQUE(int, SIZE_OF_ARR);
    if (!GET(a))
    {
        const char err_msg[]     = "out of mem";
        const size_t err_msg_len = (sizeof err_msg) / (sizeof err_msg[0]);
        write(STDERR_FILENO, err_msg, err_msg_len);
    }

    for (size_t i = 0; i < SIZE_OF_ARR; ++i)
        GET(int, a)[i] = i;

    print_ptr_arr(&a);
    return EXIT_SUCCESS;
}
