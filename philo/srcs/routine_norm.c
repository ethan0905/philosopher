/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:25:57 by esafar            #+#    #+#             */
/*   Updated: 2022/02/04 15:26:04 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/philo.h"

void	eat_while_philo_need(t_philo *philo)
{
	while (is_alive(philo) == 1 && philo->nb_meal > 0)
	{		
		eat(philo);
		if (philo->nb_meal > 0)
			sleep_and_think(philo);
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->nb_time_must_eat--;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	one_philo_eat(t_philo *philo)
{
	display(philo, "has taken left fork");
	pthread_mutex_lock(&philo->data->print_mutex);
	usleep(philo->data->time_to_die * 1000);
	printf("%ld ms : philo %d died\n", (get_time() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
