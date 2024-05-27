//
// Created by 35148 on 2024/3/23.
//

#ifndef UNTITLED_MY_REDIS_API_H
#define UNTITLED_MY_REDIS_API_H
#include "hiredis.h"
#include "read.h"
#include <stdbool.h>

struct Redis{
    char ip[20];
    char prot[10];
};
typedef struct Redis Redis;

//需要添加到redis的任务
struct Task{
    char Key[20];
    char value[255];
    unsigned long time;
    struct Task * next;
    struct Task * head;
    struct Task * tail;
};
typedef struct Task Task;

//初始化连接信息
Redis* Init_Redis();
//释放
void Delet_Redis(Redis * R);

//创建初始化
Task* Net_Task();
//插入任务队列
void Task_push_back(Task *T,const char * key,const char * value,unsigned int time);
//释放队列
void Task_Delet(Task*T);

bool Fine_Key_Redis();

//插入用户登录的 user:cookie  过期time
int Insert_Redis(Task *T,Redis *R);


#endif //UNTITLED_MY_REDIS_API_H