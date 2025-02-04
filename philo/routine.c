/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:06:03 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/04 09:13:36 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (detect_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	mutex_print(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right_fork);
	if (detect_death(philo))
	{
		unlock_fork(philo);
		return ;
	}
	mutex_print(philo, "has taken a fork\n");
	mutex_print(philo, "is eating\n");
	usleep(philo->data->time_to_eat * 1000);
	if (detect_death(philo))
	{
		unlock_fork(philo);
		return ;
	}
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	unlock_fork(philo);
}

static void	one_philo(t_philosopher *philo)
{
	mutex_print(philo, "has taken a fork\n");
	usleep(philo->data->time_to_die * 1000);
	mutex_print(philo, "died\n");
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
			usleep(1000);
		philo_eat(philo);
		if (detect_death(philo))
			return (NULL);
		mutex_print(philo, "is sleeping\n");
		usleep(philo->data->time_to_sleep * 1000);
		if (detect_death(philo))
			return (NULL);
		mutex_print(philo, "is thinking\n");
	}
	return (NULL);
}
