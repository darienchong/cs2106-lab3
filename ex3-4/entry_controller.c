/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * Your implementation should go in this file.
 */
#include "entry_controller.h"
#include <stdbool.h>
#include <stdio.h>

#define SHARED_BETWEEN_THREADS 0

void increment_queue_counter( entry_controller_t *entry_controller ) {
	sem_wait(&(entry_controller -> queue_semaphore));
	entry_controller -> num_trains_in_queue = (entry_controller -> num_trains_in_queue) + 1;
	sem_post(&(entry_controller -> queue_semaphore));
}

void decrement_queue_counter( entry_controller_t *entry_controller ) {
	sem_wait(&(entry_controller -> queue_semaphore));
	entry_controller -> num_trains_in_queue = (entry_controller -> num_trains_in_queue) - 1;
	sem_post(&(entry_controller -> queue_semaphore));
}

void wait_bays( entry_controller_t *entry_controller ) {
	sem_wait(&(entry_controller -> num_free_bays));
}

void signal_bays( entry_controller_t *entry_controller ) {
	sem_post(&(entry_controller -> num_free_bays));
}

void entry_controller_init( entry_controller_t *entry_controller, int loading_bays ) {
	entry_controller -> num_trains_in_queue = 0;
	sem_init(&(entry_controller -> num_free_bays), SHARED_BETWEEN_THREADS, loading_bays);
	sem_init(&(entry_controller -> queue_semaphore), SHARED_BETWEEN_THREADS, 1);
}

void entry_controller_wait( entry_controller_t *entry_controller ) {
	increment_queue_counter(entry_controller);
	
	int my_queue_number = entry_controller -> num_trains_in_queue;
	
	wait_bays(entry_controller);
	while (my_queue_number > 1) {
		signal_bays(entry_controller);
		my_queue_number--;
		wait_bays(entry_controller);
	}
	
	decrement_queue_counter(entry_controller);
}

void entry_controller_post( entry_controller_t *entry_controller ) {
	signal_bays(entry_controller);
}

void entry_controller_destroy( entry_controller_t *entry_controller ) {
	sem_destroy(&(entry_controller -> num_free_bays));
	sem_destroy(&(entry_controller -> queue_semaphore));
}

