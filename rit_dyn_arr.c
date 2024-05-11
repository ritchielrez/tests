#include "../rit_dyn_arr/rit_dyn_arr.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARENA_ALLOCATOR_IMPLEMENTATION
#include "../arena_allocator/arena_allocator.h"

#define nullptr (void *)0

#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void *arena_allocator_alloc(void *t_arena, size_t t_size_in_bytes) {
  return arena_alloc((Arena *)t_arena, t_size_in_bytes);
}
void arena_allocator_free(void *t_arena, void *t_ptr) {
  (void)t_ptr;
  arena_free(t_arena);
}
void *arena_allocator_realloc(void *t_arena, void *t_old_ptr,
                              size_t t_old_size_in_bytes,
                              size_t t_new_size_in_bytes) {
  return arena_realloc((Arena *)t_arena, t_old_ptr, t_old_size_in_bytes,
                       t_new_size_in_bytes);
}

void *libc_malloc(void *t_ctx, size_t t_size_in_bytes) {
  (void)t_ctx;
  return malloc(t_size_in_bytes);
}

void libc_free(void *t_ctx, void *t_ptr) {
  (void)t_ctx;
  free(t_ptr);
}

void *libc_realloc(void *t_ctx, void *t_old_ptr, size_t t_old_size_in_bytes,
                   size_t t_new_size_in_bytes) {
  (void)t_ctx;
  (void)t_old_size_in_bytes;
  return realloc(t_old_ptr, t_new_size_in_bytes);
}

#define rit_dyn_arr_for_each(t_it, t_rit_dyn_arr)    \
  for (typeof(rit_dyn_arr_begin(t_rit_dyn_arr)) it = \
           rit_dyn_arr_begin(t_rit_dyn_arr);         \
       it < rit_dyn_arr_end(t_rit_dyn_arr); it++)

int main() {
  Arena arena = {nullptr, nullptr};
  rit_dyn_arr_allocator ctx_allocator = {libc_malloc, libc_free, libc_realloc,
                                         nullptr};

  rit_dyn_arr(int, arr, 10, &ctx_allocator);
  for (int i = 0; i < 10; ++i) {
    rit_dyn_arr_set(arr, i, i + 1);
    printf("%d\n", rit_dyn_arr_at(arr, i));
  }
  rit_dyn_arr_push_back(arr, 11, &ctx_allocator);
  rit_dyn_arr_pop_back(arr);
  rit_dyn_arr_insert(arr, 2, 69, &ctx_allocator);
  rit_dyn_arr_erase(arr, 1);
  rit_dyn_arr_resize(arr, 3, 0, &ctx_allocator);
  for (int *it = rit_dyn_arr_begin(arr); it < rit_dyn_arr_end(arr); it++) {
    printf("%d\n", *it);
  }
  printf("1st element: %d, last element: %d\n", rit_dyn_arr_front(arr),
         rit_dyn_arr_back(arr));
  rit_dyn_arr_clear(arr);
  printf("arr.empty() = %d\n", rit_dyn_arr_empty(arr));

  printf("size: %zu, capacity: %zu\n", rit_dyn_arr_size(arr),
         rit_dyn_arr_capacity(arr));

  rit_dyn_arr(int, arr2, 10, &ctx_allocator);
  for (int *it = rit_dyn_arr_begin(arr2); it < rit_dyn_arr_end(arr2); it++) {
    *it = 0;
  }

  for (int *it = rit_dyn_arr_begin(arr); it < rit_dyn_arr_end(arr); it++) {
    printf("%d ", *it);
  }
  rit_dyn_arr_resize(arr, 30, 1, &ctx_allocator);
  printf("\n[Before swap]\n1st array: \n");
  for (int *it = rit_dyn_arr_begin(arr); it < rit_dyn_arr_end(arr); it++) {
    printf("%d ", *it);
  }
  printf("\n2nd array: \n");
  for (int *it = rit_dyn_arr_begin(arr2); it < rit_dyn_arr_end(arr2); it++) {
    printf("%d ", *it);
  }
  rit_dyn_arr_swap(&arr, &arr2);
  printf("\n[After swap]\n1st array: \n");
  rit_dyn_arr_for_each(it, arr) { printf("%d ", *it); }
  printf("\n2nd array: \n");
  rit_dyn_arr_for_each(it, arr2) { printf("%d ", *it); }

  rit_dyn_arr(int, arr3, 0, &ctx_allocator);
  rit_dyn_arr_copy(arr, arr3, &ctx_allocator);
  printf("\n3rd array(copy of the 1st one): \n");
  rit_dyn_arr_for_each(it, arr3) { printf("%d ", *it); }
}