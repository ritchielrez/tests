#include <stdio.h>
#include <string.h>

#define ARENA_IMPLEMENTATION
#include "./arena.h"

int main() {
  Arena default_arena = {0};
  Arena new_arena = {0};

  arena_alloc(&default_arena, 1024);
  arena_alloc(&default_arena, 8192 * 10);
  // arena_realloc(&new_arena, &default_arena, 1024 + 8192 * 10, 8192 * 100);

  char *my_str = arena_alloc(&default_arena, 13);
  strcpy(my_str,
         "Hello World!\n");  // even though we only allocated space for "Hello
                             // World\n", the actual arena region is bigger
  printf("%s\n", my_str);

  arena_reset(&new_arena);
  arena_reset(&default_arena);

  arena_free(&new_arena);
  arena_free(&default_arena);

  return 0;
}
