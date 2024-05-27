//
// Created by 35148 on 2024/3/13.
//
#include "my_json_user.h"


/*
 * 初始化
 * */
void initialization(Register *R) {
    memset(R->name, 0, 20);
    memset(R->em, 0, 30);
    memset(R->password, 0, 30);
    memset(R->phone, 0, 12);
    memset(R->accout, 0, 20);
}

cJSON *initLogOn( const char *name, int id) {

    cJSON *J = cJSON_CreateObject();
    cJSON_AddNumberToObject(J, "id", id);
    cJSON_AddStringToObject(J, "user", name);
    cJSON_AddNumberToObject(J, "exp", get_time_stamp() + 24 * 60 * 60);
    return J;
}

/*对“的去除*/
void eliminate_(Register *R) {
    R->accout[strlen(R->accout) - 1] = '\0';
    R->em[strlen(R->em) - 1] = '\0';
    R->name[strlen(R->name) - 1] = '\0';
    R->password[strlen(R->password) - 1] = '\0';
    R->phone[strlen(R->phone) - 1] = '\0';
}

/*
 *
 *
 * 通过json对注册对象进行封装
 * */
void init_Register(Register *R, const char *buf) {
    cJSON *root = cJSON_Parse(buf);
    strcpy(R->accout, (cJSON_Print(cJSON_GetObjectItem(root, "accout"))) + 1);
    strcpy(R->em, (cJSON_Print(cJSON_GetObjectItem(root, "em"))) + 1);
    strcpy(R->name, (cJSON_Print(cJSON_GetObjectItem(root, "name"))) + 1);
    strcpy(R->password, (cJSON_Print(cJSON_GetObjectItem(root, "password"))) + 1);
    strcpy(R->phone, (cJSON_Print(cJSON_GetObjectItem(root, "phone"))) + 1);
    eliminate_(R);
    cJSON_Delete(root);
}

/*
 *
 * 对用户注册数据进行封装成json
 * */
cJSON *set_json(Register *R) {
    cJSON *J = cJSON_CreateObject();
    cJSON_AddItemToObject(J, "accout", cJSON_CreateString(R->accout));
    cJSON_AddItemToObject(J, "em", cJSON_CreateString(R->em));
    cJSON_AddItemToObject(J, "name", cJSON_CreateString(R->name));
    cJSON_AddItemToObject(J, "password", cJSON_CreateString(R->password));
    cJSON_AddItemToObject(J, "phone", cJSON_CreateString(R->phone));
    return J;
}


/*
 * 日志输出
 * */
void show_Register(Register *R) {
    LOG("cJSON", "Register", "%s:%s:%s:%s:%s:%s\n", R->accout,
        R->em,
        R->name,
        R->password,
        R->phone);
}

char *show_json(cJSON *J) {
    LOG("cJSON", "json", "%s\n", cJSON_Print(J));
    return cJSON_Print(J);
}

void show_LogOn(LogOn *L) {
    LOG("cJSON", "LogOn", "%d:%s:%s\n", L->exp,
        L->id,
        L->user);
}

/*
 *
 *
 * 获取当前时间在吃饭*/
char *getTime() {
    char *Time = (char *) malloc(sizeof(char) * 50);
    time_t t = time(NULL);//获取当前时间句柄, time_t 就是 int64
    struct tm *ptime = localtime(&t);//将时间句柄转换为时间结构体tm, localtime 以前的函数可能会报 error C4996
    int nYear = ptime->tm_year + 1900;
    int nMonth = ptime->tm_mon + 1;
    int nDay = ptime->tm_mday;
    int nHour = ptime->tm_hour;
    int nMinute = ptime->tm_min;
    int nSecond = ptime->tm_sec;
    sprintf(Time,
            "%d-%02d-%02d %02d:%02d:%02d",
            nYear, nMonth, nDay, nHour, nMinute, nSecond
    );
    return Time;
}

/*
 *
 * 获取时间戳
 * */
unsigned long get_time_stamp() {
    time_t current_time;
    current_time = time(NULL);

    if (current_time == -1) {
        LOG("cJSON", "time", " __%d__", __FILE__);
        return 0;
    }
    localtime(&current_time);
    return (unsigned long) current_time;
}

/*
 *
 * 获取密钥*/
void init_Key(Key *K) {
    dictionary *ini = iniparser_load(CONF_INI);
    strcpy(K->Key, iniparser_getstring(ini, "JWT:Key", "null"));
    iniparser_freedict(ini);
}

/*
 *
 * 通过字符串读取cookie
 * */
void get_cookie(char *data, char *buf) {
    char *K = strstr(data, "=") + 1;
    if (K == NULL) {
        buf = NULL;
        return;
    }
    int i = 0;
    while (*K != ';') {
        buf[i] = *K;
        i++;
        K++;
    }
    buf[i]='\0';
    LOG("cJSON","cookie","%s\n",buf);
}

/*
 *
 * 初始化登录数据
 * */
loguser * init_loguser(char *buf) {
    loguser * LOGIN = (loguser * )malloc(sizeof(loguser));
    cJSON *json = cJSON_Parse(buf);
    if(!json){
        LOG("cJSON","error","[%d] [解析密码错误] [%s]\n",__LINE__,buf);
        return NULL;
    }
    strcpy(LOGIN->user,cJSON_Print(cJSON_GetObjectItem(json,"user"))+1);
    strcpy(LOGIN->password,cJSON_Print(cJSON_GetObjectItem(json,"password"))+1);

    LOGIN->user[strlen(LOGIN->user)-1]='\0';
    LOGIN->password[strlen(LOGIN->password)-1]='\0';

    LOG("cJSON","OK","buf:%s:%s:%s\n",buf,LOGIN->user,LOGIN->password);
    cJSON_Delete(json);
    return LOGIN;
}