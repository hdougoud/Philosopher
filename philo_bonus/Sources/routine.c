/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/14 01:05:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/fork.h"
#include "../include/struct.h"

// void	clean_exit(t_data *data, const int id)
// {
// 	int	i;

// 	i = 0;
// 	(void) id;
// 	usleep(1000);
// 	sem_close(data->fork);
// 	sem_close(data->print);
// 	sem_close(data->satiated);
// 	sem_close(data->death_check);
// 	while (i < data->philosophers)
// 	{
// 		sem_close(data->philo[id].end.sem);
// 		sem_close(data->philo[id].last_meal.sem);
// 		i++;
// 	}
// 	free(data->philo);
// 	exit(EXIT_SUCCESS);
// }

// void	check_the_end(t_data *data, const int id)
// {
// 	int	status;

// 	status = 0;
// 	sem_wait(data->philo[id].end.sem);
// 	if (data->philo[id].end.status == 1)
// 		status = 1;
// 	sem_post(data->philo[id].end.sem);
// 	if (status == 1)
// 		clean_exit(data, id);
// }

// void	print_fork_error(t_data *data, const int id, char *str)
// {
// 	sem_wait(data->print);
// 	putstr_fd(2, RED"Error\n");
// 	putstr_fd(2, str);
// 	putstr_fd(2, YELLOW"Exit program"RESET);
// 	sem_post(data->print);
// 	sem_post(data->satiated);
// 	clean_exit(data, id);
// }

// static char	*find_semname(const int id, char *sem_name, char *generic)
// {
// 	int		i;
// 	int		j;
// 	char	nb[5];

// 	i = 0;
// 	j = 0;
// 	while (generic[i])
// 	{
// 		sem_name[i] = generic[i];
// 		i++;
// 	}
// 	ft_itoa(id, nb);
// 	while (nb[j])
// 	{
// 		sem_name[i++] = nb[j++];
// 	}
// 	sem_name[i] = '\0';
// 	return (sem_name);
// }

// static int	init_philo_struct(t_philo *philo, int id)
// {
// 	(void) id;
// 	philo->meals = 0;
// 	philo->killed = 0;
// 	philo->end.status = 0;
// 	// find_semname(id, philo->last_meal.sem_name, "/sem_last_meal_");
// 	// sem_unlink(philo->last_meal.sem_name);
// 	// philo->last_meal.sem = sem_open(philo->last_meal.sem_name, O_CREAT | O_EXCL, 0644, 1); //ganna create leaks
// 	// find_semname(id, philo->end.sem_name, "/sem_end_");
// 	// sem_unlink(philo->end.sem_name);
// 	// philo->end.sem = sem_open(philo->end.sem_name, O_CREAT | O_EXCL, 0644, 1);
// 	//if (gettimeofday(&philo->last_meal.tv, NULL))
// 	//	return (print_error(data->print, "gettimeofday : function failed"));
// 	//if (gettimeofday(&philo->nap_time, NULL))
// 	//	return (print_error(data->print, "gettimeofday : function failed"));
// 	return (0);
// }

void	start_routine(t_data *data)
{
	//t_philo	philo;

	//init_philo_struct(&philo, id);
	//(void)	philo;
	// if ((id % 2) == 0)
	// 	usleep(50);
	if (data->philosophers == 1)
	{
		//print_activity(data, id, TAKEN_FORK);
		usleep(data->time_to_die * 1000);
		//clean_exit(data, id);
	}
	//next_action(data, id);
	//clean_exit(data, id);
	if (0 < data->philosophers)
	{
		sem_wait(data->print);
		printf("Hello i'm philo 0\n");
		sem_post(data->print);
	}
	usleep(100000);
	exit(EXIT_SUCCESS);
}
