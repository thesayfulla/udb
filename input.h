#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define INITIAL_BUFFER_SIZE 1024

typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer();
void close_input_buffer(InputBuffer *input_buffer);
void read_input(InputBuffer *input_buffer);

#endif
