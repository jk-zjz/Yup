#ifndef _FDFS_API_H
#define _FDFS_API_H
#include <make_log.h>
//删除
typedef struct {
    char source_id[10];
    char source_ip_addr[20];
    char create_timestamp[50];
    char size[5];
    char crc32[15];
}File_info;

void show_File_info(File_info *p);
File_info *  my_file_info(const char *conf_filename,char * file_id);
#endif