/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c2h6 <c2h6@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:44:38 by esafar            #+#    #+#             */
/*   Updated: 2022/07/27 10:32:06 by c2h6             ###   ########.fr       */
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
# include <limits.h>

# define malloc(...) NULL //in order to test malloc fails

typedef struct s_data
{
	long int		start_time;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	bool			is_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philo_lst;
}				t_data;

typedef struct s_philo
{
	int					id;
	int					nb_meal;
	long int			last_meal;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*forks;
}				t_philo;

/*--------Parsing---------*/
int		parsing(t_data *data, int ac, char **av);
int		check_errors(int ac, char **av);
int		check_if_digit(int ac, char **av);
int		check_if_int_are_valid(int ac, char **av);

/*--------Initialize_philosophers---------*/
int		init_philo(t_data *data);

/*--------Start_simulation---------*/
int		start(t_data *data);
int		start_even_group(t_philo *philo_lst, int nb_philo);
int		start_odd_group(t_philo *philo_lst, int nb_philo);

/*--------Routine---------*/
void	*routine(void *arg);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	one_philo_eat(t_philo *philo);
void	eat_while_philo_need(t_philo *philo);
int		is_alive(t_philo *philo);

/*--------Print---------*/
long	int	display(t_philo *philo, char *str);

/*--------Forks---------*/
void	lock_forks(t_philo *philo, t_data *data);
void	unlock_forks(t_philo *philo, t_data *data);

/*--------Time_functions---------*/
long	int	get_time(void);
void	handmade_usleep(long int timetosleep);

/*--------End_simulation---------*/
void	end(t_data *data);
void	kill_philo(t_data *data, long int actual_time, int i);
void	check_philo_death(t_data *data);
int		endofmeal(t_data *data);
void	check_philo_death_n_meals(t_data *data);

/*--------Utils---------*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(char const *str);

#endif
