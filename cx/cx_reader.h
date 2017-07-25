#pragma once
#include "cx_tokens.h"

typedef struct cx_reader
{
	const char* pb;
	const char* pc;
	const char* pe;
	const char* last;
	cx_position pos;
	unsigned int flags;
}cx_reader;

int cx_next(cx_reader* r);

int cx_peek(cx_reader* r, int index);

void cx_skip(cx_reader* r, int count);

#define CX_EOF	-1

