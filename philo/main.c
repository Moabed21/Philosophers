#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *routine()
{
    while(1)
    {
        printf(" test \n \n");
        sleep(3);
    }
    return (NULL);
}

int main()
{
    pthread_t t1;

    pthread_create(&t1, NULL ,&routine, NULL);
    //pthread_create(&t2, NULL ,&routine, NULL);
    pthread_join(t1, NULL);
    //pthread_join(t2, NULL);
}