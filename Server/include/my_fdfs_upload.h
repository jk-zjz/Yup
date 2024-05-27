#ifndef _FDFS_API_H
#define _FDFS_API_H
//正常上传
#include <stdlib.h>
int my_upload_file(const char *conf_filename,const char * local_filename,char * file_id);
//上传可以追加的文件
int my_upload_appender(const char * conf_filename,const char *local_filename,char * file_id);
//追加
int my_upload_appender_file(const char * conf_filename,const char *local_filename,char * appender_file_id);
#endif