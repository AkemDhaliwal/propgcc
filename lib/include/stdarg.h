#ifndef _STDARG_H
#define _STDARG_H

#include <sys/va_list.h>

typedef __va_list va_list;

#if defined(__GNUC__)
#define va_start(v, l) __builtin_va_start(v,l)
#define va_end(v)      __builtin_va_end(v)
#define va_arg(v, l)   __builtin_va_arg(v, l)
#define va_copy(d,s)   __builtin_va_copy(d, s)

#else

#error "need definition for the varargs macros"

#endif

#endif