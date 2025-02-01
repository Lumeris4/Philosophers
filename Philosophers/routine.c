/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:06:03 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/01 16:11:01 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (detect_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
	pthread_mutex_lock(philo->right_fork);
	if (detect_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
	printf("%lld %d is eating\n", get_time_in_ms(), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	one_philo(t_philosopher *philo)
{
	printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
	usleep(philo->data->time_to_die * 1000);
	printf("%lld %d died\n", get_time_in_ms(), philo->id);
	pthread_mutex_lock(&philo->data->game_mutex);
	philo->data->game_over = true;
	pthread_mutex_unlock(&philo->data->game_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->data->num_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	philo->last_meal = get_time_in_ms();
	while (philo->meals_eaten != philo->data->number_time)
	{
		if (detect_death(philo))
			return (NULL);
		if (philo->id % 2 == 0)
			usleep(10 * 1000);
		philo_eat(philo);
		if (detect_death(philo))
			return (NULL);
		printf("%lld %d is sleeping\n", get_time_in_ms(), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		if (detect_death(philo))
			return (NULL);
		printf("%lld %d is thinking\n", get_time_in_ms(), philo->id);
	}
	return (NULL);
}
