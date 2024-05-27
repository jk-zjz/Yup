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
#include "my_json_user.h"
#include "my_jwt.h"
#include "my_mysql_api.h"
#endif

#ifdef _WIN32
#include <process.h>
#else
extern char **environ;
#endif
#include "make_log.h"
#include "fcgi_stdio.h"


int main() {
    char **initialEnv = environ;
    int count = 0;

    while (FCGI_Accept() >= 0) {
        char *contentLength = getenv("CONTENT_LENGTH");
        int len;

        printf("Content-type:application/json\r\n"
               "\r\n");

        if (contentLength != NULL) {
            len = strtol(contentLength, NULL, 10);
        } else {
            len = 0;
        }

        if (len <= 0) {
        } else {
            int i, ch;
            char buf[1024]={0};
            for (i = 0; i < len; i++) {
                if ((ch = getchar()) < 0) {
                    printf("Error: Not enough bytes received on standard input<p>\n");
                    break;
                }
                buf[i]=ch;
            }
            Register R;
            Key K;
            //初始化密钥
            init_Key(&K);
            int id=0;
            //初始化
            initialization(&R);
            //初始化注册对象
            init_Register(&R,buf);
            //初始化mysql对象
            Mysqluser * mysql = init_Mysqluser();
            //注册  返回执行码
            int ret = my_mysql_register(mysql,&R,&id);
            //释放
            delet_Mysqluser(mysql);
            //返回json对象
            cJSON * json = initLogOn(R.name,id);
            LOG("register","buf_key","%s",cJSON_Print(json));
            char * key_ =  jwt_encryption(K.Key, cJSON_Print(json));
            printf("{\"StatusCode\":%d,\"key\":\"%s\"}",ret,key_);
            cJSON_Delete(json);
            free(key_);
        }

    } /* while */

    return 0;
}
