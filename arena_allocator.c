#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define nullptr 0

#define DEFAULT_CHUNK_MAX_COUNT 8192

typedef struct Buffer Buffer;
typedef struct Arena Arena;

/// @brief Holds data as uintptr(usually 8 byte) chunks.
///
/// Buffers are just like nodes in a linked list
struct Buffer {
  Buffer *m_next;
  size_t m_chunk_max_count;
  size_t m_chunk_current_count;
  /// holds the actual memory chunks, where user data is stored
  uintptr_t m_data[];
};

/// @brief Creates a new buffer, where chunks of bytes are allocated
/// @param t_chunk_count Maximum number of chunks the buffer can hold
/// @return Buffer*
Buffer *buffer_new(size_t t_chunk_count) {
  size_t size_in_bytes = sizeof(Buffer) + sizeof(uintptr_t) * t_chunk_count;
  Buffer *new_buffer = malloc(size_in_bytes);

  new_buffer->m_next = nullptr;
  new_buffer->m_chunk_max_count = t_chunk_count;
  new_buffer->m_chunk_current_count = 0;

  return new_buffer;
}

/// @brief Frees up a buffer
/// @param t_buffer The buffer to be freed
/// @return void
void buffer_free(Buffer *t_buffer) { free(t_buffer); }

/// @brief Arena is just a growing list of buffers.
///
/// An arena usually looks like this:
/// begin -> next buffer -> active buffer
struct Arena {
  /// contains the starting buffer
  Buffer *begin;
  /// contains the active buffer
  Buffer *end;
};

/// @brief Allocate some data inside an arena.
///
/// The allocated data are stored in a buffer.
/// If the data is too big, a new buffer will be created.
///
/// @param t_arena The arena where data gets allocated
/// @param t_size_in_bytes The requested number of bytes to be allocated
/// @return void*
void *arena_alloc(Arena *t_arena, size_t t_size_in_bytes) {
  // To understand the following code, you need to have proper knowledge about
  // memory alignment. Align the requsted size to 8 bytes
  t_size_in_bytes = t_size_in_bytes + (sizeof(uintptr_t) - 1);
  size_t chunk_count = t_size_in_bytes / sizeof(uintptr_t);

  if (t_arena->end == nullptr) {
    // If there is no active buffer in an arena, there also should not be a
    // starting buffer
    assert(t_arena->begin == nullptr);
    size_t chunk_max_count = DEFAULT_CHUNK_MAX_COUNT;
    if (chunk_max_count < chunk_count) chunk_max_count = chunk_count;
    t_arena->end = buffer_new(chunk_max_count);
    t_arena->begin = t_arena->end;
  }

  void *result = &(t_arena->end->m_data[t_arena->end->m_chunk_current_count]);
  t_arena->end->m_chunk_current_count += chunk_count;
  return result;
}

/// @brief Resets the allocated chunk count of an arena
/// @param t_arena The arena that will be resetted
/// @retrun void
void arena_reset(Arena *t_arena) {
  Buffer *current_buffer = t_arena->begin;
  while (current_buffer != nullptr) {
    current_buffer->m_chunk_current_count = 0;
    current_buffer = current_buffer->m_next;
  }
}

/// @brief Frees up an arena
/// @param t_arena The arena that will be freed
/// @return void
void arena_free(Arena *t_arena) {
  Buffer *current_buffer = t_arena->begin;
  while (current_buffer->m_next != nullptr) {
    Buffer *next_buffer = current_buffer->m_next;
    free(current_buffer);
    current_buffer = next_buffer;
  }

  // Assigning null value to freed pointers is a good practice
  // because this ensures that by accessing any freed pointers
  // does not cause undefined behaviours, even though accessing
  // null values do cause them too, it is more easily debuggable.
  t_arena->begin = nullptr;
  t_arena->end = nullptr;
}

int main() {
  Arena default_arena = {nullptr, nullptr};

  char *str = (char *)arena_alloc(&default_arena, 256);
  strcpy(str, "Hello World!\n");
  printf("%s\n", str);
  // Even though we are accessing memory completely out of the bounds
  // of the region, where the string has been allocated, the statement
  // below yet does not cause any error. This is not still recommended
  // to do though, because this is acttually an undefined behaviour :)
  // str[70000] = nullptr;

  char *str2 = (char *)arena_alloc(&default_arena, DEFAULT_CHUNK_MAX_COUNT * 8);
  size_t i;
  for (i = 0; i < (DEFAULT_CHUNK_MAX_COUNT * 8) - 1; ++i) {
    str2[i] = 'H';
  }
  str2[i] = '\0';
  // strcpy(str2, "Hello World again!\n");
  printf("%s\n", str2);

  char *str3 =
      (char *)arena_alloc(&default_arena, DEFAULT_CHUNK_MAX_COUNT * 10);
  strcpy(str3, "This is getting too much though -.- \n");
  printf("%s\n", str3);

  arena_reset(&default_arena);
  arena_free(&default_arena);

  return 0;
}
