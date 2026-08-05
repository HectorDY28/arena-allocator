<pre>
 █████╗ ██████╗ ███████╗███╗ ██╗ █████╗
██╔══██╗██╔══██╗██╔════╝████╗ ██║██╔══██╗ v0.1.0 // SECTOR-01
███████║██████╔╝█████╗ ██╔██╗ ██║███████║ ARCH: x86_64 LINUX
██╔══██║██╔══██╗██╔══╝ ██║╚██╗██║██╔══██║ MEM: 1MB ARENA
██║ ██║██║ ██║███████╗██║ ╚████║██║ ██║ STATUS: [ONLINE]
╚═╝ ╚═╝╚═╝ ╚═╝╚══════╝╚═╝ ╚═══╝╚═╝ ╚═╝
> github.com/HectorDY28/arena-allocator
</pre>

> **CORE DUMP:** `mmap() > malloc()` // NO FRAGMENTATION // O(1) ALLOC

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Status](https://img.shields.io/badge/STATUS-ONLINE-00FF00?style=for-the-badge)

---

#### ▓█  SYSTEM OVERVIEW

```
┌──────────────────────────────────────────────────┐
│ MAINFRAME: ARENA SUBSYSTEM │
│ MODE: BUMP ALLOCATOR / LINEAR │
│ DESC: ONE MMAP. BUMP POINTER. ONE MUNMAP. │
└──────────────────────────────────────────────────┘
```

Ideal for game loops, compilers, request scopes. 10-100x faster than `malloc` for short-lived data.

#### ▓█  SPEC SHEET

| REGISTER | VALUE |
| :--- | :--- |
| **BACKEND** | `sys/mman.h` `MAP_PRIVATE \| MAP_ANON` |
| **ALIGNMENT** | 16-BYTE ` (size+15) & ~15` |
| **ALLOC** | `O(1)` - `return buffer + offset` |
| **FREE** | `O(1)` - `munmap()` all at once |
| **FOOTPRINT** | < 70 LOC |

#### ▓█  MEMORY MAP

```c
0x00000000 ┌─────────────────┐
           │ Arena Header │ -> buffer*, size, offset
0x00000010 ├─────────────────┤
           │ │
           │ FREE SPACE │ <- offset bumps here
           │ │
0x00000400 ├─────────────────┤
           │ ALLOC  │ <- arena_alloc(64)
0x00000440 ├─────────────────┤
           │ ALLOC  │
0x00100000 └─────────────────┘ <- munmap()
```

#### ▓█ BOOT SEQUENCE

```bash
$ make run
[BIOS] CHECKING MEMORY... OK
[KRNL] MMAP 1048576 BYTES @ 0x7F8A1C000000... OK
[ARENA] ALLOC TEST... OK
> ARENA FUNCIONANDO!
[ARENA] MUNMAP... OK - 0 LEAKS DETECTED
[SYSTEM] HALT CODE 0
```

#### ▓█ INSTRUCTION SET

```c
#include "arena.h"

Arena arena;
arena_init(&arena, 1024 * 1024); // [INIT] reserve 1MB

char *msg = arena_alloc(&arena, 128); // [ALLOC] bump pointer
int *data = arena_alloc(&arena, 256);

arena_destroy(&arena); // [DESTROY] munmap
```

#### ▓█ LICENSE

```
MIT LICENSE // (c) 2026 HectorDY28
REBUILD AFTER TOTAL LOSS OF PREVIOUS MAINFRAME.
BACK BETTER.
```

> _END OF TRANSMISSION_ █
