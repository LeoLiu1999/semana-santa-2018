#include "control.h"

#define LINESIZE 6940
#define KEY 694

void checkForSem(){
  if (semget(KEY, 1, 0644) == -1){
    printf("Semaphore does not exist\n");
    exit(1);
  }
}

int main(int argc, char **argv){

  int sem, fd, sizeLine;
  char *currLine;

  union semun us;
  
  //If no command line arguments
  if (argc < 2){
    printf("No specified arguments\n");
    printf("Try again using at least 1 argument in addition to the executable file\n");
    exit(1);
  }

  //creates a semaphore and sets its value
  else if (!strcmp(argv[1], "-c")){
    //Create shared memory for line size
    sizeLine = shmget( LINESIZE, sizeof(int), IPC_CREAT | 0600);

    //Create semaphore and set it to one
    sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (sem == -1){
      printf("Semaphore already exists\n");
      return 0;
    }
    us->val = 1;
    semctl(sem, 0, SETVAL, us); 
    printf("Set semaphore %d's value to %d\n", sem, semctl(sem, 0, GETVAL));
  }

  /*
  //views current value of semaphore
  else if (!strcmp(argv[1], "-v")){
    checkForSem();
    sem = semget(KEY, 1, 0644);
    value = semctl(sem, 0, GETVAL);
    printf("Semaphore %d's value: %d\n", sem, value);
  }

  //removes the semaphore
  else if (!strcmp(argv[1], "-r")){
    checkForSem();
    sem = semget(KEY, 1, 0644);
    semctl(sem, 0, IPC_RMID);
    printf("Semaphore %d removed\n", sem);
  }
  */

  //if incorrect arguments are used
  else{
    printf("Incorrect arguments\n");
    printf("Try again using either \"-c N\", \"-v\", or \"-r\"\n");
  }

  return 0;
}
