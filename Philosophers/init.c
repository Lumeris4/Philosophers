/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:03:02 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/01 16:20:19 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		data->number_time = atoi(argv[5]);
	else
		data->number_time = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (printf("Failed memory allocated\n"), 0);
	while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->start_time = get_time_in_ms();
	pthread_mutex_init(&data->game_mutex, NULL);
	data->game_over = false;
	return (1);
}

void	init_philosophers(t_philosopher *philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].meals_eaten = 0;
		philosophers[i].last_meal = data->start_time;
		philosophers[i].left_fork = &data->forks[i];
		philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}
