//
// Created by 35148 on 2024/3/20.
//
#include "my_mysql_info.h"

//初始化
User_File_Info *New_User_File_Info() {
    User_File_Info *info = (User_File_Info *) malloc(sizeof(User_File_Info));
    if (info == NULL) {
        LOG("New_User_File_Info", "error", "malloc User_File_Info file\n");
        return NULL;
    }
    memset(info, 0, sizeof(User_File_Info));
    info->next = NULL;
    return info;
}

User_File_List *New_User_File_List() {
    User_File_List *List = (User_File_List *) malloc(sizeof(User_File_List));
    if (List == NULL) {
        LOG("New_User_File_List", "error", "malloc New_User_File_List file\n");
        return NULL;
    }
    memset(List, 0, sizeof(User_File_List));
    List->next = NULL;
    return List;
}

File_Share *New_File_Share() {
    File_Share *share = (File_Share *) malloc(sizeof(File_Share));
    if (share == NULL) {
        LOG("New_File_Share", "error", "malloc New_File_Share file\n");
        return NULL;
    }
    memset(share, 0, sizeof(File_Share));
    share->next = NULL;
    return share;
}

User_Table *New_User_Table() {
    User_Table *table = (User_Table *) malloc(sizeof(User_Table));
    if (table == NULL) {
        LOG("New_User_Table", "error", "malloc New_User_Table file\n");
        return NULL;
    }
    memset(table, 0, sizeof(User_Table));
    table->next = NULL;
    return table;
}

User_Count *New_User_Count() {
    User_Count *count = (User_Count *) malloc(sizeof(User_Count));
    if (count == NULL) {
        LOG("New_User_Count", "error", "malloc New_User_Count file\n");
        return NULL;
    }
    memset(count, 0, sizeof(User_Count));
    count->next = NULL;
    return count;
}

//释放
void free_User_File_Info(User_File_Info *info) {
    if (info == NULL) {
        return;
    }
    free_User_File_Info(info->next);
    free(info);
}

void free_User_File_List(User_File_List *list) {
    if (list == NULL) {
        return;
    }
    free_User_File_List(list->next);
    free(list);
}

void free_File_Share(File_Share *share) {
    if (share == NULL) {
        return;
    }
    free_File_Share(share->next);
    free(share);
}

void free_User_Table(User_Table *table) {
    if (table == NULL) {
        return;
    }
    free_User_Table(table->next);
    free(table);
}

void free_User_Count(User_Count *count) {
    if (count == NULL) {
        return;
    }
    free_User_Count(count->next);
    free(count);
}

/*
 * 重新所有用户信息
 * */
User_Table *seletc_User_ALL(int id_) {
    User_Table *T = New_User_Table();
    User_Table *T1 = T;
    User_Table *T2 = T;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL *mysql = NULL;
    mysql = mysql_init(mysql);
    Mysqluser *M = init_Mysqluser();
    if (!my_mysql_getid(M, mysql)) {
        LOG("mysql", "error", "connect failed \n");
        free_User_Table(T);
    };
    mysql_set_character_set(mysql, "utf8");
    char query[1024];
    if (id_ == -1) {
        sprintf(query, "select * from %s",
                M->user_table);
    } else {
        sprintf(query, "select * from %s where id=%d",
                M->user_table,
                id_);
    }
    int ret = mysql_query(mysql, query);
    if (ret != 0) {
        LOG("mysql", "error", "select 404  %s---%d\n", query, ret);
        free_User_Table(T);
        return NULL;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        free_User_Table(T);
        LOG("mysql", "error", "error_mysql_store_result 405 [__%d__] %s table %s\n", __LINE__, mysql_error(mysql), query);
        return NULL;
    }
    int cot=0;
    while ((row = mysql_fetch_row(res))) {
        cot++;
        char *pVoid=NULL;
        T1->id= (int)strtol(row[0], &pVoid, 10);
        strcpy(T1->username, row[1]);
        strcpy(T1->nickname, row[2]);
        strcpy(T1->phone, row[3]);
        strcpy(T1->email, row[4]);
        strcpy(T1->createtime, row[5]);
        strcpy(T1->passwrod, row[6]);
        User_Table *new_T = New_User_Table();
        T2 = T1;
        T1->next = new_T;
        T1 = new_T;
    }
    free_User_Table(T1);
    if(!cot){
        T=NULL;
    }else{
        T2->next = NULL;
    }
    delet_Mysqluser(M);
    mysql_free_result(res);
    mysql_close(mysql);
    return T;
}

