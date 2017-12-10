#ifndef CONTROL
#define CONTROL

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

union semun {
  int val;                 // Value for SETVAL 
  struct semid_ds *buf;    // Buffer for IPC_STAT, IPC_SET 
  unsigned short *array;  // Array for GETALL, SETALL 
  struct seminfo *__buf;  // Buffer for IPC_INFO
};

int main();

#endif
