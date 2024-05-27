#ifndef _HTTP_API_H
#define _HTTP_API_H
#include <make_log.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "make_log.h"
struct HHTP_HEAD{
    char filename[100];
    char Content_Type[30];
    char file_id[128];
    size_t file_size;
    void * data;
}typedef HHTP_HEAD;


struct HTTP_fiel_information{
    HHTP_HEAD hhtp_head[10];
    size_t size;
    char Content_Disposition[100];
    char KEY[50];
    bool type;
}typedef HTTP_fiel_information;

HTTP_fiel_information* init_file_size(char * data);
void delet_file(HTTP_fiel_information * HTTP);
void data_migration(const char * file_name,HTTP_fiel_information * HTTP);

#endif
