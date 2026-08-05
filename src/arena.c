void arena_init(Arena *a, size_t size)
{
    a->buffer = mmap(NULL,
                     size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1,
                     0);

    if (a->buffer == MAP_FAILED) {
        a->buffer = NULL;
        a->size = 0;
        a->offset = 0;
        return;
    }

    a->size = size;
    a->offset = 0;
}

void *arena_alloc(Arena *a, size_t size)
{
    if (size == 0)
        return NULL;

    size = (size + 15) & ~15;

    if (size > a->size - a->offset)
        return NULL;

    void *ptr = (char *)a->buffer + a->offset;

    a->offset += size;

    return ptr;
}

void arena_destroy(Arena *a)
{
    if (a->buffer)
        munmap(a->buffer, a->size);

    a->buffer = NULL;
    a->size = 0;
    a->offset = 0;
}
