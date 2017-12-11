#include "client.h"
#include "control.h"

int main(){
  
  int fd, sem, shm;

  fd = checkForStory(O_RDWR | O_APPEND);

  sem = semget(KEY, 1, 0644);

  //Await access
  printf("Wait your turn\n");
  struct sembuf sBuf;
  sBuf.sem_nun = 0; //index we want to work on
  sBuf.sum_op = -1; //Down the Semaphore
  sBuf.sem_flag = SEM_UNDO; //Allow OS to undo operation
  semop(sem, &sBuf, 1);
  printf("Aight, you may use the semaphone now (I hope)\n");

  shm = shmget(LINESIZE, sizeof(int), 0644);
  int *sizeOfLine = shmat(shm, 0, 0644);

  printf("Line last added:\n\n");
  lseek(fd, -1 * *sizeOfLine, SEEK_END); //offset fd from the end of the file
  char lastLine[*sizeOfLine];
  read(fd, lastLine, *sizeOfLine);
  printf("%s\n\n", lastLine);
  
  char input[512];
  printf("Gimme your addition:");
  fgets(input, sizeof(input), stdin);

  lseek(fd, 0, SEEK_END);
  write(fd, input, strlen(input));

  *size = strlen(input);
  shmdt(size):

  sBuf.sem_op = 1;
  semop(sem, &sBuf, 1);
  

  return 0;
}
