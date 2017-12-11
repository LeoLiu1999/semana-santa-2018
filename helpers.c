#include "headers.h"

int checkForStory(int flags){
  int fd = open("Story", flags);
  if (fd == -1){
    printf("Story does not exist, create a story with ./control -c\n");
    exit(1);
  }
  return fd;
}

void printStory(){
    int fd = checkForStory( O_RDONLY);
    
    struct stat sb;
    stat("Story", &sb);

    int size = sb.st_size;
    char buf[size];
    read(fd, buf, size);
    close(fd);
    buf[size] = 0;    
   
    printf("\nSTORY:\n\n%s\n", buf);
}

