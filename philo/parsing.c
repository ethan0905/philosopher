/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:19:48 by esafar            #+#    #+#             */
/*   Updated: 2022/02/07 17:54:34 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("Error: use only digit caracters.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_if_int_are_valid(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) > INT_MAX || ft_strlen(av[i]) > 11)
		{
			printf("Error: int overflow.\n");
			return (0);
		}
		if (ft_atoi(av[i]) < 1)
		{
			printf("Error: invalid amount of philosophers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_errors(int ac, char **av)
{
	if (check_if_digit(ac, av) == 0)
		return (0);
	if (check_if_int_are_valid(ac, av) == 0)
		return (0);
	if (ac == 6 && ft_atoi(av[5]) < 1)
	{
		printf("Error: <number of time each philosopher \
		must eat> must be > 0.\n");
		return (0);
	}
	return (1);
}

int	parsing(t_data *data, int ac, char **av)
{
	if (check_errors(ac, av) == 0)
		return (0);
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_time_must_eat = ft_atoi(av[5]);
	else if (ac == 5)
		data->nb_time_must_eat = 0;
	data->is_dead = false;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (1);
}
