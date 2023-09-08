#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define nullptr 0

#define HEAP_CAPACITY 24
typedef unsigned char bytes;
bytes heap[HEAP_CAPACITY] = {0};
bytes mem_block[sizeof(uintptr_t)] = {0};

#define ARENA_CAPACITY 8192

typedef struct {
    size_t size;
} MetaData;

// TODO: Is memory alignment even neccasary here
size_t my_malloc(size_t t_size_bytes) { 
    srand((unsigned)time(NULL));
    //MetaData metadata;
    //metadata.size = t_size_bytes;
    MetaData* metadata = (MetaData*)malloc(sizeof(MetaData));
    uintptr_t metadata_addr = (uintptr_t)metadata;
    assert(metadata);
    metadata->size = t_size_bytes;

    printf("%p\n", metadata);
    printf("%p\n", metadata_addr);

    //size_t metadata_heap_start_addr = rand() % HEAP_CAPACITY;
    size_t metadata_heap_start_addr = 0;
    size_t metadata_heap_end_addr = metadata_heap_start_addr + sizeof(void*);

    //bytes mem_block[sizeof(void*)];

    // Allocate space for the metadata structure first
    bytes metadata_addr_in_bytes[sizeof(uintptr_t)];
    
    for (size_t i = 0; i < sizeof(uintptr_t); ++i) {
      metadata_addr_in_bytes[i] = (metadata_addr >> i) & 0xFF;
    }

    // Allocate the memory now that the user requested
    for (size_t i = metadata_heap_end_addr;
         i < metadata_heap_end_addr + t_size_bytes; ++i) {
      heap[i] = 'A';
    }

    return metadata_heap_end_addr;
}

void my_free(size_t t_addr) {
    size_t metadata_heap_start_addr = t_addr - sizeof(void*);
    uintptr_t metadata_reconstructed_addr = nullptr;

    for (size_t i = metadata_heap_start_addr; i < t_addr; ++i) {
      metadata_reconstructed_addr <<= 8;
      metadata_reconstructed_addr |= heap[i];
    }

    printf("%p\n", metadata_reconstructed_addr);
}

int main() {
    size_t buffer_addr = my_malloc(4);
    my_free(buffer_addr);
    assert(false);
    return 0;
}
