/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:16:37 by lelanglo          #+#    #+#             */
/*   Updated: 2025/02/01 17:20:53 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	errors_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("args errors\n"), false);
	if (ft_atoi(argv[1]) > 200)
		return (printf("too many philosophers\n"), false);
	while (argv[i])
	{
		if (!ft_isdigit_str(argv[i]))
			return (printf("The parameters should be only positive numbers\n"),
				false);
		if (ft_atoi(argv[i]) > INT_MAX)
			return (printf("The paramters must be an integers\n"), false);
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (printf("The program should have at least one philosophers\n"),
			false);
	return (true);
}
