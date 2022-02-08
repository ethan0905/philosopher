/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:24:52 by esafar            #+#    #+#             */
/*   Updated: 2022/02/07 17:55:37 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	display(t_philo *philo, char *str)
{
	long int	actual_time;

	actual_time = get_time();
	if (is_alive(philo) == 0)
		return (0);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld ms : philo %d %s\n", (actual_time - \
	philo->data->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (actual_time);
}
