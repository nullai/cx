#pragma once

typedef struct cx_pool cx_pool;

cx_pool* cx_pool_create(int size);

void cx_pool_destroy(cx_pool* pool);

const char* cx_pool_dupstr(cx_pool* pool, const char* text);
const char* cx_pool_dupstr_len(cx_pool* pool, const char* text, int size);
void* cx_pool_alloc(cx_pool* pool, int size);
