#include "cx_buffer.h"
#include <windows.h>
#include "cx_error.h"

#define BUFFER_SIZE  64 * 1024

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

struct cx_buffer
{
	cx_buffer* active;
	cx_buffer* next;
	int size;
	int used;
};

cx_buffer* cx_buffer_create(int size)
{
	size += sizeof(cx_buffer);
	if (size < BUFFER_SIZE)
		size = BUFFER_SIZE;
	else
		size = align_size(size);
	cx_buffer* p = (cx_buffer*)valloc(size);
	if (!p)
	{
		cx_error(0, CX_E_OUTOFMEMORY);
		cx_exit(1);
	}

	p->active = p;
	p->next = 0;
	p->size = size - sizeof(cx_buffer);
	p->used = 0;
	return p;
}

void cx_buffer_destroy(cx_buffer* buffer)
{
	while (buffer)
	{
		cx_buffer* next = buffer->next;
		vfree(buffer);
		buffer = next;
	}
}

const char* cx_buffer_dupstr(cx_buffer* buffer, const char* text)
{
	return cx_buffer_dupstr_len(buffer, text, strlen(text));
}

const char* cx_buffer_dupstr_len(cx_buffer* buffer, const char* text, int size)
{
	char* p = (char*)cx_buffer_alloc(buffer, size + 1);
	memcpy(p, text, size);
	p[size] = 0;
	return p;
}

void* cx_buffer_alloc(cx_buffer* buffer, int size)
{
	cx_buffer* active = buffer->active;
	if (active->size - active->used < size)
	{
		active = cx_buffer_create(size);
		active->next = buffer->next;
		buffer->next = active;
		buffer->active = active;
	}

	char* p = (char*)(active + 1) + active->used;
	active->used += size;
	return p;
}

