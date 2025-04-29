/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:22:28 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/29 15:52:16 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DIED "died"
# define IS_EATING "is eating"
# define IS_THINKING "is thinking"
# define IS_SLEEPING "is sleeping"
# define TAKEN_FORK "has taken a fork"
# define SLEEP_TIME 500

typedef struct s_args t_args;
typedef struct s_data t_data;
typedef struct s_mutex t_mutex;
typedef struct s_perso_timer t_perso_timer;
typedef struct s_global_timer t_global_timer;

int				is_ended(t_mutex *is_finished, t_mutex *satiated, t_args *args);
int				update_local_timer(t_perso_timer *timer);
int				uptade_global_timer(t_global_timer *timer);

void			next_activity(t_data *data);
void			check_last_meal(t_data *data);
void			reset_local_timer(t_perso_timer *timer);
void			print_activity(t_data *data, char *activity);

t_perso_timer	*init_personnal_timer_struct(void);

#endif