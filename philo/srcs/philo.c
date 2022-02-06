/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:50:06 by esafar            #+#    #+#             */
/*   Updated: 2022/01/26 15:51:23 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, ac, av) == 0)
			return (-1);
		init_philo(&data);
		if (start(&data) == -1)
			return (-1);
		end(&data);
	}
	else
		printf("Error: Wrong amount of arguments.");
	return (0);
}
