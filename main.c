#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

int main(void)
{
    Arena arena;

    arena_init(&arena, 1024 * 1024);

    if (arena.buffer == NULL) {
        fprintf(stderr, "Falha ao criar arena.\n");
        return EXIT_FAILURE;
    }

    printf("[*] Arena criada em %p\n", (void *)arena.buffer);

    char *msg = arena_alloc(&arena, 64);
    int *nums = arena_alloc(&arena, 10 * sizeof(*nums));

    if (msg == NULL || nums == NULL) {
        fprintf(stderr, "Falha na alocacao.\n");
        arena_destroy(&arena);
        return EXIT_FAILURE;
    }

    snprintf(msg, 64, "Arena funcionando!");

    for (int i = 0; i < 10; i++)
        nums[i] = i;

    printf("[+] %s\n", msg);
    printf("[+] Memoria usada: %zu / %zu bytes\n",
           arena.offset,
           arena.size);

    arena_destroy(&arena);

    printf("[*] Arena destruida.\n");

    return EXIT_SUCCESS;
}
