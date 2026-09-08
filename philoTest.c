#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/* trying to replicate simple philosophers dinning problem
(as simple as possible) */


// this will be shared between threads, 0 it means the fork is on the table
// 1 it means fork is on hands
int forks[5] = {0, 0, 0, 0, 0};
int SIZE = sizeof(forks) / sizeof(int);

pthread_mutex_t	lock_1;

void	eat() {
	printf("eating...");
	sleep(1);
}

void	think() {
	printf("thinking... ");
	sleep(1);
}

/* Here will try to grab both forks

FIX LATER: maybe try to put everything in a loop so it constantly tries to grab
forks idk
*/
void	*tries_to_eat(void *arg) {
	struct		timespec ts;
	int id =	(int)(long)arg;
	int	left = 0;
	int right = 0;

	clock_gettime(CLOCK_REALTIME, &ts);
	printf("ID (%d) started\n", id);
	pthread_mutex_lock(&lock_1);
	if (forks[(SIZE - 1) - id] == 0) {
		// grab left
		printf("(%d) grabbed left fork!\n", id);
		left = 1;
		forks[(SIZE - 1) - id] = 1;
	}

	if (forks[(id - 1 + SIZE) % SIZE] == 0) {
		// grab right
		right = 1;
		forks[(id - 1 + SIZE) % SIZE] = 1;
		printf("(%d) grabbed right fork!\n", id);
	}
	pthread_mutex_unlock(&lock_1);
	printf("(%d)[left = %d | right = %d]\n", id, left, right);
}

int	main(void) {
	pthread_t philo[5];

	pthread_mutex_init(&lock_1, NULL);

	// create 5 philosofers
	for (int i = 0; i < 5; i++) {
		/* Instead of passing the address of i, passing the value itself but
		reading as a "long int" than read as a void pointer. (this way I take
		the literal value, instead of the address of the value)*/
		if (pthread_create(&philo[i], NULL, tries_to_eat, (void *)(long)i) != 0)
			perror("Failed to create thread !!!");
	}

	// joining everyone
	for (int i = 0; i < 5; i++) {
		if (pthread_join(philo[i], NULL) != 0)
			perror("Failed to join thread !!!");
	}

	printf("[");
	for (int i = 0; i < 5; i++) {
		printf(" %d, ", forks[i]);
	}
	printf("]\n");

	pthread_mutex_destroy(&lock_1);
}