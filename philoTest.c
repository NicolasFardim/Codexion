#include <stdio.h>
#include <pthread.h>
#include <time.h>

/* trying to replicate simple philosophers dinning problem
(as simple as possible) */


// this will be shared between threads, 0 it means the fork is on the table
// 1 it means fork is on hands
int *forks[5] = {0, 0, 0, 0, 0};
int SIZE = sizeof(forks) / sizeof(int);


/* Here will try to grab both forks

FIX LATER: maybe try to put everything in a loop so it constantly tries to grab
forks idk
*/
void	*tries_to_eat(void *arg) {
	int	left = 0;
	int right = 0;
	for (int i = 0; i < SIZE; i++) {
	// CRITICAL SECTION: add mutex later
		if (forks[i] == 0) {
			left = 1;
			forks[i] == 1;
		}
		if (forks[i] == 0)
			right = 1;
			forks[i] == 1;
	}
	if (left == 1 && right == 2)
		eat();
}

void	eat() {
	print("eating...");
	sleep(1);
	return NULL;
}

void	think(void *arg) {
	print("thinking... ");
}

int	main(void) {
	pthread_t philo[5];

	// create 5 philosofers
	for (int i = 0; i < 5; i++) {
		if (pthread_create(philo[i], NULL, tries_to_eat, NULL) != 0)
			perror("Failed to create thread !!!");
	}

	// joing everyone
	for (int i = 0; i < 5; i++) {
		if (pthread_join(philo[i], NULL) != 0)
			perror("Failed to creaet thread !!!");
	}
}