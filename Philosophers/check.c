/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:09:11 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/01 15:37:39 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_end(t_philosopher *philo)
{
	bool	game_over;

	pthread_mutex_lock(&philo->data->game_mutex);
	game_over = philo->data->game_over;
	pthread_mutex_unlock(&philo->data->game_mutex);
	return (game_over);
}

bool	detect_death(t_philosopher *philo)
{
	long long	current_time;

	current_time = get_time_in_ms();
	pthread_mutex_lock(&philo->data->game_mutex);
	if (philo->data->game_over)
	{
		pthread_mutex_unlock(&philo->data->game_mutex);
		return (true);
	}
	if (current_time - philo->last_meal >= philo->data->time_to_die)
	{
		printf("%lld %d died\n", current_time, philo->id);
		philo->data->game_over = true;
		pthread_mutex_unlock(&philo->data->game_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->game_mutex);
	return (false);
}
