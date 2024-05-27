/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "fdfs_client.h"
#include "logger.h"
#include<my_fdfs_delete.h>

int my_delete_file(const char *conf_filename,char * file_id){
	ConnectionInfo *pTrackerServer;
	int result;

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
	if ((result=storage_delete_file1(pTrackerServer, NULL, file_id)) != 0)
	{
		char buf[128];
		sprintf(buf,"delete file fail, " \
			"error no: %d, error info: %s\n",result, STRERROR(result));
		LOG("fdfs","error",buf);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}

