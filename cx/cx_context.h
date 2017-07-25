#pragma once
#include "cx_pool.h"
typedef struct cx_context cx_context;

#define COND		(1 << 0)
#define IF_COND		(1 << 1)
#define INCL		(1 << 2)
#define IN_I		(1 << 3)
#define EXPAND		(1 << 4)
#define DEPRECATED	(1 << 5)

struct if_stack
{
	struct if_stack *next;
	struct cx_location* line;		/* Line where condition started.  */
	bool skip_elses;				/* Can future #else / #elif be skipped?  */
	bool was_skipping;				/* If were skipping on entry.  */
	int type;						/* Most recent conditional for diagnostics.  */
};

struct cx_context
{
	cx_context *next, *prev;
	cx_pool* pool;
};

