/*
 * echo.c --
 *
 *	Produce a page containing all FastCGI inputs
 *
 *
 * Copyright (c) 1996 Open Market, Inc.
 *
 * See the file "LICENSE.TERMS" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */
#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

#include "fcgi_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H

#include <unistd.h>

#endif

#ifdef _WIN32
#include <process.h>
#else
extern char **environ;
#endif

#define TEMPORARY_STORAGE "./temporary_storage.txt"

#include "fcgi_stdio.h"
#include "my_stdio.h"
#include <string.h>
#include <my_http_analysis.h>

static void PrintEnv(char *label, char **envp) {
    printf("%s:<br>\n<pre>\n", label);
    for (; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    printf("</pre><p>\n");
}

int main() {
    char **initialEnv = environ;
    int count = 0;
    while (FCGI_Accept() >= 0) {
        char *contentLength = getenv("CONTENT_LENGTH");
        char *bbll = getenv("CONTENT_TYPE");
        HTTP_fiel_information *HTTP = init_file_size(bbll);
        int len;
        char buf[1028] = {0};
        printf("Content-type: text/html\r\n"
               "\r\n");
        if (contentLength != NULL) {
            len = strtol(contentLength, NULL, 10);
        } else {

            len = 0;
        }

        if (len <= 0) {
            printf("sdasd");
        } else {
            FILE *file = my_stdio_fopen(TEMPORARY_STORAGE, "w");
            int i, ch;
            //写入
            for (i = 0; i < len; i++) {
                if ((ch = getchar()) < 0) {
                    break;
                }
                //putchar(ch);
                my_stdio_fputc(ch, file);
            }
            my_stdio_fclose(file);
            file=NULL;
        }
        data_migration(TEMPORARY_STORAGE,HTTP);
        len = 0;
        printf("%s\n", getenv("CONTENT_TYPE"));
        printf("%s\n", HTTP->Content_Disposition);
        printf("%d\n", HTTP->type);
        printf("%s\n", HTTP->KEY);
        PrintEnv("Request environment", environ);
        PrintEnv("Initial environment", initialEnv);
        //delet_file(HTTP);
    } /* while */
    return 0;
}
