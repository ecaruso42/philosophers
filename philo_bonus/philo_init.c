/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:41:41 by ecaruso           #+#    #+#             */
/*   Updated: 2023/11/07 19:16:56 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_usleep(int ms)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < (u_int64_t)ms)
		usleep(ms / 10);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / (u_int64_t)1000));
}

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				printf("ERROR:\nInput is not valid\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_philo(t_env *env)
{
	env->philo.id = 0;
	env->philo.is_alive = 1;
	env->philo.is_eating = 0;
	env->philo.eat_count = 0;
	env->philo.env = env;
}

int	init(t_env *env, int argc, char **argv)
{
	sem_unlink("semlock");
	sem_unlink("semdead");
	sem_unlink("semeat");
	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->start_time = get_time();
	if (argc == 6)
		env->max_eat = ft_atoi(argv[5]);
	else
		env->max_eat = -1;
	env->sem_lock = sem_open("semlock", O_CREAT, 0666, env->number_of_philosophers);
	env->sem_dead = sem_open("semdead", O_CREAT, 0666, 1);
	env->sem_eat = sem_open("semeat", O_CREAT, 0666, 1);
	init_philo(env);
	return (0);
}
