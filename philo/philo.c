/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c2h6 <c2h6@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:50:06 by esafar            #+#    #+#             */
/*   Updated: 2022/07/27 10:02:16 by c2h6             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, ac, av) == 0)
			return (-1);
		if (init_philo(&data) == -1)
			return (-1);
		if (start(&data) == -1)
			return (-1);
		end(&data);
	}
	else
		printf("Error: Wrong amount of arguments.");
	return (0);
}
