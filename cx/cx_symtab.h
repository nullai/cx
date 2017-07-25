#pragma once

typedef struct cx_symtab cx_symtab;

struct cx_hashnode
{
	cx_hashnode* next;
	unsigned int hash;
	const char* name;
	void* tag;
};

cx_symtab* cx_symtab_create();

void cx_symtab_destroy(cx_symtab* tab);

cx_hashnode* cx_symtab_add(cx_symtab* tab, const char* k, int size);
bool cx_symtab_remove(cx_symtab* tab, cx_hashnode* node);

cx_hashnode* cx_symtab_find(cx_symtab* tab, const char* k);
cx_hashnode* cx_symtab_find_ex(cx_symtab* tab, const char* k, int size);

