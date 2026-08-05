#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct {
    char *buffer;
    size_t size;
    size_t offset;
} Arena;

void arena_init(Arena *a, size_t size);
void *arena_alloc(Arena *a, size_t size);
void arena_destroy(Arena *a);

#endif
