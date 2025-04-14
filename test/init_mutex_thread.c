#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_pos
{
	int	*current;
	int	mypos;
}	t_pos;

void	*handle_thread(void *status)
{
	t_pos *position;

	position = (t_pos *)status;
	while (*position->current != position->mypos)
	{
		usleep(10);
	}
	usleep(10000);
	printf("Bonjour, je suis le thread numéro %d\n", position->mypos);
	*position->current += 1;
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
	int			i = 0;
	int			n_thread;
	t_pos		*pos;
	pthread_t	*thread_tab;

	if (argc != 2)
		return (1);

	pos = malloc(sizeof(t_pos));
	if (!pos)
		return (1);
	pos->current = malloc(sizeof(int));
	if (!pos->current)
		return(1);

	n_thread = atoi(argv[1]);
	thread_tab = alloc_thread(n_thread);

	*(pos)->current = 1;
	while (i < n_thread)
	{
		pos->mypos = i;
		if (pthread_create(&thread_tab[i], NULL, handle_thread, (void *) pos))
		{
			printf("Create thread failed");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < n_thread)
	{
		if (pthread_join(thread_tab[i], NULL))
		{
			printf("Create thread failed");
			return (1);
		}
		i++;
	}
	return (0);
}