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

#include "fcgi_stdio.h"
#include "cJSON.h"
#include "my_StrategyRequest.h"

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
    Mysqluser *M = init_Mysqluser();
    while (FCGI_Accept() >= 0) {
        char *contentLength = getenv("CONTENT_LENGTH");
        int len;

        printf("Content-type: application/json\r\n"
               "\r\n");

        if (contentLength != NULL) {
            len = strtol(contentLength, NULL, 10);
        } else {
            len = 0;
        }
        if (len <= 0) {
        } else {
            int i, ch;
            char buf[128] = {0};
            for (i = 0; i < len; i++) {
                if ((ch = getchar()) < 0) {
                    printf("Error: Not enough bytes received on standard input<p>\n");
                    break;
                }
                buf[i] = ch;
            }
            cJSON *json = cJSON_Parse(buf);
            int type = cJSON_GetObjectItem(json, "type")->valueint;
            int id = cJSON_GetObjectItem(json, "id")->valueint;
            char *data;
            LOG("1", "2", "%d--%s\n", type, buf);
            char buf_[1024];
            switch (type) {
                case 101:
                    LOG("userinfo","101","%d",id);
                    User_Table * User = seletc_User_ALL(id);
                    if(User==NULL){
                        printf("\"type\":404");
                        break;
                    }
                    get_101(User,id,buf_);
                    printf(buf_);
                    break;
                case 102:
                    LOG("userinfo","102","%d",id);
                    User_File_List * user_file_list = seletc_User_File_List(id);
                    if(user_file_list==NULL){
                        printf("\"type\":404");
                        break;
                    }
                    get_102(user_file_list,id,buf_);
                    printf("%s",buf_);
                    break;
                default:
                    printf("{\"type\":404,\"data\":%s}");
                    break;
            }
            cJSON_Delete(json);
        }

    } /* while */

    return 0;
}
