/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

/*
gcc mina.c ../common/my_fdfs_delete.c  ../common/make_log.c -I  
../include/ -I /usr/include/fastdfs/ 
-I /usr/include/fastcommon -lfastcommon -lfdfsclient
*/


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "fdfs_client.h"
#include "logger.h"
#include<my_fdfs_download.h>

int my_download_file(const char *conf_filename,char * file_id)
{
	char *local_filename;
	ConnectionInfo *pTrackerServer;
	int result;
	int64_t file_size;
	int64_t file_offset;
	int64_t download_bytes;
	
	log_init();
	g_log_context.log_level = LOG_ERR;
	ignore_signal_pipe();

	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return result;
	}

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}

	file_offset = 0;
	download_bytes = 0;


	local_filename = strrchr(file_id, '/');
	if (local_filename != NULL)
	{
		local_filename++;  //skip /
	}
	else
	{
		local_filename = file_id;
	}
	result = storage_do_download_file1_ex(pTrackerServer, \
                NULL, FDFS_DOWNLOAD_TO_FILE, file_id, \
                file_offset, download_bytes, \
                &local_filename, NULL, &file_size);
	if (result != 0)
	{
		char buf[128];
		sprintf(buf,"download file fail, "  \
			"error no: %d, error info: %s\n",result, STRERROR(result));
		LOG("fdfs","error",buf);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return 0;
}

