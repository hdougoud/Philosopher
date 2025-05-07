/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:26:59 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 18:17:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (mutex)
		pthread_mutex_destroy(mutex);
	mutex = NULL;
}

static void safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	free_global_struct(t_global *global)
{
	int	i;

	i = 0;
	if (!global)
		return;
	if (global->is_finished)
		safe_mutex_destroy(&global->is_finished->mutex);
	if (global->satiated)
		safe_mutex_destroy(&global->satiated->mutex);
	while ((global->fork && global->args) && i < global->args->philosophers)
		safe_mutex_destroy(&global->fork[i++]);
	safe_mutex_destroy(&global->print);
	safe_free((void **)&global->tv);
	safe_free((void **)&global->fork);
	safe_free((void **)&global->satiated);
	safe_free((void **)&global->is_finished);
	safe_free((void **)&global);
}

void	free_all(t_data **data, t_global *global)
{
	int	i;

	i = -1;
	if (data && data[0]->is_finished)
		safe_mutex_destroy(&data[0]->is_finished->mutex);
	if (data && data[0]->satiated)
		safe_mutex_destroy(&data[0]->satiated->mutex);
	if (data && data[0]->print)
		safe_mutex_destroy(data[0]->print);
	if (data && data[0])
	{
		safe_free((void **)&data[0]->is_finished);
		safe_free((void **)&data[0]->satiated);
		safe_free((void **)&data[0]->timer);
	}
	while (data && data[++i])
	{
		pthread_mutex_destroy(data[i]->right_hand->mutex);
		safe_free((void **)&data[i]->right_hand);
		safe_free((void **)&data[i]->left_hand);
		safe_free((void **)&data[i]);
	}
	safe_free((void **)&data);
	safe_free((void **)&global->fork);
	safe_free((void **)&global);
}
