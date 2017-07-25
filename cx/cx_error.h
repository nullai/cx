#pragma once

#define CX_W_BEGIN	101
#define CX_E_BEGIN	301

typedef enum error_kind
{
	CX_OK,

	CX_W_SKIP_NULL_CHAR = CX_W_BEGIN,


	CX_E_EOF = CX_E_BEGIN,
	CX_E_OUTOFMEMORY,
	CX_E_INVALID_CHAR,
	CX_E_MISS_CHAR_END,
	CX_E_MISS_STRING_END,
	CX_E_MISS_COMMENT_END,
} error_kind;

typedef struct cx_position cx_position;

void cx_error(cx_position* pos, error_kind kind, ...);

void cx_exit(int err);