cJSON *init_User_Table(User_Table *T) {
    cJSON *obje = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    int cont = 0;
    while (T) {
        cont++;
        char id[20];
        sprintf(id, "%d", T->id);
        cJSON *user = cJSON_CreateObject();
        cJSON_AddNumberToObject(user, "id", T->id);
        cJSON_AddStringToObject(user, "username", T->username);
        cJSON_AddStringToObject(user, "nickname", T->nickname);
        cJSON_AddStringToObject(user, "phone", T->phone);
        cJSON_AddStringToObject(user, "email", T->email);
        cJSON_AddStringToObject(user, "createtime", T->createtime);
        cJSON_AddItemToObject(data, id, user);
        T = T->next;
    }
    LOG("user", "register", "%s\n", cJSON_Print(data));

    cJSON_AddNumberToObject(obje, "cont", cont);
    cJSON_AddItemToObject(obje, "data", data);
    return obje;
}

/*
 *
 * 用户对应的文件
 * */

User_File_List * seletc_User_File_List(int id){
    User_File_List *L = New_User_File_List();
    User_File_List *L1 = L;
    User_File_List *L2 = L;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL *mysql = NULL;
    mysql = mysql_init(mysql);
    Mysqluser *M = init_Mysqluser();
    if (!my_mysql_getid(M, mysql)) {
        LOG("mysql", "error", "connect failed \n");
        free_User_File_List(L);
    };
    mysql_set_character_set(mysql, "utf8");
    char query[1024];
    if(id==-1){
        sprintf(query, "select * from %s",
                M->UserFileList);
    }else{
        sprintf(query, "select * from %s where user=%d",
                M->UserFileList,
                id);
    }
    int ret = mysql_query(mysql, query);
    if (ret != 0) {
        LOG("mysql", "error", "select 404 %s---%d\n", query, ret);
        free_User_File_List(L);
        return NULL;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        free_User_File_List(L);
        LOG("mysql", "error", "error_mysql_store_result 405 [__%d__] %s table %s\n", __LINE__, mysql_error(mysql), query);
        return NULL;
    }
    int cot=0;
    while ((row = mysql_fetch_row(res))) {
        cot++;
        char *pVoid=NULL;
        L1->user = (int)strtol(row[0], &pVoid, 10);
        strcpy(L1->sha256,row[1]);
        strcpy(L1->createtime,row[2]);
        strcpy(L1->filename,row[3]);
        L1->shared_status=(int)strtol(row[4], &pVoid, 10);
        L1->pv=(int) strtol(row[5],&pVoid,10);
        User_File_List *new_L = New_User_File_List();
        L2 = L1;
        L1->next = new_L;
        L1 = new_L;
    }
    free_User_File_List(L1);
    if(!cot){
        L=NULL;
    }else{
        L2->next = NULL;
    }
    delet_Mysqluser(M);
    mysql_free_result(res);
    mysql_close(mysql);
    return L;
}

cJSON * init_User_File_List(User_File_List* L){
    cJSON *obje = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    int cont = 0;
    while(L){
        cont++;
        cJSON * user_info = cJSON_CreateObject();
        cJSON_AddNumberToObject(user_info,"user",L->user);
        cJSON_AddStringToObject(user_info,"sha256",L->sha256);
        cJSON_AddStringToObject(user_info,"createtime",L->createtime);
        cJSON_AddStringToObject(user_info,"filename",L->filename);
        cJSON_AddBoolToObject(user_info,"shared_status",L->shared_status);
        cJSON_AddNumberToObject(user_info,"pv",L->pv);
        cJSON_AddItemToObject(data,L->filename,user_info);
        L=L->next;
    }
    LOG("FileList","OK","%s\n", cJSON_Print(data));
    cJSON_AddNumberToObject(obje,"cont",cont);
    cJSON_AddItemToObject(obje,"data",data);
    return obje;
}

