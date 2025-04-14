#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void	*handle_thread(void *status)
{
	int *stat;

	stat = (int *)status;
	usleep(10000);
	printf("Bonjour, je suis le thread numéro %d\n", *stat);
}

pthread_t	*alloc_thread(int n_thread)
{
	int			i;
	pthread_t	*thread_tab;

	i = 0;
	thread_tab = malloc(sizeof(pthread_t) * n_thread);
	if (!thread_tab)
		exit(EXIT_FAILURE);
	return (thread_tab);
}

int main (int argc, char **argv)
{
	int			i;
	int			n_thread;
	int			*status_bar;
	pthread_t	*thread_tab;

	i = 0;
	if (argc != 2)
		return (1);
	n_thread = atoi(argv[1]);
	
	thread_tab = alloc_thread(n_thread);
	status_bar = malloc(sizeof(int) * n_thread);
	if (!status_bar)
		return (1);

	while (i < n_thread)
	{
		status_bar[i] = i + 1;
		if (pthread_create(&thread_tab[i], NULL, handle_thread, (void *) &status_bar[i]) == -1)
		{
			printf("Create thread failed");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < n_thread)
	{
		pthread_join(thread_tab[i], NULL);
		i++;
	}
	return (0);
}