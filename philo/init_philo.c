/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c2h6 <c2h6@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:27:27 by esafar            #+#    #+#             */
/*   Updated: 2022/07/27 10:01:14 by c2h6             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!forks)
	{
		printf("TEST MALLOC ERROR\n");
		return (-1);
	}
	data->philo_lst = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo_lst)
	{
		free(forks);
		return (-1);
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo_lst[i].id = i + 1;
		data->philo_lst[i].nb_meal = data->nb_time_must_eat;
		data->philo_lst[i].data = data;
		data->philo_lst[i].forks = forks;
		data->philo_lst[i].last_meal = get_time();
		pthread_mutex_init(&data->philo_lst[i].forks[i], NULL);
		i++;
	}
	data->nb_time_must_eat = data->nb_of_philo;
	return (1);
}
