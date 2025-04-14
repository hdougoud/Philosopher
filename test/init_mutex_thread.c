#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_current
{
	pthread_mutex_t	mutex;
	int				*current_pos;
}	t_current;


typedef struct s_pos
{
	t_current		*current;
	int				mypos;
}	t_pos;

void	*handle_thread(void *status)
{
	t_pos *position;

	position = (t_pos *)status;
	while (*position->current->current_pos != position->mypos)
	{
		usleep(10);
	}
	pthread_mutex_lock(&(position->current->mutex));
	printf("Bonjour, je suis le thread numéro %d\n", position->mypos);
	*position->current->current_pos += 1;
	pthread_mutex_unlock(&(position->current->mutex));
	return NULL;
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
	int			*actual;
	t_pos		**pos;
	t_current	*current;
	pthread_t	*thread_tab;

	if (argc != 2)
		return (1);

	n_thread = atoi(argv[1]);
	thread_tab = alloc_thread(n_thread);

	pos = malloc(sizeof(t_pos) * n_thread);
	if (!pos)
		return (1);
	actual = malloc(sizeof(int));
	if (!actual)
		return (1);
	current = malloc(sizeof(t_current));
	if(!current)
		return (1);

	pthread_mutex_init(&(current->mutex), NULL);
	*actual = 1;
	while (i < n_thread)
	{
		pos[i] = malloc(sizeof(t_pos));
		if (!pos[i])
			return (1);
		pos[i]->current = current;
		pos[i]->current->current_pos = actual;
		pos[i]->mypos = i + 1;
		if (pthread_create(&thread_tab[i], NULL, handle_thread, (void *) pos[i]))
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