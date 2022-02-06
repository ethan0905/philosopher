/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:27:27 by esafar            #+#    #+#             */
/*   Updated: 2022/02/04 14:27:28 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/philo.h"

void	init_philo(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	data->philo_lst = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo_lst || !forks)
		return ;
	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo_lst[i].id = i + 1;
		data->philo_lst[i].nb_meal = data->nb_time_must_eat;
		data->philo_lst[i].data = data;
		data->philo_lst[i].forks = forks;
		data->philo_lst[i].last_meal = get_time();
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
