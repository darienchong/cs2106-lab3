CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE
LDLIBS=-lpthread

.PHONY: clean

train_runner_small_test_ex4: entry_controller.o exit_controller.o train_runner_small_test_exit.o
train_runner_big_test_ex4: entry_controller.o exit_controller.o train_runner_big_test_exit.o
clean:
	rm entry_controller.o exit_controller.o train_runner.o train_runner

.PHONY: all
all: train_runner
