#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void *pointer;
typedef void (*dealloc_fn_t)(pointer);

typedef struct
{
    pointer ptr;
    size_t size_of;
    dealloc_fn_t dealloc_fn;
} unique_ptr_t;

#define NULL_UNIQUE_PTR                                                        \
    (unique_ptr_t) { .ptr = NULL, .size_of = 0, .dealloc_fn = NULL }

static void cleanup_heap_pointer(unique_ptr_t *ptr)
{
    if (ptr->ptr != NULL && ptr->dealloc_fn != NULL)
        ptr->dealloc_fn(ptr->ptr);
    *ptr = NULL_UNIQUE_PTR;
}

void take_ptr_ownership(unique_ptr_t *new_owner, unique_ptr_t *old_owner)
{
    cleanup_heap_pointer(new_owner);
    *new_owner = *old_owner;
    *old_owner = NULL_UNIQUE_PTR;
}

#define SIZEOF(P) P.size_of
#define LEN(TYPE, P) (SIZEOF(P) / sizeof(TYPE))

#define GET_TYPE_CAST_MACRO(_1, _2, NAME, ...) NAME
#define GET_WITH_TYPE_CAST(TYPE, P) ((TYPE *)(P.ptr))
#define GET_WITH_NO_CAST(P) (P.ptr)
#define GET(...)                                                               \
    GET_TYPE_CAST_MACRO(__VA_ARGS__, GET_WITH_TYPE_CAST,                       \
                        GET_WITH_NO_CAST)(__VA_ARGS__)

#define IS_NULL(P) (GET(P) == NULL)

#define ALLOC_SZ(TYPE, SIZE) sizeof(TYPE[SIZE])
#define ALLOC(TYPE, SIZE) ((SIZE) > 0 ? malloc(ALLOC_SZ(TYPE, SIZE)) : NULL)

#define GET_MK_UNQ_MACRO(_1, _2, _3, NAME, ...) NAME
#define MAKE_UNIQUE_WITH_CUSTOM_DELETER(TYPE, SIZE, DELETER)                   \
    (unique_ptr_t)                                                             \
    {                                                                          \
        .ptr = ALLOC(TYPE, SIZE), .size_of = ALLOC_SZ(TYPE, SIZE),             \
        .dealloc_fn = DELETER                                                  \
    }
#define MAKE_UNIQUE_WITH_DEFAULT_DELETER(TYPE, SIZE)                           \
    MAKE_UNIQUE_WITH_CUSTOM_DELETER(TYPE, SIZE, free)

#define MAKE_UNIQUE(...)                                                       \
    GET_MK_UNQ_MACRO(__VA_ARGS__, MAKE_UNIQUE_WITH_CUSTOM_DELETER,             \
                     MAKE_UNIQUE_WITH_DEFAULT_DELETER)(__VA_ARGS__)

#define UNIQUE_PTR                                                             \
    __attribute__((__cleanup__(cleanup_heap_pointer))) unique_ptr_t
#define DECLARE_UNIQUE_PTR(name) UNIQUE_PTR name

const size_t SIZE_OF_ARR = 24;

static void print_ptr_arr(unique_ptr_t *a)
{
    DECLARE_UNIQUE_PTR(tmp_unq_ptr) = NULL_UNIQUE_PTR;
    take_ptr_ownership(&tmp_unq_ptr, a);

    write(STDOUT_FILENO, GET(tmp_unq_ptr), SIZEOF(tmp_unq_ptr));
    putchar('\n');
}

int main(void)
{
    DECLARE_UNIQUE_PTR(a) = MAKE_UNIQUE(char, SIZE_OF_ARR);
    if (IS_NULL(a))
    {
        const char err_msg[]     = "out of mem";
        const size_t err_msg_len = (sizeof err_msg) / (sizeof err_msg[0]);
        write(STDERR_FILENO, err_msg, err_msg_len);
        return EXIT_FAILURE;
    }

    memcpy(GET(a), "Hello, World!", sizeof("Hello, World!"));

    print_ptr_arr(&a);
    return EXIT_SUCCESS;
}
