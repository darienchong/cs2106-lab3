/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * This file contains declarations. You should only modify the barrier_t struct,
 * as the method signatures will be needed to compile with the runner.
 */
#ifndef __CS2106_BARRIER_H_
#define __CS2106_BARRIER_H_

#include <semaphore.h>

typedef struct barrier {
  int count;
  // add additional fields here
  
  // We need two mutexes
  // count_mutex (initialised at 1)
  // queue_mutex (initialised at 0)
  
  sem_t count_mutex;
  sem_t queue_mutex;
} barrier_t;

void barrier_init ( barrier_t *barrier, int count );
void barrier_wait ( barrier_t *barrier );
void barrier_destroy ( barrier_t *barrier );

#endif // __CS2106_BARRIER_H_
