/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:18:13 by esafar            #+#    #+#             */
/*   Updated: 2022/02/07 17:53:40 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	long int	actual_time;

	lock_forks(philo, philo->data);
	display(philo, "has taken a fork");
	display(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_mutex);
	actual_time = display(philo, "is eating");
	philo->last_meal = actual_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	handmade_usleep(philo->data->time_to_eat);
	unlock_forks(philo, philo->data);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->nb_meal > 0)
		philo->nb_meal--;
	pthread_mutex_unlock(&philo->data->meal_mutex);
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
	usleep(((philo->data->time_to_die - (philo->data->time_to_eat \
	+ philo->data->time_to_sleep)) / 2) * 1000);
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

void	*routine(void *arg)
{
	t_philo	*philo;

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
