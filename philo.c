/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:50:06 by esafar            #+#    #+#             */
/*   Updated: 2022/01/26 15:51:23 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*----------faire tous les checks d'erreur------------*/
int parsing(t_data *data, int ac, char **av)
{
	data->nb_of_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->nb_time_must_eat = atoi(av[5]);
	else if (ac == 5)
		data->nb_time_must_eat = -1;
	data->finished = false;
	pthread_mutex_init(&data->mutex, NULL);
	return (1);
}

long int	get_time()
{
	long int	timestamp;
	struct timeval time;

	timestamp = 0;
	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}
/*---------------------PB AVEC LE MUTEX DU DISPLAY-------------------*/
long int	display(t_philo *philo, char *str)
{
	long int	actual_time;

	actual_time = get_time();
	// pthread_mutex_lock(&philo->data->mutex);
	printf("%ld ms : philo %d %s\n", (actual_time - philo->data->start_time), philo->id, str);
	// pthread_mutex_unlock(&philo->data->mutex);
	return (actual_time);
}

void	lock_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id % data->nb_of_philo]);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->forks[philo->id % data->nb_of_philo]);
	}
}

void	unlock_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id % data->nb_of_philo]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id % data->nb_of_philo]);
	}
}

void	handmade_usleep(long int timetosleep)
{
	long int start;
	long int actual_time;
	long int end;

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

void	eat(t_philo *philo)
{
	long int	actual_time;

	lock_forks(philo, philo->data);
	display(philo, "took left fork");
	display(philo, "took right fork");
	actual_time = display(philo, "is eating");
	philo->last_meal = actual_time;
	handmade_usleep(philo->data->time_to_eat);
	unlock_forks(philo, philo->data);
}

void	sleeep(t_philo *philo)
{
	display(philo, "is sleeping");
	handmade_usleep(philo->data->time_to_sleep);
}

void    *routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	pthread_mutex_lock(&philo.data->mutex);
	eat(&philo);
	sleeep(&philo);
	pthread_mutex_unlock(&philo.data->mutex);
	return (0);
}

void    init_philo(t_data *data)
{
	int i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	data->philo_lst = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo_lst || !forks)
		return ;
	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo_lst[i].id = i + 1;
		data->philo_lst[i].data = data;
		data->philo_lst[i].forks = forks;
		data->philo_lst[i].last_meal = 0;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	start_even_group(t_philo *philo_lst, int nb_philo)
{
	int i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, &routine, &philo_lst[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

int start_odd_group(t_philo *philo_lst, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, &routine, &philo_lst[i]) != 0)
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
	return(1);
}

void	end(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo_lst[i].thread, NULL);
		pthread_mutex_destroy(&data->philo_lst[i].forks[i]);
		i++;
	}
	free(data->philo_lst->forks);
	free(data->philo_lst);
	pthread_mutex_destroy(&data->mutex);
	return ;
}


int main(int ac, char **av)
{
	t_data      data;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, ac, av) == -1)
			return (-1);
		init_philo(&data);
		if (start(&data) == -1)
			return (-1);
		end(&data);
	}
	return (0);
}