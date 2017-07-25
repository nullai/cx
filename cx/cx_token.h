#pragma once

typedef unsigned int token_kind;

typedef struct cx_position
{
	const char* file;
	int line;
	int col;
	struct cx_position* upper;
} cx_position;

#pragma pack(1)
typedef struct cx_token
{
	struct cx_token* next;
	token_kind kind;
	unsigned int flags;
	cx_position pos;
	int length;
	char value[1];
} cx_token;
#pragma pack()

#define CX_NAMED_OP			1
#define CX_LINK_LINE		2
#define CX_PREV_WHITE		4
#define CX_DIGRAPH			8
#define CX_NO_EXPAND		16
#define CX_STRINGIFY_ARG	32
#define CX_PASTE_LEFT		64
#define CX_BOL				128
#define CX_PURE_ZERO		256
#define CX_SP_DIGRAPH		512
#define CX_SP_PREV_WHITE	1024

#define CX_NAME		'id'
#define CX_STRING	'S'
#define CX_NUMBER	'N'
#define CX_CHAR		'c'
#define CX_OTHER	'O'

#define CX_TRUE		'1'
#define CX_FALSE	'0'
#define CX_NULL		'n'

enum cx_token_fld_kind
{
	CX_TOKEN_FLD_NODE,
	CX_TOKEN_FLD_SOURCE,
	CX_TOKEN_FLD_STR,
	CX_TOKEN_FLD_ARG_NO,
	CX_TOKEN_FLD_TOKEN_NO,
	CX_TOKEN_FLD_PRAGMA,
	CX_TOKEN_FLD_NONE
};

struct cx_macro_arg
{
	/* Argument number. */
	unsigned int arg_no;
};

struct cx_identifier
{

};

struct cx_token
{
	source_location src_loc;
};

