#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "sqlfs.h"

int main(int argc, char *argv[])
{
	char *db = "test.db";
	char *path = "/test.txt";
	int rc;
	sqlfs_t *sqlfs = NULL;
	struct fuse_file_info fi;

	printf("Create/open DB\n");
	rc = sqlfs_open(db, &sqlfs);
	if (!rc)
		return 1;

	printf("Begin transaction\n");
	rc = sqlfs_begin_transaction(sqlfs);
	if (!rc)
		return 1;

	printf("Write #1\n");
	memset(&fi, 0, sizeof(fi));
	//rc = sqlfs_proc_open(sqlfs, path, &fi);
	//if (rc < 0)
	//	return 1;
	rc = sqlfs_proc_write(sqlfs, path, "Hello\n", 7, 0, &fi);
	if (rc < 0)
		return 1;

	printf("=> Press return to continue:");
	getchar();

	printf("Write #2\n");
	rc = sqlfs_proc_write(sqlfs, path, " world\n", 8, 5, &fi);
	if (rc < 0)
		return 1;

	printf("Complete transaction\n");
	rc = sqlfs_complete_transaction(sqlfs, 1);
	if (!rc)
		return 1;

	printf("Close DB\n");	
	sqlfs_close(sqlfs);

	return 0;	
}

