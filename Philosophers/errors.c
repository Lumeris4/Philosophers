/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:16:37 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/28 10:29:51 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	errors_check(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("args errors\n"),false);
	while (argv[i])
	{
		if (!ft_isdigit_str(argv[i++]))
			return (printf("The parameters should be only positive numbers"),
					false);
	}
	if (ft_atoi(argv[1]) < 1)
		return (printf("The program should have at least one philosophers\n",
				false));
	return (true);
}
