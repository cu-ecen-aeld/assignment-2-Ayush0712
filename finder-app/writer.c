#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>  // Needed for close()
#include <stdlib.h>  // Needed for exit()
#include <syslog.h>

#define NUMBER_OF_ARGS 3

int main(int argc, char *argv[]){
    openlog(NULL, 0, LOG_USER);
    syslog(LOG_DEBUG,  "Writing %s to %s", argv[2], argv[1]);
    if(argc != NUMBER_OF_ARGS){
        syslog(LOG_ERR,  "Invalid number of input args : %d\n", argc);
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
    if(fd == -1){
        perror("file path");
        syslog(LOG_ERR,  "Unablle to create the specified file %s", argv[1]);
        return 1;
    }

    int bytes_written = write(fd, argv[2], strlen(argv[2]));
    if(bytes_written == -1){
        perror("bytes written");
        return -1;
    }
    else if(bytes_written != strlen(argv[2])){
        syslog(LOG_ERR,  "Possible error with write, not all bytes got written\n");
    }
    close(fd);
    return 0;
}