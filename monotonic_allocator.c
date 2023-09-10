#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define nullptr 0

typedef uint8_t bytes;

// NOTE: A monotonic allocator first allocates a buffer and stores the current
// free position of it in a variable. This variable is incremented when
// some memory is allocated in the buffer. A monotonic allocator cannot
// deallocate some specific chunk of memory, because you have to deallocate
// the whole buffer in a monotonic allocator. It is indeed a simple allocator,
// but performant because of it's simplicity, pre-defined max capacity and
// no frequent deallocation operations.
typedef struct {
  bytes *m_buffer;
  size_t m_capacity;
  size_t m_current;
} MonotonicAllocator;

MonotonicAllocator MonotonicAllocatorInit(size_t t_capacity) {
  MonotonicAllocator allocator = {
      .m_buffer = (bytes *)malloc(sizeof(bytes) * t_capacity),
      .m_capacity = t_capacity,
      .m_current = 0};
  return allocator;
}

void MonotonicAllocatorFree(void *t_buffer) { free(t_buffer); }

void *alloc(MonotonicAllocator *t_allocator, size_t t_size) {
  if (t_allocator->m_current + t_size > t_allocator->m_capacity) {
    return nullptr;
  }

  void *ptr = t_allocator->m_buffer + t_allocator->m_current;
  t_allocator->m_current += t_size;
  return ptr;
}

void release(MonotonicAllocator *t_allocator) { t_allocator->m_current = 0; }

// NOTE: No-op function, as this allocator cannot free up individual chunks
void free(void *ptr) { (void *)ptr; }

int main() {
  // MonotonicAllocator allocator = {
  //     .m_buffer = (bytes *)malloc(sizeof(bytes) * 1024),
  //     .m_capacity = 1024,
  //     .m_current = 0};
  MonotonicAllocator allocator = MonotonicAllocatorInit(1024);

  bytes *buffer = (bytes *)alloc(&allocator, 1);

  // NOTE: Here is the thing, we only allocated only one byte for this buffer,
  // but actually this buffer pointer has access to the whole monotonic
  // allocator buffer.
  for (int i = 0; i < 1024; ++i) {
    buffer[i] = 'A';
    printf("%d\n", buffer[i]);
  }
  printf("\n");

  MonotonicAllocatorFree(allocator.m_buffer);

  // free(allocator.m_buffer);
  assert(false);
  return 0;
}