User_Count * seletc_User_Count(int id){
    User_Count *C = New_User_Count();
    User_Count *C1 = C;
    User_Count *C2 = C;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL *mysql = NULL;
    mysql = mysql_init(mysql);
    Mysqluser *M = init_Mysqluser();
    if (!my_mysql_getid(M, mysql)) {
        LOG("mysql", "error", "connect failed \n");
        free_User_Count(C);
    };
    mysql_set_character_set(mysql, "utf8");
    char query[1024];
    if(id==-1){
        sprintf(query, "select * from %s",
                M->UserFileCount);
    }else{
        sprintf(query, "select * from %s where user=%d",
                M->UserFileCount,
                id);
    }
    int ret = mysql_query(mysql, query);
    if (ret != 0) {
        LOG("mysql", "error", "select 404 %s---%d\n", query, ret);
        free_User_Count(C);
        return NULL;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        free_User_Count(C);
        LOG("mysql", "error", "error_mysql_store_result 405 [__%d__] %s table %s\n", __LINE__, mysql_error(mysql), query);
        return NULL;
    }
    int cot = 0;
    while ((row = mysql_fetch_row(res))) {
        cot++;
        char *pVoid=NULL;
        C1->user = (int)strtol(row[0], &pVoid, 10);
        C1->count=(int)strtol(row[1], &pVoid, 10);
        User_Count *new_L = New_User_Count();
        C2 = C1;
        C1->next = new_L;
        C1 = new_L;
    }
    free_User_Count(C1);
    if(!cot){
        C=NULL;
    }else{
        C2->next = NULL;
    }
    delet_Mysqluser(M);
    mysql_free_result(res);
    mysql_close(mysql);
    return C;
}
cJSON * init_User_Count(User_Count* C){
    cJSON *obje = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    int cont = 0;
    while(C){
        cont++;
        char id[20];
        sprintf(id, "%d", C->user);
        cJSON * user =cJSON_CreateObject();
        cJSON_AddNumberToObject(user,"user",C->user);
        cJSON_AddNumberToObject(user,"count",C->count);
        cJSON_AddItemToObject(data, id,user);
        C=C->next;
    }
    LOG("UserCount","OK","%s\n", cJSON_Print(data));
    cJSON_AddNumberToObject(obje,"cont",cont);
    cJSON_AddItemToObject(obje,"data",data);
    return obje;
}

/*
 *
 * 文件信息，按sha256操作，一次一个
 */
User_File_Info *select_User_File_Info(const char *sha256) {
    User_File_Info *I= New_User_File_Info();
    User_File_Info *I1 = I;
    User_File_Info *I2 = I;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL *mysql = NULL;
    mysql = mysql_init(mysql);
    Mysqluser *M = init_Mysqluser();
    if (!my_mysql_getid(M, mysql)) {
        LOG("mysql", "error", "connect failed \n");
        free_User_File_Info(I);
    };
    mysql_set_character_set(mysql, "utf8");
    char query[1024];
    sprintf(query, "select * from %s where sha256='%s'",
            M->FileInfo,
            sha256);
    int ret = mysql_query(mysql, query);
    if (ret != 0) {
        LOG("mysql", "error", "select 404 %s---%d\n", query, ret);
        free_User_File_Info(I);
        return NULL;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        free_User_File_Info(I);
        LOG("mysql", "error", "error_mysql_store_result 405  [__%d__] %s table %s\n", __LINE__, mysql_error(mysql), query);
        return NULL;
    }
    int cot = 0;
    while ((row = mysql_fetch_row(res))) {
        cot++;
        char *pVoid=NULL;
        strcpy(I1->sha256,row[0]);
        strcpy(I1->file_id,row[1]);
        strcpy(I1->url,row[2]);
        I1->size = (int)strtol(row[3],&pVoid,10);
        strcpy(I1->type,row[4]);
        I1->const_ = (int) strtol(row[5],&pVoid,10);
        User_File_Info *new_L = New_User_File_Info();
        I2 = I1;
        I1->next = new_L;
        I1 = new_L;
    }
    free_User_File_Info(I1);
    if(!cot){
        I=NULL;
    }else{
        I2->next = NULL;
    }
    delet_Mysqluser(M);
    mysql_free_result(res);
    mysql_close(mysql);
    return I;
}
cJSON * init_User_File_Info(User_File_Info* I){
    cJSON *obje = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    int cont = 0;
    while(I){
        cont++;
        char id[20];
        sprintf(id, "%d",cont);
        cJSON * user =cJSON_CreateObject();
        cJSON_AddStringToObject(user,"sha256",I->sha256);
        cJSON_AddStringToObject(user,"file_id",I->file_id);
        cJSON_AddStringToObject(user,"url",I->url);
        cJSON_AddNumberToObject(user,"size",I->size);
        cJSON_AddStringToObject(user,"type",I->type);
        cJSON_AddNumberToObject(user,"const_",I->const_);
        cJSON_AddItemToObject(data, id,user);
        I=I->next;
    }
    LOG("UserFileInfo","OK","%s\n", cJSON_Print(data));
    cJSON_AddNumberToObject(obje,"cont",cont);
    cJSON_AddItemToObject(obje,"data",data);
    return obje;
}

