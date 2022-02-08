/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:21:56 by esafar            #+#    #+#             */
/*   Updated: 2022/02/07 17:55:12 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_even_group(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, \
		&routine, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

int	start_odd_group(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, \
		&routine, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

int	start(t_data *data)
{
	data->start_time = get_time();
	if (start_even_group(data->philo_lst, data->nb_of_philo))
		return (-1);
	usleep(100);
	if (start_odd_group(data->philo_lst, data->nb_of_philo))
		return (-1);
	if (data->nb_of_philo != 1 && data->nb_time_must_eat > 0)
		check_philo_death_n_meals(data);
	else
		check_philo_death(data);
	return (1);
}
