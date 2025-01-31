/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:40:54 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/31 10:12:13 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long long		start_time;
	pthread_mutex_t	game_mutex;
	bool			game_over;
}	t_data;

typedef struct s_philosopher
{
	t_data			*data;
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

int			ft_atoi(const char *nptr);
bool		errors_check(int argc, char **argv);
bool		ft_isdigit_str(char *str);
int			init_data(t_data *data, char **argv);
void		init_philosophers(t_philosopher *philosophers, t_data *data);
long long	get_time_in_ms(void);
int			check_end(t_philosopher *philo);
#endif