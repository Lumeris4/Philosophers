/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:35 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/01 14:17:39 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->data->num_philos == 1)
	{
		printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
		usleep(philo->data->time_to_die * 1000);
		printf("%lld %d died\n", get_time_in_ms(), philo->id);
		philo->data->game_over = true;
	}
	if (check_end(philo))
		return (NULL);
	while (philo->meals_eaten != philo->data->number_time)
	{
		if (philo->id % 2 == 0)
			usleep(10);
		if (get_time_in_ms() - philo->last_meal >= philo->data->time_to_die)
		{
			printf("%lld %d died\n", get_time_in_ms(), philo->id);
			philo->data->game_over = true;
			break ;
		}
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
		printf("%lld %d is eating\n", get_time_in_ms(), philo->id);
		usleep(philo->data->time_to_eat);
		philo->last_meal = get_time_in_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d is sleeping\n", get_time_in_ms(), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		if (check_end(philo))
			return (NULL);
	}
	return (NULL);
}

void	start_threads(t_philosopher *philosophers, t_data *data)
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

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
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
