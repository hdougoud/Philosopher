/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/15 14:35:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/fork.h"
#include "../include/struct.h"

void	clean_exit(t_data *data)
{
	usleep(1000);
	sem_post(data->death_check);
	sem_close(data->fork);
	sem_close(data->print);
	sem_close(data->satiated);
	sem_close(data->death_check);
	sem_close(data->this_philo.end.sem);
	sem_close(data->this_philo.last_meal.sem);
	sem_unlink(data->this_philo.end.sem_name);
	sem_unlink(data->this_philo.last_meal.sem_name);
	pthread_join(data->this_philo.end.thread, NULL);
	pthread_join(data->this_philo.last_meal.thread, NULL);
	exit(EXIT_SUCCESS);
}

void	print_fork_error(t_data *data, char *str)
{
	sem_wait(data->print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit program"RESET);
	sem_post(data->print);
	sem_post(data->satiated);
	clean_exit(data);
}

static char	*find_semname(int id, char *sem_name, char *generic)
{
	int		i;
	int		j;
	char	nb[5];

	i = 0;
	j = 0;
	while (generic[i])
	{
		sem_name[i] = generic[i];
		i++;
	}
	ft_itoa(id, nb);
	while (nb[j])
	{
		sem_name[i++] = nb[j++];
	}
	sem_name[i] = '\0';
	return (sem_name);
}

static int	init_philo_struct(t_data *data, int id)
{
	data->this_philo.id = id;
	data->this_philo.meals = 0;
	data->this_philo.end.status = 0;
	find_semname(id, data->this_philo.last_meal.sem_name, "/sem_last_meal_");
	sem_unlink(data->this_philo.last_meal.sem_name);
	data->this_philo.last_meal.sem = sem_open(data->this_philo.last_meal.sem_name, O_CREAT | O_EXCL, 0644, 1);
	find_semname(id, data->this_philo.end.sem_name, "/sem_end_");
	sem_unlink(data->this_philo.end.sem_name);
	data->this_philo.end.sem = sem_open(data->this_philo.end.sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (gettimeofday(&data->this_philo.last_meal.tv, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	if (gettimeofday(&data->this_philo.nap_time, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	return (0);
}

void	start_routine(t_data *data, int id)
{
	init_philo_struct(data, id);
	sem_wait(data->death_check);
	if (data->philosophers == 1)
	{
		print_activity(data, TAKEN_FORK);
		usleep(data->time_to_die * 1000);
		print_activity(data, DIED);
		clean_exit(data);
	}
	init_monitorings(data);
	if ((id % 2) == 0)
		usleep(50);
	next_action(data);
	clean_exit(data);
}
