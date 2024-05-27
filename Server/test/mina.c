//#include <stdio.h>
//#include <stdarg.h>
//#include <mysql/mysql.h>
//// 定义一个接受可变数量char *类型参数的函数
//void print_strings(int count,MYSQL *mysql,char * sql,...) {
//    va_list args;
//    va_start(args, sql); // 初始化args，并告诉它count是最后一个固定参数
//    int i=0;
//    for (; i < count; ++i) {
//        char *str = va_arg(args, char *); // 获取下一个char *类型的参数
//        if (str != NULL) { // 检查指针是否为NULL，以避免打印空指针
//            printf("%s\n", str);
//        }
//    }
//
//    va_end(args); // 清理
//}
//
//int main() {
//    print_strings(2,NULL,"Hello", "World", "!"); // 输出: Hello, World, !
//    //print_strings(2, "First", "Second"); // 输出: First, Second
//    return 0;
//}
//#include "my_fdfs_upload.h"
//#include "my_fdfs_file_info.h"
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "my_jwt.h"
#include <time.h>
#include "my_json_user.h"
#include "openssl/sha.h"
#include "my_mysql_info.h"
#include "hiredis.h"
#include "read.h"
#include "my_redis_api.h"
#include "my_StrategyRequest.h"
#include "my_jwt.h"

#include <stdio.h>

