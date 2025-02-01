/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:35 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/01 16:20:26 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_threads(t_philosopher *philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
			&philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->game_mutex);
		if (data->game_over)
		{
			pthread_mutex_unlock(&data->game_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->game_mutex);
		pthread_join(philosophers[i++].thread, NULL);
	}
}

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philosophers;

	if (!errors_check(argc, argv))
		return (1);
	if (!init_data(&data, argv))
		return (1);
	philosophers = malloc(sizeof(t_philosopher) * data.num_philos);
	if (!philosophers)
		return (printf("error\n"), cleanup(&data), 1);
	init_philosophers(philosophers, &data);
	start_threads(philosophers, &data);
	free(philosophers);
	cleanup(&data);
	return (0);
}
