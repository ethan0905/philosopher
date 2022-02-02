/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:44:38 by esafar            #+#    #+#             */
/*   Updated: 2021/12/27 18:44:42 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long int	start_time;
	int		nb_of_philo;
	int 	time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_time_must_eat;
	bool	is_dead;
	bool	finished;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philo_lst;
}			t_data;

typedef struct s_philo
{
	int	id;
	long int last_meal;
	pthread_t	thread;
	t_data	*data;
	pthread_mutex_t	*forks;
}           t_philo;

void	check_philo_death(t_data *data);
int	is_alive(t_philo *philo);

#endif
