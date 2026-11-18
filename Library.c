
#include <stdio.h>
#include <pthread.h>

int available = 3;
pthread_mutex_t lock;

void* reserveBook(void* arg)
{
    int student = *(int*)arg;

    pthread_mutex_lock(&lock);

    if (available > 0)
    {
        available--;
        printf("Student %d reserved a book successfully.\n", student);
    }
    else
    {
        printf("Student %d: Book not available.\n", student);
    }

    printf("Available copies: %d\n\n", available);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t t[5];
    int students[5] = {1, 2, 3, 4, 5};

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++)
        pthread_create(&t[i], NULL, reserveBook, &students[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
