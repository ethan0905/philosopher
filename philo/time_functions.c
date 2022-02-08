/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:25:53 by esafar            #+#    #+#             */
/*   Updated: 2022/02/07 17:52:49 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	long int		timestamp;
	struct timeval	time;

	timestamp = 0;
	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

void	handmade_usleep(long int timetosleep)
{
	long int	start;
	long int	actual_time;
	long int	end;

	start = get_time();
	end = start + timetosleep;
	while (1)
	{
		actual_time = get_time();
		if (actual_time >= end)
			break ;
		usleep(100);
	}
}
