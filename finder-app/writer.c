#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <stddef.h>
#include <errno.h>
int main(int argc, char *argv[]) {
	if (argc < 2) {
        	return EXIT_FAILURE;
    	}
    	const char *filename = argv[1];
    	printf("%s\n",filename);
	FILE *file = fopen(filename,"wb");
	if (file == NULL) {
		fprintf(stderr, "Value of errorno attempting to open file %s: %d\n", filename, errno);
		perror("perror returned");
		openlog(NULL,0,LOG_USER);
		syslog(LOG_ERR, "Invalid Number of arguments: %d", argc);
        	return EXIT_FAILURE;
		//fprintf(stderr, "Error opening file %s: %s\n", filename, strerror(errno));

	}
	const char *content = argv[2]; 	
	if (fputs(content, file) < 0) {
		openlog(NULL,0,LOG_USER);
        	syslog(LOG_DEBUG, "Writing %s to %s", content, filename);
	}
	closelog();
    	fclose(file);
    	return EXIT_SUCCESS;
}
