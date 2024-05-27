//
// Created by 35148 on 2024/3/20.
//

#ifndef UNTITLED_MY_MYSQL_INFO_H
#define UNTITLED_MY_MYSQL_INFO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "make_log.h"
#include "my_mysql_api.h"
#define SHA256 128
#define URL 255
#define TYPE 20
#define CREATETIME 255
#define FILENAME 255
#define FILE_ID 255
#define USERNAME 20
#define PASSWROD 20
#define EMAIL 30
#define PHONE 30
#define NICKNAME 30
//文件信息
struct User_File_Info{
    char sha256[SHA256];
    char file_id[FILE_ID];
    char url[URL];
    int size;
    char type[TYPE];
    int const_;
    struct User_File_Info *next;
};
typedef struct User_File_Info User_File_Info;

//用户文件信息表
struct User_File_List{
    int user;
    char sha256[SHA256];
    char createtime[CREATETIME];
    char filename[FILENAME];
    bool shared_status;
    unsigned int pv;
    struct User_File_List *next;
};
typedef struct User_File_List User_File_List;

struct File_Share{
    int user;
    char sha256[SHA256];
    char createtime[CREATETIME];
    char filename[FILENAME];
    unsigned int pv;
    struct File_Share *next;
};
typedef struct File_Share File_Share;

struct User_Table{
    int id;
    char username[USERNAME];
    char nickname[NICKNAME];
    char phone[PHONE];
    char email[EMAIL];
    char createtime[CREATETIME];
    char passwrod[PASSWROD];
    struct User_Table *next;
};
typedef struct User_Table User_Table;


struct User_Count{
    int user;
    int count;
    struct User_Count *next;
};
typedef struct User_Count User_Count;

//new 用户文件信息
User_File_Info * New_User_File_Info();
//释放 User_File_Info
void free_User_File_Info(User_File_Info * info);

//new New_User_File_List
User_File_List * New_User_File_List();
//释放 User_File_List
void free_User_File_List(User_File_List * info);

File_Share * New_File_Share();
void free_File_Share(File_Share * share);

User_Table * New_User_Table();
void free_User_Table(User_Table * table);

User_Count * New_User_Count();
void free_User_Count(User_Count * count);



//查询所有用户信息--id为-1 代表查全部
User_Table * seletc_User_ALL(int id);
cJSON * init_User_Table(User_Table* T);

//查询用户的文件信息 -1为全部，也可以指定
User_File_List * seletc_User_File_List(int id);
cJSON * init_User_File_List(User_File_List* L);

//查询用户文件数量 -1 为全部
User_Count * seletc_User_Count(int id);
cJSON * init_User_Count(User_Count* L);

User_File_Info *select_User_File_Info(const char *sha256);
cJSON * init_User_File_Info(User_File_Info* I);

File_Share * seletc_File_Share(int id);
cJSON * init_File_Share(File_Share* L);

//switch--->1....
void get_101(User_Table * User,int id,char *buf);
//---->2...
void get_102(User_File_List *List,int id,char *buf);



#endif //UNTITLED_MY_MYSQL_INFO_H
