/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:09:11 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/31 13:14:26 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_philosopher *philo)
{
	bool	game_over;

	pthread_mutex_lock(&philo->data->game_mutex);
	game_over = philo->data->game_over;
	pthread_mutex_unlock(&philo->data->game_mutex);
	return (game_over);
}
