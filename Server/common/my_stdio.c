//
// Created by 35148 on 2024/3/8.
//

#include "my_stdio.h"
extern FILE * my_stdio_fopen (const char *__restrict _filename,const char *__restrict _modes)__wur
{
    FILE * file = fopen(_filename,_modes);
    if(!file){
        return NULL;
    }
    return file;
}

extern int my_stdio_fclose (FILE *_stream)
{
    return fclose(_stream);
}

extern int my_stdio_fputc (int __c, FILE *_stream)
{
    return fputc(__c,_stream);
}

extern char * my_stdio_fgets (char *__restrict _s, int _n, FILE *__restrict _stream)
__wur
{
    return fgets(_s,_n,_stream);
}
extern void my_stdio_rewind (FILE *_stream)
__END_NAMESPACE_STD
{
    rewind(_stream);
}
