//
// Created by 35148 on 2024/3/14.
//
#include "my_mysql_api.h"

MYSQL* my_mysql_getid(Mysqluser* M,MYSQL*mysql){
    return mysql_real_connect(mysql,
                           M->Ip,
                           M->name,
                           M->passwrod,
                           M->table,
                           (unsigned int)atoi(M->port),
                           NULL,
                           0);
}

int my_mysql_register(Mysqluser* M,Register *R,int * id)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL * mysql = NULL;
    mysql = mysql_init(NULL);
    if(!my_mysql_getid(M,mysql))
    {
        LOG("mysql","error","error 401 mysql_real_connect fial %d--%s \n",__LINE__,mysql_error(mysql));
        return 401;
    }
    mysql_set_character_set(mysql,"utf8");
    char _register_[1024];
    char * T =getTime();
    sprintf(_register_,"insert into %s (name,nickname,phone,email,createtime,passwrod) "
                "values('%s','%s','%s','%s','%s','%s');",
            M->user_table,
            R->accout,
            R->name,
            R->phone,
            R->em,
            T,
            R->password
            );
    int ret = mysql_query(mysql,_register_);
    free(T);
    if(ret!=0){
        LOG("mysql","error"," install 402 %s---%d\n",_register_,ret);
        return 402;
    }
    char _register_id[512]={0};
    sprintf(_register_id,"select id from %s where name='%s'",
            M->user_table,
            R->accout);
    ret = mysql_query(mysql,_register_id);
    if(ret!=0){
        LOG("mysql","error","error 404[%d]_select_%s\n",__LINE__,_register_id);
        return 404;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        LOG("mysql","error", "error_mysql_store_result 405  [__%d__]  %s  name: %s  table\n",__LINE__,mysql_error(mysql),R->accout);
        return 405;
    }
    if (mysql_num_rows(res) > 0) {
        row = mysql_fetch_row(res);
        int ii = atoi(row[0]); // 假设id是整数类型，并且是第一列
        *id =ii;
    } else {
        LOG("mysql","error","No record found for name 405 [--%d--]--id :%s\n",__LINE__,R->name);
    }
    LOG("mysql","register","OK  %s\n",R->name);
    mysql_free_result(res);
    mysql_close(mysql);
    return 200;
}
//初始化
Mysqluser * init_Mysqluser()
{
    Mysqluser * M  = (Mysqluser*)malloc(sizeof(Mysqluser));
    dictionary * ini = iniparser_load(CONF_INI);
    strcpy(M->name, iniparser_getstring(ini,"MYSQL:Name","null"));
    strcpy(M->passwrod, iniparser_getstring(ini,"MYSQL:Passwrod","null"));
    strcpy(M->table, iniparser_getstring(ini,"MYSQL:Table","null"));
    strcpy(M->Ip, iniparser_getstring(ini,"MYSQL:Ip","null"));
    strcpy(M->port, iniparser_getstring(ini,"MYSQL:Port","null"));
    strcpy(M->user_table, iniparser_getstring(ini,"MYSQL:UserTable","null"));
    strcpy(M->UserFileList, iniparser_getstring(ini,"MYSQL:UserFileList","null"));
    strcpy(M->UserFileCount, iniparser_getstring(ini,"MYSQL:UserFileCount","null"));
    strcpy(M->FileInfo, iniparser_getstring(ini,"MYSQL:FileInfo","null"));
    strcpy(M->UserFileShare, iniparser_getstring(ini,"MYSQL:UserFileShare","null"));
    iniparser_freedict(ini);
    return M;
}
/*
 *
 * 通过用户验证密码 返回的id 失败为-1
 * */
int Matched_password(loguser *L,Mysqluser* M,int *i){
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL * mysql = NULL;
    mysql = mysql_init(NULL);
    //建立mysql连接
    if(!my_mysql_getid(M,mysql)){
        LOG("mysql","error","401 [%d]\n",__LINE__);
        return 401;
    }
    char find_passwrod[512]={0};
    sprintf(find_passwrod,"select id,passwrod from %s where name='%s';",
            M->user_table,
            L->user);
    int ret = mysql_query(mysql,find_passwrod);
    if(ret!=0){
        mysql_close(mysql);
        LOG("mysql","error","error 404 [%d]_select_%s\n",__LINE__,find_passwrod);
        return 404;
    }
    res = mysql_store_result(mysql);
    if (res == NULL) {
        mysql_close(mysql);
        LOG("mysql","error", "error_mysql_store_result 405 [__%d__]  %s  name: %s  table\n",__LINE__,mysql_error(mysql));
        return 405;
    }
    char* passwrod_;
    if (0 < mysql_num_rows(res)) {
        row = mysql_fetch_row(res);
        *i = atoi(row[0]); // 假设id是整数类型，并且是第一列
        passwrod_=row[1];
    } else {
        mysql_close(mysql);
        LOG("mysql","error","No record found for name 405 [--%d--]--id :%s\n",__LINE__);
        return 405;
    }

    char buf[SHA256_DIGEST_LENGTH * 2 + 1];
    LOG("1","2","%s",passwrod_);
    sha256_K(buf,passwrod_);

    LOG("mysql","passwrod"," %s \n [mtsql :%s]:[qt: %s]\n",passwrod_,buf,L->password);
    if(strcasecmp(buf,L->password) != 0){
        mysql_free_result(res);
        mysql_close(mysql);
        return 404;
    }
    mysql_free_result(res);
    mysql_close(mysql);
    return 200;
}
//解决sql注入
MYSQL_STMT * mysql_sql_inject(int count,MYSQL *mysql,char * sql,...) {
    MYSQL_BIND ** P;
    MYSQL_STMT *stmt = NULL;
    va_list args;
    //告诉sql是最后一个固定参数
    va_start(args,sql);
    int i=0;
    P =(MYSQL_BIND **)malloc(count*sizeof(MYSQL_BIND));
    //预编
    stmt = mysql_stmt_init(mysql);
    if (!stmt) {
        LOG("mysql","inject","%s  预编失败\n",mysql_error(mysql));
        free(P);
        va_end(args); // 清理
        return NULL;
    }
    //准备sql
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        LOG("mysql","inject","%s sql语句出错\n",mysql_stmt_error(stmt));
        free(P);
        va_end(args); // 清理
        return NULL;
    }
    unsigned long int_length=0;
    for (; i < count; ++i) {
        char *str = va_arg(args, char *); // 获取下一个char *类型的参数
        if (str == NULL) { // 检查指针是否为NULL，以避免打印空指针
            LOG("mysql","inject","value NULL :%d\n",i);
            free(P);
            va_end(args); // 清理
            return NULL;
        }
        P[i]->buffer_type = MYSQL_TYPE_STRING;
        P[i]->buffer = str;
        P[i]->buffer_length = strlen(str);
        P[i]->length = &int_length;
        P[i]->is_null = 0;
    }
    //绑定信息
    if (mysql_stmt_bind_param(stmt, *P) != 0) {
        LOG("mysql","inject", "Error 绑定？ parameter: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        free(P);
        return NULL;
    }
    //执行
    if (mysql_stmt_execute(stmt) != 0) {
        LOG("mysql","inject","Error 执行 statement: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        free(P);
        return NULL;
    }
    //存储结果集
    if (mysql_stmt_store_result(stmt)) {
        LOG("mysql","inject","mysql_stmt_store_result failed\n");
        mysql_stmt_close(stmt);
        free(P);
        return NULL;
    }
    free(P);
    va_end(args); // 清理
    return stmt;
}
//释放
void delet_Mysqluser(Mysqluser* M)
{
    free(M);
}
