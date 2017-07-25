#pragma once
#include "cx_type.h"
#include "cx_file.h"
typedef struct cx_buffer cx_buffer;

struct cx_buffer
{
	const byte* cur;
	const byte* line_base;
	const byte* next_line;

	const byte* buf;
	const byte* rlimit;
	const byte* to_free;

	cx_buffer* prev;
	cx_file* file;

	bool need_line;
};

