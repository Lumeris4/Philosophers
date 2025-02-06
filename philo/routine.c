/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:06:03 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/06 10:31:04 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philosopher *philo, pthread_mutex_t *first,
	pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (detect_death(philo))
		return (pthread_mutex_unlock(first), 0);
	mutex_print(philo, "has taken a fork\n");
	pthread_mutex_lock(second);
	if (detect_death(philo))
		return (unlock_fork(first, second), 0);
	mutex_print(philo, "has taken a fork\n");
	return (1);
}

static void	philo_perform_eating(t_philosopher *philo)
{
	long	start_time;

	mutex_print(philo, "is eating\n");
	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < philo->data->time_to_eat)
	{
		if (detect_death(philo))
			return ;
		usleep(1000);
	}
	if (!detect_death(philo))
	{
		philo->meals_eaten++;
		philo->last_meal = get_time_in_ms();
	}
}

static void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (!take_forks(philo, first_fork, second_fork))
		return ;
	philo_perform_eating(philo);
	unlock_fork(first_fork, second_fork);
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
	long long		start_time;

	philo = (t_philosopher *)arg;
	if (philo->data->num_philos == 1)
		return (one_philo(philo), NULL);
	while (philo->meals_eaten != philo->data->number_time)
	{
		if (detect_death(philo))
			return (NULL);
		if (philo->id % 2 == 0)
			usleep(1000);
		philo_eat(philo);
		mutex_print(philo, "is sleeping\n");
		start_time = get_time_in_ms();
		while (get_time_in_ms() - start_time < philo->data->time_to_eat)
		{
			if (detect_death(philo))
				return (NULL);
			usleep(1000);
		}
		mutex_print(philo, "is thinking\n");
		usleep(1000);
	}
	return (NULL);
}
