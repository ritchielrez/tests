#include <stdlib.h>

#define RIT_STR_IMPLEMENTATION
#include "../rit_str/rit_str.h"

#define nullptr (void *)0

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

rit_str_allocator allocator = {libc_malloc, libc_free, libc_realloc, nullptr};

int main() {
  rit_str *str = rit_str_create("Test", &allocator);
  rit_str_view str_view = rit_str_view_create(str->m_str, 0, str->m_size);
  rit_str_view str_view2 = rit_str_view_create("Hello", 0, 5);
  rit_str *str2 = rit_str_view_concat(&str_view, &str_view2, &allocator);
  rit_str *str3 = rit_str_concat(str, str2, &allocator);
  printf("str: %s, size: %zu \n", str->m_str, str->m_size);
  rit_str_view_print(&str_view);
  printf("\n%s\n", str2->m_str);
  rit_str_free(str, &allocator);

  rit_str *str4 = rit_str_create("John Doe", &allocator);
  rit_str_set(str4, "John Doeeeeeeeeeeeeeeeeeee", &allocator);
  printf("str: %s, size: %zu \n", str4->m_str, str4->m_size);
  return 0;
}