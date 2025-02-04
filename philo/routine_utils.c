/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:19:26 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/04 10:22:21 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	take_forks(t_philosopher *philo,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (detect_death(philo))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	mutex_print(philo, "has taken a fork\n");
	pthread_mutex_lock(second);
	if (detect_death(philo))
	{
		unlock_fork(philo);
		return (0);
	}
	mutex_print(philo, "has taken a fork\n");
	return (1);
}

void	eat_meal(t_philosopher *philo)
{
	if (detect_death(philo))
	{
		unlock_fork(philo);
		return ;
	}
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
