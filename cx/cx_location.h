#pragma once

typedef struct cx_location cx_location;

struct cx_location
{
	struct cx_file* file;
	int line;
	cx_location* upper;
};

cx_location* cx_location_create(struct cx_pool* pool, struct cx_file* file, int line);

