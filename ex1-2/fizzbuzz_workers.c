/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * Your implementation should go in this file.
 */
#include "fizzbuzz_workers.h"
#include "barrier.h" // you may use barriers if you think it can help your
                     // implementation
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// declare variables to be used here

int total_count;
barrier_t *barriers;

// The idea is that we have n barriers
// Each thread must synchronise at the barrier and all print
// before proceeding to the next number.
// At each n, only one thread will call their printing function.

bool is_not_fizzbuzz ( int i) {
	return !(i % 15 == 0);
}

bool is_not_fizz ( int i ) {
	return !(i % 3 == 0);
}

bool is_not_buzz ( int i ) {
	return !(i % 5 == 0);
}

void fizzbuzz_init ( int n ) {
	// We add 1 for ease of use, since then we can
	// treat the array as 1-indexed.
	total_count = n;
	
	barriers = malloc(sizeof(barrier_t) * (n + 1));
	for (int i = 1; i <= n; i++) {
		barrier_init(&barriers[i], 4);
	}
}

void num_thread( int n, void (*print_num)(int) ) {
	for (int i = 1; i <= n; i++) {
		bool is_regular_number = is_not_fizzbuzz(i) && is_not_fizz(i) && is_not_buzz(i);
		
		barrier_wait(&barriers[i]);
		
		if (is_regular_number) {
			print_num(i);
		}
	}
}

void fizz_thread( int n, void (*print_fizz)(void) ) {
	for (int i = 1; i <= n; i++) {
		bool is_fizz = is_not_fizzbuzz(i) && !is_not_fizz(i);
		
		barrier_wait(&barriers[i]);
		
		if (is_fizz) {
			print_fizz();
		}
	}
}

void buzz_thread( int n, void (*print_buzz)(void) ) {
	for (int i = 1; i <= n; i++) {
		bool is_buzz = is_not_fizzbuzz(i) && !is_not_buzz(i);
		
		barrier_wait(&barriers[i]);
		
		if (is_buzz) {
			print_buzz();
		}
	}
}

void fizzbuzz_thread( int n, void (*print_fizzbuzz)(void) ) {
	for (int i = 1; i <= n; i++) {
		bool is_fizzbuzz = !is_not_fizzbuzz(i);
		
		barrier_wait(&barriers[i]);
		
		if (is_fizzbuzz) {
			print_fizzbuzz();
		}
	}
}

void fizzbuzz_destroy() {
	for (int i = 0; i < total_count + 1; i++) {
		barrier_destroy(&barriers[i]);
	}
	free(barriers);
}
