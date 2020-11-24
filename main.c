#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main (int argc, char **argv) {
	
	DIR *d;
	struct dirent * entry;
	int check;
	char buffer[100];
	char *delete;
	
	if (argv [1] != NULL) {
		check = open(argv[1], O_RDONLY);
       	if (check == -1) {
			printf("%s\n", strerror(errno));
            		return 0;
            	}
            	else {
            		d = opendir(argv[1]);
            		entry = readdir(d);
            		printf ("Statistics for Directory: %s\n", argv[1]);
		}
	}
	
	else {
		printf ("Enter a directory to be scanned: ");
		fgets (buffer, sizeof(buffer), stdin);
		delete = strchr (buffer, '\n');
		if (delete != NULL) {
			*delete = '\0';
		}
		check = open (buffer, O_RDONLY);
		if (check == -1) {
			printf("%s\n", strerror(errno));
            		return 0;
            	}
            	else {
            		d = opendir(buffer);
            		entry = readdir(d);
            		printf ("Statistics for Directory: %s\n", buffer);
		}
	}
	
	struct stat sb;
	if (argv[1] != NULL) {
		stat (argv[1], &sb);
	}
	else {
		stat (buffer, &sb);
	}
	
	int size = 0;
	while (entry) {
		if (entry->d_type == DT_REG) {	
			stat (entry->d_name, &sb);
			size += sb.st_size;
		}
		entry = readdir(d);
	}
	
	printf ("Total Directory Size: %d bytes\n", size);
	
	rewinddir(d);
	entry = readdir(d);
	
	printf ("Directories:\n");
	while (entry) {
		if (entry->d_type == DT_DIR) {	
			printf ("\t%s\n", entry->d_name);
		}
		entry = readdir(d);
	}	
	
	rewinddir(d);
	entry = readdir(d);
	
	printf ("Regular Files:\n");
	while (entry) {
		if (entry->d_type == DT_REG) {	
			printf ("\t%s\n", entry->d_name);
		}
		entry = readdir(d);
	}
	
	closedir(d);
	return 0;
}
