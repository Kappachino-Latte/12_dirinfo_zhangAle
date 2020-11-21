#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main () {
	
	DIR *d;
	d = opendir("./");
	struct dirent * entry;
	entry = readdir (d);
	
	printf ("Statistics for Directory: %s\n", entry->d_name);
	
	int size = 0;
	while (entry) {
		if (entry->d_type == DT_REG) {	
			struct stat sb;
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

