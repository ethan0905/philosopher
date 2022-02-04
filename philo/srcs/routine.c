/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:18:13 by esafar            #+#    #+#             */
/*   Updated: 2022/02/04 14:18:14 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/philo.h"

void	eat(t_philo *philo)
{
	long int	actual_time;

	lock_forks(philo, philo->data);
	display(philo, "took left fork");
	display(philo, "took right fork");
	pthread_mutex_lock(&philo->data->meal_mutex);
	actual_time = display(philo, "is eating");
	philo->last_meal = actual_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	handmade_usleep(philo->data->time_to_eat);
	unlock_forks(philo, philo->data);
	if (philo->nb_meal > 0)
		philo->nb_meal--;
}

void	sleep_and_think(t_philo *philo)
{
	if (is_alive(philo) == 0)
		return ;
	display(philo, "is sleeping");
	handmade_usleep(philo->data->time_to_sleep);
	if (is_alive(philo) == 0)
		return ;
	display(philo, "is thinking");
	usleep(100);
}

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}

// void	eat_while_philo_need(t_philo *philo)
// {
// 	while (is_alive(philo) == 1 && philo->nb_meal > 0)
// 	{		
// 		eat(philo);
// 		if (philo->nb_meal > 0)
// 			sleep_and_think(philo);
// 	}
// 	pthread_mutex_lock(&philo->data->meal_mutex);
// 	philo->data->nb_time_must_eat--;
// 	pthread_mutex_unlock(&philo->data->meal_mutex);
// }

// void	one_philo_eat(t_philo *philo)
// {
// 	display(philo, "has taken left fork");
// 	usleep(philo->data->time_to_die * 1000);
// 	printf("%ld ms : philo %d died\n", (get_time() - philo->data->start_time), philo->id);
// }

void    *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_of_philo == 1)
	{
		one_philo_eat(philo);
		return (0);
	}
	if (philo->nb_meal == 0)
	{
		while (is_alive(philo) == 1)
		{		
			eat(philo);
			sleep_and_think(philo);
		}
		return (0);
	}
	else
	{
		eat_while_philo_need(philo);
		return (0);
	}
}
