#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int	item_ready = 0;
pthread_mutex_t	key;
pthread_cond_t	cond;

void	*produce(void *arg) {
	printf("Producer thread start it\n");
	(void)arg;
	for (int i = 0; i < 10; i++) {
		pthread_mutex_lock(&key);
		if (!item_ready)  {
			printf("(PRODUCER) Making item... \n");
			sleep(2);
			item_ready = 1;
			pthread_cond_signal(&cond);
			printf("(PRODUCER) Item ready!\n");
		}
		while (item_ready) {
			printf("(PRODUCER) Item already created it!\n");
			pthread_cond_wait(&cond, &key);
		}
		pthread_mutex_unlock(&key);
		printf("(PRODUCER) Finished loop %d\n", i);
	}
}

void	*consume(void *arg) {
	(void)arg;
	printf("Consumer thread start it\n");
	for (int i  = 0; i < 10; i++) {
		pthread_mutex_lock(&key);
		while (item_ready == 0) {
			printf("(CONSUMER) No item... waiting\n");
			pthread_cond_wait(&cond, &key);
		}

		printf("(CONSUMER) Consuming item\n");
		sleep(2);
		item_ready = 0;
		pthread_cond_signal(&cond);
		printf("(CONSUMER) Item consumed\n");
		pthread_mutex_unlock(&key);
		printf("(CONSUMER) Finished loop %d\n", i);
	}
}


int	main(void) {
	pthread_t	producer;
	pthread_t	consumer;

	pthread_mutex_init(&key, NULL);

	pthread_create(&producer, NULL, &produce, NULL);
	pthread_create(&consumer, NULL, &consume, NULL);

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	pthread_mutex_destroy(&key);
	pthread_cond_destroy(&cond);
	return (0);
}
