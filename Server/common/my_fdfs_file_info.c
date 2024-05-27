/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/
/**
gcc mina.c ../common/my_fdfs_file_info.c 
../common/make_log.c -I ../include/ 
-I /usr/include/fastdfs/ -I /usr/include/fastcommon 
-lfastcommon -lfdfsclient
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fdfs_client.h"
#include "logger.h"
#include<my_fdfs_file_info.h>
void show_File_info(File_info *p){
	printf("[%s\n,%s\n,%s\n,%s\n,%s\n]",
		p->source_id,p->source_ip_addr,p->create_timestamp,p->size,p->crc32);
}

File_info * my_file_info(const char *conf_filename,char * file_id)
{
	int result;
	FDFSFileInfo file_info;
	
	log_init();
	g_log_context.log_level = LOG_ERR;
	ignore_signal_pipe();

	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return 0;
	}
	memset(&file_info, 0, sizeof(file_info));
	result = fdfs_get_file_info_ex1(file_id, true, &file_info);
	if (result != 0)
	{
		char buf[128];
		sprintf(buf,"query file info fail, " \
			"error no: %d, error info: %s\n" \
			,result, STRERROR(result));
		LOG(__FILE__,"OK",buf);
	}
	else
	{
		char szDatetime[32];
		char string[16] = {0};

		sprintf(string,"%d",file_info.source_id);
		File_info * p=(File_info *)malloc(sizeof(File_info));
		sprintf(p->source_id,"%s", string);

		sprintf(p->source_ip_addr,"%s", file_info.source_ip_addr);
		
		sprintf(p->create_timestamp,"%s", formatDatetime(
			file_info.create_timestamp, "%Y-%m-%d %H:%M:%S", \
			szDatetime, sizeof(szDatetime)));
		
		sprintf(string,"%ld",file_info.file_size);
		sprintf(p->size,"%s", string);
		
		sprintf(string,"%d",file_info.crc32);
		sprintf(p->crc32,"%s", string);


		return p;
	}

	tracker_close_all_connections();
	fdfs_client_destroy();

	return NULL;
}