/*
 * 查询表
 * */
File_Share * seletc_File_Share(int id){
    File_Share *L = New_File_Share();
    File_Share *L1 = L;
    File_Share *L2 = L;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    MYSQL *mysql = NULL;
    mysql = mysql_init(mysql);
    Mysqluser *M = init_Mysqluser();
    if (!my_mysql_getid(M, mysql)) {
        LOG("mysql", "error", "connect failed \n");
        free_File_Share(L);
    };
    mysql_set_character_set(mysql, "utf8");
    char query[1024];
    if(id==-1){
        sprintf(query, "select * from %s",
                M->UserFileShare);
    }else{
        sprintf(query, "select * from %s where user=%d",
                M->UserFileShare,
                id);
    }
    int ret = mysql_query(mysql, query);
    if (ret != 0) {
        LOG("mysql", "error", "select 404 %s---%d\n", query, ret);
        free_File_Share(L);
        return NULL;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        free_File_Share(L);
        LOG("mysql", "error", "error_mysql_store_result 405  [__%d__] %s table %s\n", __LINE__, mysql_error(mysql), query);
        return NULL;
    }
    int cot=0;
    while ((row = mysql_fetch_row(res))) {
        cot++;
        char *pVoid=NULL;
        L1->user = (int)strtol(row[0], &pVoid, 10);
        strcpy(L1->sha256,row[1]);
        strcpy(L1->createtime,row[2]);
        strcpy(L1->filename,row[3]);
        L1->pv=(int) strtol(row[5],&pVoid,10);
        File_Share *new_L = New_File_Share();
        L2 = L1;
        L1->next = new_L;
        L1 = new_L;
    }
    free_File_Share(L1);
    if(!cot){
        L=NULL;
    }else{
        L2->next = NULL;
    }
    delet_Mysqluser(M);
    mysql_free_result(res);
    mysql_close(mysql);
    return L;
}

cJSON * init_File_Share(File_Share* L){
    cJSON *obje = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    int cont = 0;
    while(L){
        cont++;
        cJSON * user_info = cJSON_CreateObject();
        cJSON_AddNumberToObject(user_info,"user",L->user);
        cJSON_AddStringToObject(user_info,"sha256",L->sha256);
        cJSON_AddStringToObject(user_info,"createtime",L->createtime);
        cJSON_AddStringToObject(user_info,"filename",L->filename);
        cJSON_AddNumberToObject(user_info,"pv",L->pv);
        cJSON_AddItemToObject(data,L->filename,user_info);
        L=L->next;
    }
    LOG("FileShare","OK","%s\n", cJSON_Print(data));
    cJSON_AddNumberToObject(obje,"cont",cont);
    cJSON_AddItemToObject(obje,"data",data);
    return obje;
}
void get_101(User_Table * User,int id,char *buf_){
    cJSON * json_ = init_User_Table(User);
    char * data_= cJSON_Print(json_);
    char outstr1[1024] = {0};
    base64_encode(data_, strlen(data_),outstr1);
    sprintf(buf_,"{\"data\":\"%s\",\"type\":200}",outstr1);
    LOG("userinfo","base64","%s\n",outstr1);
    free(data_);
    free_User_Table(User);
    cJSON_Delete(json_);
    json_=NULL;
    User=NULL;
    data_=NULL;
}
void get_102(User_File_List *List,int id,char* buf){
    cJSON * cjson = init_User_File_List(List);
    char * data = cJSON_Print(cjson);
    char outstr1[1024] = {0};
    base64_encode(data, strlen(data),outstr1);
    sprintf(buf,"{\"data\":\"%s\",\"type\":200}",outstr1);
    LOG("userinfo","base64","%s\n",outstr1);
    cJSON_Delete(cjson);
    free_User_File_List(List);
    free(data);
    data=NULL;
    List=NULL;
    cjson=NULL;
}