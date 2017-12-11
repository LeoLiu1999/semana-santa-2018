#include "headers.h"

int main(int argc, char **argv){

  int sem, fd, shm;
  char *currLine;

  union semun us;
  
  //If no command line arguments
  if (argc < 2){
    printf("No specified arguments\n");
    printf("Try again using at least 1 argument in addition to the executable file\n");
    exit(1);
  }

  //creates a semaphore, shared memory, and file
  else if (!strcmp(argv[1], "-c")){
    //Create semaphore and set it to one
    sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (sem == -1){
      printf("Semaphore already exists\n");
      return 0;
    }
    us.val = 1;
    semctl(sem, 0, SETVAL, us); 
    printf("Set semaphore %d's value to %d\n", sem, semctl(sem, 0, GETVAL));
    
    //Create shared memory for line size
    shm = shmget( LINESIZE, sizeof(int), IPC_CREAT | 0644);
    printf("Set Shared Memory\n");

    //Create file
    fd = open("Story", O_CREAT | O_TRUNC, 0644);
    close(fd);
    printf("Story file created\n");
  }

  //Opens the contents of the story file
  else if (!strcmp(argv[1], "-v")){
    printStory();    
  }

  //Remove shared memory, semaphore and the story
  else if (!strcmp(argv[1], "-r")){
    sem = semget(KEY, 1, 0644);
    if (sem == -1){
      printf("Semaphore, shared memory, and story don't exist\n");
      printf("Try running \"./control -c\"\n");
      return 0;
    }

    printf("Wait your turn\n");
    struct sembuf sBuf;
    sBuf.sem_num = 0; //index we want to work on
    sBuf.sem_op = -1; //Down the Semaphore
    sBuf.sem_flg = SEM_UNDO; //Allow OS to undo operation
    semop(sem, &sBuf, 1);
    printf("Aight, you may have access now\n\n");

    semctl(sem, 0, IPC_RMID);
    printf("Semaphore %d removed\n", sem);
    
    shm = shmget(LINESIZE, sizeof(int), 0644);
    shmctl(shm, IPC_RMID, 0);
    printf("Removed Shared Memory\n");

    printStory();
    remove("Story");   
  }

  //if incorrect arguments are used
  else{
    printf("Incorrect arguments\n");
    printf("Try again using either \"-c\", \"-v\", or \"-r\"\n");
  }

  return 0;
}
