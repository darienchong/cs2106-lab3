/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * This file contains function definitions. Your implementation should go in
 * this file.
 */

#define SHARED_BETWEEN_THREADS 0
#include <stdio.h>
#include <stdlib.h>
#include "barrier.h"

// Initialise barrier here
void barrier_init ( barrier_t *barrier, int count ) {
	sem_t *count_mutex_ptr = &(barrier -> count_mutex);
	sem_t *queue_mutex_ptr = &(barrier -> queue_mutex);
	
    barrier -> count = count;
    
    // Set up count_mutex, the mutex for barrier->count.
    // Initial value should be 1 (allow 1 person in).
    sem_init(count_mutex_ptr, SHARED_BETWEEN_THREADS, 1);
    
    // Set up queue_mutex, the mutex that blocks all threads
    // until all threads arrive.
    // Initial value should be 0 (no one allowed through).
    sem_init(queue_mutex_ptr, SHARED_BETWEEN_THREADS, 0);
}

void barrier_wait ( barrier_t *barrier ) {
	sem_t *count_mutex_ptr = &(barrier -> count_mutex);
	sem_t *queue_mutex_ptr = &(barrier -> queue_mutex);
	
	sem_wait(count_mutex_ptr);
	barrier -> count = barrier -> count - 1;
	sem_post(count_mutex_ptr);
	
	// count == 0 means everyone's here.
	if (barrier -> count == 0) {
		sem_post(queue_mutex_ptr); // Allow everyone through!	
	}
	
	// All threads but the last will block here.
	sem_wait(queue_mutex_ptr);
	sem_post(queue_mutex_ptr);
}

// Perform cleanup here if you need to
void barrier_destroy ( barrier_t *barrier ) {
	// Destroy all mutexes
	sem_t *count_mutex_ptr = &(barrier -> count_mutex);
	sem_t *queue_mutex_ptr = &(barrier -> queue_mutex);
	
	sem_destroy(count_mutex_ptr);
	sem_destroy(queue_mutex_ptr);
}
