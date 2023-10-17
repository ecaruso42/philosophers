/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:24:48 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/17 21:50:31 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

struct	s_env;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				is_alive;
	int				is_eating;
	int				eat_count;
	pthread_mutex_t	*fork;
	struct s_env	*env;
}t_philo;

typedef struct	s_env
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_mutex_t	lock;
	t_philo			*table;
}t_env;

int	check_input(char **argv);
int	init(t_env *env, int argc, char **argv);
int	ft_atoi(const char *str);

#endif