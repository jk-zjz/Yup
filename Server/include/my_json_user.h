//
// Created by 35148 on 2024/3/13.
//

#ifndef UNTITLED_MY_JSON_USER_H
#define UNTITLED_MY_JSON_USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cjson/cJSON.h"
#include "make_log.h"
#include <jwt.h>
#include "iniparser/iniparser.h"
#include "iniparser/dictionary.h"
#include <time.h>
#define CONF_INI "../conf/config.ini"

//注册
typedef struct {
    char accout[20];
    char em[30];
    char name[20];
    char password[30];
    char phone[12];
}Register;

//登录
typedef struct{
    size_t id;
    char user[20];
    int exp;
}LogOn;

typedef struct {
    char Key[20];
}Key;

typedef struct {
    char user[20];
    char password[100];
}loguser;
//初始化
void init_Key(Key *K);
void initialization(Register *R);
cJSON * initLogOn(const char * name,int id);
loguser * init_loguser(char * buf);

//解析json注册信息
void init_Register(Register *R,const char * buf);
//反序列为json
cJSON * set_json(Register *R);

//去掉双引号
void eliminate_(Register *R);

//输出到日志
void show_Register(Register *R);
void show_LogOn(LogOn *L);
char * show_json(cJSON *J);

//通过字符串读取cookie
void get_cookie(char * data,char * buf);
//年月日时分秒
char * getTime();
//获取当前时间戳
unsigned long int get_time_stamp();

void init_Register(Register *R,const char * buf);


#endif //UNTITLED_MY_JSON_USER_H