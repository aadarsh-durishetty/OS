#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (philosopher_num + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_num + 1) % NUM_PHILOSOPHERS

typedef enum
{
    THINKING,
    HUNGRY,
    EATING
} PhilosopherState;

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond_var[NUM_PHILOSOPHERS];
    PhilosopherState state[NUM_PHILOSOPHERS];
} Monitor;

Monitor monitor;

void pickup_forks(int philosopher_num)
{
    pthread_mutex_lock(&monitor.mutex);
    monitor.state[philosopher_num] = HUNGRY;
    test(philosopher_num);
    while (monitor.state[philosopher_num] != EATING)
        pthread_cond_wait(&monitor.cond_var[philosopher_num], &monitor.mutex);
    pthread_mutex_unlock(&monitor.mutex);
}

void return_forks(int philosopher_num)
{
    pthread_mutex_lock(&monitor.mutex);
    monitor.state[philosopher_num] = THINKING;
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&monitor.mutex);
}

void test(int philosopher_num)
{
    if (monitor.state[philosopher_num] == HUNGRY &&
        monitor.state[LEFT] != EATING &&
        monitor.state[RIGHT] != EATING)
    {
        monitor.state[philosopher_num] = EATING;
        pthread_cond_signal(&monitor.cond_var[philosopher_num]);
    }
}

void *philosopher(void *num)
{
    int philosopher_num = *(int *)num;
    int eat_count = 0;

    while (eat_count < 5)
    { // Each philosopher eats 5 times
        printf("Philosopher %d is thinking\n", philosopher_num);

        usleep(rand() % 500000);

        pickup_forks(philosopher_num);

        printf("Philosopher %d is eating\n", philosopher_num);

        usleep(rand() % 500000);

        return_forks(philosopher_num);

        eat_count++;
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_nums[NUM_PHILOSOPHERS];

    pthread_mutex_init(&monitor.mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_init(&monitor.cond_var[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosopher_nums[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_nums[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    pthread_mutex_destroy(&monitor.mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_destroy(&monitor.cond_var[i]);

    return 0;
}
