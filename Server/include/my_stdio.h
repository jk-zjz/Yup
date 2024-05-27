//
// Created by 35148 on 2024/3/8.
//
#include <stdio.h>

#ifndef UNTITLED_MY_STDIO_H_H
#define UNTITLED_MY_STDIO_H

// my_stdio_fopn
extern FILE * my_stdio_fopen (const char *__restrict __filename,
                    const char *__restrict __modes) __wur;

extern int my_stdio_fclose(FILE *__stream);

extern int my_stdio_fputc (int __c, FILE *__stream);

extern char * my_stdio_fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
__wur;

extern void my_stdio_rewind (FILE *__stream);
__END_NAMESPACE_STD

#endif //UNTITLED_MY_STDIO_H_H
