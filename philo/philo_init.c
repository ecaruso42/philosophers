/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:41:41 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/31 16:54:53 by ecaruso          ###   ########.fr       */
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

int	init_philo(t_env *env, int i)
{
	env->table[i].id = i;
	env->table[i].is_alive = 1;
	env->table[i].is_eating = 0;
	env->table[i].eat_count = 0;
	env->table[i].env = env;
	if (i == env->number_of_philosophers - 1)
		env->table[i].next_fork = 0;
	else
		env->table[i].next_fork = i + 1;
	if (pthread_mutex_init(&env->table[i].fork, NULL))
		return (1);
	return (0);
}

int	init(t_env *env, int argc, char **argv)
{
	int	i;

	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->start_time = get_time();
	if (argc == 6)
		env->max_eat = ft_atoi(argv[5]);
	else
		env->max_eat = -1;
	env->table = (t_philo *)malloc(sizeof(t_philo)
			* env->number_of_philosophers);
	if (pthread_mutex_init(&env->lock, NULL))
		return (1);
	i = 0;
	while (i < env->number_of_philosophers)
	{
		if (init_philo(env, i))
			return (1);
		i++;
	}
	return (0);
}
