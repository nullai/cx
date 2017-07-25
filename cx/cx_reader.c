#include "cx_reader.h"

int cx_next(cx_reader* r)
{
	int c;
	if (r->pc >= r->pe)
		return CX_EOF;

	c = *r->pc;
	r->last = r->pc;
	switch (c)
	{
	case '\n':
		r->pos.col = 0;
		++r->pos.line;
		++r->pc;
		break;
	default:
		++r->pos.col;
		++r->pc;
		break;
	}

	return c;
}

int cx_peek(cx_reader* r, int index)
{
	const char* v = r->pc + index;
	if (v < r->pe)
		return *v;
	return CX_EOF;
}

void cx_skip(cx_reader* r, int count)
{
	int c;
	while (count--)
	{
		c = *r->pc;
		r->last = r->pc;
		++r->pc;
		switch (c)
		{
		case '\n':
			r->pos.col = 0;
			++r->pos.line;
			break;
		default:
			++r->pos.col;
			break;
		}
	}
}
