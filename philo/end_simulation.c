/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:23:19 by esafar            #+#    #+#             */
/*   Updated: 2022/02/07 17:56:39 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo_lst[i].thread, NULL);
		++i;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->philo_lst[i].forks[i]);
		++i;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philo_lst->forks);
	free(data->philo_lst);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	return ;
}

void	kill_philo(t_data *data, long int actual_time, int i)
{
	pthread_mutex_lock(&data->death_mutex);
	data->is_dead = true;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if (data->nb_of_philo > 1)
		printf("%ld ms : philo %d died\n", (actual_time - \
	data->start_time), data->philo_lst[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}

void	check_philo_death(t_data *data)
{
	int			i;
	long int	actual_time;

	i = 0;
	while (1)
	{
		actual_time = get_time();
		pthread_mutex_lock(&data->meal_mutex);
		if ((actual_time - data->philo_lst[i].last_meal) >= \
		(long int)data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			kill_philo(data, actual_time, i);
			return ;
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
		if (i == (data->nb_of_philo - 1))
			i = 0;
		usleep(10);
	}
}

int	endofmeal(t_data *data)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (data->nb_time_must_eat > 0)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

void	check_time_of_death(struct s_philo *philo)
{
	long int actual_time;

	actual_time = get_time();
	pthread_mutex_lock(&philo->data->meal_mutex);
	if ((actual_time - philo->last_meal) >= (long int)philo->data->time_to_die)
	{
		kill_philo(philo->data, actual_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	check_philo_death_n_meals(t_data *data)
{
	int			i;
	long int	actual_time;

	i = 0;
	while (1)
	{
		actual_time = get_time();
		pthread_mutex_lock(&data->meal_mutex);
		// printf("NB_OF_TIME_MUST EAT: [%d] - [%d]\n", data->nb_time_must_eat, data->philo_lst[i].nb_meal);
		if (data->nb_time_must_eat == 0)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->meal_mutex);
		check_time_of_death(&(data->philo_lst[i]));
		if (data->is_dead == true)
			return ;
		i++;
		if (i == (data->nb_of_philo - 1))
			i = 0;
		usleep(100);
	}
}
