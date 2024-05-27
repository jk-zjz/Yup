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
#include "my_json_user.h"
#include "my_mysql_api.h"
#include "my_redis_api.h"
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
        char *http_cookie = getenv("HTTP_COOKIE");
        int len = 0;

        printf("Content-type: application/json\r\n"
               "\r\n");

        if (contentLength != NULL) {
            len = strtol(contentLength, NULL, 10);
        }
        char buf[1024] = {0};
        int i, ch;
        for (i = 0; i < len; i++) {
            if ((ch = getchar()) < 0) {
                printf("Error: Not enough bytes received on standard input<p>\n");
                break;
            }
            buf[i] = ch;
        }
        //做处理
        //用户密码(加密)
        LOG("login","key","%s\n",buf);
        Key K;
        init_Key(&K);
        Mysqluser *M = init_Mysqluser();
        loguser *L = init_loguser(buf);
        Redis* R =  Init_Redis();
        Task* T = Net_Task();
        int id;
        int type = Matched_password(L, M, &id);
        if (http_cookie == NULL) {
            label:
            //没有cookie需要重新生成的
            if (type == 200) {
                char * key_ =jwt_encryption(K.Key, cJSON_Print(initLogOn(L->user, id)));
                printf("{\"type\":%d,\"cookie\":\"%s\",\"id\":%d}",
                       type,
                       key_,
                       id);
                Task_push_back(T,L->user,key_,24*60*60);
                LOG("login","cookie ","lose efficacy %d\n",type);
            } else {
                printf("{\"type\":%d,\"cookie\":\"\",\"id\":-1}", type);
            }
        }
        else {
            char cookie[128] = {0};
            get_cookie(http_cookie, cookie);
            if(strcasecmp(cookie,"")==0){
                goto label;
            }
            cJSON *json = jwt_decrypt(cookie, K.Key);
            LOG("Tk","asd","%s",cookie);
            unsigned long int time = cJSON_GetObjectItem(json, "exp")->valueint;
            int id_s = cJSON_GetObjectItem(json, "id")->valueint;
            if (type == 200 && json != NULL) {
                LOG("login", "login", "%d---%d----%d---%d\n", time,type,get_time_stamp(),id_s);
                if(id_s!=id){
                    goto label;
                }
                if (time <= get_time_stamp()) {
                    //密码正确了才回过期
                    printf("{\"type\":203,\"cookie\":\"\",\"id\":-1}");
                }else{
                    //OK
                    printf("{\"type\":%d,\"cookie\":\"%s\",\"id\":%lu}", type, cookie,id);
                    Task_push_back(T,L->user,cookie,time-get_time_stamp());
                }

            } else {
                //错误
                printf("{\"type\":%d,\"cookie\":\"\",\"id\":-1}", type);
            }
            cJSON_Delete(json);
        }
        Insert_Redis(T,R);
        Delet_Redis(R);
        Task_Delet(T);
        delet_Mysqluser(M);
        free(L);
    } /* while */

    return 0;
}
