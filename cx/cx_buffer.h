#pragma once

typedef struct cx_buffer cx_buffer;

cx_buffer* cx_buffer_create(int size);

void cx_buffer_destroy(cx_buffer* buffer);

const char* cx_buffer_dupstr(cx_buffer* buffer, const char* text);
const char* cx_buffer_dupstr_len(cx_buffer* buffer, const char* text, int size);
void* cx_buffer_alloc(cx_buffer* buffer, int size);
