/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:46:46 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/06 09:33:43 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 7 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

bool	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	unlock_fork(pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}
