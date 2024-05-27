//
// Created by 35148 on 2024/3/23.
//
#include "my_redis_api.h"
#include "my_json_user.h"

//初始化
Redis* Init_Redis(){
    Redis * R = (Redis *)malloc(sizeof (Redis));
    dictionary * ini = iniparser_load(CONF_INI);
    strcpy(R->ip, iniparser_getstring(ini,"REDIS:IP","null"));
    strcpy(R->prot, iniparser_getstring(ini,"REDIS:Prot","null"));
    iniparser_freedict(ini);
    return R;
}
Task* Net_Task(){
    Task * T = (Task *)malloc(sizeof(Task));
    T->next=NULL;
    T->tail=NULL;
    T->head=NULL;
    return T;
}

//插入
void Task_push_back(Task *T,const char * key,const char * value,unsigned int time){
    Task * net = Net_Task();
    strcpy(net->Key,key);
    strcpy(net->value,value);
    net->time=time;
    net->head=T;
    if(T->tail==NULL){
        T->next=net;
    }else{
        T->tail->next=net;
    }
    T->tail=net;
}

//写入redis
int Insert_Redis(Task *T,Redis *R){
    Task *data =T->next;
    char * error;
    redisReply *reply;
    redisContext *c = redisConnect(R->ip, (int)strtol(R->prot,&error,10));
    if(c==NULL){
        LOG("redis","error","redisConnect NULL 406\n");
        return 406;
    }
    if(c->err) {
        LOG("redis","error","%s\n",c->errstr);
        return 406;
    }
    while(data){
        reply = redisCommand(c, "SET %s %s", data->Key, data->value);
        freeReplyObject(reply);
        reply = redisCommand(c, "expire %s %d",data->Key,data->time);
        data=data->next;
    }
    redisFree(c);
    return 200;
}


//释放
void Delet_Redis(Redis * R){
    free(R);
};

void Task_Delet(Task*T){
    if(T==NULL){
        return;
    }
    Task_Delet(T->next);
    free(T);
}