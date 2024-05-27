//
// Created by 35148 on 2024/3/14.
//

#ifndef UNTITLED_MY_MYSQL_API_H
#define UNTITLED_MY_MYSQL_API_H
#include "my_json_user.h"
#include <mysql/mysql.h>
#include "iniparser/iniparser.h"
#include "iniparser/dictionary.h"
#include "my_jwt.h"
#include <stdarg.h>

typedef struct {
    char name[10];
    char passwrod[30];
    char table[20];
    char Ip[20];
    char port[10];
    char user_table[20];
    char UserFileList[30];
    char UserFileCount[30];
    char FileInfo[30];
    char UserFileShare[30];
}Mysqluser;

//初始化和释放
Mysqluser * init_Mysqluser();
void delet_Mysqluser(Mysqluser* M);


//注册
int my_mysql_register(Mysqluser* M,Register *R,int *id);
//建立连接
MYSQL* my_mysql_getid(Mysqluser* M,MYSQL*mysql);
//通过用户，验证密码
int Matched_password(loguser *L,Mysqluser* M,int *i);

//处理sql注入函数执行
//返回结果集
MYSQL_STMT * mysql_sql_inject(int count,MYSQL *mysql,char * sql,...) ;

#endif //UNTITLED_MY_MYSQL_API_H