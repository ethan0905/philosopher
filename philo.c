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
	data->is_dead = false;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (1);
}

long int	get_time()
{
	long int	timestamp;
	struct timeval time;

	timestamp = 0;
	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	// printf("timestamp : %ld\n", timestamp);
	return (timestamp);
}
/*---------------------PB AVEC LE MUTEX DU DISPLAY-------------------*/
long int	display(t_philo *philo, char *str)
{
	long int	actual_time;

	actual_time = get_time();
	if (is_alive(philo) == 0)
		return (0);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld ms : philo %d %s\n", (actual_time - philo->data->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
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
	// if (is_alive(philo) == 0)
	// 	return ;
	display(philo, "took left fork");
	display(philo, "took right fork");
	pthread_mutex_lock(&philo->data->meal_mutex);
	actual_time = display(philo, "is eating");
	philo->last_meal = actual_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	// philo->last_meal = display(philo, "is eating");
	handmade_usleep(philo->data->time_to_eat);
	unlock_forks(philo, philo->data);
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

// bool	is_dead(t_philo *philo)
// {
// 	// if (philo->data->is_end == true)
// 	// 	return (true);
// 	if (get_time() - philo->last_meal >= philo->data->time_to_eat)
// 		return (true);
// 	return (false);
// }

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}

void    *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (is_alive(philo) == 1)
	{		
		// if (is_alive(philo) == 1)
		// 	return (0);
		eat(philo);
		// if (is_alive(philo) == 1)
		// 	return (0);
		sleep_and_think(philo);
		// if (is_alive(philo) == 1)
		// 	return (0);
	}
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
		// printf("start->time : %ld\n", data->start_time);
	while (i < data->nb_of_philo)
	{
		data->philo_lst[i].id = i + 1;
		data->philo_lst[i].data = data;
		data->philo_lst[i].forks = forks;
		data->philo_lst[i].last_meal = get_time();
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
	check_philo_death(data);
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
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	return ;
}

// long int	update_time(t_data *data, long int actual_time, int i)
// {
// 	long int	last_meal;
	
// 	pthread_mutex_lock(&data->meal_mutex);
// 	// printf("last meal = %ld\n", data->philo_lst[i].last_meal);
// 	last_meal = actual_time - data->philo_lst[i].last_meal;
// 	pthread_mutex_unlock(&data->meal_mutex);
// 	return (last_meal);
// }

void	kill_philo(t_data *data, long int actual_time, int i)
{
	pthread_mutex_lock(&data->death_mutex);
	data->is_dead = true;
	data->finished = true;
	pthread_mutex_unlock(&data->death_mutex);
	printf("%ld ms : philo %d died\n", (actual_time - data->start_time), data->philo_lst[i].id);
}

void	check_philo_death(t_data *data)
{
	int	i;
	long int actual_time;
	// long int last_meal_time;

	// usleep(30000);
	i = 0;
	while (1)
	{
		actual_time = get_time() - 0;
		// last_meal_time = update_time(data, actual_time, i);
		// if (data->philo_lst[i].last_meal/*last_meal_time*/ + data->time_to_die < actual_time)
		// printf("[last meal %ld + time to die : %d] > actual time  : %d", last_meal_time, data->time_to_die);
		// printf("actualtime = %ld || philolst[i].lastmeal = %ld || l'unmoinsl'autre = %ld || timetodie = %d\n", actual_time, data->philo_lst[i].last_meal, (actual_time - data->philo_lst[i].last_meal), data->time_to_die);
		pthread_mutex_lock(&data->meal_mutex);
		// printf("philo[i].last_meal %ld\n", data->philo_lst[i].last_meal);
		if ((actual_time - data->philo_lst[i].last_meal) >= (long int)data->time_to_die)
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
		// check_philo_death(&data);
		end(&data);
	}
	return (0);
}