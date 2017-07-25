#pragma once

typedef struct cx_file cx_file;

struct cx_file
{
	const char* name;
	const char* path;
	const char* dir;

	const char* data;
	const char* limit;

	bool once_only;
	bool main_file;
	bool included;
};


