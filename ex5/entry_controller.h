/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * This file contains declarations. You should only modify the entry_controller_t struct,
 * as the method signatures will be needed to compile with the runner.
 */
#ifndef __CS2106_ENTRY_CONTROLLER_H_
#define __CS2106_ENTRY_CONTROLLER_H_

#include <semaphore.h>

#define ENTRY_CONTROLLER_MAX_USES 5000 // we impose a limit on the number of uses we can
                                       // have

typedef struct entry_controller {
    // define your variables here
    
    // A general semaphore initialised to the number of free bays.
    sem_t num_free_bays;
    
    // Keeps track of how many people are currently in queue
    int num_trains_in_queue;
    // Mutex for controlling access to num_trains_in_queue
    sem_t queue_semaphore;
    
} entry_controller_t;

void entry_controller_init( entry_controller_t *entry_controller, int loading_bays );
void entry_controller_wait( entry_controller_t *entry_controller );
void entry_controller_post( entry_controller_t *entry_controller );
void entry_controller_destroy( entry_controller_t *entry_controller );

#endif // __CS2106_ENTRY_CONTROLLER_H_