int main() {
//    User_Table * jk =seletc_User_ALL(50);
//    cJSON * sb = init_User_Table(jk);
//    LOG("nh","12","%s", cJSON_Print(sb));

//    User_Table * kl =seletc_User_ALL(50);
//    printf("%s",cJSON_Parse(init_User_Table(kl)));
    //sorterContext.sortFunc(M,90);

//    char instr[] = "123456789";
//    char outstr1[1024] = {0};
//    base64_encode(instr, strlen(instr),outstr1);
//    printf("base64:%s\n",outstr1);
    MYSQL *mysql = NULL;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    mysql = mysql_init(NULL);
    Mysqluser *M = init_Mysqluser();
    if (!my_mysql_getid(M, mysql)) {
        printf("连接失败\n");
        return 0;
    }
    MYSQL_STMT *kk = mysql_sql_inject(1, mysql, "SELECT * FROM user WHERE id=?","123 OR '1'='1'");
    if (kk == NULL) {
        printf("JB了\n");
        return 0;
    }
    printf("okok思密达\n");
}
////    stmt = mysql_stmt_init(mysql);
////    if (!stmt) {
////        printf("预编错误");
////        return 0;
////    }
////    const char *query = "SELECT * FROM user WHERE id=?";
////    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
////        printf("语句准备错误\n");
////        return 0;
////    }
////    unsigned int id = 50;
////    memset(bind, 0, sizeof(bind));
////    bind[0].buffer_type = MYSQL_TYPE_LONG;
////    bind[0].buffer = (char *) &id;
////    bind[0].is_null = 0;
////    bind[0].length = 0;
////
////    if (mysql_stmt_bind_param(stmt, bind) != 0) {
////        printf("绑定错误\n");
////        return 0;
////    }
////    if(mysql_stmt_execute(stmt) != 0){
////        printf("执行失败");
////        return 0;
////    }
////
////        printf("执行成功\n");
//
//    return 0;
//}
//
//
//
//
//
//
//
//
//
//
////void* userinfo_(Mysqluser *M, size_t id) {
////    // 实现你的排序策略
////    printf("%s--%s--%lu",M->name,M->passwrod,id);
////    return NULL; // 或返回其他void*类型的值
////}
////int main(){
////    SorterContext* sorterContext = (SorterContext *)malloc(sizeof(SorterContext));
////    Mysqluser* M  = init_Mysqluser();
////    setSortStrategy(sorterContext,userinfo_);
////    executeSort(sorterContext,M,10);
//
////    Redis* R =  Init_Redis();
////    Task* T = Net_Task();
////    Task_push_back(T,"1","sdad",12);
////    Task_push_back(T,"2","sd",12);
////    Task_push_back(T,"3","sd",12);
////    Task_push_back(T,"4","sd",12);
////    Task_push_back(T,"5","sd",12);
////    Insert_Redis(T,R);
////    Delet_Redis(R);
////    Task_Delet(T);
////    Mysqluser* M  = init_Mysqluser();
////    SorterContext context;
////
////
////    setSortStrategy(&context, userinfo);
////    executeSort(&context,M,10);
////    unsigned char hash[SHA256_DIGEST_LENGTH];
////    const char *data = "123456";
////    char hash_string[SHA256_DIGEST_LENGTH * 2 + 1]; // +1 for null terminator
////    unsigned int i;
////    // Calculate SHA-256 hash
////    SHA256_CTX sha256;
////    SHA256_Init(&sha256);
////    SHA256_Update(&sha256, data, strlen(data));
////    SHA256_Final(hash, &sha256);
////
////    // Convert hash to hexadecimal string representation
////    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
////        sprintf(hash_string + (i * 2), "%02x", hash[i]);
////    }
////
////    // Print the hash string
////    printf("Hash as string: %s\n", hash_string);
////    return 0;
////}
//
////int main() {
////    const char *hostname = "localhost";
////    int port = 6379;
////    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
////    redisReply *reply;
////
////    // 连接到Redis服务器
////
////    redisContext *c = redisConnect("127.0.0.1", 6379);
////    if(c==NULL){
////        printf("pContext null!\n");
////        exit(1);
////    }
////    if(c->err) {
////        printf("connection error:%s\n", c->errstr);
////        exit(1);
////    }
////
////    // 使用HSET命令设置哈希表的字段值
////    const char *key = "cookie_data";
////    const char *field1 = "123123123";
////    const char *value1 = "45566";
////    const char *field2 = "lk";
////    const char *value2 = "sdasd";
////    reply = redisCommand(c, "HSET %s %s %s", key, field1, value1);
////    freeReplyObject(reply);
////    reply = redisCommand(c, "HSET %s %s %s", key, field2, value2);
////    freeReplyObject(reply);
////    int expire_time = 10; // 10 seconds
////    reply = redisCommand(c, "expire field1 10", key);
////    int i=0;
////    // 使用HGETALL命令获取哈希表的所有字段和值
////    reply = redisCommand(c, "HGETALL %s", key);
////    if (reply->type == REDIS_REPLY_ARRAY) {
////        for (; i < reply->elements; i++) {
////            printf("%s: %s\n", (char*)reply->element[i]->str, (char*)reply->element[i+1]->str);
////            i++; // Skip the value
////        }
////    }
////    freeReplyObject(reply);
////
////    // 断开与Redis服务器的连接
////    redisFree(c);
////
////    return 0;
////}
//
////int main() {
////    redisContext *pContext = redisConnect("127.0.0.1", 6379);
////    File_Share * I =seletc_File_Share(2);
////    cJSON* J = init_File_Share(I);
////    printf("%s", cJSON_Print(J));
////    cJSON_Delete(J);
////    free_File_Share(I);
////
//////    User_Table *T = seletc_User_ALL(-1);
//////    cJSON *json = init_User_Table(T);
//////    printf("%s", cJSON_Print(json));
//////    cJSON_Delete(json);
//////    free_User_Table(T);
//////    User_File_List  * L =seletc_User_File_List(2);
//////    cJSON *json = init_User_File_List(L);
//////    printf("%s", cJSON_Print(json));
//////    cJSON_Delete(json);
//////    free_User_File_List(L);
//////
//////
//////
//////    User_Count *C = seletc_User_Count(3);
//////
//////    printf("%p",C);
//////    cJSON *json = init_User_Count(C);
//////    printf("%s", cJSON_Print(json));
////
////
////    //my_upload_file("/etc/fdfs/client.conf","./bb.txt",buf);
////    //my_upload_appender("/etc/fdfs/client.conf","./bb.txt",buf);
////    //my_download_file("/etc/fdfs/client.conf","group1/M00/00/00/Z2XMh2Xm7uGAJ01MAAAAAAAAAAA450.txt");
////    //my_delete_file("/etc/fdfs/client.conf","group1/M00/00/00/Z2XMh2Xm7uGAJ01MAAAAAAAAAAA450.txt");
////    //my_file_info("/etc/fdfs/client.conf","group1/M00/00/00/Z2XMh2Xm9yCEJT6zAAAAAAAAAAA915.txt");
////    //"/etc/fdfs/client.conf","bb.txt","group1/M00/00/00/Z2XMh2XnOaGEFqPaAAAAAAAAAAA884.txt"
////    //my_upload_appender_file("/etc/fdfs/client.conf","bb.txt","group1/M00/00/00/Z2XMh2XnOaGEFqPaAAAAAAAAAAA884.txt");
//////    MYSQL* mysql;
//////    mysql = mysql_init(NULL);
//////    mysql_real_connect(mysql, "localhost", "root", "486466132Ws.", "cloud_disk", 0, NULL, 0);
//////    if(mysql==NULL){
//////        printf("KONG");
//////    }else{
//////        printf("OK");
//////    }
////
//////    cJSON * J =jwt_decrypt("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3MTA4NDUyMzAsImlkIjo0MiwidXNlciI6IjEyMzQ1Njc4In0.xsl7yx5EGXJ0DU_fEYnLpApc9YERKYhVitFLOrV7cVs",
//////                "hhkkndb");
//////    {
//////        "exp": 1710777069,
//////                "id": 42,
//////                "user": "gg"
//////    }
////
////
//////    jwt_encryption("hhkkndb","{\"exp\": 12345,\"id\": 43, \"user\": \"hh\"}");
////
////
////
//////    time_t current_time;
//////    current_time = time(NULL);
//////
//////    if (current_time == -1) {
//////        perror("Failed to get the current time");
//////        return 1;
//////    }
//////
//////    // 将时间戳转换为本地时间
//////    struct tm *local_time = localtime(&current_time);
//////
//////    // 打印本地时间
//////    printf("Current local time: %s", asctime(local_time));
//////
//////    // 如果只需要时间戳（秒数）
//////    printf("Current timestamp: %ld\n", (long)current_time);
////    return 0;
////}