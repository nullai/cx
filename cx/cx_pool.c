#include "cx_pool.h"
#include <windows.h>
#include "cx_error.h"

#define POOL_SIZE  64 * 1024

static void* valloc(int size)
{
	return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
}

static void vfree(void* ptr)
{
	VirtualFree(ptr, 0, MEM_RELEASE);
}

static int align_size(int size)
{
	int v = 1024 * 64;
	while (v < size)
		v *= 2;

	return v;
}

struct cx_pool
{
	cx_pool* active;
	cx_pool* next;
	int size;
	int used;
};

cx_pool* cx_pool_create(int size)
{
	size += sizeof(cx_pool);
	if (size < POOL_SIZE)
		size = POOL_SIZE;
	else
		size = align_size(size);
	cx_pool* p = (cx_pool*)valloc(size);
	if (!p)
	{
		cx_error(0, CX_E_OUTOFMEMORY);
		cx_exit(1);
	}

	p->active = p;
	p->next = 0;
	p->size = size - sizeof(cx_pool);
	p->used = 0;
	return p;
}

void cx_pool_destroy(cx_pool* pool)
{
	while (pool)
	{
		cx_pool* next = pool->next;
		vfree(pool);
		pool = next;
	}
}

const char* cx_pool_dupstr(cx_pool* pool, const char* text)
{
	return cx_pool_dupstr_len(pool, text, strlen(text));
}

const char* cx_pool_dupstr_len(cx_pool* pool, const char* text, int size)
{
	char* p = (char*)cx_pool_alloc(pool, size + 1);
	memcpy(p, text, size);
	p[size] = 0;
	return p;
}

void* cx_pool_alloc(cx_pool* pool, int size)
{
	cx_pool* active = pool->active;
	if (active->size - active->used < size)
	{
		active = cx_pool_create(size);
		active->next = pool->next;
		pool->next = active;
		pool->active = active;
	}

	char* p = (char*)(active + 1) + active->used;
	active->used += size;
	return p;
}

