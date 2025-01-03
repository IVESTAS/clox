#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int offset;
    int line;
} LineStart;

/*
 * This is our dynamic array.
 * If we have no spare capacity:
 * 1. Allocate the new array with more capacity
 * 2. Copy the existing elements from the old array to the new one
 * 3. Store the new capacity
 * 4. Delete the old array
 * 5. Update code to point to the new array
 * 6. Store the element in the new array now that there is room
 * 7. Update the count
 */
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    ValueArray constants;
    int line_count;
    int line_capacity;
    LineStart *lines;
} Chunk;

void init_chunk(Chunk* chunk);
void free_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte, int line);
int add_constant(Chunk* chunk, Value value);
int get_line(Chunk* chunk, int instruction);

#endif
