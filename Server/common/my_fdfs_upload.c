/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

/*
gcc mina.c ../common/my_fdfs_upload.c 
../common/make_log.c -I ../include/ -I /usr/include/fastdfs/
 -I /usr/include/fastcommon  -lfastcommon -lfdfsclient
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "fdfs_client.h"
#include "logger.h"
#include <make_log.h>
#include<my_fdfs_upload.h>
//group1/M00/00/00/Z2XMh2Xm7uGAJ01MAAAAAAAAAAA450.txt
static void usage(char *argv[])
{
	char buf[128];
	sprintf(buf,"Usage: %s <config_file> <local_filename> " \
		"[storage_ip:port] [store_path_index]\n",argv[0]);
	LOG(__FILE__,"OK",buf);
}
int my_upload_file(const char *conf_filename,const char * local_filename,char * file_id)
{
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;
	
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

	*group_name = '\0';

	if ((result=tracker_query_storage_store(pTrackerServer, \
	                &storageServer, group_name, &store_path_index)) != 0)
	{
		fdfs_client_destroy();
		char buf[128];
		sprintf(buf,"tracker_query_storage fail, " \
				"error no: %d, error info: %s\n", \
					result,STRERROR(result));
		LOG(__FILE__,"error",buf);
		return result;
	}

	result = storage_upload_by_filename1(pTrackerServer, \
			&storageServer, store_path_index, \
			local_filename, NULL, \
			NULL, 0, group_name, file_id);
	if (result == 0)
	{
		printf("%s\n", file_id);
	}
	else
	{
		char buf[128];
		sprintf(buf,"upload file fail, " \
				"error no: %d, error info: %s\n", \
				result,STRERROR(result));
		LOG(__FILE__,"error",buf);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();
	return result;
}
int my_upload_appender(const char * conf_filename,const char *local_filename,char *file_id){

	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;

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


	*group_name = '\0';
	store_path_index = 0;
	if ((result=tracker_query_storage_store(pTrackerServer, \
	                &storageServer, group_name, &store_path_index)) != 0)
	{
		char buf[128];
		sprintf(buf,"tracker_query_storage fail, " \
			"error no: %d, error info: %s\n",result, STRERROR(result));
		LOG(__FILE__,"error",buf);
		fdfs_client_destroy();
		return result;
	}

	result = storage_upload_appender_by_filename1(pTrackerServer, \
			&storageServer, store_path_index, \
			local_filename, NULL, \
			NULL, 0, group_name, file_id);
	if (result != 0)
	{
		char buf[128];
		sprintf(buf,"upload file fail, " \
			"error no: %d, error info: %s\n",result, STRERROR(result));
		LOG(__FILE__,"error",buf);
		tracker_disconnect_server_ex(pTrackerServer, true);
		fdfs_client_destroy();
		return result;
	}

	printf("%s\n", file_id);

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return 0;
}
int my_upload_appender_file(const char * conf_filename,const char *local_filename,char * appender_file_id)
{
	
	ConnectionInfo *pTrackerServer;
	int result;
	
	log_init();
	g_log_context.log_level = LOG_ERR;

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
	if ((result=storage_append_by_filename1(pTrackerServer, \
		NULL, local_filename, appender_file_id)) != 0)
	{
		char buf[128];
        sprintf(buf,"append file fail, " \
			"error no: %d, error info: %s\n",result, STRERROR(result));
		LOG(__FILE__,"OK",buf);
		return result;
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}

